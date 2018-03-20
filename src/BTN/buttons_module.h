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
/**                     EXPORTED VARIABLES                                 **/
/**                                                                        **/
/****************************************************************************/

#ifndef _SYSTEM_INIT_C_SRC
    extern uint8_t Btn_resetEncoderCnt;
#endif

/****************************************************************************/
/**                                                                        **/
/**                     EXPORTED FUNCTIONS                                 **/
/**                                                                        **/
/****************************************************************************/
void Btn_mapping(void);

#endif /* _BUTTONS_MODULE_INCLUDED */

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
