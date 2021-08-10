#include <avr/io.h>
#include "iessensors.h"
#include "iesusart.h"
#include "iessensor_lights.h"
#include <stdio.h>



void shift(uint8_t count){
    for (uint8_t i = 0; i < count; i++){
        PORTD = (1 << PD4);
        PORTD = ~(1 << PD4);
    }
}

/**
 * @brief Reset register.
 * 
 */
void reset() {
    PORTB = ~(1 << PB2);
    shift(3);

}

void blink() {
    PORTB ^= (1 << PB2);
    shift(3); 
}



/**
 * @brief Handles sensor light to show which sensor is detecting line and
 * which is not.
 * 
 * @param state current linefollower state.
 */
void sensor_lights(enum lf_state state){

    static enum lf_state prev_state = 0;

    if (state != prev_state) {
        
    


    switch (state){
    case all_three:
        prev_state = all_three;
        reset();
        PORTB = (1 << PB2);
        shift(3);
        PORTB = ~(1 << PB2);
        break;
    
    case left:
        prev_state =left;
        reset();
        PORTB = (1 << PB2);
        shift(1);
        PORTB = ~(1 << PB2);
        shift(2);
        break;

    case left_mid:
        prev_state = left_mid;
        reset();
        PORTB = (1 << PB2);
        shift(2);
        PORTB = ~(1 << PB2);
        shift(1);
        break;
          

    case mid:
        prev_state = mid;
        reset();
        PORTB = (1 << PB2);
        shift(1);
        PORTB = ~(1 << PB2);
        shift(1);
        break;
    
    case mid_right:
        prev_state = mid_right;
        reset();
        PORTB = (1 << PB2);
        shift(2);
        PORTB = ~(1 << PB2);
        break;     
        

    case right:
    prev_state = right;
        reset();
        PORTB = (1 << PB2);
        shift(1);
        PORTB = ~(1 << PB2);
        break;

    case left_right:
        prev_state = left_right;
        reset();
        PORTB = (1 << PB2);
        shift(1);
        PORTB = ~(1 << PB2);
        shift(1);
        PORTB = (1 << PB2);
        shift(1);
        PORTB = ~(1<< PB2);
        break;

    case no_line:
        prev_state = no_line;
        reset();
        break;           
    }  
    }
    
    
    

}