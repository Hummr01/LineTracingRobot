#ifndef IESMOTORS
#define IESMOTORS
#include <avr/io.h>
#include <avr/interrupt.h>

/*Motor pins*/
#define ENA DD5
#define ENB DD6

/*Direction input*/
#define LEFT_FORWARD PD7
#define LEFT_BACKWARD PB0

/*Settings for the ADC if the ADC is abough a certain threshold it is on 1 otherwise 0*/
#define THRESHOLD_LEFT_LFS 512
#define THRESHOLD_RIGHT_LFS 512
#define THRESHOLD_MIDDLE_LFS 512

/*Dutycycle Speed*/
#define SPEED_SLOW 100
#define SPEED_HALF 155
#define SPEED_MAX 255

void test_print();


void setupTimer0(void);

void setDutyCycle(uint8_t pin, uint8_t value);

void motors_init();

void motors_steering();

#endif




