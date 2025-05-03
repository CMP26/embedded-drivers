#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>

typedef struct {
    uint8_t trig_pin;
    uint8_t echo_pin;
} UltrasonicSensor;

void ultrasonic_init(UltrasonicSensor sensor);
float ultrasonic_read_cm(UltrasonicSensor sensor);

#endif
