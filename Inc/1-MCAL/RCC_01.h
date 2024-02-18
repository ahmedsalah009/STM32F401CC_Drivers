/*
 * RCC_01.h
 *
 *  Created on: Feb 16, 2024
 *      Author: Ahmed Salah
 */

#ifndef RCC_01_H_
#define RCC_01_H_

/************************************************* DEFINE ****************************************************/
#define CLK_HSI							0x1
#define CLK_HSE							0x10000
#define CLK_PLL							0x1000000

#define PLL_SRC_HSI 					0xFFBFFFFF
#define PLL_SRC_HSE  					0x400000

#define CLK_STATE_ENABLE    			1
#define CLK_STATE_DISABLE   			0

#define SYSCLK_HSI 						0x0
#define SYSCLK_HSE						0x1
#define SYSCLK_PLL						0x2

#define PERIPHERAL_STATE_DISABLE    	0
#define PERIPHERAL_STATE_ENABLE     	1
/* options to enable and disable Peripherals on AHB1 bus */
#define       RCC_GPIOA			 1
#define       RCC_GPIOB			 2
#define       RCC_GPIOC          4
#define       RCC_CRCE           12
#define       RCC_DMA1E          21
#define       RCC_DMA2E			 22

/* options to enable and disable Peripherals on AHB2 bus */
#define       RCC_OTGFS	         39

/* options to enable and disable Peripherals on APB1 bus */
#define      RCC_PWREN		    92
#define      RCC_I2C3		    87
#define      RCC_I2C2		    86
#define      RCC_I2C1		    85
#define      RCC_USART2		    81
#define      RCC_SPI3		    79
#define      RCC_SPI2		    78
#define      RCC_WWDG		    75
#define      RCC_TIM5		    67
#define      RCC_TIM4		    66
#define      RCC_TIM3		    65
#define      RCC_TIM2		    64

/* options to enable and disable Peripherals on APB2 bus */
#define      RCC_TIM11		    114
#define      RCC_TIM10		    113
#define      RCC_TIM9		    112
#define      RCC_SPI4		    110
#define      RCC_SPI1		    109
#define      RCC_SDIO		    108
#define      RCC_ADC1		    107
#define      RCC_USART6		    101
#define      RCC_USART1		    100
#define      RCC_TIM1		    96
//#define APB2_ENR_SYSCFGEN
/**************************************************************************************************************/

/************************************************* TYPES ******************************************************/
typedef unsigned char u8 ;
typedef unsigned int  u32;

typedef enum {
	RCC_NOK=0 ,
	RCC_OK,
	RCC_NULL_POINTER,
	RCC_WRONG_CONFIGURATION_VALUE
}RCC_Return_ErrorState_t;

typedef struct {
		u32 CR;
	    u32 PLLCFGR;
	    u32 CFGR;
	    u32 CIR;
	    u32 AHB1RSTR;
	    u32 AHB2RSTR;
	    u32 reserved1[2];
	    u32 APB1RSTR;
	    u32 APB2RSTR;
	    u32 reserved2[2];
	    u32 AHB1ENR;
	    u32 AHB2ENR;
	    u32 reserved3[2];
	    u32 APB1ENR;
	    u32 APB2ENR;
	    u32 reserved4[2];
	    u32 AHB1LPENR;
	    u32 AHB2LPENR;
	    u32 reserved5[2];
	    u32 APB1LPENR;
	    u32 APB2LPENR;
	    u32 reserved6[2];
	    u32 BDCR;
	    u32 CSR;
	    u32 reserved7[2];
	    u32 SSCGR;
	    u32 RCC_PLLI2SCFGR;
	    u32 reserved8;
	    u32 DCKCFGR;

}RCC_Peri_t;

/**************************************************************************************************************/
/*********************************************** APIs PROTOTYPE ***********************************************/

/**
 * @brief   : function to enable a clock on the system
 * @options :
 * 1-HSI
 * 2-HSE
 * 3-PLL
 * 4-LSI
 * 5-LSE
 * @return  : if return equal 0 this means its NOT OK and if its 1 it means it is OKAY
 */
RCC_Return_ErrorState_t RCC_Enable_Clk(u32 CLK);

