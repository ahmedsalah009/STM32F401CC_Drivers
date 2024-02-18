/*
 * GPIO.c
 *
 *  Created on: Feb 17, 2024
 *      Author: Ahmed Salah
 */


/***************************************************INCLUDE******************************************************/
#include "GPIO.h"
/****************************************************************************************************************/
/****************************************************DEFINE******************************************************/
#define MODE_MASK         0x18
#define OUTPUT_TYPE_MASK  0x4
#define PU_PD_MASK        0x3

#define MAX_NUM_OF_PINS   15

#define TWO_BIT_MASK     0x3
#define ONE_BIT_MASK     0x1
/****************************************************************************************************************/
/*****************************************************TYPES******************************************************/
typedef struct{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIO_Reg_t;

#define NULL ((void *)0)

/****************************************************************************************************************/
/*****************************************************VARIABLES**************************************************/


/****************************************************************************************************************/
/**********************************************STATIC FUNCTIONS PROTOTYPE****************************************/

/****************************************************************************************************************/
/***************************************************IMPELEMENTATION**********************************************/
GPIO_ErrorStatus_t  GPIO_Configure_Pin_Init(GPIO_Pin_Confg_t * Add_Str_Pin_Cfg)
{
	u32 Temp_Reg = 0 ;
	u32 Temp_Mode_Value =0 ;
	u16 Temp_Output_Type_Value = 0 ;
	u32 Temp_Connection_value = 0 ;

	GPIO_ErrorStatus_t  Loc_ErrorState = GPIO_OK ;
	if( (Add_Str_Pin_Cfg == NULL) || (Add_Str_Pin_Cfg->GPIO_Port == NULL))
	{
		Loc_ErrorState = GPIO_NULL_POINTER ;
	}
	else
	{
		Temp_Mode_Value        = (Add_Str_Pin_Cfg->GPIOMode & MODE_MASK) ;
		Temp_Output_Type_Value = (Add_Str_Pin_Cfg->GPIOMode & OUTPUT_TYPE_MASK) ;
		Temp_Connection_value  = (Add_Str_Pin_Cfg->GPIOMode & PU_PD_MASK) ;

				Temp_Reg  = ((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->MODER   ;
				Temp_Reg &=~ (TWO_BIT_MASK << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				Temp_Reg |= (Temp_Mode_Value << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->MODER = Temp_Reg ;

				Temp_Reg = ((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->OTYPER  ;
				Temp_Reg &=~ (ONE_BIT_MASK << (Add_Str_Pin_Cfg->GPIOPin)) ;
				Temp_Reg |= (Temp_Output_Type_Value << (Add_Str_Pin_Cfg->GPIOPin)) ;
				((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->OTYPER = Temp_Reg ;

				Temp_Reg = ((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->PUPDR   ;
				Temp_Reg &=~ (TWO_BIT_MASK << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				Temp_Reg |= (Temp_Connection_value << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->PUPDR = Temp_Reg ;

				Temp_Reg = ((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->OSPEEDR ;
				Temp_Reg &=~ (TWO_BIT_MASK << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				Temp_Reg |= ((Add_Str_Pin_Cfg->GPIOSpeed) << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->OSPEEDR = Temp_Reg ;
	}
	return Loc_ErrorState ;
}

/****************************************************************************************************************/





