/*
 * buttons_module.h
 *
 *  Created on: Mar 18, 2018
 *      Author: bita_
 */

#ifndef BTN_BUTTONS_MODULE_H_
#define BTN_BUTTONS_MODULE_H_

#include "type.h"
#include "gpio.h"
#include "ssp.h"
#include "mcu_regs.h"

extern uint8_t Btn_resetEncoderCnt;

void Btn_mapping(void);

#endif /* BTN_BUTTONS_MODULE_H_ */
