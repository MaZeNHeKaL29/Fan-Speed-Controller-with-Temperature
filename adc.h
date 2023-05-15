/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for ADC
 *
 * Author: Mazen Hekal
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ADC_MAXIMUM_VALUE	1023
#define ADC_REFERENCE_VOLTAGE_VALUE	2.56
#define ADC_REFERENCE_VOLTAGE	ADC_InternalVoltageRef
#define ADC_PRESCALER	F_CPU_8

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	ADC_AREF,ADC_AVCC,ADC_InternalVoltageRef = 0x03
}ADC_ReferenceVoltage;

typedef enum{
	F_CPU_2 = 0x01,F_CPU_4,F_CPU_8,F_CPU_16,F_CPU_32,F_CPU_64,F_CPU_128
}ADC_Prescaler;

typedef struct{
	ADC_ReferenceVoltage ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize ADC
 */
void ADC_init(const ADC_ConfigType* Config_Ptr);
/*
 * Description:
 * Function to read channel from ADC
 */
uint16 ADC_readChannel(uint8 Ch_num);

#endif /* ADC_H_ */
