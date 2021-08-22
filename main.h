/**
 * @file main.h
 * @author Daniel Laber
 * @brief robot initilasiation and main function
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <avr/io.h>
#include <stdio.h>

#include "iesusart.h"
#include "iesmotors.h"
#include "iessensors.h"
#include "iessensor_lights.h"

/**
 * @brief Setup all ports for light, motors and sensors
 * 
 */
void robot_init();

/**
 * @brief Inititilze robot and start linefollow logic
 * 
 * @return int 
 */
int main(void);
