// Here the main application code 

extern "C" {
    #include "motor.h"
}
extern "C" {
    #include "ultrasonic.h"
}

void setup()
{

    motor_initializer();
    ultrasonic_initializer();

}



void loop()
{

}