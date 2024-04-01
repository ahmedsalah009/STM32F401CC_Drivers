/*
 * LCD.c
 *
 *  Created on: Mar 30, 2024
 *      Author: Ahmed Salah
 */

/***************************************************INCLUDE******************************************************/
#include "LCD.h"
#include "GPIO.h"
#include "RCC_01.h"

/****************************************************************************************************************/
/****************************************************DEFINE******************************************************/
#define LCD_OFF					0
#define LCD_INIT				1
#define LCD_OPERATIONAL			2
#define LCD_STATE_INIT_VALUE	55


/****************************************************************************************************************/
/*****************************************************TYPES******************************************************/

/****************************************************************************************************************/
/*****************************************************VARIABLES**************************************************/
/* globL variable that holds the state of the LCD
 * there is three states
 * 1- LCD_INIT
 * 2- LCD_OPERATIONAL
 * 3- LCD_OFF
 * */
static u8 LCD_STATE = LCD_INIT ;

 u8 Counter = 0 ;


extern LCD_Pins_Cfg_t LCD_Pins_arr[_MAX_PIN_NUM] ;

static User_Req_t Loc_Req = {
			.Str= NULL,
			.Len = 0,
			.X_Pos = 0,
			.Y_Pos = 0,
			.Req_State = No_Request,
			.Req_Type = None
		};

/****************************************************************************************************************/
/**********************************************STATIC FUNCTIONS PROTOTYPE****************************************/
static void LCD_Init_Pins(void) ;
static void LCD_Send_Command(u8 Copy_Command) ;
static void LCD_Send_Data(u8 Copy_Data) ;
static void LCD_Write_Process(void) ;
static void LCD_Clear_Process(void) ;
static void LCD_Set_Crsor_Process(void) ;
static void LCD_Init_SM(void) ;
void LCD_Runnable(void) ;


/****************************************************************************************************************/
/***************************************************IMPELEMENTATION**********************************************/
void LCD_Runnable(void)
{

	if(LCD_STATE == LCD_INIT)
	{
		LCD_Init_SM();
	}

	else if( (LCD_STATE == LCD_OPERATIONAL))
	{
		Counter += TICK_TIME ;
		switch(Loc_Req.Req_Type)
		{
		case Write :
			if(Loc_Req.Len != 0)
			{
				LCD_Write_Process();
			}
			else
			{
				Counter = 0 ;
				Loc_Req.Req_State = No_Request ;
			}

			break ;

		case Clear :
			if(Counter == 1)
			{
				LCD_Clear_Process();
			}
			else {/* do nothing */}
			if(Counter == 2)
			{
				LCD_Clear_Process();
			}
			else if(Counter == 4)
			{
				Counter = 0 ;
				Loc_Req.Req_State = No_Request ;
			}
			else {/* do nothing */}
			break ;

		case Set_Cursor :
			if(Counter == 1)
			{
				LCD_Set_Crsor_Process();
			}
			else {/* do nothing */}
			if(Counter == 2)
			{
				LCD_Set_Crsor_Process();
				Counter = 0 ;
				Loc_Req.Req_State = No_Request ;
			}
			else {/* do nothing */}
			break ;

		default :
			Counter = 0 ;
			break ;
		}
	}

}

/* Every 2 ms */
void LCD_Init_SM(void)
{
	static Enu_Init_Operation_t Init_Operation = Power_On ;
	Counter += TICK_TIME ;

	switch(Init_Operation)
	{
	case Power_On :
		if(Counter==1)
		{
			LCD_Init_Pins();
		}
		else {/* do nothing */}

		if(Counter==30)
		{
			Init_Operation = Functional_Set ;
			Counter = 0 ;
		}
		else {/* do nothing */}
		break ;

	case Functional_Set :
		if(Counter == 1)
		{
			LCD_Send_Command(FUNCTION_SET_COMMAND);
		}
		else {/* do nothing */}
		if(Counter == 2)
		{
			LCD_Send_Command(FUNCTION_SET_COMMAND);
			Init_Operation = Display_On_Off ;
			Counter = 0 ;
		}

		break ;

	case Display_On_Off :
		if(Counter == 1)
		{
			LCD_Send_Command(DISPLAY_ON_OFF_COMMAND);
		}
		else {/* do nothing */}
		if(Counter == 2)
		{
			LCD_Send_Command(DISPLAY_ON_OFF_COMMAND);
			Init_Operation = Display_Clear ;
			Counter = 0 ;
		}
		else {/* do nothing */}

		break ;

	case Display_Clear :
		if(Counter == 1)
		{
			LCD_Send_Command(DISPLAY_CLEAR_COMMAND);

		}
		else {/* do nothing */}
		if(Counter == 2)
		{
			LCD_Send_Command(DISPLAY_CLEAR_COMMAND);
			Init_Operation = Entry_Mode ;
			Counter = 0 ;
		}
		else {/* do nothing */}
		break ;

	case Entry_Mode :
		if(Counter == 1)
		{
			LCD_Send_Command(ENTRY_MODE_COMMAND);

		}
		else {/* do nothing */}
		if(Counter == 2)
		{
			LCD_Send_Command(ENTRY_MODE_COMMAND);
			Init_Operation = End_Of_Init ;
			Counter = 0 ;
		}
		else {/* do nothing */}
		break ;

	case End_Of_Init :
		LCD_STATE = LCD_OPERATIONAL ;
		Counter = 0 ;
		break;
	default :
		break;
	}

}