/**
 * @brief   : function to Disable a clock on the system
 * @options :
 * 1-HSI
 * 2-HSE
 * 3-PLL
 * 4-LSI
 * 5-LSE
 * @return  : if return equal 0 this means its NOT OK and if its 1 it means it is OKAY
 */
RCC_Return_ErrorState_t RCC_DISABLE_Clk(u32 CLK);


/**
  * @brief      : function to set the clock source for system
  * @options    :
  * 		      1-SYSCLK_HSI
  * 		      2-SYSCLK_HSE
  * 		      3-SYSCLK_PLL
  * @constrains : before choosing any source  make sure it is on and ready
  * @return     : if return equal 0 this means its NOT OK and if its 1 it means it is OKAY
  */
RCC_Return_ErrorState_t RCC_Set_SYSCLK(u32 SYSCLK);

/**
  * @brief      : function to set the clock source for 	PLL
  * @options    :
  *               1-PLL_SRC_HSI
  *               2-PLL_SRC_HSE
  * @constrains : before choosing any source for PLL make sure it is ON and READY
  * @return  : if return equal 0 this means its NOT OK and if its 1 it means it is OKAY
  */
RCC_Return_ErrorState_t RCC_Set_PLL_SOURCE_CLK(u32 PLL_SRC_CLK);

/**
  * @brief     : function to get the source clock
  * @parameter : pointer to local variable to return the source clock value in it
  * @options   :
  *              1-HSI represented by 0
  *              2-HSE represented by 1
  *              3-PLL represented by 2
  * @return     : if return equal 0 this means its NOT OK and if its 1 it means it is OKAY
  *               if return equal 2 this means NULL pointer
  */
RCC_Return_ErrorState_t RCC_Get_SYSCLK(u32 *Add_SYSCLK);

/**
  * @brief     : function to get the source clock for PLL
  * @parameter : pointer to local variable to return the  PLL source clock value in it
  * @options   :
  *              1-HSI represented by 0
  *              2-HSE represented by any number else
  * @return     : if return equal 0 this means its NOT OK and
  *               if its 1 it means it is OKAY
  *               if return equal 2 this means NULL pointer
  */
RCC_Return_ErrorState_t RCC_Get_PLL_SOURCE_CLK(u32 *Add_PLL_SOURCE_CLK);

/**
  * @brief     : function to get configure PLL clock
  * @parameters : 1-PLLM -> 2=<PLLM>=63
  *				: 2-PLLN -> 192=<PLLM>=432
  * 			  3-PLLP -> PLLP = 2 , 4 , 6 OR 8
  * @return     : if return equal 0 this means its NOT OK and
  *               if its 1 it means it is OKAY
  *               if return equal 3 this means WRONG CONFIGURATION VALUE FOR PLL
  */
RCC_Return_ErrorState_t RCC_Config_PLL(u32 PLLM , u32 PLLN , u32 PLLP);

/**
  * @brief                   :  function to enable an peripheral  ON AHB1 , AHB2 , APB1 OR APB2 BUS
  * @options for peripherals :
                               1-RCC_GPIOA	  11-RCC_I2C1	    21-RCC_TIM10
                               2-RCC_GPIOB	  12-RCC_USART2     22-RCC_TIM9
 	                           3-RCC_GPIOC    13-RCC_SPI3	    23-RCC_SPI4
 	                           4-RCC_CRCE     14-RCC_SPI2	    24-RCC_SPI1
 	                           5-RCC_DMA1E    15-RCC_WWDG	    25-RCC_SDIO
 	                           6-RCC_DMA2E	  16-RCC_TIM5	    26-RCC_ADC1
 	                           7-RCC_OTGFS    17-RCC_TIM4	    27-RCC_USART6
 	                           8-RCC_PWREN	  18-RCC_TIM3	    28-RCC_USART1
                               9-RCC_I2C3	  19-RCC_TIM2	    29-RCC_TIM1
                               10-RCC_I2C2	  20-RCC_TIM11

   * @return                 : if return equal 0 this means its NOT OK and if its 1 it means it is OKAY
   */
