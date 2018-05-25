/*
                             *******************
******************************* C SOURCE FILE *******************************
**                           *******************                           **
**                                                                         **
** project          : PIEsA                                                **
** filename         : main.c                                               **
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
Date		  Version		Author		Short Task Description (specify task ID if available)
13/03/2018	  1.0			RBI			Creation of file and defining the main function
22/05/2018	  1.1			RBI			Added the logic for temperature sensor and switch between states.
*/

#define _MAIN_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                     MODULES USED                                       **/
/**                                                                        **/
/****************************************************************************/
#include "INIT/system_init.h"
#include "ROT/rotary_module.h"
#include "TEMP/temperature_module.h"

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
    \name       main
    \module     Not applicable
    \param      Not applicable
    \return     Not applicable
    \brief      This is the function where the program will start executing. Initialization of the system and mode selection will start from here.
    \remarks    No remarks
        \Requirement(s) :
            TO BE ADDED IN FUTURE RELEASES IF NECESSARY
*/

// default init mode of the system is ROTARY_MODE(0)
uint8_t modeSelected = ROTARY_MODE; // @@@@@@@@@@@@@@@@@@@@@@@@@
uint8_t prec_modeSelected = ROTARY_MODE; // @@@@@@@@@@@@@@@@@@@@@@@@@
int main (void)
{
	// When the system will start, first step is to initialize it by using the Init_system() function
	Init_system();

	// Main loop, where the mode selection will be implemented in future releases
    while(1)
    {
    	Btn_modeSelection(); // @@@@@@@@@@@@@@@@@@@@@@@

    	switch (modeSelected)
    	{
    		case ROTARY_MODE:
    			Rot_modeSelected();
    			break;
    		case TEMPERATURE_MODE:
				Temp_modeSelected();
				break;
    		default:
    			if (modeSelected != prec_modeSelected)
    			{
    				oled_clearScreen(OLED_COLOR_WHITE);
    				oled_putString(1,1,  (uint8_t*)"Unsupported", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
    				oled_putString(1,9,  (uint8_t*)"State !", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
    			}
    			// TO-DO: Implement Handler for INVALID_MODE (display text on screen)
    			break;
    	}

    	// TO-DO: add behavior for reset system button in the switch case (future releases)

    	// update the value of prec variables
    	prec_modeSelected = modeSelected; // rename the variable according to the coding/naming rules
    }
}

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
