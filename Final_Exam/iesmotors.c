#include "iesmotors.h"
#include "iesusart.h"
#include "iessensors.h"
#include <util/delay.h>
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


  /*
  @brief Steering logic depending on state the robot is at.
  Using the check state function. 
  
  
  */

  void follow_line(){
    
    while(1){



      // int adcval0 = ADC_Read_Avg(0, 20);
      //   int adcval1 = ADC_Read_Avg(1, 20);
      //   int adcval2 = ADC_Read_Avg(2, 20);
        
      //   char strbuff[17];
        
      //   USART_print("ADCVAL: ");
      //   sprintf(strbuff, "%u", adcval0);
      //   USART_print(strbuff);
      //   USART_print("   ");
      //   sprintf(strbuff, "%u", adcval1);
      //   USART_print(strbuff);
      //   USART_print("   ");
      //   sprintf(strbuff, "%u", adcval2);
      //   USART_print(strbuff);
      //   USART_print("\n");

    unsigned short adcValue0 = ADC_Read_Avg(LEFT_SENSOR, 20);
    unsigned short adcValue1 = ADC_Read_Avg(MIDDLE_SENSOR, 20);
    unsigned short adcValue2 = ADC_Read_Avg(RIGHT_SENSOR, 20);

    if (adcValue0 > THRESHOLD_LEFT_LFS) {
      
      setDutyCycle(PD5, SPEED_HALF);
      PORTD =  0;     
      PORTD |= LEFT_FORWARD;

      }
    if (adcValue0 < THRESHOLD_LEFT_LFS) {
      setDutyCycle(PD5, 0);

      PORTD &= ~LEFT_FORWARD;
      
      } 
    

    if (adcValue2 > THRESHOLD_RIGHT_LFS) {
      
      setDutyCycle(PD6, SPEED_HALF);
      
      PORTB |= RIGHT_FORWARD;

      }

    if (adcValue2 < THRESHOLD_RIGHT_LFS) {
      
      setDutyCycle(PD6, 0);
      PORTB &= ~RIGHT_FORWARD;
      
      } 
    }
    
  }
  


  

