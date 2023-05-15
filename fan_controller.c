/******************************************************************************
 *
 * Module: Fan Controller Main
 *
 * File Name: fan_controller.c
 *
 * Description: Main Function file for Fan Controller
 *
 * Author: Mazen Hekal
 *
 *******************************************************************************/

#include "adc.h"
#include "lcd.h"
#include "dc_motor.h"
#include "lm35_sensor.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define FAN_STOP_ROTATION	DC_MOTOR_STOP
#define FAN_START_ROTATION	DC_MOTOR_A_CW


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	FAN_OFF,FAN_ON
}FAN_State;

/*******************************************************************************
 *                              	Functions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to display State of fan and Temperature
 */
void LCD_displayState(FAN_State a_state, uint8 a_temp)
{
	LCD_moveCursor(0, 9);
	a_state ? LCD_displayString("ON ") : LCD_displayString("OFF");
	LCD_moveCursor(1, 9);
	if(a_temp >= 100)
	{
		LCD_displayInteger(a_temp);
	}
	else if(a_temp >= 10)
	{
		LCD_displayInteger(a_temp);
		LCD_displayCharacter(' ');
	}
	else
	{
		LCD_displayInteger(a_temp);
		LCD_displayCharacter(' ');
		LCD_displayCharacter(' ');
	}
}


/*******************************************************************************
 *                                Main Function                                *
 *******************************************************************************/

int main(void)
{
	uint8 temp;
	DC_MOTOR_State s_state;
	uint8 speed;
	ADC_ConfigType ADC_Config = {ADC_REFERENCE_VOLTAGE, ADC_PRESCALER};
	/* initialize ADC Driver */
	ADC_init(&ADC_Config);
	/* initialize LCD Driver */
	LCD_init();
	/* initialize DC MOTOR Driver */
	DC_MOTOR_init();
	/* Display in "Fan is " in first row and "Temp =     C" in second row */
	LCD_moveCursor(0, 2);
	LCD_displayString("Fan is ");
	LCD_moveCursor(1, 2);
	LCD_displayString("Temp =     C");
	while(1)
	{
		/* Get Temperature */
		temp = LM35_getTemperature();
		/* Check Temperature */
		if(temp < 30)
		{
			s_state = FAN_STOP_ROTATION; /* Fan is OFF */
			speed = 0; /* speed is 0% */
			DC_MOTOR_rotate(s_state, speed);
			LCD_displayState(FAN_OFF, temp);
		}
		else if(temp >= 30 && temp < 60)
		{
			s_state = FAN_START_ROTATION; /* Fan is ON */
			speed = 25; /* speed is 25%*/
			DC_MOTOR_rotate(s_state, speed);
			LCD_displayState(FAN_ON, temp);
		}
		else if(temp >= 60 && temp < 90)
		{
			s_state = FAN_START_ROTATION; /* Fan is ON */
			speed = 50; /* speed is 50%*/
			DC_MOTOR_rotate(s_state, speed);
			LCD_displayState(FAN_ON, temp);
		}
		else if(temp >= 90 && temp < 120)
		{
			s_state = FAN_START_ROTATION; /* Fan is ON */
			speed = 75; /* speed is 75%*/
			DC_MOTOR_rotate(s_state, speed);
			LCD_displayState(FAN_ON, temp);
		}
		else if(temp >= 120)
		{
			s_state = FAN_START_ROTATION; /* Fan is ON */
			speed = 100; /* speed is 100%*/
			DC_MOTOR_rotate(s_state, speed);
			LCD_displayState(FAN_ON, temp);
		}
	}
}
