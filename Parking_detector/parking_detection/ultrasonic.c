#include "ultrasonic.h"
#include <avr/io.h>
#include <util/delay.h>

void timer1_init() {
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << CS11); // Prescaler 8
    TCNT1 = 0;
}

void ultrasonic_init(UltrasonicSensor sensor) {
    timer1_init();

    DDRD |= (1 << sensor.trig_pin);    // TRIG as output
    DDRD &= ~(1 << sensor.echo_pin);   // ECHO as input
}

float ultrasonic_read_cm(UltrasonicSensor sensor) {
    // Send 10us trigger pulse
    PORTD &= ~(1 << sensor.trig_pin);
    _delay_us(2);
    PORTD |= (1 << sensor.trig_pin);
    _delay_us(10);
    PORTD &= ~(1 << sensor.trig_pin);

    // Wait for echo to go high
    while (!(PIND & (1 << sensor.echo_pin)));

    TCNT1 = 0;

    // Wait while echo is high
    while ((PIND & (1 << sensor.echo_pin))) {
        if (TCNT1 > 60000) {
            return -1.0; // timeout
        }
    }

    uint16_t count = TCNT1;
    TCNT1 = 0;

    float distance = (float)count * 8.0 * 34300.0 / (16000000.0 * 2.0);
    distance = distance * 1.0589 + 0.016;

    return distance;
}
