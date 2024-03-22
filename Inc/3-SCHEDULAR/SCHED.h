/*
 * SCHED.h
 *
 *  Created on: Mar 12, 2024
 *      Author: Ahmed Salah
 */

#ifndef SCHED_H_
#define SCHED_H_
/************************************************* DEFINE ****************************************************/
/**************************************************************************************************************/
/************************************************* TYPES ******************************************************/

typedef void(* Runnble_CB_t)(void) ;
typedef unsigned int u32 ;
typedef unsigned char u8 ;
#define NULL ((void *)0)

typedef struct{
	u8 * name ;
	u32 peridicity_ms ;
	u32 periority ;
	Runnble_CB_t cb ;
	u32 delay_ms ;
}Runnable_t;

typedef enum{
	SCHED_NOK,
	SCHED_OK,
	SCHED_NULL_POINTER,
}SCHED_ErrorStatus_t ;
/**************************************************************************************************************/
/*********************************************** APIs PROTOTYPE ***********************************************/
void SCHED_Init(void) ;
void SCHED_Start(void) ;
//SCHED_ErrorStatus_t SCHED_Register_runnable(Runnable_t *run);
void SCHED(void) ;
void SCHED_tick_callback(void) ;
/**************************************************************************************************************/











#endif /* SCHED_H_ */
