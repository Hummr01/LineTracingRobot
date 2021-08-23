/**
 * @file iesmotors.h
 * @brief Motor control and linefollow logic
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef IESMOTORS
#define IESMOTORS
#include <avr/io.h>
#include <avr/interrupt.h>

/** @name MOTOR SETUP
*  Macros for the pins controlling the powering of the rotors
* 
*/
///@{

///Used to set PD5 as output for ENA of the L298 FULL-BRIDGE DRIVER
#define ENA DD5
///Used to set PD6 as output for ENB of the L298 FULL-BRIDGE DRIVER
#define ENB DD6

///Motor pin PD5 for the duty cycle of the left side
#define LEFT_SIDE PD5
///Motor pin PD6 for the duty cycle of the right side
#define RIGHT_SIDE PD6
///@}

/** @name DIRECTION
*   Macros for setting the polarity in the HB to set a spinning direction of the
*   wheels.
* 
*/
///@{

/// Setting HB_IN1 to 1
#define LEFT_FORWARD (1 << PD7)

/// Setting HB_IN2 to 1
#define LEFT_BACKWARD (1 << PB0)

/// Setting HB_IN3 to 1
#define RIGHT_BACKWARD (1 << PB1)

/// Setting HB_IN4 to 1
#define RIGHT_FORWARD (1 << PB3)
///@}

/** @name THRESHOLD
*   Threshold for the ADC if the ADCvalue gets above the given threshold
*   it turn from 0 to 1.
* 
*/
///@{
#define THRESHOLD_LEFT_LFS 315
#define THRESHOLD_MIDDLE_LFS 470
#define THRESHOLD_RIGHT_LFS 600
///@}

///Round count buffer for counting in going signals to count one round
#define ROUND_COUNT_BUFFER 60

/** @name SPEED
*   Values for the duty cycle 0 is the lowest 255 the max value 
* 
*/
///@{

///Optimal speed for corrections.
#define SPEED_HALF 100

///Fast possible speed without the chance to shoot over a corner.
#define SPEED_MAX 190
///@}

///Compare Match value for the 15s timer counter for a prescaler of 1024
#define T1_COMP 15625

/**
 * @brief Set pins PD5 and PD6 as output and set
 * 
 */
void motors_init();

/**
 * @brief Setup Timer0
 * 
 * @details Setup Timer0 with a prescaler of 64 and PWM Mode to Fast
 *  
 * 
 */
void setupTimer0(void);

//Make  Global timer counter for waiting time on start and end
volatile static unsigned short t1_count = 0;

/**
 * 
 *@brief setup Timer1 for start function (16 bit)
 *
 *
 * @details Setup Timer1 with prescaler of 1024 and a Compare Match Interupt of 
 * the value of #T1_COMP which trigger #ISR(TIMER1_COMPA_vect) 
 *  
 */
void setupTimer1();

/**
 * @brief Increment the timer counter by one 
 * 
 */
ISR(TIMER1_COMPA_vect);

/**
 * @brief stop Timer1 
 * 
 */
void stopTimer1();

/**
 * @details Sets duty-cycle at pin PD5 or PD6 which defined in the with #LEFT_SIDE and 
 * '#RIGHT_SIDE'
 * to a value (0 - 255 = 0% - 100%). Good Defined values are #SPEED_HALF and 
 * #SPEED_MAX.
 * 
 * @brief Set the Duty Cycle object
 * 
 * @param pin Set to #LEFT_SIDE or #RIGHT_SIDE
 * @param value 0-255 
 * 
 * @attention Timer0 needs to be setup before usage.
 * @attention The required pins also need to be set as output first.
 */
void setDutyCycle(uint8_t pin, uint8_t value);

/**
 * @brief 
 * Steering logic depending on the state given by #check_state().
 * 
 * 
 * @details Additional to the steerign logic there is the start and finish logic 
 * implemnted
 */

void follow_line();

/**
 * @name Steering functions 
 * 
 *
 * @brief Functions for implementation of forward, right, left, backward
 * and small corrections on either side.
 */

///@{

/**
 * @brief Go forward
 * 
 * @details Let all wheels turn forward.
 */
void forward();

/**
 * 
 * @brief Go backwards
 * 
 * @details Let all wheels turn backward.
 */
void backward();

/**
 * @brief Correct lightly to the right
 * 
 * @details Let all wheels turn forward while the left side is faster than the 
 * right side
 */
void right_forward();

/**
 * 
 * @brief Turn right
 * 
 * @details Let the right wheels go backwards while the left wheels go forward 
 * to turn the robot to the right to turn on corners
 * 
 */
void right_turn();

/**
 * 
 * @brief Correct lightly to the right
 * 
 * @details Let all wheels turn forward while the left side is faster than the 
 * right side.
 */
void left_forward();
///@}

/**
 * 
 * @brief Turn left
 * 
 * 
 * @details Let the right wheels go forward while the left wheels go backward 
 * to turn the robot to the left to turn on corners.
 * 
 */
void left_turn();

/**
 * @brief Stop motors
 * 
 * @details Set the duty cycle of both sides to 0 and set all pins to 0.
 * 
 */
void stop();

#endif
