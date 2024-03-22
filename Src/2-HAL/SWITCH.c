/*
 * SWITCH.c
 *
 *  Created on: Feb 20, 2024
 *      Author: Ahmed Salah
 */

/***************************************************INCLUDE******************************************************/
#include "SWITCH.h"
#include "GPIO.h"
/****************************************************************************************************************/
extern SWITCH_str_Cfg_t SWITCHS[_SWITCH_NUM] ;
/****************************************************DEFINE******************************************************/

/****************************************************************************************************************/
/*****************************************************TYPES******************************************************/
#define NULL ((void *)0)

/****************************************************************************************************************/
/*****************************************************VARIABLES**************************************************/
u8 state ;

/****************************************************************************************************************/
/**********************************************STATIC FUNCTIONS PROTOTYPE****************************************/

/****************************************************************************************************************/
/***************************************************IMPELEMENTATION**********************************************/
void SWITCH_Init(void)
{
	u8 Loc_Iterator = 0;
	GPIO_Pin_Confg_t Loc_SWITCH ;
	Loc_SWITCH.GPIOSpeed= GPIO_Speed_High ;

	for(Loc_Iterator=0 ; Loc_Iterator < _SWITCH_NUM ; Loc_Iterator++)
	{
		Loc_SWITCH.GPIOMode=SWITCHS[Loc_Iterator].mode ;
		Loc_SWITCH.GPIO_Port=SWITCHS[Loc_Iterator].port ;
		Loc_SWITCH.GPIOPin=SWITCHS[Loc_Iterator].Pin;
		GPIO_Configure_Pin_Init(&Loc_SWITCH);
	}
}

SWITCH_Return_ErrorState_t SWITCH_Get_Read(u32 Switch_Num,u32* Add_Switch_Read){
	GPIO_ErrorStatus_t  Loc_ErrorState = SWITCH_OK ;

	u32 Loc_Switch_Read = 0;
if (Switch_Num> _SWITCH_NUM){
	Loc_ErrorState = SWITCH_NOK ; }
else if(Add_Switch_Read==NULL){
	Loc_ErrorState=SWITCH_NULL_POINTER;
}
else{
	GPIO_Get_Pin_Value(SWITCHS[Switch_Num].port ,SWITCHS[Switch_Num].Pin ,&Loc_Switch_Read);
}
switch(SWITCHS[Switch_Num].mode){
case GPIO_MODE_INPUT_PU:       * Add_Switch_Read=~Loc_Switch_Read     ; break ;
case GPIO_MODE_INPUT_PD:       * Add_Switch_Read=Loc_Switch_Read      ; break ;
case GPIO_MODE_INPUT_FLOATING: * Add_Switch_Read=Loc_Switch_Read      ; break ;
default: Loc_ErrorState = SWITCH_NOK ;                                ; break ;
}
return Loc_ErrorState;
}


void SW_Runnable(void)
{
	u32 current = 0 ;
	u32 prev = 0 ;
	u32 counts = 0 ;
	GPIO_Get_Pin_Value(GPIO_A, GPIO_PIN0, &current) ;

	if(current == prev)
	{
		counts++ ;
	}
	else
	{
		counts = 0 ;
	}
	if(counts == 5)
	{
		state = current ;
		counts = 0 ;
		prev = current ;
	}
	else
	{

	}
}
/****************************************************************************************************************/