LCD_Return_Error_Status_t LCD_Write_String_Async( char *Add_String , u16 Copy_Length )
{
	LCD_Return_Error_Status_t Loc_Error_Status = LCD_OK ;
	if(Add_String == NULL)
	{
		Loc_Error_Status = LCD_NULL_POINTER ;
	}
	else
	{
			if( (Loc_Req.Req_State == No_Request) && (LCD_STATE == LCD_OPERATIONAL) )
			{
				Loc_Req.Req_State = In_Progress ;
				Loc_Req.Str = Add_String ;
				Loc_Req.Len = Copy_Length ;
				Loc_Req.Req_Type = Write ;
			}
			else
			{
				Loc_Error_Status = LCD_NOK ;

			}
	}
	return Loc_Error_Status ;
}

void LCD_Set_XY_Pos_Async( u8 Copy_X_Pos , u8 Copy_Y_Pos)
{
	if( (Loc_Req.Req_State == No_Request) && (LCD_STATE == LCD_OPERATIONAL) )
				{
					Loc_Req.Req_State = In_Progress ;
					Loc_Req.X_Pos = Copy_X_Pos ;
					Loc_Req.Y_Pos = Copy_Y_Pos ;
					Loc_Req.Req_Type = Set_Cursor ;
				}
	else {/* do nothing */}
}

void LCD_Clear_Async(void)
{
	if( (Loc_Req.Req_State == No_Request) && (LCD_STATE == LCD_OPERATIONAL) )
					{
					Loc_Req.Req_State = In_Progress ;
					Loc_Req.Req_Type = Clear ;
					}
	else {/* do nothing */}
}


static void LCD_Init_Pins(void)
{
	    u8 Loc_Iterator = 0;
		GPIO_Pin_Confg_t Loc_LCD ;
		Loc_LCD.GPIOMode=GPIO_MODE_OUTPUT_PP ;
		Loc_LCD.GPIOSpeed= GPIO_Speed_High ;

		for(Loc_Iterator=0 ; Loc_Iterator < _MAX_PIN_NUM ; Loc_Iterator++)
		{
			Loc_LCD.GPIO_Port=LCD_Pins_arr[Loc_Iterator].Port ;
			Loc_LCD.GPIOPin=LCD_Pins_arr[Loc_Iterator].Pin;
			GPIO_Configure_Pin_Init(&Loc_LCD);

		}
}

static void LCD_Send_Command(u8 Copy_Command)
{
	if((Counter % 2) != 0)
		{
        /*Set RW pin to write*/
	    GPIO_Set_Pin_Value(LCD_Pins_arr[READ_WRITE_PIN].Port,LCD_Pins_arr[READ_WRITE_PIN].Pin,GPIO_PIN_LOW);

		/*Set Rs pin to command*/
	    GPIO_Set_Pin_Value(LCD_Pins_arr[REGISTER_SELSECT_PIN].Port,LCD_Pins_arr[REGISTER_SELSECT_PIN].Pin,GPIO_PIN_LOW);

	    //0b00111000
		/*Send the command to the LCD*/

	    GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN0].Port,LCD_Pins_arr[DATA_PIN0].Pin, (u32)(1 & (Copy_Command >> DATA_PIN0)) );
	    GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN1].Port,LCD_Pins_arr[DATA_PIN1].Pin, (u32)(1 & (Copy_Command >> DATA_PIN1)) );
	    GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN2].Port,LCD_Pins_arr[DATA_PIN2].Pin, (u32)(1 & (Copy_Command >> DATA_PIN2)) );
	    GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN3].Port,LCD_Pins_arr[DATA_PIN3].Pin, (u32)(1 & (Copy_Command >> DATA_PIN3)) );
	    GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN4].Port,LCD_Pins_arr[DATA_PIN4].Pin, (u32)(1 & (Copy_Command >> DATA_PIN4)) );
	    GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN5].Port,LCD_Pins_arr[DATA_PIN5].Pin, (u32)(1 & (Copy_Command >> DATA_PIN5)) );
	    GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN6].Port,LCD_Pins_arr[DATA_PIN6].Pin, (u32)(1 & (Copy_Command >> DATA_PIN6)) );
	    GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN7].Port,LCD_Pins_arr[DATA_PIN7].Pin, (u32)(1 & (Copy_Command >> DATA_PIN7)) );

		/*Enable pulse*/
	    GPIO_Set_Pin_Value(LCD_Pins_arr[ENABLE_PIN].Port,LCD_Pins_arr[ENABLE_PIN].Pin,GPIO_PIN_HIGH);
		}

	else if((Counter % 2) == 0)
			{
		        GPIO_Set_Pin_Value(LCD_Pins_arr[ENABLE_PIN].Port,LCD_Pins_arr[ENABLE_PIN].Pin,GPIO_PIN_LOW);
		        //Counter = 0 ;
			}
	else {/* do nothing */}

}

