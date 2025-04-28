#include "motor.h"


// Motor pins
#define MOTOR_IN1 PD5
#define MOTOR_IN2 PD6
#define MOTOR_ENA PD3

void motor_init(void) {
    // Set IN1, IN2, ENA as output
    DDRD |= (1 << MOTOR_IN1) | (1 << MOTOR_IN2) | (1 << MOTOR_ENA);
    TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B |= (1 << CS21);  // Prescaler 8
}

void motor_forward(uint8_t speed) {
    PORTD |= (1 << MOTOR_IN1);
    PORTD &= ~(1 << MOTOR_IN2);

    OCR2B = speed;
}

void motor_backward(uint8_t speed) {
    PORTD &= ~(1 << MOTOR_IN1);
    PORTD |= (1 << MOTOR_IN2);

    OCR2B = speed;
}

void motor_stop(void) {
    PORTD &= ~((1 << MOTOR_IN1) | (1 << MOTOR_IN2));
    OCR2B = 0;
}
