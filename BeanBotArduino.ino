// Standard communication and setup, don't change.
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

String startsequence = "CMDS/";
String stopsequence = "/CMDEND/";

String startsequenceSetup = "SETUPB/";
String stopsequenceSetup = "/SETUPE/";

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// constants used throughout the code, (SERVOMIN/MAX to specific servo model (trail and error))
#define SERVO_FREQ 50
#define SERVOMIN  80 
#define SERVOMAX  409
#define STEPS 100

// Names for pins for inputs and outputs from sensors

// Runs once when opening code
void setup() {
  // Setup for the servo
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  
  
  pinMode(25, OUTPUT);
  digitalWrite(25,HIGH); 
  
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
  }
}


String checkwifi() {
  // Checks if something was sent to the Arduino over wifi, recieves and decodes it as well.
  String command = "";
    // Read input drom ESP32.
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
    dowhite(message.toInt());
  }
  else if (commando.equals("Red")){
    dored(message.toInt());
  }
  else if (commando.equals("Black")){
    doblack(message.toInt());
  }
  else {
    sendWifi("Command not recognized");
  }
}

void dowhite(int grams){
  Serial.println(grams);
  sendWifi("White");
}

void dored(int grams){
  Serial.println(grams);
  sendWifi("Red");
}

void doblack(int grams){
  Serial.println(grams);
  sendWifi("Black");
}

void fromMonitorToApp(String message){
  sendWifi("MonitorToApp/"+message);
}

void sendWifi(String message){
  // Send a message to ESP32 which then sends it to the app.
  Serial2.println(message);
}
