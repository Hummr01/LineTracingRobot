#ifndef IESMOTORS
#define IESMOTORS
#include <avr/io.h>
#include<avr/interrupt.h>

/*Motor pins*/
#define ENA DD5
#define ENB DD6

/*Motor pins for the duty cycle*/
#define LEFT_SITE PD5
#define RIGHT_SITE PD6

/*Direction input*/
#define LEFT_FORWARD (1 << PD7)
#define LEFT_BACKWARD (1 << PB0)
#define RIGHT_FORWARD (1 << PB3)
#define RIGHT_BACKWARD (1 << PB1)

/*Settings for the ADC if the ADC is abough a certain threshold it is on 1 otherwise 0*/
#define THRESHOLD_LEFT_LFS 100
#define THRESHOLD_MIDDLE_LFS 400
#define THRESHOLD_RIGHT_LFS 400


/*Dutycycle Speed*/
#define SPEED_CORRECT 130
#define SPEED_SLOW 100
#define SPEED_HALF 155
#define SPEED_MAX 255

/*Compare value for the 15s timer counter for a prescaler of 1024*/
#define T1_COMP 15625

/*Compare value for the 15s timer led blinking*/
#define T1_BLINK 3125


void setupTimer0(void);


// Counter for the 15s start counter
static unsigned short t1_count = 0;

/**
 * @brief setup Timer1 for start function (16 bit)
 * 
 */
void setupTimer1();

/**
 * @brief increment the start counter by one 
 * 
 */
ISR(TIMER1_COMPA_vect);

/**
 * @brief stopt Timer1 for the period of driving
 * 
 */
void stopTimer1();

void setDutyCycle(uint8_t pin, uint8_t value);

void motors_init();

/**
 * @brief 
 * Steering logic depending on the state given by check_state.
 */

void follow_line();

/**
 * @brief 
 * Functions for implementation of foward, right, left, backward
 * movement given argument should not be bigger than 255
 */
void forward();

void backward();

void right_forward();

void right_turn();

void left_forward();

void left_turn();

void stop();

/**
 * @brief Function initializiation of start sequence.
 * 
 */
void start();

#endif




