// Here the main application code 

extern "C" {
    #include "motor.h"
}
extern "C" {
    #include "ultrasonic.h"
}

void setup()
{

    motor_init();
    ultrasonic_initializer();

}



void loop()
{

}
