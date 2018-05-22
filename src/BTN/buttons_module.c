/*
                             *******************
******************************* C SOURCE FILE *******************************
**                           *******************                           **
**                                                                         **
** project          : PIEsA                                                **
** filename         : buttons_module.c                                     **
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
13/03/2018	  	1.0			RBI			Creation of source file and mapping the reset button for the counter of rotary encoder.
20/03/2018		1.1			GAN			Added the definitions and macros used for the reset counter button.

*/

#define _BUTTONS_MODULE_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                     MODULES USED                                       **/
/**                                                                        **/
/****************************************************************************/
#include "buttons_module.h"
#include "joystick.h"
#include "oled.h"


/****************************************************************************/
/**                                                                        **/
/**                     DEFINITIONS AND MACROS                             **/
/**                                                                        **/
/****************************************************************************/
#define FIRST_BIT_POSITION 	1
#define DIRECTION_INPUT    	0
#define PIN_MASK           	0x7

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
    \name       Btn_mapping
    \module     BTN
    \param      Not applicable
    \return     Not applicable
    \brief      This is the function in charge of mapping the physical buttons present on the BaseBoard.
    \remarks    No remarks
        \Requirement(s) :
            TO BE ADDED IN FUTURE RELEASE IF NECESSARY
*/
void Btn_mapping(void)
{
    // Button mapping used to reset the counter of rotary encoder
	GPIOSetDir(PORT0, FIRST_BIT_POSITION, DIRECTION_INPUT);
    LPC_IOCON->PIO0_1 &= ~ PIN_MASK;
}

/*!
    \name       Btn_modeSelect
    \module     BTN
    \param      Not applicable
    \return     uint8_t modeSelected
    \brief      This is the function in charge of mapping the physical buttons present on the BaseBoard.
    \remarks    No remarks
        \Requirement(s) :
            TO BE ADDED IN FUTURE RELEASE IF NECESSARY
*/
void Btn_modeSelection()
{
	uint8_t joyState = joystick_read(); // @@@@@@@@@@@@@@@

	if ( joyState != 0 ) // joystick is used
	{
		if ( (joyState & JOYSTICK_LEFT) != 0 ) // 0x08
	    {
	    	if (modeSelected > 0) // decrement only if not on first state (0)
	    	{
	    		modeSelected--; // go to previous state (ROTARY_MODE = 0)
	    	}
	    }
	    else if ( (joyState & JOYSTICK_RIGHT) != 0 ) // 0x10
	    {
	    	if (modeSelected < 1/*(INVALID_MODE-1)*/) // increment only if not on last valid state (1)
	    	{
	    		modeSelected++; // go to next state (TEMPERATURE_MODE = 1)
	    	}
	    }
	    else	// (joyState & JOYSTICK_UP) != 0 || (joyState & JOYSTICK_DOWN) != 0 || (joyState & JOYSTICK_CENTER) != 0
	    {
	    	// do-nothing
	    	// joystick used but the direction is not supported

	    	// TO-DO: Implement a handler for INVALID_STATE (message on OLED)
	    }
	}
}

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
