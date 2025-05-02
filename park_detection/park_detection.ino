extern "C" {
  #include "parking_detector.h"
  #include "ultrasonic.h"
}

void setup(){
    Serial.begin(9600);
}

void loop() {
    float obstacleDist = ultrasonic_read_cm();
    unsigned long currentTime = millis();
    float speed_CM_S = 10.0; // cm/s

    DetectionState state = SEARCHING_FIRST_OBSTACLE;
    state=updateParkingDetection(obstacleDist, currentTime, speed_CM_S);
    Serial.print("the current state: ");
    Serial.println(state);

    if (isParkingSpotFound()) {
        //stopCar();
        //parkCar();
        Serial.println("park found");
    }
  delay(500);
}
