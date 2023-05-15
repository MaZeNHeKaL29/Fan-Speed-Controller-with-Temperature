/******************************************************************************
 *
 * Module: LM35 Temperature Sensor
 *
 * File Name: LM35_sensor.c
 *
 * Description: Source file for LM35 Temperature Sensor
 *
 * Author: Mazen Hekal
 *
 *******************************************************************************/

#include "lm35_sensor.h"
#include "adc.h"

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void)
{
	uint16 adc_value;

	uint8 temp;

	/*Read ADC channel where temperature sensor is connected*/
	adc_value =  ADC_readChannel(LM35_SENSOR_CHANNEL_ID);

	temp = (uint8)(((uint32)adc_value*LM35_SENSOR_MAX_TEMPERATURE*ADC_REFERENCE_VOLTAGE_VALUE)/\
			(LM35_SENSOR_MAX_VOLT_VALUE*ADC_MAXIMUM_VALUE));

	/*Calculate Temperature from ADC value */
	return temp;
}
