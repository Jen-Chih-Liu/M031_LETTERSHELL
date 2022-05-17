/*******************************************************************************
 * @file    shell_port.c
 * @author  King
 * @version V1.00
 * @date    16-Sep-2020
 * @brief   ......
 *******************************************************************************
 * @attention
 * 
 * THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
 * CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
 * TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
 * HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
 * CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
 * <H2><CENTER>&COPY; COPYRIGHT 2020 MINDMOTION </CENTER></H2>
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#define __SHELL_PORT_C__


/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "NuMicro.h"
#include "shell.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
SHELL_TypeDef shell;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/


/*******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
*******************************************************************************/
void shellPortWrite(const char ch)
{
    while(DEBUG_PORT->FIFOSTS & UART_FIFOSTS_TXFULL_Msk);

    DEBUG_PORT->DAT = ch;
}


/*******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
*******************************************************************************/
void shellPortInit(void)
{
    
    shell.write = shellPortWrite;
    shellInit(&shell);
}


/*---------------------------------------------------------------------------------------------------------*/
/* ISR to handle UART Channel 0 interrupt event                                                            */
/*---------------------------------------------------------------------------------------------------------*/
void UART02_IRQHandler(void)
{
	uint8_t u8InChar = 0xFF;

   if (UART_GET_INT_FLAG(UART0,UART_INTSTS_RDAINT_Msk))
   {  
		  u8InChar = UART_READ(UART0);
		  shellHandler(&shell, u8InChar);
	 }
}

/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/

