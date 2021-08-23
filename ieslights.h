/**
 * @file ieslights.h
 * @brief Handling of register shifting to indicate state of robot
 * @version 0.1
 * @date 2021-08-23
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef IESLIGHTS
#define IESLIGHTS

/**
 * @brief Set Pins PB2 and PD4 as output
 * 
 */
void light_init();

/**
 * @brief Handles sensor light to show which sensor is detecting line and
 * which is not.
 * 
 * @param state Take a value of #lf_state
 */
void sensor_lights(enum lf_state state);

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
 * @details Shift 3 times zero in the register
 */
void reset();

/**
 * @brief let all leds blink in 5Hz if called multiple times
 * 
 */
void blink();

#endif
