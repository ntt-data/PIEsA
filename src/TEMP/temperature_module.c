/*
                             *******************
******************************* C SOURCE FILE *******************************
**                           *******************                           **
**                                                                         **
** project          : PIEsA                                                **
** filename         : temperature_module.c                                 **
** template version : 1                                                    **
** date             : 21 May, 2018                                         **
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
22/05/2018	  	1.0			RBI			Creation of source file and defining the temperature and switch mode functionality.
*/

#define _TEMPERATURE_MODULE_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                     MODULES USED                                       **/
/**                                                                        **/
/****************************************************************************/
#include "temperature_module.h"


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
	uint8_t temp_decimal = 0;

	if (modeSelected != prec_modeSelected)
	{
		oled_clearScreen(OLED_COLOR_WHITE);
		temp_init (&getTicks);
		tempFunc();
		oled_putString(1,1,  (uint8_t*)"Temperature: ", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	}

	 /* Temperature */
	 t = temp_read();

	 temp_decimal = t % 10;

	 /* output values to OLED display */
	 Oled_intToString((t/10), buf, 10, 10);
	 oled_fillRect((18+9*6),1, 80, 8, OLED_COLOR_WHITE);
	 oled_putString((18+9*6),1, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	 // Display temperature with decimal point: 26.0, 29.4, etc
	 Oled_intToString(temp_decimal, buf, 10, 10);
	 oled_putString((30+9*6),1, ".", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	 oled_putString((32+9*6),1, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
