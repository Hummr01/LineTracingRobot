#include <avr/io.h>
#include <stdio.h>

#include "iesusart.h"
#include "iesmotors.h"
#include "iessensors.h"
#include "ieslights.h"

void robot_init()
{

    ///Initialize USART port
    USART_init(UBRR_SETTING);

    ///Initialze analog pins and configure ADC pins aswell as motors
    sensor_init();

    ///Initialize motors
    motors_init();

    ///INIT  LIGHTS
    light_init();

    USART_print("SETUP FINISHED!\n");
}

int main(void)
{

    robot_init();

    follow_line();

    return 0;
}
