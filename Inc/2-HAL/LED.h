/*
 * LED.h
 *
 *  Created on: Feb 19, 2024
 *      Author:  Ahmed Salah
 */

#ifndef LED_H_
#define LED_H_
/************************************************* INCLUDES ********************************************************/
#include "LED_CFG.h"
/*******************************************************************************************************************/
/************************************************* DEFINE **********************************************************/
#define  LED_STATE_ON        1
#define  LED_STATE_OFF       0
#define CONNECTION_FORWARD   0
#define CONNECTION_REVERSE   1

/*******************************************************************************************************************/
/************************************************* TYPES ***********************************************************/
typedef unsigned char u8 ;
typedef unsigned int  u32;

typedef enum {
	LED_NOK=0 ,
	LED_OK,
	LED_NULL_POINTER,
	LED_WRONG_CONFIGURATION_VALUE
}LED_Return_ErrorState_t;

typedef struct
{
	void *port ;
	u32 Pin ;
	u32 Connetion ;
	u32 Default_Value ;
}LED_str_Cfg_t;
/*******************************************************************************************************************/
/*********************************************** APIs PROTOTYPE ****************************************************/
/**
 * @brief : function to initialize LEDs
 */
void LED_Init(void);


void LED_Set_State(LEDs_t Led_Name,u8 LED_STATE);
/*******************************************************************************************************************/



#endif /* LED_H_ */
