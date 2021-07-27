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

/**
 * @brief 
 * Checks the state of the robot on the line.
 * 
 */
 void check_state();


#endif


