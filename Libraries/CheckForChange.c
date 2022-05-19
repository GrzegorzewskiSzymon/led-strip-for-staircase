#include <avr/io.h>
#include <util/delay.h>
#include "CheckForChange.h"


void Init_contactors()
{
	contactor_1_state = LIGHT_NUMB_NOT_LIGHTED;
	contactor_2_state = LIGHT_NUMB_NOT_LIGHTED;

	CONTACTOR_1_INIT;
	CONTACTOR_2_INIT;
}


void CheckForChange()
{

	switch(contactor_1_state)
	{
		case LIGHT_UP: // while brightening
		case LIGHT_NUMB_LIGHTED: // lighted
			if(!CONTACTOR_1_CHECK_STATE) //Pushed down
			{
				_delay_ms(15);
				if(!CONTACTOR_1_CHECK_STATE) //Still pushed down
				{
					contactor_1_state = LIGHT_DOWN;
				}
			}
			break;

		case LIGHT_DOWN: // while dimming
		case LIGHT_NUMB_NOT_LIGHTED: // not lighted
			if(CONTACTOR_1_CHECK_STATE)//Pushed Up
			{
				_delay_ms(15);
				if(CONTACTOR_1_CHECK_STATE) //Still pushed Up
				{
					contactor_1_state = LIGHT_UP;
				}
			}
			break;
	}

	switch(contactor_2_state)
	{
		case LIGHT_UP: // while brightening
		case LIGHT_NUMB_LIGHTED: // lighted
			if(!CONTACTOR_2_CHECK_STATE) //Pushed down
			{
				_delay_ms(15);
				if(!CONTACTOR_2_CHECK_STATE) //Still pushed down
				{
					contactor_2_state = LIGHT_DOWN;
				}
			}
			break;

		case LIGHT_DOWN: // while dimming
		case LIGHT_NUMB_NOT_LIGHTED: // not lighted
			if(CONTACTOR_2_CHECK_STATE)//Pushed Up
			{
				_delay_ms(15);
				if(CONTACTOR_2_CHECK_STATE) //Still pushed Up
				{
					contactor_2_state = LIGHT_UP;
				}
			}
			break;
	}

}
