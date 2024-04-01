/*
 * LCD.h
 *
 *  Created on: Mar 30, 2024
 *      Author: Ahmed Salah
 */

#ifndef LCD_H_
#define LCD_H_

/************************************************* DEFINE *****************************************************/
#define TICK_TIME			1
#define _MAX_PIN_NUM        11

#define DATA_PIN0	            	0
#define DATA_PIN1	            	1
#define DATA_PIN2	            	2
#define DATA_PIN3	            	3
#define DATA_PIN4	            	4
#define DATA_PIN5	            	5
#define DATA_PIN6	            	6
#define DATA_PIN7	            	7
#define ENABLE_PIN	            	8
#define READ_WRITE_PIN		        9
#define REGISTER_SELSECT_PIN		10

#define LCD_FIRST_LINE 					1
#define LCD_SECOND_LINE 				2


/*Function set command
	 * 1- 2 lines
	 * 2- Font = 5*7
	 * */
#define FUNCTION_SET_COMMAND 		0b00111000

/* Display On Off control command
	 * 1- Display enable
	 * 2- Cursor off
	 * 3- Blink Cursor off
	 * */
#define DISPLAY_ON_OFF_COMMAND	    0b00001111

#define DISPLAY_CLEAR_COMMAND       0b00000001

#define ENTRY_MODE_COMMAND                  0x06
/**************************************************************************************************************/
/************************************************* TYPES ******************************************************/
typedef unsigned char u8 ;
typedef unsigned short u16 ;
typedef unsigned int u32 ;
#define NULL ((void *)0)

typedef enum {
	LCD_NOK,
	LCD_OK,
	LCD_NULL_POINTER
}LCD_Return_Error_Status_t;
typedef struct
{
	u8 Pin;
	void *Port  ;
}LCD_Pins_Cfg_t;

typedef enum
{
	No_Request,
	In_Progress,
}Req_State_t;

typedef enum
{
	None,
	Write,
	Clear,
	Set_Cursor,
}Req_Type_t;


typedef struct {
	 char * Str ;
	u16 Len ;
	u8 X_Pos ;
	u8 Y_Pos ;
	Req_State_t Req_State  ;
	Req_Type_t Req_Type ;
}User_Req_t;

typedef enum
{
	Power_On,
	Functional_Set,
	Display_On_Off,
	Display_Clear,
	Entry_Mode,
	End_Of_Init,
}Enu_Init_Operation_t;

/**************************************************************************************************************/
/*********************************************** APIs PROTOTYPE ***********************************************/
// state machine to initialize LCD

// runnable comes every 2 ms
void LCD_Runnable(void) ;

void LCD_Set_XY_Pos_Async( u8 Copy_X_Pos , u8 Copy_Y_Pos) ;

LCD_Return_Error_Status_t LCD_Write_String_Async( char *Add_String , u16 Copy_Length ) ;

void LCD_Clear_Async(void) ;

/**************************************************************************************************************/











#endif /* LCD_H_ */
