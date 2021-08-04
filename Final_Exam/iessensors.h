/**
 * @file iessensors.h
 * @brief Basic inititialisation of sensors and implementation of the detecting 
 * logic
 * @version 0.1
 * @date 2021-08-02
 */

#ifndef IESSENSORS
#define IESSENSORS

/*Sensor pins*/
#define LEFT_SENSOR PC0
#define MIDDLE_SENSOR PC1
#define RIGHT_SENSOR PC2


/* Configuration for ADC*/
#define MAX_ADC 1023




/**
 * @brief 
 * Initilaze PC0, PC1, PC2 for linesensors and PB5 and PB6
 * for the motor. 
 */

void sensor_init();

/*
Reads
*/
uint16_t ADC_Read(uint8_t channel);


/*Returns the Average ADCValue */
uint16_t ADC_Read_Avg(uint8_t channel, uint8_t nsamples);


/*States of all possible sensor combinations */
enum lf_state {no_line, all_three, left, left_mid, mid, mid_right, right, left_right};

/**
 * @brief Returns current state of the sensor
 * 
 * @return enum lf_state state of sensor
 */
enum lf_state check_state();


#endif


