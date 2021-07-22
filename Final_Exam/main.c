#include <avr/io.h>
#include <stdio.h>

#include "iesusart.h"
#include "iesmotors.h"
#include "line_tracing.h"





void robot_init() {

    /*Initialize USART port*/
    USART_init(UBRR_SETTING);

    /*Initialze analog pins and configure ADC pins aswell as motors*/    
    sensor_init();

    /*Initialize motors*/
    motors_init();

    USART_print("SETUP FINISHED");
}



int main(void){

    robot_init();

    motors_steering();

    return 0;


}