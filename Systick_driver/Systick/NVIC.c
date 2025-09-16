/*
 * NVIC.c
 *
 *  Created on: Jul 30, 2024
 *      Author: dell
 */
#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"
/*********************************************************************
* Service Name: NVIC_EnableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    //EN0
    if (IRQ_Num < 32)
    {
        NVIC_EN0_REG |= (1 << IRQ_Num);
    }
    //EN1
    else if (IRQ_Num < 64)
    {
        NVIC_EN1_REG |= (1 << (IRQ_Num - 32));
    }
    //EN2
    else if (IRQ_Num < 96)
    {
        NVIC_EN2_REG |= (1 << (IRQ_Num - 64));
    }
    //EN3
    else if (IRQ_Num < 128)
    {
        NVIC_EN3_REG |= (1 << (IRQ_Num - 96));
    }
    //EN4
    else
    {
        NVIC_EN4_REG |= (1 << (IRQ_Num - 128));
    }
}
/*********************************************************************
* Service Name: NVIC_DisableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    //DIS0
    if (IRQ_Num < 32)
    {
        NVIC_DIS0_REG |= (1 << IRQ_Num);
    }
    //DIS1
    else if (IRQ_Num < 64)
    {
        NVIC_DIS1_REG |= (1 << (IRQ_Num - 32));
    }
    //DIS2
    else if (IRQ_Num < 96)
    {
        NVIC_DIS2_REG |= (1 << (IRQ_Num - 64));
    }
    //DIS3
    else if (IRQ_Num < 128)
    {
        NVIC_DIS3_REG |= (1 << (IRQ_Num - 96));
    }
    //DIS4
    else
    {
        NVIC_DIS4_REG |= (1 << (IRQ_Num - 128));
    }
}
/*********************************************************************
* Service Name: NVIC_SetPriorityIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table,IRQ_Priority -priority for IRQ
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to make priority for specific IRQ
**********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num,NVIC_IRQPriorityType IRQ_Priority)
{
    uint8 registerIndex = IRQ_Num / 4;
    uint8 priorityShift = (IRQ_Num % 4) * 8 + 5;
    volatile uint32 *priorityRegister = (volatile uint32 *)(&NVIC_PRI0_REG + registerIndex);

    *priorityRegister = (*priorityRegister & ~(0x1F << priorityShift)) | (IRQ_Priority << priorityShift);
}
/*********************************************************************
* Service Name: NVIC_EnableException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Exception_Num - Number of the Exception from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to enable for specific exception
**********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    if(Exception_Num==EXCEPTION_MEM_FAULT_TYPE) /* Memory Management Fault */
    {
        NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num==EXCEPTION_BUS_FAULT_TYPE) /* Bus Fault */
    {
        NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num==EXCEPTION_USAGE_FAULT_TYPE) /* Usage Fault */
    {
        NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num==EXCEPTION_PEND_SV_TYPE) /* Pend The PendSV */
    {
        NVIC_SYSTEM_INTCTRL |= (1<<28);
    }
}
/*********************************************************************
* Service Name: NVIC_DisableException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Exception_Num - Number of the Exception from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable for specific exception
**********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    if(Exception_Num==EXCEPTION_MEM_FAULT_TYPE) /* Memory Management Fault */
    {
        NVIC_SYSTEM_SYSHNDCTRL &= ~MEM_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num==EXCEPTION_BUS_FAULT_TYPE) /* Bus Fault */
    {
        NVIC_SYSTEM_SYSHNDCTRL &= ~BUS_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num==EXCEPTION_USAGE_FAULT_TYPE) /* Usage Fault */
    {
        NVIC_SYSTEM_SYSHNDCTRL &= ~USAGE_FAULT_ENABLE_MASK;
    }
    else if(Exception_Num==EXCEPTION_PEND_SV_TYPE) /* UnPend The PendSV */
    {
        NVIC_SYSTEM_INTCTRL |= (1<<27);
    }
}
/*********************************************************************
* Service Name: NVIC_SetPriorityIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Exception_Num - Number of the exception from the target vector table,Exception_Priority -priority for exception
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to make priority for specific exception
**********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num,NVIC_ExceptionPriorityType Exception_Priority)
{
    if(Exception_Num==EXCEPTION_MEM_FAULT_TYPE) /* Memory Management Fault */
    {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & 0xFFFFFF1F) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
    }
    else if(Exception_Num==EXCEPTION_BUS_FAULT_TYPE) /* Bus Fault */
    {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & 0xFFFF1FFF) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
    }
    else if(Exception_Num==EXCEPTION_USAGE_FAULT_TYPE) /* Usage Fault */
    {
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & 0xFF1FFFFF) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
    }
    else if(Exception_Num==EXCEPTION_SVC_TYPE) /* SVC */
    {
        NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & 0x1FFFFFFF) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
    }
    else if(Exception_Num==EXCEPTION_DEBUG_MONITOR_TYPE) /* Debug Monitor */
    {
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & 0xFFFFFF1F) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
    }
    else if(Exception_Num==EXCEPTION_PEND_SV_TYPE) /* PendSV */
    {
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & 0xFF1FFFFF) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
    }
    else if(Exception_Num==EXCEPTION_SYSTICK_TYPE) /* SysTick Timer */
    {
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & 0x1FFFFFFF) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
    }
}
