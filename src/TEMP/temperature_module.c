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
29/05/2018      1.1         GAN         Added the definitions and macros used for the temperature sensor module.
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
#define INIT_TIMER_MS 	                 0
#define INDEX_TEN                        10
#define SIMPLIFY_BY_A_THOUSAND           1000
#define MASK_CLK                         1
#define SYS_CLOCK_DIVISION               0x08
#define INIT_TEMP                        0
#define X0                               1
#define Y0                               1
#define SIMPLIFY_BY_TEN                  10
#define LENGTH_TEN                       10
#define BASE_TEN                         10
#define X1                               80
#define Y1                               8
#define SECOND_X                         (18+9*6)
#define THIRD_X                          (30+9*6)
#define FOURTH_X                         (32+9*6)
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
static uint32_t msTicks = INIT_TIMER_MS;
static uint8_t buf[INDEX_TEN];

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
	SysTick_Config(SystemCoreClock / SIMPLIFY_BY_A_THOUSAND);
	if ( !(SysTick->CTRL & (MASK_CLK << SysTick_CTRL_CLKSOURCE_Msk)) )
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
	      LPC_SYSCON->SYSTICKCLKDIV = SYS_CLOCK_DIVISION;
	}
}

void Temp_modeSelected(void)
{
	static int32_t t = INIT_TEMP;
	uint8_t temp_decimal = INIT_TEMP;

	if (modeSelected != prec_modeSelected)
	{
		oled_clearScreen(OLED_COLOR_WHITE);
		temp_init (&getTicks);
		tempFunc();
		oled_putString(X0,Y0,  (uint8_t*)"Temperature: ", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	}

	 /* Temperature */
	 t = temp_read();

	 temp_decimal = t % SIMPLIFY_BY_TEN;

	 /* output values to OLED display */
	 Oled_intToString((t/SIMPLIFY_BY_TEN), buf, LENGTH_TEN, BASE_TEN);
	 oled_fillRect(SECOND_X,Y0, X1, Y1, OLED_COLOR_WHITE);
	 oled_putString(SECOND_X,Y0, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	 // Display temperature with decimal point: 26.0, 29.4, etc
	 Oled_intToString(temp_decimal, buf, LENGTH_TEN, BASE_TEN);
	 oled_putString(THIRD_X,Y0, ".", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	 oled_putString(FOURTH_X,Y0, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
