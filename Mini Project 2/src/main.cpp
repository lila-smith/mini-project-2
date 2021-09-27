#include <Arduino.h>
#include <Servo.h>

Servo myservoX;  // create servo object to control a servo's X rotation
Servo myservoY;  // create servo object to control a servo's Y rotation

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int servoXPin = 9; // Sets pin num for pan servo
const int servoYPin = 10; // Sets pin num for tilt servo

const int posLimitsX[] = {0, 180, 5}; // pan servo: starting angle, ending angle, angle increment
const int posLimitsY[] = {0, 180, 5}; // tilt servo: starting angle, ending angle, angle increment


int posX = 0;    // variable to store the servo position along X axis
int posY = 0;    // variable to store the servo position along Y axis

int sensorValue = 0;    // value read from the pot

void setup() {
  myservoX.attach(servoXPin);  
  myservoY.attach(servoYPin); 
  Serial.begin(9600);
}

void loop() {
    for (posX = posLimitsX[0]; posX <= posLimitsX[1]; posX += posLimitsX[2]) {  // goes from 0 degrees to 180 degrees X axis
        myservoX.write(posX);                 // tell servo to go to position in variable 'posX'
        delay(150);                           // waits 15ms for the servo to reach the position
        sensorValue = analogRead(analogInPin);
        
        for (posY = posLimitsY[0]; posY <= posLimitsY[1]; posY += posLimitsY[2]) {  // goes from 0 degrees to 180 degrees Y axis
            myservoY.write(posY);                 // tell servo to go to position in variable 'posY'
            delay(150);                            // waits 15ms for the servo to reach the position

            sensorValue = analogRead(analogInPin); 
            Serial.println((String) posX + ", " + posY + ", " + sensorValue); // prints data to be recorded with python script
        }
    }
}
