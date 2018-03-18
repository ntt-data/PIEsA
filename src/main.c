/*****************************************************************************
 *   TO DO - ADD TEMPLATE
 *
 ******************************************************************************/
#include "INIT/system_init.h"
#include "ROT/rotary_module.h"

int main (void)
{
    // add system init function
	Init_system();

    while(1)
    {
    	// add a switch statement (in the infinite loop) to select mode
    	// based on the switch mode call functions
    	Rot_modeSelected();
    }
}

