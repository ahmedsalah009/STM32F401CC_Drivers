/*
 * SYSTICK_TIMER.c
 *
 *  Created on: Mar 8, 2024
 *      Author: Ahmed Salah
 */

/***************************************************INCLUDE******************************************************/
#include "SYSTICK_TIMER.h"
/****************************************************************************************************************/
/****************************************************DEFINE******************************************************/
#define SYSTICK_BASE_ADDR		  	        0xE000E010
#define SYSTICK_COUNTER_ENABLE_MASK         0x1
#define SYSTICK_INT_ENABLE_MASK             0x2
#define LOAD_MIN_VALUE                      0x01
#define LOAD_MAX_VALUE                      0x00FFFFFF
/****************************************************************************************************************/
/*****************************************************TYPES******************************************************/
typedef struct
{
	volatile u32 STK_CTRL;
	volatile u32 STK_LOAD;
	volatile u32 STK_VAL;
	volatile u32 STK_CALIB;
}SYSTICK_Register_t;


/****************************************************************************************************************/
/*****************************************************VARIABLES**************************************************/
static SYSTICK_Register_t* const SYSTICK = (SYSTICK_Register_t*)SYSTICK_BASE_ADDR;

static Systick_CBF_t  App_CallBackFun ;
/****************************************************************************************************************/
/**********************************************STATIC FUNCTIONS PROTOTYPE****************************************/

/****************************************************************************************************************/
/***************************************************IMPELEMENTATION**********************************************/
void SYSTICK_Start(void)
{
	SYSTICK->STK_CTRL |=  SYSTICK_COUNTER_ENABLE_MASK ;
	SYSTICK->STK_CTRL |=  SYSTICK_INT_ENABLE_MASK ;
}

void SYSTICK_Stop()
{
	SYSTICK->STK_CTRL &=~  SYSTICK_COUNTER_ENABLE_MASK ;
	SYSTICK->STK_CTRL &=~  SYSTICK_INT_ENABLE_MASK ;
}

SYSTICK_ErrorStatus_t SYSTICK_setPreScaler(u32 Copy_Prescaler_Value)
{
	SYSTICK_ErrorStatus_t Loc_error_status = SYSTICK_OK ;
				switch(Copy_Prescaler_Value)
				{
				case NO_PRESCALER           : SYSTICK->STK_CTRL |= NO_PRESCALER           ; break ;
				case PRESCALER_DIVIDED_BY_8 : SYSTICK->STK_CTRL &= PRESCALER_DIVIDED_BY_8 ; break ;
				default                     : Loc_error_status = SYSTICK_WRONG_PRESCALER  ; break ;
				}
				return Loc_error_status ;

}

SYSTICK_ErrorStatus_t SYSTICK_setTimeMs(u32 Copy_Time)
{
	SYSTICK_ErrorStatus_t Loc_error_status = SYSTICK_OK ;
	u32 Loc_Timer_CLK_FRQ = 0 ;
	u32 Loc_Temp = 0 ;
	if(!(SYSTICK->STK_CTRL & CLK_SOURCE_MASK))
	{
		Loc_Timer_CLK_FRQ = AHB_CLK_FRQ / 8 ;
	}
	else
	{
		Loc_Timer_CLK_FRQ = AHB_CLK_FRQ ;
	}
	Loc_Temp = (((Loc_Timer_CLK_FRQ * Copy_Time)/1000 )-1);

	if(Loc_Temp < LOAD_MIN_VALUE || Loc_Temp > LOAD_MAX_VALUE)
	{
		 Loc_error_status = SYSTICK_NOK ;
	}
	else
	{
		SYSTICK->STK_LOAD = Loc_Temp ;
		SYSTICK->STK_VAL = 0 ;
	}

	return Loc_error_status ;
}

SYSTICK_ErrorStatus_t SYSTICK_SetCBF(Systick_CBF_t Copy_CBF)
{
	SYSTICK_ErrorStatus_t Loc_error_status = SYSTICK_OK ;

	if(Copy_CBF == NULL)
	{
		Loc_error_status = SYSTICK_NULL_POINTER ;
	}
	else
	{
		App_CallBackFun = Copy_CBF ;
	}
	return Loc_error_status ;
}

void SYSTICK_Handler(void)
{
	App_CallBackFun() ;
}

/****************************************************************************************************************/

