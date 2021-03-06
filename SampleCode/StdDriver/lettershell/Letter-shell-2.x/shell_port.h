/*******************************************************************************
 * @file    shell_port.h
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
#ifndef __SHELL_PORT_H__
#define __SHELL_PORT_H__


#ifdef __cplusplus
extern "C" {
#endif


#undef  EXTERN


#ifdef  __SHELL_PORT_C__
#define EXTERN
#else
#define EXTERN extern
#endif




/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
EXTERN void shellPortInit(void);


#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/

