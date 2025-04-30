#include "ultrasonic.h"
#include <avr/io.h>
#include <util/delay.h>

#define TRIG_PIN PB1  // Digital pin 9
#define ECHO_PIN PB0  // Digital pin 8

void timer1_init(){
  TCCR1A = 0; // Normal mode
  TCCR1B = 0;
  TCCR1B |= (1 << CS11); // Prescaler = 8 (2 MHz tick rate)
  TCNT1 = 0;
}
void ultrasonic_init(void) {
  timer1_init();
  DDRB |= (1 << TRIG_PIN);   // TRIG = output
  DDRB &= ~(1 << ECHO_PIN);  // ECHO = input
}

float ultrasonic_read_cm(void) {
  // Send 10us trigger
  PORTB &= ~(1 << TRIG_PIN);
  _delay_us(2);
  PORTB |= (1 << TRIG_PIN);
  _delay_us(10);
  PORTB &= ~(1 << TRIG_PIN);

  // Wait for echo to go high
  while (!(PINB & (1 << ECHO_PIN)));

  TCNT1 = 0;

  // Count how long it's high
  while ((PINB & (1 << ECHO_PIN))) {
    if (TCNT1 > 60000){
      return -1.0;
    } // timeout
  }

  uint16_t count = TCNT1;
  
  TCNT1=0;
  
  float distance = (float)count * 8.0 * 34300.0 / (16000000.0 * 2.0);  // Prescaler 8
  distance=distance* 1.0589+0.016;

  return distance;
}
