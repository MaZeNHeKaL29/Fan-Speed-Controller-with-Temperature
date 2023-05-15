/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for ADC
 *
 * Author: Mazen Hekal
 *
 *******************************************************************************/

#include "adc.h"
#include <avr/io.h>
#include "common_macros.h"


/*
 * Description:
 * Function to initialize ADC
 */
void ADC_init(const ADC_ConfigType* Config_Ptr)
{
	/*VREF = AVCC, VREF = 5V*/
	ADMUX = (ADMUX & ~(0xC0)) | ((Config_Ptr -> ref_volt) << 6);
	/*Input Channel for ADC is ADC0(Default)*/
	CLEAR_BIT(ADMUX,MUX0);
	CLEAR_BIT(ADMUX,MUX1);
	CLEAR_BIT(ADMUX,MUX2);
	CLEAR_BIT(ADMUX,MUX3);
	CLEAR_BIT(ADMUX,MUX4);
	/*ADC Enable*/
	SET_BIT(ADCSRA,ADEN);
	/*Disable interrupt in ADC*/
	CLEAR_BIT(ADCSRA,ADIE);
	/*Configure Division Factor for ADC clock (N = 128) (F_ADC = F_CPU/128)
	 * Note That : F_ADC for AVR =  50 ~ 200 KHZ
	 */
	ADCSRA = (ADCSRA & ~(0x07)) | (Config_Ptr -> prescaler);
}

/*
 * Description:
 * Function to read channel from ADC
 */
uint16 ADC_readChannel(uint8 Ch_num)
{
	/*insert Ch_num in ADMUX*/
	ADMUX = (ADMUX & ~(0x1F)) | (Ch_num & 0x07);
	/*Start Conversion of ADC*/
	SET_BIT(ADCSRA,ADSC);
	/*Polling until ADIF flag equals 1*/
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	/*clear ADIF flag by writing Logic High to ADIF flag*/
	SET_BIT(ADCSRA,ADIF);
	/*read data*/
	return ADC;
}

