/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 18/07/16 10:25a $
 * @brief
 *           Transmit and receive data from PC terminal through RS232 interface.
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "stdio.h"
#include "NuMicro.h"
#include "shell.h"
#include "shell_port.h"
#include "task.h"
#include "malloc.h"
void SYS_Init(void)
{

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable HIRC clock (Internal RC 48MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Wait for HIRC clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Select HCLK clock source as HIRC and HCLK clock divider as 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    /* Set both PCLK0 and PCLK1 as HCLK */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV1 | CLK_PCLKDIV_APB1DIV_DIV1;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HIRC and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set PB multi-function pins for UART0 RXD=PB.12 and TXD=PB.13 */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk))    |       \
                    (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
}

void UART0_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART0 */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

void funca(int i, char ch, char *str)
{
    printf("input int: %d, char: %c, string: %s\r\n", i, ch, str);
}
uint32_t SysTick_Tick = 0;
uint32_t SysDelayTick = 0;
void SysTick_Handler(void)             
{
   SysTick_Tick++;
    TASK_TimeSlice(SysTick_Tick);

    if(SysDelayTick)
    {
        SysDelayTick--;
    }
}

void config_systick(uint32_t us)  
{
    SysTick->LOAD =  (24*us)-1;      //systick clock=hclk/2=48000000/2=24000000;        
    SysTick->VAL   =     0;                  
    SysTick->CTRL  |=  SysTick_CTRL_TICKINT_Msk   | SysTick_CTRL_ENABLE_Msk; 	
    NVIC_SetPriority(SysTick_IRQn, 0);
}
#define TASK_ID_PRINT   0

unsigned i=0;
void printf_task(void)
{
	i++;
	printf("%d\n\r",i);
}
 
SHELL_EXPORT_CMD(funca, funca, test function);
/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();
    my_mem_init(0); //initial memory
    /* Lock protected registers */
    SYS_LockReg();
     config_systick(1000); //1ms
    /* Init UART0 for printf and test */
    UART0_Init();
    NVIC_EnableIRQ(UART02_IRQn);
    UART_EnableInt(UART0, (UART_INTEN_RDAIEN_Msk));
    shellPortInit();

		TASK_Append(TASK_ID_PRINT, printf_task, 1000);
    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);

    while(1)
    {
        TASK_Scheduling();
    }

    while (1);

}

