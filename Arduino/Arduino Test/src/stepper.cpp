//Includes the Arduino Stepper Library
#include <Arduino.h>
#include <Stepper.h>
#include <Servo.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2100;

Servo servo1;
Servo servo2;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 4, 5, 6, 7);

void setup() {
	servo1.attach(9);
	servo2.attach(10);

	servo1.write(0);
	servo2.write(0);
}

void loop() {
	servo1.write(10);
	servo2.write(170);
	// Rotate CW slowly at 5 RPM
    myStepper.setSpeed(5);
    myStepper.step(stepsPerRevolution/8);
	servo1.write(70);
	servo2.write(100);
	delay(1000);

}