/*******************************************************************************
 * @file    task.h
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
#ifndef __TASK_H__
#define __TASK_H__


#ifdef __cplusplus
extern "C" {
#endif


#undef  EXTERN


#ifdef  __TASK_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "NuMicro.h"


/* Exported constants --------------------------------------------------------*/
#define TASK_ID_LED     0
#define TASK_ID_KEY     1
#define TASK_ID_LOG     2


/* Exported types ------------------------------------------------------------*/
typedef void(*Task_Handler)(void);


/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint8_t index;
    uint8_t ready;
    uint32_t tick;
    Task_Handler handler;
} TASK_InfoTypeDef;


/* Exported types ------------------------------------------------------------*/
typedef struct _Node_Struct
{
    TASK_InfoTypeDef info;
    struct _Node_Struct *next;
} LinkedList_TypeDef;


/* Exported macro ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
EXTERN void TASK_Append(uint8_t index, Task_Handler handler, uint32_t tick);
EXTERN void TASK_TimeSlice(uint32_t tick);
EXTERN void TASK_Scheduling(void);


#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/

