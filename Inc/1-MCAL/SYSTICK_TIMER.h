/*
 * SYSTICK_TIMER.h
 *
 *  Created on: Mar 8, 2024
 *      Author: Ahmed Salah
 */

#ifndef SYSTICK_TIMER_H_
#define SYSTICK_TIMER_H_

/************************************************* DEFINE ****************************************************/
#define NO_PRESCALER             0x4
#define PRESCALER_DIVIDED_BY_8   0xFFFFFFFB
#define AHB_CLK_FRQ              16
#define CLK_SOURCE_MASK          0x4
/**************************************************************************************************************/
/************************************************* TYPES ******************************************************/
typedef enum{
	SYSTICK_NOK,
	SYSTICK_OK,
	SYSTICK_NULL_POINTER,
	SYSTICK_WRONG_PRESCALER
}SYSTICK_ErrorStatus_t ;

typedef void(*Systick_CBF_t)(void) ;
typedef unsigned int u32 ;
typedef unsigned char u8 ;
#define NULL ((void *)0)
/**************************************************************************************************************/
/*********************************************** APIs PROTOTYPE ***********************************************/
/**
 * @brief     : Starts the timer with the given mode
 *
 * @parameter : Mode
 *             1-ONE_TIME
 *             2-PERIODIC
 *
 * @return  : SYSTICK_OK
 * 			  SYSTICK_NOK
 */
void SYSTICK_Start(void);



/**
 * @brief     : Set a function to call when SYSTICK timer interrupt occurs
 *
 * @parameter :
 *              1- Add_Callback   	: address of the callback function
 *
 * @return    : SYSTICK_OK
 * 				SYSTICK_NOK
 */
SYSTICK_ErrorStatus_t SYSTICK_SetCBF(void (*Add_Callback)(void));

/**
 * @brief     : Sets the reload value of the SysTick timer
 *
 * @parameter : Copy_u32Time   	: time to set the SYSTICK timer to
 *
 * @return    :
 *
 */
SYSTICK_ErrorStatus_t SYSTICK_setTimeMs(u32 Copy_Time);

SYSTICK_ErrorStatus_t SYSTICK_setPreScaler(u32 Copy_Prescaler_Value) ;

/**************************************************************************************************************/


#endif /* SYSTICK_TIMER_H_ */
