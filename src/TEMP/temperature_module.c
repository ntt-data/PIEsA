/*
                             *******************
******************************* C SOURCE FILE *******************************
**                           *******************                           **
**                                                                         **
** project          : PIEsA                                                **
** filename         : rotary_module.c                                      **
** template version : 1                                                    **
** date             : 13 March, 2018                                       **
**                                                                         **
*****************************************************************************
**                                                                         **
** Copyright (c) 2018, NTT DATA Romania                                    **
** All rights reserved.                                                    **
**                                                                         **
*****************************************************************************

VERSION HISTORY:
----------------
Date		  	Version		Author		Short Task Description (specify task ID if available)
13/03/2018	  	1.0			RBI			Creation of source file and defining the rotary encoder mode functionality.
20/03/2018		1.1			GAN			Added the definitions and macros used for rotary encoder functionality.

*/

#define _TEMPERATURE_MODULE_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                     MODULES USED                                       **/
/**                                                                        **/
/****************************************************************************/
#include "temperature_module.h"
#include "temp.h"
#include "LPC11xx.h"

/****************************************************************************/
/**                                                                        **/
/**                     DEFINITIONS AND MACROS                             **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                     TYPEDEFS AND STRUCTURES                            **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                     PROTOTYPES OF LOCAL FUNCTIONS                      **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                     EXPORTED VARIABLES                                 **/
/**                                                                        **/
/****************************************************************************/
extern uint8_t modeSelected;
extern uint8_t prec_modeSelected;
/****************************************************************************/
/**                                                                        **/
/**                     GLOBAL VARIABLES                                   **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                     EXPORTED FUNCTIONS                                 **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                     LOCAL FUNCTIONS                                    **/
/**                                                                        **/
/****************************************************************************/
/*!
    \name       Temp_modeSelected
    \module     ROT
    \param      Not applicable
    \return     Not applicable
    \brief      This is the function in charge of treating the specific temperature mode behavior.
    \remarks    No remarks
        \Requirement(s) :
*/
static uint32_t msTicks = 0;
static uint8_t buf[10];

void SysTick_Handler(void) {
    msTicks++;
}

static uint32_t getTicks(void)
{
    return msTicks;
}

void tempFunc()
{
	/* setup sys Tick. Elapsed time is e.g. needed by temperature sensor */
	SysTick_Config(SystemCoreClock / 1000);
	if ( !(SysTick->CTRL & (1<<SysTick_CTRL_CLKSOURCE_Msk)) )
	{
	      /* When external reference clock is used(CLKSOURCE in
	      Systick Control and register bit 2 is set to 0), the
	      SYSTICKCLKDIV must be a non-zero value and 2.5 times
	      faster than the reference clock.
	      When core clock, or system AHB clock, is used(CLKSOURCE
	      in Systick Control and register bit 2 is set to 1), the
	      SYSTICKCLKDIV has no effect to the SYSTICK frequency. See
	      more on Systick clock and status register in Cortex-M3
	      technical Reference Manual. */
	      LPC_SYSCON->SYSTICKCLKDIV = 0x08;
	}
}

void Temp_modeSelected(void)
{
	static int32_t t = 0;

	if (modeSelected != prec_modeSelected)
	{
		oled_clearScreen(OLED_COLOR_WHITE);
		temp_init (&getTicks);
		tempFunc();
		oled_putString(1,1,  (uint8_t*)"Temp   : ", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	}

	 /* Temperature */
	 t = temp_read();

	 /* output values to OLED display */

	 // TO-DO: Display temperature with decimal point: 26.0, 29.4, etc
	 Oled_intToString(t, buf, 10, 10);
	 oled_fillRect((1+9*6),1, 80, 8, OLED_COLOR_WHITE);
	 oled_putString((1+9*6),1, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);



}

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
