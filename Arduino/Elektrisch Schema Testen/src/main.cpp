#include <Arduino.h>
#include <LiquidCrystal_I2C.h> // Library for LCD

const int trigPin = 12;
const int echoPin = 11;
int analogpin = A10;
int sensor = 2;  
int state = LOW; 
#define enPin 2
#define stepPin 3
#define dirPin 4

int led = 13;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(analogpin, OUTPUT);
  pinMode(sensor, INPUT);

  pinMode(45, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(enPin,OUTPUT); 
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  pinMode(enPin,OUTPUT); 
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  lcd.init();
  lcd.backlight();
}

void motor() {
  for (int i; i<=255; i++) {
    analogWrite(analogpin, i);
  }
}

int read_distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  motor();

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  Serial.println(distance);
  return distance;
}

void read_motion() {
  int val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
}

void i2c() {
  int distance = read_distance();
  if (distance < 15) {
    digitalWrite(10, HIGH);
    digitalWrite(45, HIGH);
    delay(3000);
    digitalWrite(45, LOW);
    delay(3000);
    digitalWrite(10, LOW);
    delay(3000);

    for(int x = 0; x < 800; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(700);    // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(700); 
    }
  }
  else {
    
  }

  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print(distance);        // print message at (0, 0)
  delay(500);
}

void loop() {
  i2c();
}
