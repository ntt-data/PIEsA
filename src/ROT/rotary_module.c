/*
 * rotary_module.c
 *
 *  Created on: Mar 18, 2018
 *      Author: bita_
 */

#include "rotary_module.h"
#include "../BTN/buttons_module.h"

static uint8_t Rot_encoderState    =  0;
static uint8_t Rot_encoderCnt	   = '0'; // SW-COMM-ROT-0006(1)
uint8_t Btn_resetEncoderCnt 	   =  0;

void Rot_modeSelected(void)
{
	Rot_encoderState = rotary_read();
	Btn_resetEncoderCnt = GPIOGetValue(PORT0, 1);

	// SW-COMM-ROT-0008(1)
	if (Btn_resetEncoderCnt == 0)
	{
		Rot_encoderCnt = '0';
		Rot_printValue(Rot_encoderCnt);

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
	    Rot_printValue(Rot_encoderCnt);
	}
	else
	{
		// SW-COMM-ROT-0005(1)
		// The position counter shall not alter its value, if the rotary encoder is not changed.
	}
}

//*************************************
void Rot_printValue(uint8_t p_encoderCnt)
{
	/* output values to OLED display */
	// SW-COMM-ROT-0003(1)
	// SW-COMM-ROT-0004(1)
	// SW-COMM-ROT-0010(1)
	Oled_intToString(((p_encoderCnt-48)*10), buf, 10, 10);
	oled_fillRect((1+13*6),1, 80, 8, OLED_COLOR_WHITE);
	oled_putString(1+13*6,1, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

