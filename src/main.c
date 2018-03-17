/*****************************************************************************
 *   An example illustrating how to control the 7-segment display
 *   using the Rotary switch
 *
 *   Copyright(C) 2009, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#include "type.h"
#include "uart.h"
#include "stdio.h"
#include "timer32.h"
#include "gpio.h"
#include "ssp.h"

#include "led7seg.h"
#include "rotary.h"


int main (void) {

    uint8_t state    = 0;
    uint8_t ch = '0';

    GPIOInit();
    init_timer32(0, 10);

    UARTInit(115200);
    UARTSendString((uint8_t*)"7-segment Display and Rotary\r\n");

    SSPInit();


    rotary_init();
    led7seg_init();


    while(1) {
        state = rotary_read();

        if (state != ROTARY_WAIT) {

            if (state == ROTARY_RIGHT) {
                ch++;
            }
            else {
                ch--;
            }

            if (ch > '9')
                ch = '0';
            else if (ch < '0')
                ch = '9';

            led7seg_setChar(ch, FALSE);

        }

    }

}
