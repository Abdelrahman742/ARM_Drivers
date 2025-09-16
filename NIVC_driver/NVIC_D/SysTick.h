/*
 * SysTick.h
 *
 *  Created on: Jul 30, 2024
 *      Author: Abdelrahman Ibrahem Adel
 * Description: Header file of Systick driver
 */
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include"std_types.h"
/*********************************************************************
* Service Name: SysTick_Init
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): a_TimeInMilliSeconds - Number of the miliseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to initiate systick
**********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds);
/*********************************************************************
* Service Name: SysTick_StartBusyWait
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): a_TimeInMilliSeconds - Number of the miliseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to use polling
**********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);
/*********************************************************************
* Service Name: SysTick_Handler
* Sync/Async: ASynchronous
* Reentrancy: nonreentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to use interrupt
**********************************************************************/
void SysTick_Handler(void);
/*********************************************************************
* Service Name: SysTick_SetCallBack
* Sync/Async: Synchronous
* Reentrancy: nonreentrant
* Parameters (in): Ptr2Func -
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to use call back
**********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));
/*********************************************************************
* Service Name: SysTick_Stop
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to stop the systick
**********************************************************************/
void SysTick_Stop(void);
/*********************************************************************
* Service Name: SysTick_Start
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to start the systick
**********************************************************************/
void SysTick_Start(void);
/*********************************************************************
* Service Name: SysTick_DeInit
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Deinitiate the systick
**********************************************************************/
void SysTick_DeInit(void);

#endif /* SYSTICK_H_ */
