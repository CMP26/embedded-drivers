extern "C" {
  #include "ultrasonic.h"
  #include "parking_detector.h"
}

#define TRIG_LEFT_PIN PD4
#define ECHO_LEFT_PIN PD3
#define TRIG_RIGHT_PIN PD2
#define ECHO_RIGHT_PIN PD1

UltrasonicSensor leftSensor = {TRIG_LEFT_PIN, ECHO_LEFT_PIN};  // Define TRIG and ECHO pins for left sensor
UltrasonicSensor rightSensor = {TRIG_RIGHT_PIN, ECHO_RIGHT_PIN};  // Define TRIG and ECHO pins for right sensor

void setup() {
    ultrasonic_init(leftSensor);
    ultrasonic_init(rightSensor);

    Serial.begin(9600);
}

void loop() {
    float distanceLeft = ultrasonic_read_cm(leftSensor);
    float distanceRight = ultrasonic_read_cm(rightSensor);

    Serial.print("Left Sensor Distance: ");
    Serial.print(distanceLeft);
    Serial.println(" cm");

    Serial.print("Right Sensor Distance: ");
    Serial.print(distanceRight);
    Serial.println(" cm");

    unsigned long currentTime = millis();  // Example current time
    float carSpeed = 1000.0;  //in cm/s

    int parkFound = updateParkingDetection(distanceLeft, distanceRight, currentTime, carSpeed);

    if (parkFound) {
        if(isParkingSpotFoundLeft()){
            Serial.println("Parking Spot Found Left!");
        }
        else if(isParkingSpotFoundRight()){
            Serial.println("Parking Spot Found Right!");
        }
    } else {
        Serial.println("No Parking Spot Found");
    }

    delay(500);
}