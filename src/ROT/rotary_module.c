/*
 * rotary_module.c
 *
 *  Created on: Mar 18, 2018
 *      Author: bita_
 */

#include "rotary_module.h"
#include "../BTN/buttons_module.h"

static uint8_t Rot_encoderState    =  0;
static uint8_t Rot_encoderCnt	   = '0';
uint8_t Btn_resetEncoderCnt 	   =  0;

void Rot_modeSelected(void)
{
	Rot_encoderState = rotary_read();
	Btn_resetEncoderCnt = GPIOGetValue(PORT0, 1);

	if (Btn_resetEncoderCnt == 0)
	{
		Rot_encoderCnt = '0';
		Rot_printValue(Rot_encoderCnt);

	}
	else if (Rot_encoderState != ROTARY_WAIT)
	{
	    if (Rot_encoderState == ROTARY_RIGHT)
	    {
	    	Rot_encoderCnt++;
	    }
	    else
	    {
	    	Rot_encoderCnt--;
	    }

	    if (Rot_encoderCnt > '9')
	    {
	    	Rot_encoderCnt = '0';
	    }
	    else if (Rot_encoderCnt < '0')
	    {
	    	Rot_encoderCnt = '9';
	    }

	    Rot_printValue(Rot_encoderCnt);
	}
}

//*************************************
void Rot_printValue(uint8_t p_encoderCnt)
{
	/* output values to OLED display */
	Oled_intToString((p_encoderCnt-48), buf, 10, 10);
	oled_fillRect((1+13*6),1, 80, 8, OLED_COLOR_WHITE);
	oled_putString(1+13*6,1, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

