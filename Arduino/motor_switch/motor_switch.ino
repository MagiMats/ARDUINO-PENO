# include <Arduino.h>

#define enPin 2
#define stepPin 3
#define dirPin 4

void setup() {
    pinMode(45, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(enPin,OUTPUT); 
    pinMode(stepPin,OUTPUT); 
    pinMode(dirPin,OUTPUT);
}

void loop() {
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
    delay(1000); // One second delay
}