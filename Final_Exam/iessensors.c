#include "iesmotors.h"
#include <avr/io.h>
#include "iessensors.h"
#include "iesusart.h"






void sensor_init(){
    //Set ADC on input
    DDRC &= ~(1 << LEFT_SENSOR) & ~(1 << MIDDLE_SENSOR) & ~(1 << RIGHT_SENSOR);    
    ADMUX = (1<<REFS0);    
    ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
    ADCSRA |= (1<<ADEN);
    ADCSRA |= (1<<ADSC); // Single conversion
    while (ADCSRA & (1<<ADSC) );
    ADCW; // Read once to "warm up" ADC.
    USART_print("Linesensor ready!\n");


}



uint16_t ADC_Read(uint8_t channel) {
  ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
  ADCSRA |= (1<<ADSC);
  while (ADCSRA & (1<<ADSC) );
  return ADCW;                    
}

uint16_t ADC_Read_Avg(uint8_t channel, uint8_t nsamples) {
  uint32_t sum = 0;

  for (uint8_t i = 0; i < nsamples; ++i ) {
    sum += ADC_Read( channel );
  }

  return (uint16_t)( sum / nsamples );
}



void check_state(){
  

}






