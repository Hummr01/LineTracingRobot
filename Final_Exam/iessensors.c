#include "iesmotors.h"
#include <avr/io.h>
#include "iessensors.h"
#include "iesusart.h"
#include <stdio.h>


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



enum lf_state check_state() {


      // int adcval0 = ADC_Read_Avg(0, 20);
      //   int adcval1 = ADC_Read_Avg(1, 20);
      //   int adcval2 = ADC_Read_Avg(2, 20);
        
      //   char strbuff[17];
        
      //   USART_print("ADCVAL: ");
      //   sprintf(strbuff, "%u", adcval0);
      //   USART_print(strbuff);
      //   USART_print("   ");
      //   sprintf(strbuff, "%u", adcval1);
      //   USART_print(strbuff);
      //   USART_print("   ");
      //   sprintf(strbuff, "%u", adcval2);
      //   USART_print(strbuff);
      //   USART_print("\n");
  

  unsigned short adcValueLeft = ADC_Read_Avg(LEFT_SENSOR, 20);
  unsigned short adcValueMid = ADC_Read_Avg(MIDDLE_SENSOR, 20);
  unsigned short adcValueRight = ADC_Read_Avg(RIGHT_SENSOR, 20);

  char strbuff[17];

     sprintf(strbuff, "%u", adcValueLeft);
         USART_print(strbuff);
         USART_print("\n");

  if((adcValueMid > THRESHOLD_MIDDLE_LFS) && (adcValueLeft < THRESHOLD_LEFT_LFS)
    && adcValueRight < THRESHOLD_RIGHT_LFS){
    return mid;
  }
  if (((adcValueMid > THRESHOLD_MIDDLE_LFS) && (adcValueRight > THRESHOLD_RIGHT_LFS))
  || (adcValueRight > THRESHOLD_RIGHT_LFS)) {
    return right;
  }
  if (((adcValueMid > THRESHOLD_MIDDLE_LFS) && (adcValueRight > THRESHOLD_LEFT_LFS))
  || (adcValueLeft > THRESHOLD_LEFT_LFS)) {
    return right;
  }
  
  
  
}












