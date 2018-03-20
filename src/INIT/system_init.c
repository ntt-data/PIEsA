/*
                             *******************
******************************* C SOURCE FILE *******************************
**                           *******************                           **
**                                                                         **
** project          : PIEsA                                                **
** filename         : system_init.c                                        **
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
13/03/2018	  	1.0			RBI			Creation of source file and defining the system initialization phase (pins, UART, etc.).
20/03/2018		1.1			GAN			Added the definitions and macros used for the system initialization.
*/

#define _SYSTEM_INIT_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                     MODULES USED                                       **/
/**                                                                        **/
/****************************************************************************/
#include "system_init.h"

/****************************************************************************/
/**                                                                        **/
/**                     DEFINITIONS AND MACROS                             **/
/**                                                                        **/
/****************************************************************************/
#define INIT_BAUDRATE 	115200
#define INIT_TIME     	0
#define INIT_STEP     	10
#define STARTING_X    	1
#define STARTING_Y    	1

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
    \name       Init_system
    \module     INIT
    \param      Not applicable
    \return     Not applicable
    \brief      This is the function in charge of initialization the system (pins, communication, ).
    \remarks    No remarks
        \Requirement(s) :
            SW-COMM-ROT-0001
			SW-COMM-ROT-0009
*/
void Init_system(void)
{
    GPIOInit(); // Initialize GPIO, install the GPIO interrupt handler
    init_timer32(INIT_TIME, INIT_STEP); // Initialize timer, set timer interval, reset timer, install timer interrupt handler

    UARTInit(INIT_BAUDRATE); // Initialize UART0 port, setup pin select, clock, parity, stop bits, FIFO, etc.
    UARTSendString((uint8_t*)"System Initialisation !\r\n"); // Send a null-terminated string

    SSPInit(); // SSP port initialization routine

    // SW-COMM-ROT-0001(1)
    rotary_init(); // Initialize Rotary switch driver
    oled_init(); // Initialize the OLED Display

    oled_clearScreen(OLED_COLOR_WHITE); // Clear the entire screen

    // By default, initialize in rotary mode and display text on screen
    oled_putString(STARTING_X, STARTING_Y,  (uint8_t*)"Rotary Value:0", OLED_COLOR_BLACK, OLED_COLOR_WHITE); // SW-COMM-ROT-0009(1)

    // Mapping the physical buttons present on the BaseBoard.
    Btn_mapping();
}

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
