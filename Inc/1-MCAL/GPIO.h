/*
 * GPIO.h
 *
 *  Created on: Feb 17, 2024
 *      Author: Ahmed Salah
 */

#ifndef GPIO_H_
#define GPIO_H_

/************************************************* DEFINE ****************************************************/

#define GPIO_A          	((void*)0x40020000)
#define GPIO_B          	((void*)0x40020400)
#define GPIO_C          	((void*)0x40020800)
#define GPIO_D          	((void*)0x40020C00)
#define GPIO_E          	((void*)0x40021000)
#define GPIO_H          	((void*)0x40021C00)

#define GPIO_PIN0			0x00000000
#define GPIO_PIN1			0x00000001
#define GPIO_PIN2			0x00000002
#define GPIO_PIN3			0x00000003
#define GPIO_PIN4			0x00000004
#define GPIO_PIN5			0x00000005
#define GPIO_PIN6			0x00000006
#define GPIO_PIN7			0x00000007
#define GPIO_PIN8			0x00000008
#define GPIO_PIN9			0x00000009
#define GPIO_PIN10			0x0000000A
#define GPIO_PIN11			0x0000000B
#define GPIO_PIN12			0x0000000C
#define GPIO_PIN13			0x0000000D
#define GPIO_PIN14			0x0000000E
#define GPIO_PIN15          0x0000000F

#define GPIO_MODE_INPUT_FLOATING 			0x00000000
#define GPIO_MODE_INPUT_PU					0x00000001
#define GPIO_MODE_INPUT_PD                	0x00000002

#define GPIO_MODE_OUTPUT_PP					0x00000008
#define GPIO_MODE_OUTPUT_PP_PU        		0x00000009
#define GPIO_MODE_OUTPUT_PP_PD      		0x0000000A

#define GPIO_MODE_OUTPUT_OPENDRAIN			0x0000000C
#define GPIO_MODE_OUTPUT_OPENDRAIN_PU       0x0000000D
#define GPIO_MODE_OUTPUT_OPENDRAIN_PD     	0x0000000E

#define GPIO_MODE_AF_PP						0x00000010
#define GPIO_MODE_AF_PP_PU            		0x00000011
#define GPIO_MODE_AF_PP_PD          		0x00000012
#define GPIO_MODE_AF_OPENDRAIN				0x00000014
#define GPIO_MODE_AF_OPENDRAIN_PU           0x00000015
#define GPIO_MODE_AF_OPENDRAIN_PD         	0x00000016

#define GPIO_MODE_ANALOG					0x00000018


#define GPIO_Speed_Low				0x00
#define GPIO_Speed_Medium			0x1
#define GPIO_Speed_High				0x2
#define GPIO_Speed_Very_High		0x3

#define GPIO_PIN_LOW                0
#define GPIO_PIN_HIGH               1
/**************************************************************************************************************/
/************************************************* TYPES ******************************************************/
typedef unsigned int   u32 ;
typedef unsigned short u16 ;
typedef unsigned char  u8 ;

typedef struct
{
	void * GPIO_Port;
	    u32 GPIOMode;
		u32 GPIOSpeed;
		u16 GPIOPin;
}GPIO_Pin_Confg_t;

