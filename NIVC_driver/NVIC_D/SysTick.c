/*
 * SysTick.c
 *
 *  Created on: Jul 30, 2024
 *      Author: Abdelrahman Ibrahem Adel
 * Description: .c file in Systick driver
 */
#include "SysTick.h"
#include "tm4c123gh6pm_registers.h"

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

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
void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG = 0;
    SYSTICK_RELOAD_REG = ((16000*a_TimeInMilliSeconds)-1);
    SYSTICK_CURRENT_REG = 0;
    SYSTICK_CTRL_REG   |= 0x07;
}
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
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG = 0;
    SYSTICK_RELOAD_REG = ((16000*a_TimeInMilliSeconds)-1);
    SYSTICK_CURRENT_REG = 0;
    SYSTICK_CTRL_REG   |= 0x05;
    while(!(SYSTICK_CTRL_REG & (1<<16)));
}
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
void SysTick_Handler(void)
{
    if(g_callBackPtr != NULL_PTR)
    {
        (*g_callBackPtr)();
    }
}
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
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
{
    g_callBackPtr=Ptr2Func;
}
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
void SysTick_Stop(void)
{
    SYSTICK_CTRL_REG &=~(1<<0);
}
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
void SysTick_Start(void)
{
    SYSTICK_CTRL_REG |=(1<<0);
}
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
void SysTick_DeInit(void)
{
    SYSTICK_CTRL_REG = 0;
    SYSTICK_RELOAD_REG = 0;
    SYSTICK_CURRENT_REG = 0;
    g_callBackPtr = NULL_PTR;
}
