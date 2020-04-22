/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_vector.c
* Author             : MCD Application Team
* Version            : V1.0
* Date               : 10/08/2007
* Description        : This file contains the vector table for STM32F10x.
*                      After Reset the Cortex-M3 processor is in Thread mode,
*                      priority is Privileged, and the Stack is set to Main.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern unsigned long _etext;
extern unsigned long _sidata;		/* start address for the initialization values
                                   of the .data section. defined in linker script */
extern unsigned long _sdata;		/* start address for the .data section. defined
                                   in linker script */
extern unsigned long _edata;		/* end address for the .data section. defined in
                                   linker script */

extern unsigned long _sbss;			/* start address for the .bss section. defined
                                   in linker script */
extern unsigned long _ebss;			/* end address for the .bss section. defined in
                                   linker script */



/* Private typedef -----------------------------------------------------------*/
/* function prototypes -------------------------------------------------------*/
void GCC_Reset_Handler(void) __attribute__((__interrupt__));
extern int user_main(void);


/*******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000 or the address you set in the link files.
*
*******************************************************************************/

__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
  0,//这里放一个0，是因为每次初始化的时候芯片会自动把向量表的第一个单位作为堆栈顶地址来取，我们不需要初始化堆栈所以这里设为空
  GCC_Reset_Handler,             // The reset handler
 };
 
/*******************************************************************************
* Function Name  : GCC_Reset_Handler
* Description    : This is the code that gets called when the processor first
*                  starts execution following a reset event. Only the absolutely
*                  necessary set is performed, after which the application
*                  supplied main() routine is called. 
* Input          :
* Output         :
* Return         :
*******************************************************************************/
void GCC_Reset_Handler(void)
{
    unsigned long *pulSrc, *pulDest;

    //
    // Copy the data segment initializers from flash to SRAM.
    //
    pulSrc = &_sidata;
    for(pulDest = &_sdata; pulDest < &_edata; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    //
    // Zero fill the bss segment.
    //
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }

    //
    // Call the application's entry point.
    //
    user_main();
}


/****************** (C) COPYRIGHT 2007 STMicroelectronics  *****END OF FILE****/


