#include <avr/io.h>
#include "iessensors.h"
#include "iesusart.h"
#include <stdio.h>


/**
 * @brief Shift method for the 4-bit shift register to place bit to right
 * register output
 * 
 * @param count number of times bit needs to be shifted.
 */
void shift(uint8_t count){
    for (uint8_t i = 0; i < count; i++){
        PORTD = (1 << PD4);
        PORTD = ~(1 << PD4);
    }
}



/**
 * @brief Handles sensor light to show which sensor is detecting line and
 * which is not.
 * 
 * @param state current linefollower state.
 */
void sensor_lights(enum lf_state state){

    static enum lf_state state = state;

    switch (state)
    {
    case all_three:
        PORTB = (1 << PB2);
        shift(3);
        PORTB = ~(1 << PB2);
        break;
        
    case mid:
        PORTB = (1 << PB2);
        shift(1);
        PORTB = ~(1 << PB2);
        shift(1);
        
    
    default:
        break;
    }  

}