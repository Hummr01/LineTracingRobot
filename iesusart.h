/**
 * @file iesusart.h
 * @brief Basic serial communication via USART for ATMEGA328
 * @version 0.1
 * @date 2021-06-08
 */

#ifndef IESUSART_h
#define IESUSART_h

/** @name USART SETUP
*  Macros for setting up the cummunication via USART for ATMEGA328
* 
*/
///@{

/// CPU clock speed
#ifndef F_CPU
#define F_CPU 16E6
#endif

/// Desired baudrate
#define BAUD 9600
/// What to write into the UBRR register
#define UBRR_SETTING F_CPU / 16.0 / BAUD - 1
///@}
/** @name DEBUG
* 
*/
///@{
///Set DEBUG to 1 for debug information
#define DEBUG 0
///@}

/**
 * @name SETUP
 * 
 */
///@{
/**
 * @brief Sets up the USART port (The USART baudrate register)
 * @param ubrr Content to write into the UBRR register
 */
void USART_init(unsigned long ubrr);
///@}

/**
 * @name Print
 * 
 */
///@{
/**
 * @brief Writes a single byte to the USART transmit buffer
 * @param data Byte that shall be transmitted
 */
void USART_transmitByte(unsigned char data);

/**
 * @brief Transmittes a string (char by char) until '\0’ is reached
 */
void USART_print(const char *c);

/**
 * @brief Print current round count given as param
 * 
 * @param round_count current round count 
 */
void USART_round_print(unsigned short round_count);

/**
 * @brief Print current timer_count
 * 
 * @param t1_count
 */
void USART_timer_print(unsigned short t1_count);
///}@

#endif
