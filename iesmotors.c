#include "iesmotors.h"
#include "iesusart.h"
#include "iessensors.h"
#include <stdio.h>
#include "iessensor_lights.h"



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

  // Reset Timer1 Control Reg A 
  TCCR1A = 0;

  // Reset Timer1 Control Reg B
  TCCR1B = 0;

  // Set CTC mode so timer is reset every time it reaches the compare match value
  TCCR1B |= (1 << WGM12);

  // Set Prescaler to 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);

  TCNT1 = 0;                              // reset Timer1
  OCR1A = T1_COMP;                        // set compare value for 15s timer
  OCR1B = T1_BLINK;                       // set compare value for 5Hz blinking
      

  // Enable Timer1 compare Interrupt
  TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);
  

  sei(); 
}

ISR(TIMER1_COMPA_vect){
t1_count++;
  char strbuff[20];
       sprintf(strbuff, "COUNTDOWN:%d\n", t1_count);
       USART_print(strbuff); 
}

ISR(TIMER1_COMPB_vect) {
  blink();
}



void stopTimer1(){
  TCCR1B = 0;
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

    //Setup start countdown timer
    setupTimer1();
    
    // Set PB0, PB1, and PB3 as output (IN[2|3|4])
    DDRB = (1 << DD0) | (1 << DD1) | (1 << DD3);

    USART_print("MOTOR READY!\n");
     
  }

  void forward(){

    PORTD = 0;
    PORTB = 0;

    setDutyCycle(LEFT_SITE, SPEED_HALF);
    setDutyCycle(RIGHT_SITE, SPEED_HALF);
	PORTB &= ~RIGHT_BACKWARD;
	PORTB &= ~LEFT_BACKWARD;
    PORTD |= LEFT_FORWARD;
    PORTB |= RIGHT_FORWARD;
  }


void backward(){
    
    setDutyCycle(LEFT_SITE, SPEED_HALF);
    setDutyCycle(RIGHT_SITE, SPEED_HALF);
	
	PORTB &= ~RIGHT_FORWARD;
	PORTD &= ~LEFT_FORWARD;
    PORTB |= LEFT_BACKWARD;
    PORTB |= RIGHT_BACKWARD;
}

void right_forward(){

    setDutyCycle(LEFT_SITE, SPEED_MAX);
    setDutyCycle(RIGHT_SITE, SPEED_SLOW);
	
	PORTB &= ~LEFT_BACKWARD;
	PORTB &= ~RIGHT_BACKWARD;
    PORTD |= LEFT_FORWARD;
    PORTB |= RIGHT_FORWARD;
}

void right_turn() {

	setDutyCycle(LEFT_SITE, SPEED_HALF);
    setDutyCycle(RIGHT_SITE, SPEED_HALF);
	
	PORTB &= ~LEFT_BACKWARD;
	PORTB &= ~RIGHT_FORWARD;
    PORTD |= LEFT_FORWARD;
    PORTB |= RIGHT_BACKWARD;



}


void left_forward(){

    setDutyCycle(LEFT_SITE, SPEED_HALF);
    setDutyCycle(RIGHT_SITE, SPEED_MAX);
	
	PORTB &= ~RIGHT_BACKWARD;
	PORTB &= ~LEFT_BACKWARD;
    PORTD |= LEFT_FORWARD;
    PORTB |= RIGHT_FORWARD;
}

void left_turn(){

	setDutyCycle(LEFT_SITE, SPEED_HALF);
    setDutyCycle(RIGHT_SITE, SPEED_HALF);
	
	PORTB &= ~RIGHT_BACKWARD;
	PORTD &= ~LEFT_FORWARD;
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


  /**
  @brief Steering logic depending on state the robot is at.
  Using the check state function. 
  */

  void follow_line(){



    while(1){
          
    enum lf_state state = check_state();
    enum lf_state previous_state = 0;

    if(t1_count < 15) {
      stop();
      switch (state){
         
         case all_three:
         break;

         //reset timer1 
         default:
         TCNT1 = 0;                        //reset Timer1
         t1_count =0;
         break;

      }
    }
    else {
      
      stopTimer1(); 

    switch (state){

      case all_three:
        forward();
        break;

      case mid:
        forward();
        break;

      case left:
		left_forward();
		break;
      case left_mid:
        previous_state = left_mid;
        left_turn();
        break;

      case right:
		right_forward();
		break;
      case mid_right:
        previous_state = mid_right;
        right_turn();
        break;

      case left_right:

        //just works for corners 

        if(previous_state == right) {  
          left_turn();
          break;

        } else {
          right_turn();
          break;
        }
      case no_line:
		if(previous_state== left_mid) {
		left_turn();
		break;
		}if (previous_state == mid_right){
			right_turn();
			break;
		} else {
			forward();
		}
      }  
    }
    }
  }

  

