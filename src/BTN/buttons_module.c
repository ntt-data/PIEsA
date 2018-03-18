/*
 * buttons_module.c
 *
 *  Created on: Mar 18, 2018
 *      Author: bita_
 */

#include "buttons_module.h"

void Btn_mapping(void)
{
    // btn1 used to reset rotary encoder counter
	GPIOSetDir(PORT0, 1, 0);
    LPC_IOCON->PIO0_1 &= ~0x7;
}
