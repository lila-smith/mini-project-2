#include <Arduino.h>
#include <Servo.h>


Servo myservoX;  // create servo object to control a servo's X rotation
Servo myservoY;  // create servo object to control a servo's Y rotation

const uint8_t analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const uint8_t servoXPin = 9; // Sets pin num for pan servo
const uint8_t servoYPin = 10; // Sets pin num for tilt servo

const uint8_t posLimitsX[] = {0, 35, 1}; // pan servo: starting angle, ending angle, angle increment
const uint8_t posLimitsY[] = {75, 130, 1}; // tilt servo: starting angle, ending angle, angle increment


uint8_t posX = 0;    // variable to store the servo position along X axis
uint8_t posY = 0;    // variable to store the servo position along Y axis

int sensorValue = 0;    // value read from the pot
uint8_t outputValue = 0;    // value mapped to 255

const uint8_t numReadings = 5; // number of times to take a reading at each point
uint8_t tempReadings[numReadings]; // create array to store readings

int cmp_func(const void *num1, const void *num2) // used by qsort to sort the array
{
  return *(int*) num1 - *(int*) num2;
}

void setup() {
  myservoX.attach(servoXPin);  
  myservoY.attach(servoYPin); 
  Serial.begin(9600);
}

void loop() {
    delay(3000);
    Serial.println("Begin");
    delay(2000);
    for (posX = posLimitsX[0]; posX <= posLimitsX[1]; posX += posLimitsX[2]) { 
        myservoX.write(posX);                 // tell servo to go to position in variable 'posX'
        for (posY = posLimitsY[0]; posY <= posLimitsY[1]; posY += posLimitsY[2]) { 
            myservoY.write(posY);                 // tell servo to go to position in variable 'posY'
            delay(150);                            // waits 150ms for the servo to reach the position
            for (int i = 0; i < numReadings; i++) { // record numReadings datapoints
                tempReadings[i] = analogRead(analogInPin);
            }
            qsort(tempReadings, numReadings, sizeof(tempReadings[0]), cmp_func); // sort the array into ascending order
            sensorValue = tempReadings[(int) numReadings/2 - 1]; // take the median of values
            outputValue = map(sensorValue, 0, 1023, 0, 255); // map to 0-255
            if (outputValue > 30 && outputValue < 110) { // only send value if inside of bounds of IR sensor specs
                Serial.println((String) posX + ", " + posY + ", " + outputValue); // Serial to be recorded with python script   
            }
    
    }
    Serial.println("End");
}


/* // One servo version
Servo myservoY;  // create servo object to control a servo's Y rotation

const uint8_t analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const uint8_t servoYPin = 10; // Sets pin num for tilt servo

const uint8_t posLimitsY[] = {80, 140, 1}; // tilt servo: starting angle, ending angle, angle increment


uint8_t posY = 0;    // variable to store the servo position along Y axis

int sensorValue = 0;    // value read from the pot
uint8_t outputValue = 0;    // value mapped to 255

const uint8_t numReadings = 100; // number of times to take a reading at each point
uint8_t tempReadings[numReadings]; // create array to store readings

int cmp_func(const void *num1, const void *num2) // used by qsort to sort the array
{
  return *(int*) num1 - *(int*) num2;
}

void setup() {
  myservoY.attach(servoYPin); 
  Serial.begin(9600);
}

void loop() {
    delay(3000);
    Serial.println("Begin");
    for (posY = posLimitsY[0]; posY <= posLimitsY[1]; posY += posLimitsY[2]) { 
        myservoY.write(posY);                 // tell servo to go to position in variable 'posY'
        delay(150);                            // waits 150ms for the servo to reach the position
        for (int i = 0; i < numReadings; i++) { // record numReadings datapoints
            tempReadings[i] = analogRead(analogInPin);
        }
        qsort(tempReadings, numReadings, sizeof(tempReadings[0]), cmp_func); // sort the array into ascending order
        sensorValue = tempReadings[(int) numReadings/2 - 1]; // take the median of values
        outputValue = map(sensorValue, 0, 1023, 0, 255); // map to 0-255
        if (outputValue > 30 && outputValue < 110) { // only send value if inside of bounds of IR sensor specs
            Serial.println((String) posX + ", " + posY + ", " + outputValue); // Serial to be recorded with python script   
        }
    }
    Serial.println("End");
} */