RCC_Return_ErrorState_t RCC_Enable_Peripherals(u32 RCC_PERIPHERAL);

/**
  * @brief                   :  function to disable an peripheral  ON AHB1 , AHB2 , APB1 OR APB2 BUS
  * @options for peripherals :
                               1-RCC_GPIOA	  11-RCC_I2C1	    21-RCC_TIM10
                               2-RCC_GPIOB	  12-RCC_USART2     22-RCC_TIM9
 	                           3-RCC_GPIOC    13-RCC_SPI3	    23-RCC_SPI4
 	                           4-RCC_CRCE     14-RCC_SPI2	    24-RCC_SPI1
 	                           5-RCC_DMA1E    15-RCC_WWDG	    25-RCC_SDIO
 	                           6-RCC_DMA2E	  16-RCC_TIM5	    26-RCC_ADC1
 	                           7-RCC_OTGFS    17-RCC_TIM4	    27-RCC_USART6
 	                           8-RCC_PWREN	  18-RCC_TIM3	    28-RCC_USART1
                               9-RCC_I2C3	  19-RCC_TIM2	    29-RCC_TIM1
                               10-RCC_I2C2	  20-RCC_TIM11

   * @return                 : if return equal 0 this means its NOT OK and if its 1 it means it is OKAY
   */
RCC_Return_ErrorState_t RCC_DISABLE_Peripherals(u32 RCC_PERIPHERAL) ;

/**
  * @brief                   :  function to enable an peripheral  ON LOW POWER MODE on AHB1LP , AHB2LP , APB1LP OR APB2LP BUS
  * @options for peripherals :
                               1-RCC_GPIOA	  11-RCC_I2C1	    21-RCC_TIM10
                               2-RCC_GPIOB	  12-RCC_USART2     22-RCC_TIM9
 	                           3-RCC_GPIOC    13-RCC_SPI3	    23-RCC_SPI4
 	                           4-RCC_CRCE     14-RCC_SPI2	    24-RCC_SPI1
 	                           5-RCC_DMA1E    15-RCC_WWDG	    25-RCC_SDIO
 	                           6-RCC_DMA2E	  16-RCC_TIM5	    26-RCC_ADC1
 	                           7-RCC_OTGFS    17-RCC_TIM4	    27-RCC_USART6
 	                           8-RCC_PWREN	  18-RCC_TIM3	    28-RCC_USART1
                               9-RCC_I2C3	  19-RCC_TIM2	    29-RCC_TIM1
                               10-RCC_I2C2	  20-RCC_TIM11

   * @return                 : if return equal 0 this means its NOT OK and if its 1 it means it is OKAY
   */
RCC_Return_ErrorState_t RCC_Enable_LowPower_Peripherals(u32 RCC_PERIPHERAL);

/**
  * @brief                   :  function to disable an peripheral  ON LOW POWER MODE on AHB1LP , AHB2LP , APB1LP OR APB2LP BUS
  * @options for peripherals :
                               1-RCC_GPIOA	  11-RCC_I2C1	    21-RCC_TIM10
                               2-RCC_GPIOB	  12-RCC_USART2     22-RCC_TIM9
 	                           3-RCC_GPIOC    13-RCC_SPI3	    23-RCC_SPI4
 	                           4-RCC_CRCE     14-RCC_SPI2	    24-RCC_SPI1
 	                           5-RCC_DMA1E    15-RCC_WWDG	    25-RCC_SDIO
 	                           6-RCC_DMA2E	  16-RCC_TIM5	    26-RCC_ADC1
 	                           7-RCC_OTGFS    17-RCC_TIM4	    27-RCC_USART6
 	                           8-RCC_PWREN	  18-RCC_TIM3	    28-RCC_USART1
                               9-RCC_I2C3	  19-RCC_TIM2	    29-RCC_TIM1
                               10-RCC_I2C2	  20-RCC_TIM11

   * @return                 : if return equal 0 this means its NOT OK and if its 1 it means it is OKAY
   */
RCC_Return_ErrorState_t RCC_Disable_LowPower_Peripherals(u32 RCC_PERIPHERAL);



/**************************************************************************************************************/



#endif /* RCC_01_H_ */
