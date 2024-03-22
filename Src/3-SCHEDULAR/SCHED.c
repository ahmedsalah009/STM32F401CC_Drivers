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

/****************************************************************************************************************/
/*****************************************************TYPES******************************************************/
/*typedef struct{
	Runnable_t runnable ;
	//u32 remaining_time  ;
}Runnable_Info_t;
*/
/****************************************************************************************************************/
/*****************************************************VARIABLES**************************************************/
//Runnable_Info_t runnables[MAX_RUNNABLES] ;
u32 Global_Counter  ;
static u32 pending_tick ;
/****************************************************************************************************************/
/**********************************************STATIC FUNCTIONS PROTOTYPE****************************************/

/****************************************************************************************************************/
/***************************************************IMPELEMENTATION**********************************************/
void SCHED_Init(void)
{
	SYSTICK_setPreScaler(NO_PRESCALER) ;
	SYSTICK_setTimeMs(1000);
	SYSTICK_SetCBF(SCHED_tick_callback);
}
void SCHED_Start(void)
{
	SYSTICK_Start();
	while(1)
	{
		if(pending_tick)
		{
			pending_tick -- ;
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
	Global_Counter ++ ;
	for(idx=0 ; idx < _RUNNABLES_MAX ; idx++)
	{
		if((Global_Counter % runnables[idx].peridicity_ms) == 0 )
		{
			runnables[idx].cb() ;
			//runnables[idx].remaining_time = runnables[idx].runnable->peridicity_ms ;
		}
		//runnables[idx].remaining_time -- ;
	}

}

void SCHED_tick_callback(void)
{
	pending_tick ++ ;
}
/*
SCHED_ErrorStatus_t SCHED_Register_runnable(Runnable_t *run)
{
	SCHED_ErrorStatus_t Loc_error_status = SCHED_OK ;
	if(run == NULL && runnables[run->periority].runnable = NULL)
	{
		runnables[run->periority].runnable = run ;
		runnables[run->periority].remaining_time = run->peridicity_ms ;
	}
	else
	{

	}

}
*/
/****************************************************************************************************************/

