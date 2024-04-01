/*
 * LCD_SM.c
 *
 *  Created on: Apr 1, 2024
 *      Author: Interface
 */
#include "LCD.h"

typedef enum {
	Clr,
	Set_Cur,
	Wrt,
}Operation_t;

void LCD_SM_Runnable(void)
{
	static Operation_t Operation = Clr ;
	static u8 Time = 0 ;
	Time++ ;

	switch(Operation)
		{
		case Clr :
			if(Time == 1)
			{
				LCD_Clear_Async() ;
			}
			else
			{
				Operation = Set_Cur ;
				Time = 0 ;
			}
			break ;

		case Set_Cur :
			if(Time == 1)
				{
					LCD_Set_XY_Pos_Async(LCD_FIRST_LINE, 0) ;
				}
				else
				{
					Operation = Wrt ;
					Time = 0 ;
				}
			break ;

		case Wrt :
			if(Time == 1)
			{
				LCD_Write_String_Async("NOAH 01/01/2024",15);
			}
			else{/* do nothing */}
			if (Time == 3)
			{
				Operation = Clr ;
				Time = 0 ;
			}

			break ;

		default :
			break ;
		}
}
