/*******************************************************************************
 * @file    task.c
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
#define __TASK_C__


/* Includes ------------------------------------------------------------------*/
#include "task.h"
#include "malloc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
LinkedList_TypeDef *head;


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
void LinkedList_AppendNode(TASK_InfoTypeDef info)
{
    LinkedList_TypeDef *node = head;

    if(head == NULL)
    {
        head = (LinkedList_TypeDef *)mymalloc(0,sizeof(LinkedList_TypeDef));

        if(head == NULL)
        {
            myfree(0,head);
        }
        else
        {
            mymemcpy(&head->info, &info, sizeof(TASK_InfoTypeDef));
            head->next = NULL;
        }
    }
    else
    {
        while(node->next != NULL)
        {
            node = node->next;
        }

        node->next = (LinkedList_TypeDef *)mymalloc(0,sizeof(LinkedList_TypeDef));

        if(node->next != NULL)
        {
            node = node->next;

            mymemcpy(&node->info, &info, sizeof(TASK_InfoTypeDef));
            node->next = NULL;
        }
        else
        {
            myfree(0, node->next);
        }
    }
}


/*******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
*******************************************************************************/
uint8_t LinkedList_SearchNode(uint8_t index)
{
    LinkedList_TypeDef *node = head;

    while(node != NULL)
    {
        if(node->info.index == index)
        {
            return 1;
        }

        node = node->next;
    }

    return 0;
}


/*******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
*******************************************************************************/
void TASK_Append(uint8_t index, Task_Handler handler, uint32_t tick)
{
    TASK_InfoTypeDef info;

    info.index   = index;
    info.ready   = 0;
    info.tick    = tick;
    info.handler = handler;

    if(LinkedList_SearchNode(index) == 0)
    {
        LinkedList_AppendNode(info);
    }
    else
    {
        printf("\r\nDuplicate Task Index!!!");
    }
}


/*******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
*******************************************************************************/
void TASK_TimeSlice(uint32_t tick)
{
    LinkedList_TypeDef *node = head;

    while(node != NULL)
    {
        if((tick % node->info.tick) == 0)
        {
            node->info.ready = 1;
        }
        
        node = node->next;
    }
}


/*******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
*******************************************************************************/
void TASK_Scheduling(void)
{
    LinkedList_TypeDef *node = head;

    while(node != NULL)
    {
        if(node->info.ready)
        {
            node->info.ready = 0;
            node->info.handler();
        }

        node = node->next;
    }
}


/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/

