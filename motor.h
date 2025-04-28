#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include <avr/io.h>
#include <stdint.h>

void motor_init(void);
void motor_forward(uint8_t speed);
void motor_backward(uint8_t speed);
void motor_stop(void);

#endif