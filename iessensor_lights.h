/**
 * @file iessensor_lights.h
 * @brief Handling of register shifting to indicate state of robot
 * @version 0.1
 * @date 2021-08-04
 * 
 * 
 */
#ifndef IESSENSOR_LIGHTS
#define IESSENSOR_LIGHTS




/**
 * @brief Shift method for the 4-bit shift register to place bit to right
 * register output
 * 
 * @param count number of times bit need to be shifted
 */
void shift(uint8_t count);

/**
 * @brief Reset register.
 * 
 */
void reset();


/**
 * @brief Handles sensor light to show which sensor is detecting line and
 * which is not.
 * 
 */
void sensor_lights(enum lf_state state);



#endif