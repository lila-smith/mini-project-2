#include <Arduino.h>
#include <Servo.h>

Servo myservoX;  // create servo object to control a servo's X rotation
Servo myservoY;  // create servo object to control a servo's Y rotation

int posX = 0;    // variable to store the servo position along X axis
int posY = 0;    // variable to store the servo position along Y axis

bool up = true;

void setup() {
  myservoX.attach(9);  // attaches the servo on pin 9 to the servo object
  myservoY.attach(10);  // attaches the servo on pin 10 to the servo object
                       // CHECK THAT THIS IS THE CORRECT PIN NUMBER!!!
}

void loop() {
    for (posX = 0; posX <= 180; posX += 5) {  // goes from 0 degrees to 180 degrees X axis
        myservoX.write(posX);                 // tell servo to go to position in variable 'posX'
        delay(15);                            // waits 15ms for the servo to reach the position
       
        if(up == true){  // decides if servo needs to rotate up in the Y axis
            for (posY = 0; posY <= 180; posY += 5) {  // goes from 0 degrees to 180 degrees Y axis
                myservoY.write(posY);                 // tell servo to go to position in variable 'posY'
                delay(15);                            // waits 15ms for the servo to reach the position
            }
            up = !up;   //update up to false
        }
        if(up == false){ // decides if servo needs to rotate down in the Y axis
            for (posY = 180; posY >= 0; posY -= 5) {  // goes from 180 degrees to 0 degrees
                myservoY.write(posY);                 // tell servo to go to position in variable 'posY'
                delay(15);                            // waits 15ms for the servo to reach the position
            }
            up = !up;   // update up to true
        }
    }
    myservoX.write(0);
}
