#include "iesusart.h"
#include <avr/io.h>
#include <stdio.h>

void USART_transmitByte(unsigned char data)
{
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)))
    {
        // Busy waiting! zzzZZZzzzZZZzzz
    }
    // Put data into buffer, send the data
    UDR0 = data;
}

void USART_print(const char *c)
{
    while (*c != '\0')
    {
        USART_transmitByte(*c);
        c++;
    }
}

void USART_round_print(unsigned short round_count)
{

    char strbuff[17];
    sprintf(strbuff, "ROUND %u\n", round_count);
    USART_print(strbuff);
}

void USART_timer_print(unsigned short t1_count)
{

    static unsigned short t1_temp = 1; // variable to filter out multiple prints for the time counter
    char strbuff[17];
    if (t1_temp != t1_count)
    {
        t1_temp = t1_count;
        sprintf(strbuff, "COUNTDOWN: %u\n", t1_count + 1);
        USART_print(strbuff);
    }
}

void USART_init(unsigned long ubrr)
{
    // Set baud rate, high byte first
    UBRR0H = (unsigned char)(ubrr >> 8);
    // Set baud rate, low byte second
    UBRR0L = (unsigned char)ubrr;
    // Enable receiver/transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Frame format: 8 data, 2 stop bits
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
    /* Transmit something right after initialization to overcome the lagg at the
     * start of a simulation in SimulIDE.
    */
    USART_print("<(^_^)>\n\0");
}