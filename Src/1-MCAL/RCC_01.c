/*
 * RCC_01.c
 *
 *  Created on: Feb 16, 2024
 *      Author: Ahmed Salah
 */


/***************************************************INCLUDE******************************************************/
#include "RCC_01.h"
/****************************************************************************************************************/
/****************************************************DEFINE******************************************************/
#define RCC_BASE_ADDRESS		0x40023800
#define SYSCLK_RESET	        0xFFFFFFFC
#define SWS_MASK                0xC
#define PLL_SRC_MASK            0x400000
#define PLL_M_N_P_MASK          0xFFFC8000

#define HSI_RDY_MASK			0x2
#define HSE_RDY_MASK			0x20000
#define PLL_RDY_MASK			0x2000000

/****************************************************************************************************************/
/*****************************************************TYPES******************************************************/
#define NULL ((void *)0)

/***************************************************************************************************************/
/*****************************************************VARIABLES*************************************************/
static RCC_Peri_t * const RCC=((RCC_Peri_t *)(RCC_BASE_ADDRESS));

/***************************************************************************************************************/
/**********************************************STATIC FUNCTIONS PROTOTYPE***************************************/

/***************************************************************************************************************/
/***************************************************IMPELEMENTATION*********************************************/
RCC_Return_ErrorState_t RCC_Enable_Clk(u32 CLK)
{
	u32 TIME_OUT = 1000 ;
	RCC_Return_ErrorState_t  Loc_ErrorState = RCC_OK ;
		switch(CLK)
		{
		case CLK_HSI :
			RCC->CR |= CLK ;
			while(!(RCC->CR & HSI_RDY_MASK ) && (TIME_OUT))
			{
				TIME_OUT--;
			}
			if(TIME_OUT == 0) {Loc_ErrorState = RCC_NOK;}
			else {}
				break ;

		case CLK_HSE :
			RCC->CR |= CLK ;
	    	while(!(RCC->CR & HSE_RDY_MASK ) && (TIME_OUT))
	    	{
	    		TIME_OUT--;
	    	}
	    	if(TIME_OUT == 0) {Loc_ErrorState = RCC_NOK;}
	    	else {}
					break ;
		case CLK_PLL :
			RCC->CR |= CLK ;
		    	while(!(RCC->CR & PLL_RDY_MASK ) && (TIME_OUT))
		    	{
		    		TIME_OUT--;
		    	}
		    	if(TIME_OUT == 0) {Loc_ErrorState = RCC_NOK;}
		    	else {}
					break ;

		default : Loc_ErrorState = RCC_NOK ;break ;
		}
	return Loc_ErrorState ;
}

RCC_Return_ErrorState_t RCC_DISABLE_Clk(u32 CLK)
{
	RCC_Return_ErrorState_t  Loc_ErrorState = RCC_OK ;
	if((RCC->CR & SWS_MASK) == CLK)
	{
		Loc_ErrorState = RCC_NOK;
	}
	else
	{
		switch(CLK)
		{
		case CLK_HSI :RCC->CR &=~ CLK  ; break ;
		case CLK_HSE :RCC->CR &=~ CLK  ; break ;
		case CLK_PLL :RCC->CR &=~ CLK  ; break ;
		default : Loc_ErrorState = RCC_NOK ;break ;
		}
	}
	return Loc_ErrorState ;
}


RCC_Return_ErrorState_t RCC_Set_SYSCLK(u32 Copy_SYSCLK)
{
	u32 TIME_OUT = 100000 ;
	RCC_Return_ErrorState_t  Loc_ErrorState = RCC_OK ;
	if( ((Copy_SYSCLK == SYSCLK_HSI) && ( (RCC->CR & CLK_HSI) == 0) ||
		((Copy_SYSCLK == SYSCLK_HSE) && ( (RCC->CR & CLK_HSE) == 0)) ||
		((Copy_SYSCLK == SYSCLK_PLL) && ( (RCC->CR & CLK_PLL) == 0)))
	  )
	{
		Loc_ErrorState = RCC_NOK ;
	}
	else
	{
		u32 Temp_Reg = RCC->CFGR ;
		Temp_Reg &= SYSCLK_RESET;
		Temp_Reg |= Copy_SYSCLK ;
		RCC->CFGR = Temp_Reg ;

		while( ( (RCC->CFGR & SWS_MASK) != Copy_SYSCLK ) && TIME_OUT )
			{
				TIME_OUT--;
			}
			if(TIME_OUT == 0) {Loc_ErrorState = RCC_NOK;}
			else {}
	}

	return Loc_ErrorState ;
}

