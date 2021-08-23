#include "iesmotors.h"
#include <avr/io.h>
#include "iessensors.h"
#include "iesusart.h"
#include <stdio.h>
#include "ieslights.h"

void sensor_init()
{
  //Set ADC on input
  DDRC &= ~(1 << LEFT_SENSOR) & ~(1 << MIDDLE_SENSOR) & ~(1 << RIGHT_SENSOR);
  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADCSRA |= (1 << ADEN);
  ADCSRA |= (1 << ADSC); // Single conversion
  while (ADCSRA & (1 << ADSC))
    ;
  ADCW; // Read once to "warm up" ADC.
  USART_print("LINESENSOR READY!\n");
}

uint16_t ADC_Read(uint8_t channel)
{
  ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC))
    ;
  return ADCW;
}

uint16_t ADC_Read_Avg(uint8_t channel, uint8_t nsamples)
{
  uint32_t sum = 0;

  for (uint8_t i = 0; i < nsamples; ++i)
  {
    sum += ADC_Read(channel);
  }

  return (uint16_t)(sum / nsamples);
}

enum lf_state check_state()
{

  unsigned short adcValueLeft = ADC_Read_Avg(LEFT_SENSOR, 20);
  unsigned short adcValueMid = ADC_Read_Avg(MIDDLE_SENSOR, 20);
  unsigned short adcValueRight = ADC_Read_Avg(RIGHT_SENSOR, 20);

  //If DEBUG set to true it prints out the adcValue for the sensors every 200
  //state request

  if (DEBUG)
  {
    static char debug_count = 0;
    debug_count++;
    if (debug_count % 200 == 0)
    {
      char strbuff[70];
      sprintf(strbuff, "SIGNAL LEFT %u | SIGNAL MID %u | SIGNAL RIGHT: %u\n",
              adcValueLeft, adcValueMid, adcValueRight);
      USART_print(strbuff);
    }
  }

  if ((adcValueLeft > THRESHOLD_LEFT_LFS) && (adcValueMid > THRESHOLD_MIDDLE_LFS) && (adcValueRight > THRESHOLD_RIGHT_LFS))
  {

    blink();
    return all_three;
  }

  if ((adcValueLeft < THRESHOLD_LEFT_LFS) && (adcValueMid < THRESHOLD_MIDDLE_LFS) && (adcValueRight < THRESHOLD_RIGHT_LFS))
  {

    sensor_lights(no_line);
    return no_line;
  }

  if ((adcValueMid > THRESHOLD_MIDDLE_LFS) && (adcValueLeft > THRESHOLD_LEFT_LFS))
  {

    sensor_lights(left_mid);
    return left_mid;
  }

  if ((adcValueMid > THRESHOLD_MIDDLE_LFS) && (adcValueLeft < THRESHOLD_LEFT_LFS) && (adcValueRight < THRESHOLD_RIGHT_LFS))
  {

    sensor_lights(mid);
    return mid;
  }

  if ((adcValueMid > THRESHOLD_MIDDLE_LFS) && (adcValueRight > THRESHOLD_RIGHT_LFS))
  {
    sensor_lights(mid_right);
    return mid_right;
  }

  if ((adcValueLeft > THRESHOLD_LEFT_LFS) && (adcValueRight > THRESHOLD_RIGHT_LFS))
  {

    sensor_lights(left_right);
    return left_right;
  }

  else if ((adcValueRight > THRESHOLD_RIGHT_LFS) && (adcValueMid < THRESHOLD_MIDDLE_LFS) && (adcValueLeft < THRESHOLD_LEFT_LFS))
  {

    sensor_lights(right);
    return right;
  }

  else if (adcValueLeft > THRESHOLD_LEFT_LFS)
  {

    sensor_lights(left);
    return left;
  }
  else
  {

    return no_line;
  }
}
