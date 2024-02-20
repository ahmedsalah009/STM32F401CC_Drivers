/*
 * LED.c
 *
 *  Created on: Feb 19, 2024
 *      Author:  Ahmed Salah
 */


/***************************************************INCLUDE******************************************************/
#include "LED.h"
#include "GPIO.h"
/****************************************************************************************************************/
extern LED_str_Cfg_t LEDS[LED_NUM] ;
/****************************************************DEFINE******************************************************/

/****************************************************************************************************************/
/*****************************************************TYPES******************************************************/

/****************************************************************************************************************/
/*****************************************************VARIABLES**************************************************/


/****************************************************************************************************************/
/**********************************************STATIC FUNCTIONS PROTOTYPE****************************************/

/****************************************************************************************************************/
/***************************************************IMPELEMENTATION**********************************************/
void LED_Init(void)
{
	u8 Loc_Iterator = 0;
	GPIO_Pin_Confg_t Loc_LED ;
	Loc_LED.GPIOMode=GPIO_MODE_OUTPUT_PP ;
	Loc_LED.GPIOSpeed= GPIO_Speed_High ;

	for(Loc_Iterator=0 ; Loc_Iterator < _LED_NUM ; Loc_Iterator++)
	{
		Loc_LED.GPIO_Port=LEDS[Loc_Iterator].port ;
		Loc_LED.GPIOPin=LEDS[Loc_Iterator].Pin;
		GPIO_Configure_Pin_Init(&Loc_LED);
		GPIO_Set_Pin_Value(Loc_LED.GPIO_Port,
				           Loc_LED.GPIOPin,
						   LEDS[Loc_Iterator].Connetion ^ LEDS[Loc_Iterator].Default_Value);
	}
}

void LED_Set_State(LEDs_t Led_Name,u8 LED_STATE)
{
	GPIO_Set_Pin_Value(LEDS[Led_Name].port,
		               LEDS[Led_Name].Pin,
					   LEDS[Led_Name].Connetion ^ LEDS[Led_Name].Default_Value);
}
/****************************************************************************************************************/

