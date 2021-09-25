#include <Arduino.h>
#include <Servo.h>

Servo myservoX;  // create servo object to control a servo's X rotation
Servo myservoY;  // create servo object to control a servo's Y rotation

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int posX = 0;    // variable to store the servo position along X axis
int posY = 0;    // variable to store the servo position along Y axis

int sensorValue = 0;        // value read from the pot

bool up = true;

void setup() {
  myservoX.attach(9);  // attaches the servo on pin 9 to the servo object
  myservoY.attach(10);  // attaches the servo on pin 10 to the servo object

Serial.begin(9600);
}

void loop() {
    for (posX = 0; posX <= 180; posX += 5) {  // goes from 0 degrees to 180 degrees X axis
        myservoX.write(posX);                 // tell servo to go to position in variable 'posX'
        delay(150);                            // waits 15ms for the servo to reach the position
        sensorValue = analogRead(analogInPin);
        Serial.print(posX); Serial.print(", ");
        Serial.println(sensorValue);
        
        for (posY = 0; posY <= 180; posY += 5) {  // goes from 0 degrees to 180 degrees Y axis
            myservoY.write(posY);                 // tell servo to go to position in variable 'posY'
            delay(150);                            // waits 15ms for the servo to reach the position
            
            sensorValue = analogRead(analogInPin);
            Serial.print(posY); Serial.print(", ");
            Serial.println(sensorValue);
        }
        myservoY.write(0);

    }
    myservoX.write(0);
}
