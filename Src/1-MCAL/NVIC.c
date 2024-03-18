/*
 * NVIC.c
 *
 *  Created on: Mar 6, 2024
 *      Author: Ahmed Salah
 */

/***************************************************INCLUDE******************************************************/
#include <NVIC.h>
/****************************************************************************************************************/
/****************************************************DEFINE******************************************************/
#define NVIC_BASE_ADDR		  	0xE000E100
#define SCB_AIRCR    *((volatile u32 *)0xE000ED0C)

#define ZERO_BIT_GROUP      0x0
#define ONE_BIT_GROUP       0x04
#define TWO_BIT_GROUP       0x05
#define THREE_BIT_GROUP     0x06
#define FOUR_BIT_GROUP      0x07
#define MAX_PERIORITY_VALUE 0xF
#define MIN_PERIORITY_VALUE 0x00
#define GROUPING_BITS_MASK  0xFF8FFFFF
#define GROUPING_BITS_SHIFT 0X8
#define VECKEY_MASK         0x0000FFFF
#define VECKEY_VLAUE        0x5FA
#define VECKEY_SHIFT        0x10
#define PERIORITY_BITS_SHIFT 0X4
/****************************************************************************************************************/
/*****************************************************TYPES******************************************************/
typedef struct
{
	volatile u32 ISER[8];
	u32 Reserved[24];
	volatile u32 ICER[8];
	u32 Reserved_1[24];
	volatile u32 ISPR[8];
	u32 Reserved_2[24];
	volatile u32 ICPR[8];
	u32 Reserved_3[24];
	volatile u32 IABR[8];
	u32 Reserved_4[56];
	volatile u8 IPR[240];
	u32 Reserved_5[644];
	volatile u32 STIR;
}NVIC_Register_t;


/****************************************************************************************************************/
/*****************************************************VARIABLES**************************************************/
static NVIC_Register_t* const NVIC = (NVIC_Register_t*)NVIC_BASE_ADDR;


/****************************************************************************************************************/
/**********************************************STATIC FUNCTIONS PROTOTYPE****************************************/

/****************************************************************************************************************/
/***************************************************IMPELEMENTATION**********************************************/
NVIC_ErrorStatus_t NVIC_EnableIRQ(u32 IRQn)
{
	NVIC_ErrorStatus_t Loc_ErrorState = NVIC_OK ;
	if(IRQn < 0 || IRQn > IRQ_MAX_NUM)
	{
		Loc_ErrorState = NVIC_WrongIRQ ;
	}
	else
	{
		NVIC_ClearPendingIRQ(IRQn) ;
		NVIC->ISER[IRQn / 32] |= (1 << (IRQn % 32)) ;
	}
	return Loc_ErrorState ;
}

NVIC_ErrorStatus_t NVIC_DisableIRQ(u32 IRQn)
{
	NVIC_ErrorStatus_t Loc_ErrorState = NVIC_OK ;
		if(IRQn < 0 || IRQn > IRQ_MAX_NUM)
		{
			Loc_ErrorState = NVIC_WrongIRQ ;
		}
		else
		{
			NVIC->ICER[IRQn / 32] = (1 << (IRQn % 32)) ;
		}
		return Loc_ErrorState ;
}

NVIC_ErrorStatus_t NVIC_SetPendingIRQ(u32 IRQn)
{
	NVIC_ErrorStatus_t Loc_ErrorState = NVIC_OK ;
		if(IRQn < 0 || IRQn > IRQ_MAX_NUM)
		{
			Loc_ErrorState = NVIC_WrongIRQ ;
		}
		else
		{
			NVIC->ISPR[IRQn / 32] |= (1 << (IRQn % 32)) ;
		}
		return Loc_ErrorState ;
}

NVIC_ErrorStatus_t NVIC_ClearPendingIRQ(u32 IRQn)
{
	NVIC_ErrorStatus_t Loc_ErrorState = NVIC_OK ;
		if(IRQn < 0 || IRQn > IRQ_MAX_NUM)
		{
			Loc_ErrorState = NVIC_WrongIRQ ;
		}
		else
		{
			NVIC->ICPR[IRQn / 32] = (1 << (IRQn % 32)) ;
		}
		return Loc_ErrorState ;
}

NVIC_ErrorStatus_t NVIC_GetPendingIRQ(u32 IRQn , u32 *Add_Pending_Value)
{
	NVIC_ErrorStatus_t Loc_ErrorState = NVIC_OK ;
			if(IRQn < 0 || IRQn > IRQ_MAX_NUM)
			{
				Loc_ErrorState = NVIC_WrongIRQ ;
			}
			else if(Add_Pending_Value == NULL)
			{
				Loc_ErrorState = NVIC_NULL_POINTER ;
			}
			else
			{
		    	*Add_Pending_Value = NVIC->ISPR[IRQn / 32] &= (1 << (IRQn % 32)) ;
			}
			return Loc_ErrorState ;
}

NVIC_ErrorStatus_t NVIC_SetPriority(u32 IRQn, u8 priority , u32 Group_Pins)
{
	NVIC_ErrorStatus_t Loc_ErrorState = NVIC_OK ;
	u32 Temp_Reg = 0 ;
				if(IRQn < 0 || IRQn > IRQ_MAX_NUM)
				{
					Loc_ErrorState = NVIC_WrongIRQ ;
				}
				else if(priority < MIN_PERIORITY_VALUE || priority > MAX_PERIORITY_VALUE)
				{
					Loc_ErrorState = NVIC_WrongPriorityValue ;
				}
				else if (Group_Pins < ZERO_BIT_GROUP || Group_Pins > FOUR_BIT_GROUP)
				{
					Loc_ErrorState = NVIC_WrongPriorityGroup ;
				}
				else
				{
					Temp_Reg = SCB_AIRCR ;
					Temp_Reg &= (VECKEY_MASK | GROUPING_BITS_MASK);
					Temp_Reg |= ((VECKEY_VLAUE << VECKEY_SHIFT) | (Group_Pins << GROUPING_BITS_SHIFT)) ;
					SCB_AIRCR = Temp_Reg ;

					NVIC->IPR[IRQn] = (priority << PERIORITY_BITS_SHIFT) ;
				}
		return Loc_ErrorState ;

}

/****************************************************************************************************************/