RCC_Return_ErrorState_t RCC_Set_PLL_SOURCE_CLK(u32 PLL_SRC_CLK)
{
	RCC_Return_ErrorState_t  Loc_ErrorState = RCC_OK ;
	if((RCC->CR & SWS_MASK) == CLK_PLL)
		{
			Loc_ErrorState = RCC_NOK;
		}
	else
	{
		switch (PLL_SRC_CLK)
		{
		case PLL_SRC_HSI :
			if((RCC->CR & CLK_HSI) == 0)
		   {
			Loc_ErrorState = RCC_NOK;
		   }
		   else
	   	   {
			RCC->PLLCFGR &= PLL_SRC_CLK ;
	   	   }
		   break ;

		case PLL_SRC_HSE :
		    if((RCC->CR & CLK_HSE) == 0)
		   {
			Loc_ErrorState = RCC_NOK;
		   }
		   else
	   	   {
			RCC->PLLCFGR |= PLL_SRC_CLK ;
	   	   }
		break ;
		default : Loc_ErrorState = RCC_NOK ; break ;
		}
	}
	return Loc_ErrorState ;
}

RCC_Return_ErrorState_t RCC_Get_SYSCLK(u32 *Add_SYSCLK)
{
	RCC_Return_ErrorState_t  Loc_ErrorState = RCC_OK ;
	if(NULL==Add_SYSCLK)
	{
		Loc_ErrorState = RCC_NULL_POINTER ;
	}
	else
	{
		*Add_SYSCLK = RCC->CFGR & SWS_MASK ;
	}
	return Loc_ErrorState ;
}

RCC_Return_ErrorState_t RCC_Get_PLL_SOURCE_CLK(u32 *Add_PLL_SOURCE_CLK)
{
	RCC_Return_ErrorState_t  Loc_ErrorState = RCC_OK ;
		if(NULL==Add_PLL_SOURCE_CLK)
		{
			Loc_ErrorState = RCC_NULL_POINTER ;
		}
		else
		{
			*Add_PLL_SOURCE_CLK = RCC->PLLCFGR & PLL_SRC_MASK ;
		}
		return Loc_ErrorState ;
}


RCC_Return_ErrorState_t RCC_Config_PLL(u32 PLLM , u32 PLLN , u32 PLLP)
{
	RCC_Return_ErrorState_t  Loc_ErrorState = RCC_OK ;
	if(PLLM < 2 || PLLM > 63) {Loc_ErrorState = RCC_WRONG_CONFIGURATION_VALUE ;}
	else if (PLLN < 192 || PLLN > 432) {Loc_ErrorState = RCC_WRONG_CONFIGURATION_VALUE ;}
	else if (PLLP < 2 || PLLP > 8 || PLLP%2 != 0)  {Loc_ErrorState = RCC_WRONG_CONFIGURATION_VALUE ;}
	else
	{
		u32 Temp_Reg = RCC->PLLCFGR ;
		Temp_Reg &= PLL_M_N_P_MASK ;
		Temp_Reg = Temp_Reg | (((PLLP/2)-1) << 16) | PLLM | (PLLN << 6 ) ;
		RCC->PLLCFGR = Temp_Reg ;
	}
	return Loc_ErrorState ;
}

RCC_Return_ErrorState_t RCC_Enable_Peripherals(u32 RCC_PERIPHERAL)
{
	RCC_Return_ErrorState_t  Loc_ErrorState = RCC_OK ;
	    if(RCC_PERIPHERAL == 0 || 1 || 2 || 12 || 21 || 22 || 39 || 64 || 65 || 66 || 67 || 75 || 78 || 79 || 81 || 85 || 86 || 87 || 92 || 96 || 100
	    		               || 101 || 107 || 108 || 109 || 110 || 112 || 113 || 114 )
	    {
	    	if(RCC_PERIPHERAL < 32)
	    		    		    {
	    		    		        RCC->AHB1ENR |= (1<<RCC_PERIPHERAL);
	    		    		    }
	    		    		    else if( 32 < RCC_PERIPHERAL && RCC_PERIPHERAL < 64)
	    		    		    {
	    		    		        RCC->AHB2ENR |= (1<< (RCC_PERIPHERAL - 32) );
	    		    		    }
	    		    		    else if( 64 < RCC_PERIPHERAL && RCC_PERIPHERAL < 96)
	    		    		    {
	    		    		        RCC->APB1ENR |= (1<< (RCC_PERIPHERAL - 64) );
	    		    		    }
	    		    		    else if( 96 < RCC_PERIPHERAL && RCC_PERIPHERAL < 128)
	    		    		    {
	    		    		        RCC->APB2ENR |= (1<< (RCC_PERIPHERAL - 96) );
	    		    		    }
	    		    		    else
	    		    		    {
	    		    		    	Loc_ErrorState = RCC_NOK;
	    		    		    }
	    }
	    else
	    {
	    	Loc_ErrorState = RCC_NOK;

	    }
	    return Loc_ErrorState;
}

