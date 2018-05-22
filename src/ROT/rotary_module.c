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
22/05/2018	  	1.2			RBI			Added the logic for temperature sensor and switch between states.
*/

#define _ROTARY_MODULE_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                     MODULES USED                                       **/
/**                                                                        **/
/****************************************************************************/
#include "rotary_module.h"
#include "../BTN/buttons_module.h"

/****************************************************************************/
/**                                                                        **/
/**                     DEFINITIONS AND MACROS                             **/
/**                                                                        **/
/****************************************************************************/
#define INIT_STATE_FOR_ROTARY_ENCODER    0
#define CNT_VALUE_AFTER_RESET            0
#define SECOND_BIT_POSITION              1
#define ASCII_VALUE_FOR_ZERO             48
#define MUTIPLY_BY_TEN                   10
#define LENGTH_TEN                       10
#define BASE_TEN                         10
#define FIRST_INDEX                      0
#define SECOND_INDEX                     1
#define X0                               (1+13*6)
#define Y0                               1
#define X1                               80
#define Y1                               8

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
static void Rot_printEncoderCntValue(uint8_t p_encoderCnt);

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
static uint8_t Rot_encoderState    =  INIT_STATE_FOR_ROTARY_ENCODER;
uint8_t Btn_resetEncoderCnt 	   =  CNT_VALUE_AFTER_RESET;
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
    \name       Rot_modeSelected
    \module     ROT
    \param      Not applicable
    \return     Not applicable
    \brief      This is the function in charge of treating the specific rotary encoder mode behavior.
    \remarks    No remarks
        \Requirement(s) :
            SW-COMM-ROT-0008
			SW-COMM-ROT-0002
			SW-COMM-ROT-0003
			SW-COMM-ROT-0004
			SW-COMM-ROT-0011
			SW-COMM-ROT-0007
			SW-COMM-ROT-0005
*/
void Rot_modeSelected(void)
{
	static uint8_t Rot_encoderCnt	   = '0'; // SW-COMM-ROT-0006(1)

	Rot_encoderState = rotary_read();
	Btn_resetEncoderCnt = GPIOGetValue(PORT0, SECOND_BIT_POSITION);

	// init the screen only if the running mode was previous changed
	if (modeSelected != prec_modeSelected)
	{
		oled_clearScreen(OLED_COLOR_WHITE);
		// By default, initialize in rotary mode and display text on screen
		oled_putString(1, 1,  (uint8_t*)"Rotary Value:0", OLED_COLOR_BLACK, OLED_COLOR_WHITE); // SW-COMM-ROT-0009(1)
		Rot_printEncoderCntValue(Rot_encoderCnt);
	}

	// SW-COMM-ROT-0008(1)
	if (Btn_resetEncoderCnt == CNT_VALUE_AFTER_RESET ) // rename to button is pressed
	{
		Rot_encoderCnt = '0';
		Rot_printEncoderCntValue(Rot_encoderCnt);

	} // SW-COMM-ROT-0002(1)
	else if (Rot_encoderState != ROTARY_WAIT)
	{
		// SW-COMM-ROT-0002(1)
	    if (Rot_encoderState == ROTARY_RIGHT)
	    {
	    	// SW-COMM-ROT-0003(1)
	    	Rot_encoderCnt++;
	    }
	    // SW-COMM-ROT-0002(1)
	    else // CCW
	    {
	    	// SW-COMM-ROT-0004(1)
	    	Rot_encoderCnt--;
	    }

	    // SW-COMM-ROT-0011(1)
	    if (Rot_encoderCnt > '9')
	    {
	    	Rot_encoderCnt = '0';
	    }
	    else if (Rot_encoderCnt < '0')
	    {
	    	Rot_encoderCnt = '9';
	    }

	    // SW-COMM-ROT-0007(1)
	    Rot_printEncoderCntValue(Rot_encoderCnt);
	}
	else
	{
		// SW-COMM-ROT-0005(1)
		// The position counter shall not alter its value, if the rotary encoder is not changed.
	}
}


/*!
    \name       Rot_printValue
    \module     ROT
    \param      uint8_t p_encoderCnt
    \return     Not applicable
    \brief      This is the function in charge of printing the counter value of the rotary encoder, on the OLED screen.
    \remarks    No remarks
        \Requirement(s) :
            SW-COMM-ROT-0003
			SW-COMM-ROT-0004
			SW-COMM-ROT-0010
*/
static void Rot_printEncoderCntValue(uint8_t p_encoderCnt)
{
	/* output values to OLED display */
	// SW-COMM-ROT-0003(1)
	// SW-COMM-ROT-0004(1)
	// SW-COMM-ROT-0010(1)
	Oled_intToString(((p_encoderCnt - ASCII_VALUE_FOR_ZERO) * MUTIPLY_BY_TEN), buf, LENGTH_TEN, BASE_TEN);
	oled_fillRect(X0,Y0, X1, Y1, OLED_COLOR_WHITE);

	/* If the counter is reset, delete the second character from buffer, to avoid displaying 00 on screen*/
	if (buf[FIRST_INDEX] == '0')
	{
		buf[SECOND_INDEX] = ' ';
	}

	/* Print output buffer on OLED Display */
	oled_putString(X0,Y0, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