static void LCD_Send_Data(u8 Copy_Data)
{

	if((Counter % 2) != 0)
	{
		    /*Set RW pin to write*/
			GPIO_Set_Pin_Value(LCD_Pins_arr[READ_WRITE_PIN].Port,LCD_Pins_arr[READ_WRITE_PIN].Pin,GPIO_PIN_LOW);

			/*Set Rs pin to data*/
			GPIO_Set_Pin_Value(LCD_Pins_arr[REGISTER_SELSECT_PIN].Port,LCD_Pins_arr[REGISTER_SELSECT_PIN].Pin,GPIO_PIN_HIGH);

			/*Send the data to the LCD*/
			GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN0].Port,LCD_Pins_arr[DATA_PIN0].Pin, (u32)(1 & (Copy_Data >> DATA_PIN0)) );
			GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN1].Port,LCD_Pins_arr[DATA_PIN1].Pin, (u32)(1 & (Copy_Data >> DATA_PIN1)) );
			GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN2].Port,LCD_Pins_arr[DATA_PIN2].Pin, (u32)(1 & (Copy_Data >> DATA_PIN2)) );
			GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN3].Port,LCD_Pins_arr[DATA_PIN3].Pin, (u32)(1 & (Copy_Data >> DATA_PIN3)) );
			GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN4].Port,LCD_Pins_arr[DATA_PIN4].Pin, (u32)(1 & (Copy_Data >> DATA_PIN4)) );
			GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN5].Port,LCD_Pins_arr[DATA_PIN5].Pin, (u32)(1 & (Copy_Data >> DATA_PIN5)) );
			GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN6].Port,LCD_Pins_arr[DATA_PIN6].Pin, (u32)(1 & (Copy_Data >> DATA_PIN6)) );
			GPIO_Set_Pin_Value(LCD_Pins_arr[DATA_PIN7].Port,LCD_Pins_arr[DATA_PIN7].Pin, (u32)(1 & (Copy_Data >> DATA_PIN7)) );

			/*Enable pulse*/
			GPIO_Set_Pin_Value(LCD_Pins_arr[ENABLE_PIN].Port,LCD_Pins_arr[ENABLE_PIN].Pin,GPIO_PIN_HIGH);

	}
	else if((Counter % 2) == 0)
	{
        GPIO_Set_Pin_Value(LCD_Pins_arr[ENABLE_PIN].Port,LCD_Pins_arr[ENABLE_PIN].Pin,GPIO_PIN_LOW);
		Loc_Req.Str++ ;
		Loc_Req.Len--;
	}
	else {/* do nothing */}
}

static void LCD_Write_Process(void)
{
	if(*Loc_Req.Str != 0)
	{
		LCD_Send_Data(*Loc_Req.Str);
	}
	else
	{

	}

}

static void LCD_Set_Crsor_Process(void)
{
	 u8 Loc_XY_Pos = 0 ;
	if(Loc_Req.X_Pos == LCD_FIRST_LINE)
	{
		Loc_XY_Pos = Loc_Req.Y_Pos ;
	}
	else if(Loc_Req.X_Pos == LCD_SECOND_LINE)
	{
		Loc_XY_Pos = 64 + Loc_Req.Y_Pos ;
	}
	else {/* do nothing */}

	LCD_Send_Command(Loc_XY_Pos + 128) ;

}

static void LCD_Clear_Process(void)
{
	LCD_Send_Command(DISPLAY_CLEAR_COMMAND);

}
/****************************************************************************************************************/


