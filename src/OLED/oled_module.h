/*
 * oled_module.h
 *
 *  Created on: Mar 18, 2018
 *      Author: bita_
 */

#ifndef OLED_OLED_MODULE_H_
#define OLED_OLED_MODULE_H_

#include "type.h"
#include "oled.h"

void Oled_intToString(int value, uint8_t* pBuf, uint32_t len, uint32_t base);

#endif /* OLED_OLED_MODULE_H_ */
