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
#define TWO_BIT_MASK      0x3
#define ONE_BIT_MASK      0x1
#define BIR_RESET_OFFSET  0x10
#define MODE_SHIFT        0x03
#define OUTPUT_TYPE_SHIFT 0x02
/****************************************************************************************************************/
/*****************************************************TYPES******************************************************/
typedef struct{
volatile u32 MODER;
volatile u32 OTYPER;
volatile u32 OSPEEDR;
volatile u32 PUPDR;
volatile u32 IDR;
volatile u32 ODR;
volatile u32 BSRR;
volatile u32 LCKR;
volatile u32 AFRL;
volatile u32 AFRH;
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
	u32 Temp_Value =0 ;

	GPIO_ErrorStatus_t  Loc_ErrorState = GPIO_OK ;
	if( (Add_Str_Pin_Cfg == NULL) || (Add_Str_Pin_Cfg->GPIO_Port == NULL))
	{
		Loc_ErrorState = GPIO_NULL_POINTER ;
	}
	else if(Add_Str_Pin_Cfg->GPIOPin < GPIO_PIN0 && Add_Str_Pin_Cfg->GPIOPin > GPIO_PIN15 )
	{
		Loc_ErrorState = GPIO_PinError ;
	}
	else if(Add_Str_Pin_Cfg->GPIOSpeed < GPIO_Speed_Low && Add_Str_Pin_Cfg->GPIOSpeed > GPIO_Speed_Very_High)
	{
		Loc_ErrorState = GPIO_SpeedError ;

	}
	else if(Add_Str_Pin_Cfg->GPIOMode < GPIO_MODE_INPUT_FLOATING && Add_Str_Pin_Cfg->GPIOMode > GPIO_MODE_ANALOG)
	{
		Loc_ErrorState = GPIO_WrongMode ;

	}
	else
	{
				Temp_Value = ( (Add_Str_Pin_Cfg->GPIOMode & MODE_MASK) >> MODE_SHIFT);
				Temp_Reg  = ((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->MODER   ;
				Temp_Reg &=~ (TWO_BIT_MASK << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				Temp_Reg |= (Temp_Value << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->MODER = Temp_Reg ;

				Temp_Value = ( (Add_Str_Pin_Cfg->GPIOMode & OUTPUT_TYPE_MASK) >> OUTPUT_TYPE_SHIFT );
				Temp_Reg = ((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->OTYPER  ;
				Temp_Reg &=~ (ONE_BIT_MASK << (Add_Str_Pin_Cfg->GPIOPin)) ;
				Temp_Reg |= (Temp_Value << (Add_Str_Pin_Cfg->GPIOPin)) ;
				((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->OTYPER = Temp_Reg ;

				Temp_Value = (Add_Str_Pin_Cfg->GPIOMode & PU_PD_MASK) ;
				Temp_Reg = ((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->PUPDR   ;
				Temp_Reg &=~ (TWO_BIT_MASK << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				Temp_Reg |= (Temp_Value << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->PUPDR = Temp_Reg ;

				Temp_Reg = ((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->OSPEEDR ;
				Temp_Reg &=~ (TWO_BIT_MASK << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				Temp_Reg |= ((Add_Str_Pin_Cfg->GPIOSpeed) << (Add_Str_Pin_Cfg->GPIOPin * 2)) ;
				((GPIO_Reg_t *)(Add_Str_Pin_Cfg->GPIO_Port))->OSPEEDR = Temp_Reg ;
	}
	return Loc_ErrorState ;
}


GPIO_ErrorStatus_t GPIO_Set_Pin_Value(void * Add_Port,u32 Pin_Num,u32 Value)
{
	GPIO_ErrorStatus_t  Loc_ErrorState = GPIO_OK ;
	if(Add_Port == NULL)
	{
		 Loc_ErrorState = GPIO_NULL_POINTER ;
	}
	else if(Pin_Num < GPIO_PIN0 && Pin_Num > GPIO_PIN15)
	{
		 Loc_ErrorState = GPIO_PinError ;
	}
	else
	{
		switch(Value)
		{
			case GPIO_PIN_HIGH : ((GPIO_Reg_t *)Add_Port)->BSRR |= (1 << (Pin_Num)) ; break ;
			case GPIO_PIN_LOW : ((GPIO_Reg_t *)Add_Port)->BSRR  |= (1 << (Pin_Num + BIR_RESET_OFFSET )) ; break ;
			default :Loc_ErrorState = GPIO_PinError ; break ;
		}
	}
	return Loc_ErrorState ;
}

GPIO_ErrorStatus_t GPIO_Get_Pin_Value(void * Add_Port,u32 Pin_Num,u32 *Add_Pin_Value)
{
	u32 Loc_Pin_Value = 0 ;
	GPIO_ErrorStatus_t  Loc_ErrorState = GPIO_OK ;
		if(Add_Port == NULL || Add_Pin_Value == NULL)
		{
			 Loc_ErrorState = GPIO_NULL_POINTER ;
		}
		else if(Pin_Num < GPIO_PIN0 && Pin_Num > GPIO_PIN15)
		{
			 Loc_ErrorState = GPIO_PinError ;
		}
		else
		{
			Loc_Pin_Value = ((GPIO_Reg_t *)Add_Port)->IDR &= (1 << Pin_Num) ;
			*Add_Pin_Value = Loc_Pin_Value ;
		}
		return Loc_ErrorState ;
}

/****************************************************************************************************************/





