#include "iesmotors.h"
#include "iesusart.h"
#include "iessensors.h"
#include <stdio.h>


/* sets up timer 0 (8 bit) */
void setupTimer0() {
  cli();                                  // disable interrupt globally
  // Set Prescaler to 64 
  TCCR0B = 0;
  TCCR0B |= (1 << CS00) | (1 << CS01); 
// Set waveform generation mode to Fast PWM, frequency = F_CPU / (PRESCALER * 2^8)
  TCCR0A = 0;
  TCCR0A |= (1 << WGM00) | (1 << WGM01);
  sei();                                  // enable interrupts globally
}

void setupTimer1(){
  cli();
  
  TCCR1A = 0;

  // Set Prescaler to 1024
  TCCR1B = 0;
  TCCR1B = (1 << CS12) | (1 << CS10 );

  sei(); 
}

/* Sets duty-cycle at pin PD5 or PD6 (OC0A or OC0B)
 * to a value (0 - 255 = 0% - 100%).
 * Timer0 needs to be setup before usage.
 * The required pins also need to be set as output first. */
void setDutyCycle(uint8_t pin, uint8_t value) {
  if (pin == PD6) {
    if (value == 0) {
      TCCR0A &= ~(1 << COM0A1) & ~(1 << COM0A0);  // normal port operation mode
      PORTD &= ~(1 << PD6);                       // PD6 LOW
    }
    else if (value == 255) {
      TCCR0A &= ~(1 << COM0A1) & ~(1 << COM0A0);  // normal port operation mode
      PORTD |= (1 << PD6);                        // PD6 HIGH
    }
    else {
      TCCR0A |= (1 << COM0A1);                    // Clear OC0A on Compare Match, set OC0A at
      TCCR0A &= ~(1 << COM0A0);                   // BOTTOM (non-inverting mode)
      OCR0A = value;
    }
  }
  if (pin == PD5) {
    if (value == 0) {
      TCCR0A &= ~(1 << COM0B1) & ~(1 << COM0B0);  // normal port operation mode
      PORTD &= ~(1 << PD5);                       // PD5 LOW
    }
    else if (value == 255) {
      TCCR0A &= ~(1 << COM0B1) & ~(1 << COM0B0);  // normal port operation mode
      PORTD |= (1 << PD5);                        // PD5 HIGH
    }
    else {
      TCCR0A |= (1 << COM0B1);                    // Clear OC0B on Compare Match, set OC0B at
      TCCR0A &= ~(1 << COM0B0);                   // BOTTOM (non-inverting mode)
      OCR0B = value;
    }
  }
}


  void motors_init(){
    // Delete everything on ports B and D
    DDRD = 0;
    DDRB = 0;
    
    // Set PD5 and PD6 as output (EN[A|B]!)
    DDRD = (1 << DD5) | (1 << DD6);
    
    // Set PD7 as output (IN1)
    DDRD |= (1 << DD7);
    
    // Make PWM work on PD[5|6]
    setupTimer0();
    
    // Set PB0, PB1, and PB3 as output (IN[2|3|4])
    DDRB = (1 << DD0) | (1 << DD1) | (1 << DD3);
    
    /* // Set the duty cycles for PD5/PD6
    setDutyCycle(PD5, SPEED_HALF);
    setDutyCycle(PD6, SPEED_HALF); */


    USART_print("MOTOR READY!\n");
     
  }

  void forward(){

    PORTD = 0;
    PORTB = 0;

    setDutyCycle(LEFT_SITE, SPEED_HALF);
    setDutyCycle(RIGHT_SITE, SPEED_HALF);

    PORTD |= LEFT_FORWARD;
    PORTB |= RIGHT_FORWARD;
  }


void backward(){
    PORTD = 0;
    PORTB = 0;

    setDutyCycle(LEFT_SITE, SPEED_HALF);
    setDutyCycle(RIGHT_SITE, SPEED_HALF);

    PORTD |= LEFT_BACKWARD;
    PORTB |= RIGHT_BACKWARD;
}

void right_forward(){
    PORTD = 0;
    PORTB = 0;

    setDutyCycle(LEFT_SITE, SPEED_HALF);
    setDutyCycle(RIGHT_SITE, SPEED_HALF);

    PORTD |= LEFT_FORWARD;
    PORTB |= RIGHT_BACKWARD;
}

void left_forward(){
    PORTD = 0;
    PORTB = 0;

    setDutyCycle(LEFT_SITE, SPEED_HALF);
    setDutyCycle(RIGHT_SITE, SPEED_HALF);

    PORTB |= LEFT_BACKWARD;
    PORTB |= RIGHT_FORWARD;
}

  void stop() {
    
    setDutyCycle(LEFT_SITE, 0);
    setDutyCycle(RIGHT_SITE,0);

    PORTB &= ~LEFT_BACKWARD;
    PORTD &= ~LEFT_FORWARD;
    PORTB &= ~RIGHT_FORWARD;
    PORTB &= ~RIGHT_BACKWARD;

  }


  void start(){
    
  }





  /**
  @brief Steering logic depending on state the robot is at.
  Using the check state function. 
  */

  void follow_line(){

    while(1){
           
      enum lf_state state = check_state();
      static enum lf_state previous_state = 0; 


    switch (state){

      case all_three:
        start();
        break;

      case mid:
        forward();
        break;

      case left:
      case left_mid:
        previous_state = left;
        left_forward();
        break;

      case right:
      case mid_right:
        previous_state = right;
        right_forward();
        break;

      case left_right:

        //just works for corners 

        if(previous_state == right) {  
          left_forward();
          break;

        } else {
          right_forward();
          break;
        }
      case no_line:
        stop();
        break;



    }
    

    

    }
    
  }
  


  

