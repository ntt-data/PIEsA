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
29/05/2018    1.2           GAN         Added the definitions and macros used for the unsupported perspectives.
02/07/2018	  1.3			RBI			Refactoring code, adding comments and requirements ID.
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
#define X0                               1
#define Y0                               1
#define SECOND_ROW_Y                     9
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
// SW-COMM-TEMP-0014(1)
uint8_t Sys_currentMode = ROTARY_MODE; // default mode of the system is ROTARY_MODE(0)
uint8_t Sys_prevMode 	= ROTARY_MODE;
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
            SW-COMM-TEMP-0025
*/

int main (void)
{
	// When the system will start, first step is to initialize it by using the Init_system() function
	Init_system();

	// Main loop, where the mode selection will be implemented in future releases
    while(1)
    {
    	// The mode selection is based on the Joystick tilt left/right
    	Btn_modeSelection();

    	switch (Sys_currentMode)
    	{
    		case ROTARY_MODE:
    			Rot_modeSelected();
    			break;
    		case TEMPERATURE_MODE:
				Temp_modeSelected();
				break;
    		default: // Unsupported Perspective
    			// SW-COMM-TEMP-0025(1)
    			if (Sys_currentMode != Sys_prevMode)
    			{
    				oled_clearScreen(OLED_COLOR_WHITE);
    				oled_putString(X0,Y0,  (uint8_t*)"Unsupported", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
    				oled_putString(X0,SECOND_ROW_Y,  (uint8_t*)"State !", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
    			}
    			break;
    	}

    	// TO-DO: add behavior for a reset system button (future releases)

    	// Update the value of previous system mode variable
    	Sys_prevMode = Sys_currentMode;
    }
}

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
