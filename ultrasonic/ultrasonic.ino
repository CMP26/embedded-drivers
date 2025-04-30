extern "C" {
  #include "ultrasonic.h"
}

void setup() {
  Serial.begin(9600);
  
  ultrasonic_init();
}

void loop() {
  float distance = ultrasonic_read_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
} 