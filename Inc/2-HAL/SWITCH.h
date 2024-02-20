/*
 * SWITCH.h
 *
 *  Created on: Feb 20, 2024
 *      Author: Interface
 */

#ifndef SWITCH_H_
#define SWITCH_H_

/************************************************* INCLUDES ********************************************************/
#include "SWITCH_CFG.h"
/*******************************************************************************************************************/
/************************************************* DEFINE **********************************************************/
#define  SWITCH_STATE_NOT_PRESSED        1
#define  SWITCH_STATE_PRESSED       0
#define CONNECTION_FORWARD   0
#define CONNECTION_REVERSE   1

/*******************************************************************************************************************/
/************************************************* TYPES ***********************************************************/
typedef unsigned char u8 ;
typedef unsigned int  u32;

typedef enum {
	SWITCH_NOK=0 ,
	SWITCH_OK,
	SWITCH_NULL_POINTER,
	SWITCH_WRONG_CONFIGURATION_VALUE
}SWITCH_Return_ErrorState_t;

typedef struct
{
	void *port ;
	u32 Pin ;
	u32 mode ;
}SWITCH_str_Cfg_t;
/*******************************************************************************************************************/
/*********************************************** APIs PROTOTYPE ****************************************************/
/**
 * @brief : function to initialize SWITCHs
 */
void SWITCH_Init(void);

/**
 * @brief     : function to get the switch read state
 * @parameter :
 *           1- SWITCH NUMBER
 *           2- ADDRESS TO VARIABLE TO STORE THE VALUE IN IT
 *             IF return equal :
 *             = 0 ---> NOT PRESSE
 *             = 1 ---> PRESSED
 *
 * @return : if return = 0 --> SWITCH_OK
 *                     = 1 --> SWITC_NOK
 *                     = 3 --> SWITC_NULL_POINTER
 */
SWITCH_Return_ErrorState_t SWITCH_Get_Read(u32 Switch_Num,u32* Add_Switch_Read);
/*******************************************************************************************************************/



#endif /* SWITCH_H_ */
