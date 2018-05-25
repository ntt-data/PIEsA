/*
                             *******************
******************************* C SOURCE FILE *******************************
**                           *******************                           **
**                                                                         **
** project          : PIEsA                                                **
** filename         : oled_module.c                                        **
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
13/03/2018	  	1.0			RBI			Creation of source file and defining the conversion of integer to string, used for displaying the text.
20/03/2018		1.1			GAN			Added the definitions and macros used for the conversion of integer to string.

*/

#define _OLED_MODULE_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                     MODULES USED                                       **/
/**                                                                        **/
/****************************************************************************/
#include "oled_module.h"

/****************************************************************************/
/**                                                                        **/
/**                     DEFINITIONS AND MACROS                             **/
/**                                                                        **/
/****************************************************************************/
#define LENGTH_TWO         2
#define INIT_POSITION      0
#define BASE_TWO           2
#define BASE_THIRTYSIX     36
#define VALUE_ZERO         0

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
    \name       Oled_intToString
    \module     OLED
    \param      int value, uint8_t* pBuf, uint32_t len, uint32_t base
    \return     Not applicable
    \brief      This is the function in charge of the conversion of an integer data type to a string data type (useful in displaying text on the OLED screen).
    \remarks    No remarks
        \Requirement(s) :
            TO BE ADDED IN FUTURE RELEASE IF NECESSARY
*/
void Oled_intToString(int_fast8_t value, uint8_t* pBuf, uint32_t len, uint32_t base)
{
    static const uint8_t* pAscii = "0123456789abcdefghijklmnopqrstuvwxyz";
    int_fast8_t pos = INIT_POSITION;
    int_fast8_t tmpValue = value;

    // the buffer must not be null and at least have a length of 2 to handle one
    // digit and null-terminator
    if (pBuf == NULL || len < LENGTH_TWO)
    {
        return;
    }

    // a valid base cannot be less than 2 or larger than 36
    // a base value of 2 means binary representation. A value of 1 would mean only zeros
    // a base larger than 36 can only be used if a larger alphabet were used.
    if (base < BASE_TWO || base > BASE_THIRTYSIX)
    {
        return;
    }

    // negative value
    if (value < VALUE_ZERO)
    {
        tmpValue = -tmpValue;
        value    = -value;
        pBuf[pos++] = '-';
    }

    // calculate the required length of the buffer
    do
    {
        pos++;
        tmpValue /= base;
    } while(tmpValue > VALUE_ZERO);


    if (pos > len)
    {
        // the len parameter is invalid.
        return;
    }

    pBuf[pos] = '\0';

    do
    {
        pBuf[--pos] = pAscii[value % base];
        value /= base;
    } while(value > VALUE_ZERO);

    return;
}

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/
