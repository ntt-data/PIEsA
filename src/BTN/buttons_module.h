/*
                             *******************
******************************* C HEADER FILE *******************************
**                           *******************                           **
**                                                                         **
** project          : PIEsA                                                **
** filename         : buttons_module.h                                     **
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
13/03/2018	  	1.0			RBI			Creation of header file, used in button mapping.
22/05/2018	  	1.1			RBI			Added the logic for temperature sensor and switch between states.
*/

#ifndef _BUTTONS_MODULE_INCLUDED
#define _BUTTONS_MODULE_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                     MODULES USED                                       **/
/**                                                                        **/
/****************************************************************************/
#include "type.h"
#include "gpio.h"
#include "ssp.h"
#include "mcu_regs.h"
#include "joystick.h"
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
// TO-DO: Add comment and requirement
enum runningStates // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
{
	ROTARY_MODE,
	TEMPERATURE_MODE,
	INVALID_MODE
};

/****************************************************************************/
/**                                                                        **/
/**                     EXPORTED VARIABLES                                 **/
/**                                                                        **/
/****************************************************************************/

#ifndef _SYSTEM_INIT_C_SRC
    extern uint8_t Btn_resetEncoderCnt;
#endif

extern uint8_t Sys_currentMode;

/****************************************************************************/
/**                                                                        **/
/**                     EXPORTED FUNCTIONS                                 **/
/**                                                                        **/
/****************************************************************************/
void Btn_mapping(void);
void Btn_modeSelection(void);

#endif /* _BUTTONS_MODULE_INCLUDED */

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
