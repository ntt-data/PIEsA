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
22/05/2018	  	1.2			RBI			Added the logic for temperature sensor and switch between states.
*/

#define _BUTTONS_MODULE_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                     MODULES USED                                       **/
/**                                                                        **/
/****************************************************************************/
#include "buttons_module.h"



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
    \name       Btn_modeSelection
    \module     BTN
    \param      Not applicable
    \return     Not applicable
    \brief      This is the function in charge of handling the mode selection.
    \remarks    No remarks
        \Requirement(s) :
            TO BE ADDED IN FUTURE RELEASE IF NECESSARY
*/
void Btn_modeSelection(void)
{
	// TO-DO: Add requirements in the function header and body
	// TO-DO: Rename the variables, according to the established coding/naming rules
	uint8_t joyState = joystick_read(); // @@@@@@@@@@@@@@@

	if ( joyState != JOYSTICK_NOT_MOVED ) // joystick is used
	{
		if ( (joyState & JOYSTICK_LEFT) != JOYSTICK_NOT_MOVED ) // joystick moved/tilted to the left
	    {
	    	if (modeSelected > ROTARY_MODE /* ROTARY_MODE */) // decrement only if not on first state (0)
	    	{
	    		modeSelected--; // go to previous state (ROTARY_MODE = 0)
	    	}
	    }
	    else if ( (joyState & JOYSTICK_RIGHT) != JOYSTICK_NOT_MOVED ) // joystick moved/tilted to the right
	    {
	    	if (modeSelected < INVALID_MODE) /* increment only if not on last valid state (1)*/
	    	{
	    		modeSelected++; // go to next state (TEMPERATURE_MODE = 1)
	    	}
	    }
	    else	// (joyState & JOYSTICK_UP) != 0 || (joyState & JOYSTICK_DOWN) != 0 || (joyState & JOYSTICK_CENTER) != 0
	    {
	    	// Implement a handler for INVALID_STATE (message on OLED)
	    	modeSelected = INVALID_MODE;
	    }
	}
}

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