RCC_Return_ErrorState_t RCC_DISABLE_Peripherals(u32 RCC_PERIPHERAL)
{
	RCC_Return_ErrorState_t  Loc_ErrorState = RCC_OK ;
	    if(RCC_PERIPHERAL == 0 || 1 || 2 || 12 || 21 || 22 || 39 || 64 || 65 || 66 || 67 || 75 || 78 || 79 || 81 || 85 || 86 || 87 || 92 || 96 || 100
	    		               || 101 || 107 || 108 || 109 || 110 || 112 || 113 || 114 )
	    {
	    	if(RCC_PERIPHERAL < 32)
	    		    		    {
	    		    		        RCC->AHB1ENR &= ~(1<<RCC_PERIPHERAL);
	    		    		    }
	    		    		    else if( 32 < RCC_PERIPHERAL && RCC_PERIPHERAL < 64)
	    		    		    {
	    		    		        RCC->AHB2ENR  &= ~(1<< (RCC_PERIPHERAL - 32) );
	    		    		    }
	    		    		    else if( 64 < RCC_PERIPHERAL && RCC_PERIPHERAL < 96)
	    		    		    {
	    		    		        RCC->APB1ENR  &= ~(1<< (RCC_PERIPHERAL - 64) );
	    		    		    }
	    		    		    else if( 96 < RCC_PERIPHERAL && RCC_PERIPHERAL < 128)
	    		    		    {
	    		    		        RCC->APB2ENR  &= ~(1<< (RCC_PERIPHERAL - 96) );
	    		    		    }
	    		    		    else
	    		    		    {
	    		    		    	Loc_ErrorState = RCC_NOK;
	    		    		    }
	    }
	    else
	    {
	    	Loc_ErrorState = RCC_NOK;

	    }
	    return Loc_ErrorState;
}

RCC_Return_ErrorState_t RCC_Enable_LowPower_Peripherals(u32 RCC_PERIPHERAL)
{
	 RCC_Return_ErrorState_t  Loc_ErrorState = RCC_OK ;
	 if(RCC_PERIPHERAL == 0 || 1 || 2 || 12 || 21 || 22 || 39 || 64 || 65 || 66 || 67 || 75 || 78 || 79 || 81 || 85 || 86 || 87 || 92 || 96 || 100
		    		               || 101 || 107 || 108 || 109 || 110 || 112 || 113 || 114 )
		    {
		 if(RCC_PERIPHERAL < 32)
		 		    		    {
		 		    		        RCC->AHB1LPENR |= (1<<RCC_PERIPHERAL);
		 		    		    }
		 		    		    else if( 32 < RCC_PERIPHERAL < 64)
		 		    		    {
		 		    		        RCC->AHB2LPENR |= (1<< (RCC_PERIPHERAL - 32) );
		 		    		    }
		 		    		    else if( 64 < RCC_PERIPHERAL < 96)
		 		    		    {
		 		    		        RCC->APB1LPENR |= (1<< (RCC_PERIPHERAL - 64) );
		 		    		    }
		 		    		    else if( 96 < RCC_PERIPHERAL < 128)
		 		    		    {
		 		    		        RCC->APB2LPENR |= (1<< (RCC_PERIPHERAL - 96) );
		 		    		    }
		 		    		    else
		 		    		    {
		 		    		    	Loc_ErrorState = RCC_NOK;
		 		    		    }
		    }
		    else
		    {
		    	Loc_ErrorState = RCC_NOK;

		    }
		    return Loc_ErrorState;
}


RCC_Return_ErrorState_t RCC_Disable_LowPower_Peripherals(u32 RCC_PERIPHERAL)
{
   	 RCC_Return_ErrorState_t  Loc_ErrorState = RCC_OK ;
	 if(RCC_PERIPHERAL == 1 || 2 || 4 || 12 || 21 || 22 || 39 || 64 || 65 || 66 || 67 || 75 || 78 || 79 || 81 || 85 || 86 || 87 || 92 || 96 || 100
		    		               || 101 || 107 || 108 || 109 || 110 || 112 || 113 || 114 )
		    {
		 if(RCC_PERIPHERAL < 32)
		 		    		    {
		 		    		        RCC->AHB1LPENR &= ~ (1<<RCC_PERIPHERAL);
		 		    		    }
		 		    		    else if( 32 < RCC_PERIPHERAL < 64)
		 		    		    {
		 		    		        RCC->AHB2LPENR &= ~ (1<< (RCC_PERIPHERAL - 32) );
		 		    		    }
		 		    		    else if( 64 < RCC_PERIPHERAL < 96)
		 		    		    {
		 		    		        RCC->APB1LPENR &= ~ (1<< (RCC_PERIPHERAL - 64) );
		 		    		    }
		 		    		    else if( 96 < RCC_PERIPHERAL < 128)
		 		    		    {
		 		    		        RCC->APB2LPENR &= ~ (1<< (RCC_PERIPHERAL - 96) );
		 		    		    }
		 		    		    else
		 		    		    {
		 		    		    	Loc_ErrorState = RCC_NOK;
		 		    		    }
		    }
		    else
		    {
		    	Loc_ErrorState = RCC_NOK;

		    }
		    return Loc_ErrorState;
}

/***************************************************************************************************************/

