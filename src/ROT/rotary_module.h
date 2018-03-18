/*
 * rotary_module.h
 *
 *  Created on: Mar 18, 2018
 *      Author: bita_
 */

#ifndef ROT_ROTARY_MODULE_H_
#define ROT_ROTARY_MODULE_H_

#include "type.h"
#include "rotary.h"
#include "oled.h"
#include "gpio.h"
#include "ssp.h"
#include "../OLED/oled_module.h"

uint8_t buf[10];

void Rot_modeSelected(void);
void Rot_printValue(uint8_t p_encoderCnt);

#endif /* ROT_ROTARY_MODULE_H_ */
