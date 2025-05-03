// Motor A (LEFT side: M1 & M3)
#define ENA 6   // Must be PWM pin
#define IN1 8
#define IN2 7

// Motor B (RIGHT side: M2 & M4)
#define ENB 5  // Must be PWM pin
#define IN3 9
#define IN4 10

extern "C" {
  #include "ultrasonic.h"
  #include "parking_detector.h"
}

#include <avr/sleep.h>

void setup() {

  Serial.begin(9600);
  ultrasonic_init();
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}


void mv_fwd(){
  // Forward: LEFT motors forward, RIGHT motors forward
  digitalWrite(IN1, HIGH);  // Left forward
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);   // Right forward (reversed)
  digitalWrite(IN4, HIGH);

  analogWrite(ENB, 190);
  analogWrite(ENA, 80);
}

void stop(){
    // Stop
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void reverse(){
  
  // Reverse: LEFT motors backward, RIGHT motors backward
  digitalWrite(IN1, LOW);   // Left backward
  digitalWrite(IN2, HIGH);
  
  digitalWrite(IN3, HIGH);  // Right backward (reversed)
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

void park(){
  stop();
  delay(1000);

  reverse();
  delay(1700);

  // Final stop
  mv_fwd();
  delay(500);

  stop();
}

void loop() {
  // float distance = ultrasonic_read_cm();
  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println(" cm");
  // delay(500);

  // mv_fwd();

  // delay(2500);

  // // park();
  // // delay(10000);


  float obstacleDist = ultrasonic_read_cm();
  Serial.print("Distance : ");
  Serial.println(obstacleDist);
  unsigned long currentTime = millis();
  float speed_CM_S = 1000; // cm/s

  DetectionState state = SEARCHING_FIRST_OBSTACLE;
  state=updateParkingDetection(obstacleDist, currentTime, speed_CM_S);
  Serial.print("the current state: ");
  Serial.println(state);

  if (isParkingSpotFound()) {
    park();
    stop();
    Serial.println("park found");
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
  }
  else {
    mv_fwd();
    delay(10);
    stop();
    delay(20);
  }

}
