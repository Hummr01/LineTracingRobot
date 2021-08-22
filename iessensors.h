/**
 * @file iessensors.h
 * @brief Basic inititialisation of sensors and implementation of the detecting 
 * logic
 * @version 0.1
 * @date 2021-08-02
 */

#ifndef IESSENSORS
#define IESSENSORS

/** @name SENSOR PINS
* 
*/
///@{
#define LEFT_SENSOR PC2
#define MIDDLE_SENSOR PC1
#define RIGHT_SENSOR PC0
///@}

/** @name ADC THRESHOLD
*   Threshold for the ADC if the ADCvalue gets above the given threshold
*   it turns from 0 to 1.
* 
*/
///@{
#define THRESHOLD_LEFT_LFS 315
#define THRESHOLD_MIDDLE_LFS 470
#define THRESHOLD_RIGHT_LFS 600
///@}

/**
 * @brief Initilaze PC0, PC1, PC2 for linesensors and setup the ADC
 */
void sensor_init();

///Reads
uint16_t ADC_Read(uint8_t channel);

///Returns the Average ADCValue
uint16_t ADC_Read_Avg(uint8_t channel, uint8_t nsamples);

///States of all possible sensor combinations
enum lf_state
{
    no_line,
    all_three,
    left,
    left_mid,
    mid,
    mid_right,
    right,
    left_right
};

/**
 * @brief Returns current state of the sensor
 * 
 * @return lf_state state current sensor combination
 */
enum lf_state check_state();

#endif
