/*
 * system_init.c
 *
 *  Created on: Mar 18, 2018
 *      Author: bita_
 */

#include "system_init.h"


void Init_system(void)
{
    GPIOInit();
    init_timer32(0, 10);

    UARTInit(115200);
    UARTSendString((uint8_t*)"System Initialisation !\r\n");

    SSPInit();

    // SW-COMM-ROT-0001(1)
    rotary_init();
    oled_init();

    oled_clearScreen(OLED_COLOR_WHITE);

    // by default, init in rotary state
    oled_putString(1,1,  (uint8_t*)"Rotary Value:0", OLED_COLOR_BLACK, OLED_COLOR_WHITE); // SW-COMM-ROT-0009(1)

    // button init
    Btn_mapping();
}
