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
02/07/2018	  	1.2			RBI			Refactoring code, adding comments and requirements ID.
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
#define MIN_TEMP_LIMIT					 (-500)
#define MAX_TEMP_LIMIT					 (750)
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
static void Temp_printValidMeasuredValue(int32_t p_currentTempVal);
static void Temp_setPrerequisites(void);
static void Temp_setSysTick(void);

/****************************************************************************/
/**                                                                        **/
/**                     EXPORTED VARIABLES                                 **/
/**                                                                        **/
/****************************************************************************/
extern uint8_t Sys_currentMode;
extern uint8_t Sys_prevMode;
/****************************************************************************/
/**                                                                        **/
/**                     GLOBAL VARIABLES                                   **/
/**                                                                        **/
/****************************************************************************/
// SW-COMM-TEMP-0024(1)
static uint32_t msTicks = INIT_TIMER_MS;
static uint8_t buf[INDEX_TEN];

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
    \name       SysTick_Handler
    \module     TEMP
    \param      Not applicable
    \return     Not applicable
    \brief      This is the function in charge of incrementing the ms timer.
    \remarks    No remarks
        \Requirement(s) :
        	SW-COMM-TEMP-0024
*/
void SysTick_Handler(void)
{
    msTicks++;
}

/*!
    \name       getTicks
    \module     TEMP
    \param      Not applicable
    \return     Not applicable
    \brief      This is the function in charge of returning the value of ms timer.
    \remarks    No remarks
        \Requirement(s) :
        	SW-COMM-TEMP-0024
*/
static uint32_t getTicks(void)
{
    return msTicks;
}

/*!
    \name       tempFunc
    \module     TEMP
    \param      Not applicable
    \return     Not applicable
    \brief      This is the function in charge setting the system tick, required by the temperature sensor.
    \remarks    No remarks
        \Requirement(s) :
        	SW-COMM-TEMP-0024
*/
static void Temp_setSysTick(void)
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

/*!
    \name       Temp_setPrerequisites
    \module     TEMP
    \param      Not applicable
    \return     Not applicable
    \brief      This is the function in charge of preparing the system for temperature mode.
    \remarks    No remarks
        \Requirement(s) :
        	SW-COMM-TEMP-0019
*/
static void Temp_setPrerequisites(void)
{
	// SW-COMM-TEMP-0019(1)
	if (Sys_currentMode != Sys_prevMode)
	{
		oled_clearScreen(OLED_COLOR_WHITE);
		temp_init (&getTicks);
		Temp_setSysTick();
		oled_putString(X0,Y0, (uint8_t*)"Temperature: ", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	}
}

/*!
    \name       Temp_printValidMeasuredValue
    \module     TEMP
    \param      int32_t p_currentTempVal
    \return     Not applicable
    \brief      This is the function in charge of displaying the valid temperature on the OLED Screen.
    \remarks    No remarks
        \Requirement(s) :
        	SW-COMM-TEMP-0017
        	SW-COMM-TEMP-0018
        	SW-COMM-TEMP-0020
*/
static void Temp_printValidMeasuredValue(int32_t p_currentTempVal)
{
	uint8_t Temp_decimalPrecision = INIT_TEMP;

	Temp_decimalPrecision = p_currentTempVal % SIMPLIFY_BY_TEN;

	// SW-COMM-TEMP-0017(1)
	// SW-COMM-TEMP-0018(1)
	/* output values to OLED display */
	Oled_intToString((p_currentTempVal/SIMPLIFY_BY_TEN), buf, LENGTH_TEN, BASE_TEN);
    oled_fillRect(SECOND_X,Y0, X1, Y1, OLED_COLOR_WHITE);
	oled_putString(SECOND_X,Y0, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);

	// SW-COMM-TEMP-0020(1)
	// Display temperature with decimal point: 26.0, 29.4, etc
	Oled_intToString(Temp_decimalPrecision, buf, LENGTH_TEN, BASE_TEN);
	oled_putString(THIRD_X,Y0, ".", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	oled_putString(FOURTH_X,Y0, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

/*!
    \name       Temp_modeSelected
    \module     TEMP
    \param      Not applicable
    \return     Not applicable
    \brief      This is the function in charge of treating the specific temperature mode behavior.
    \remarks    No remarks
        \Requirement(s) :
        	SW-COMM-TEMP-0016
        	SW-COMM-TEMP-0017
        	SW-COMM-TEMP-0018
        	SW-COMM-TEMP-0019
        	SW-COMM-TEMP-0020
        	SW-COMM-TEMP-0026
*/
void Temp_modeSelected(void)
{
	static int32_t Temp_currentVal = INIT_TEMP;

	// When the mode is switched, the system must be prepared for temperature mode
	Temp_setPrerequisites();

	// SW-COMM-TEMP-0016(1)
	Temp_currentVal = temp_read();

	 // SW-COMM-TEMP-0023(1)
	 if ( (Temp_currentVal >= MIN_TEMP_LIMIT) && (Temp_currentVal <= MAX_TEMP_LIMIT) )
	 {
		 Temp_printValidMeasuredValue(Temp_currentVal);
	 }
	 else	// SW-COMM-TEMP-0026(1)
	 {
		 oled_clearScreen(OLED_COLOR_WHITE);
		 oled_putString(X0,Y0, (uint8_t*)"Invalid Range!", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	 }
}

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
