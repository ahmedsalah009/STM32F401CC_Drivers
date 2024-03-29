/*
 * SCHED.c
 *
 *  Created on: Mar 12, 2024
 *      Author: Ahmed Salah
 */

/***************************************************INCLUDE******************************************************/
#include "SCHED.h"
#include "SYSTICK_TIMER.h"
#include "SCHED_CFG.h"

extern Runnable_t runnables[_RUNNABLES_MAX] ;

/****************************************************************************************************************/
/****************************************************DEFINE******************************************************/
#define TICK_TIME 1000
/****************************************************************************************************************/
/*****************************************************TYPES******************************************************/

/****************************************************************************************************************/
/*****************************************************VARIABLES**************************************************/
u32 Global_Counter  ;
static u32 pending_tick=0 ;
/****************************************************************************************************************/
/**********************************************STATIC FUNCTIONS PROTOTYPE****************************************/

/****************************************************************************************************************/
/***************************************************IMPELEMENTATION**********************************************/
void SCHED_Init(void)
{
	SYSTICK_setPreScaler(NO_PRESCALER) ;
	SYSTICK_setTimeMs(TICK_TIME);
	SYSTICK_SetCBF(SCHED_tick_callback);
}
void SCHED_Start(void)
{
	SYSTICK_Start();
	while(1)
	{
		if(pending_tick)
		{
			pending_tick-- ;
			SCHED();
		}
		else
		{

		}
	}
}

void SCHED(void)
{
	u32 idx = 0 ;
	static u32 Global_Counter = 0  ;
	Global_Counter += TICK_TIME ;
	for(idx=0 ; idx < _RUNNABLES_MAX ; idx++)
	{
		if((runnables[idx].cb) && ((Global_Counter % runnables[idx].peridicity_ms) == 0 ))
		{
			runnables[idx].cb() ;
		}
		else
		{
			// do nothing
		}
	}


}

void SCHED_tick_callback(void)
{
	pending_tick ++ ;
}

/****************************************************************************************************************/

