/*
 * NVIC.h
 *
 *  Created on: Mar 6, 2024
 *      Author: Ahmed Salah
 */

#ifndef NVIC_H_
#define NVIC_H_

#include "NVIC_STM32F401CCU6_INT.h"
/************************************************* DEFINE ****************************************************/

/**************************************************************************************************************/
/************************************************* TYPES ******************************************************/
typedef enum{
	NVIC_OK,
	NVIC_NOK,
	NVIC_WrongIRQ,
	NVIC_WrongPriorityValue,
	NVIC_WrongPriorityGroup,
	NVIC_NULL_POINTER,
}NVIC_ErrorStatus_t ;

typedef unsigned int u32 ;
typedef unsigned char u8 ;
#define NULL ((void *)0)
/**************************************************************************************************************/
/*********************************************** APIs PROTOTYPE ***********************************************/
NVIC_ErrorStatus_t NVIC_EnableIRQ(u32 IRQn);
NVIC_ErrorStatus_t NVIC_DisableIRQ(u32 IRQn);
NVIC_ErrorStatus_t NVIC_SetPendingIRQ(u32 IRQn);
NVIC_ErrorStatus_t NVIC_ClearPendingIRQ(u32 IRQn);
NVIC_ErrorStatus_t NVIC_GetPendingIRQ(u32 IRQn , u32 *Add_Pending_Value);
NVIC_ErrorStatus_t NVIC_SetPriority(u32 IRQn, u8 priority , u32 Group_Pins);
u32 NVIC_GetPriority(u32 IRQn);
/**************************************************************************************************************/


#endif /* NVIC_H_ */


