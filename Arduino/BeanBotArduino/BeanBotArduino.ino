// Standard communication and setup, don't change.
#include <Wire.h>
#include <Servo.h>
#include "HX711?h"

String startsequence = "CMDS/";
String stopsequence = "/CMDEND/";

String startsequenceSetup = "SETUPB/";
String stopsequenceSetup = "/SETUPE/";

// defines stepper pins
#define enPin 2
#define stepPin 3
#define dirPin 4

// defines servo pins
Servo servo1;
int servoPin = 9;

// defines weigth sensor pins
#define DOUT  12
#define CLK  11
HX711 scale;
float calibration_factor = -910000.00; // CALIBRATE BEFORE USE!!!

// Runs once when opening code
void setup() {
  // Setup for the servo
  servo1.attach(servoPin);
  // Setup for stepper
  pinMode(enPin,OUTPUT); 
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  // Setup for weigth sensor
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  // Setup for Serial1 and Serial2
  Serial.begin(9600); // communication with serial monitor
  delay(100);
  Serial2.begin(115200); // communication with ESP32
}

void loop() {
  // Constantly checks if something was sent over wifi.
  String command = checkwifi(); // If the app sent something, command == True, else command == False
  // Do the command if something was sent.
  if (command.length()>0){
    Serial.println("Recieved command: " + command); // Print the command (debug)
    //Split the command in commando/parameters
    String commando = command.substring(0,command.indexOf('/'));
    String parameters = command.substring(command.indexOf('/')+1);
    Serial.println("Commando: "+commando);
    Serial.println("Parameters: "+parameters);
    doCommand(commando,parameters);
  }

  if(Serial.available()){ // Do this when something appears in the serial monitor.
    String message=Serial.readString(); // Make a string from whatever appeared in the serial monitor.
    fromMonitorToApp(message); // Send the string to the app.
    if(message == "stepper"){
      dowhite();
    }
    else if(message == "dc"){
      dored();      
    }
    else if(message == "servo"){
      doblack();
    }
  }
}

String checkwifi() {
  // Checks if something was sent to the Arduino over wifi, recieves and decodes it as well.
  String command = "";
    // Read input from ESP32.
    while (Serial2.available())
    {
      command = Serial2.readString();
    }
    // Remove start and stop strings from the command
    if (command.indexOf(startsequence)>0){
      command = command.substring(command.indexOf(startsequence)+startsequence.length());
      command = command.substring(0,command.indexOf(stopsequence));
    }
    // Is it a setup command?
    else if (command.indexOf(startsequenceSetup)>0){
      displayESP32Setup(command);
      command = "";
    }
    else {
      command = "";
    }
  return command;
}

void displayESP32Setup(String command){
  command = command.substring(command.indexOf(startsequenceSetup)+startsequenceSetup.length());
  command = command.substring(0,command.indexOf(stopsequenceSetup));
  Serial.println(command);
}

void doCommand(String commando, String message) {
  // Which command was sent?
  if (commando.equals("White")){
    sendWifi("White/");;
  }
  else if (commando.equals("Red")){
    sendWifi("Red/");
  }
  else if (commando.equals("Black")){
    sendWifi("Black/");
  }
  else {
    sendWifi("Command not recognized");
  }
}

void dowhite(){
  digitalWrite(enPin, LOW);
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 2000; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1500);    // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1500); 
  }
  delay(1000); // One second delay
  
  digitalWrite(dirPin,LOW); //Changes the rotations direction
  delay(1000);
}

void dored(){
    digitalWrite(10, HIGH);
    // set motor rotation    
    digitalWrite(45, HIGH);
    delay(3000);
    //    Change rotation with 1s pause first
    digitalWrite(10, LOW);
    delay(1000);
    
    digitalWrite(45, LOW);
    delay(3000);

    digitalWrite(10, LOW);
    delay(1000);
}

void doblack(){
  servo1.write(0);
  delay(1000);
  servo1.write(90);
  delay(1000);
  servo1.write(180);
  delay(1000);
}

void fromMonitorToApp(String message){
  sendWifi("MonitorToApp/"+message);
}

void sendWifi(String message){
  // Send a message to ESP32 which then sends it to the app.
  Serial2.println("Mass/"+message);
}