typedef enum{
	GPIO_OK,
	GPIO_NOK,
	GPIO_PortError,
	GPIO_PinError,
	GPIO_SpeedError,
	GPIO_ValueError,
	GPIO_WrongConfig,
	GPIO_NULL_POINTER,
	GPIO_WrongMode
}GPIO_ErrorStatus_t ;
/**************************************************************************************************************/
/*********************************************** APIs PROTOTYPE ***********************************************/
/**
 * @brief : function to configure the GPIO pins
 *          1-MODE (EX: INPUT OR OUTPUT)
 *          2-OUTPUT_TYPE (EX: PUSH PULL OR OPEN DRAIN)
 *          3-CONNECTON (EX : PULL_UP OR PULL_DOWN)
 *
 * @parameters : a structure holds 4 members
 *               1-PORT : 1-GPIO_A
 *                        2-GPIO_B
 *                        3-GPIO_C
 *
 *               2-MODE : 1-GPIO_MODE_INPUT_FLOATING 		    9-GPIO_MODE_OUTPUT_OPENDRAIN_PD
 *                        2-GPIO_MODE_INPUT_PU				    10-GPIO_MODE_AF_PP
 *                        3-GPIO_MODE_INPUT_PD                  11-GPIO_MODE_AF_PP_PU
 *                        4-GPIO_MODE_OUTPUT_PP				    12-GPIO_MODE_AF_PP_PD
 *                        5-GPIO_MODE_OUTPUT_PP_PU              13-GPIO_MODE_AF_OPENDRAIN
 *                        6-GPIO_MODE_OUTPUT_PP_PD      	    14-GPIO_MODE_AF_OPENDRAIN_PU
 *                        7-GPIO_MODE_OUTPUT_OPENDRAIN		    15-GPIO_MODE_AF_OPENDRAIN_PD
 *                        8-GPIO_MODE_OUTPUT_OPENDRAIN_PU
 *
 *              3-SPEED : 1-GPIO_Speed_Low
 *                        2-GPIO_Speed_Medium
 *                        3-GPIO_Speed_High
 *                        4-GPIO_Speed_Very_High
 *
 *              4-PIN  : 1-GPIO_PIN0                     9-GPIO_PIN8
 *                       2-GPIO_PIN1                    10-GPIO_PIN9
 *                       3-GPIO_PIN2                    11-GPIO_PIN10
 *                       4-GPIO_PIN3                    12-GPIO_PIN11
 *                       5-GPIO_PIN4                    13-GPIO_PIN12
 *                       6-GPIO_PIN5                    14-GPIO_PIN13
 *                       7-GPIO_PIN6                    15-GPIO_PIN14
 *                       8-GPIO_PIN7                    16-GPIO_PIN15
 *
 * @return : if return = 0 --> GPIO_OK
 *                     = 1 --> GPIO_NOK
 *                     = 2 --> GPIO_PortError
 *                     = 3 --> GPIO_PinError
 *                     = 4 --> GPIO_SpeedError
 *                     = 5 --> GPIO_ValueError
 *                     = 6 --> GPIO_WrongConfig
 *                     = 7 --> GPIO_NULL_POINTER
 *                     = 8 --> GPIO_WrongMode
 */
GPIO_ErrorStatus_t  GPIO_Configure_Pin_Init(GPIO_Pin_Confg_t * Add_Str_Pin_Cfg) ;



/**
 * @brief      :function to set GPIO pin value
 * @parameters : 1-PORT  :
 *                       1-GPIO_A
 *                       2-GPIO_B
 *                       3-GPIO_C
 *
 *               2-PIN   :
 *                       1-GPIO_PIN0                     9-GPIO_PIN8
 *                       2-GPIO_PIN1                    10-GPIO_PIN9
 *                       3-GPIO_PIN2                    11-GPIO_PIN10
 *                       4-GPIO_PIN3                    12-GPIO_PIN11
 *                       5-GPIO_PIN4                    13-GPIO_PIN12
 *                       6-GPIO_PIN5                    14-GPIO_PIN13
 *                       7-GPIO_PIN6                    15-GPIO_PIN14
 *                       8-GPIO_PIN7                    16-GPIO_PIN15
 *
 *               3-VALUE :
 *                       1-GPIO_PIN_LOW
 *                       2-GPIO_PIN_HIGH
 *
 * @return     :  if return = 0 --> GPIO_OK
 *                          = 1 --> GPIO_NOK
 *                          = 2 --> GPIO_PortError
 *                          = 3 --> GPIO_PinError
 *                          = 5 --> GPIO_ValueError
 *                          = 7 --> GPIO_NULL_POINTER
 */
GPIO_ErrorStatus_t GPIO_Set_Pin_Value(void * Add_Port,u32 Pin_Num,u32 Value);


/**
 * @brief      : function to get pin value
 * @parameters : 1-PORT  :
 *                       1-GPIO_A
 *                       2-GPIO_B
 *                       3-GPIO_C
 *
 *               2-PIN   :
 *                       1-GPIO_PIN0                     9-GPIO_PIN8
 *                       2-GPIO_PIN1                    10-GPIO_PIN9
 *                       3-GPIO_PIN2                    11-GPIO_PIN10
 *                       4-GPIO_PIN3                    12-GPIO_PIN11
 *                       5-GPIO_PIN4                    13-GPIO_PIN12
 *                       6-GPIO_PIN5                    14-GPIO_PIN13
 *                       7-GPIO_PIN6                    15-GPIO_PIN14
 *                       8-GPIO_PIN7                    16-GPIO_PIN15
 *
 *               3-VALUE : it holds the value of the wanted bit
 *                         if it equal :
 *                       =0 --> GPIO_PIN_LOW
 *                       =1 --> GPIO_PIN_HIGH
 *
 * @return               :  if return
 *                          = 0 --> GPIO_OK
 *                          = 1 --> GPIO_NOK
 *                          = 2 --> GPIO_PortError
 *                          = 3 --> GPIO_PinError
 *                          = 5 --> GPIO_ValueError
 *                          = 7 --> GPIO_NULL_POINTER
 */
GPIO_ErrorStatus_t GPIO_Get_Pin_Value(void * Add_Port,u32 Pin_num,u32 *Add_Pin_Value);
/**************************************************************************************************************/

#endif /* GPIO_H_ */











