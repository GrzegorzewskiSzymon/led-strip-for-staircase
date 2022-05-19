#include <avr/io.h>
#include <util/delay.h>
#include "Libraries/ws2812_config.h"
#include "Libraries/light_ws2812.h"
#include "Libraries/effects.h"
#include "Libraries/CheckForChange.h"

void Init();
void ControlLedStrips(SELECTED_EFFECTS LIGHT_UP_EFFECT, SELECTED_EFFECTS LIGHT_DOWN_EFFECT);

int main(void)
{
	Init(); // Initialize components and shows visual confirmation of start

	while(1)
	{
		CheckForChange();//Check if switch changed position

		ControlLedStrips(LIGHT_DOWN_SECOND_EFFECT, LIGHT_DOWN_FIRST_EFFECT); //Run effects
	}

	return 0;
}

void Init()
{
	LED_INIT;
	//visual confirmation of start
	LED_ON;
	_delay_ms(200);
	LED_OFF;

	Init_WS2811();
	Init_contactors();
}

void ControlLedStrips(SELECTED_EFFECTS LIGHT_UP_EFFECT, SELECTED_EFFECTS LIGHT_DOWN_EFFECT)
{

	if(contactor_1_state == LIGHT_UP)
	{
		//Run right effect
		if(LIGHT_UP_EFFECT == LIGHT_UP_FIRST_EFFECT)
			FirstEffect_Light_Up_1strip();
		else if(LIGHT_UP_EFFECT == LIGHT_UP_SECOND_EFFECT)
			SecondEffect_Light_Up_1strip();

		//If another strip is changing compensate difference in timing
		if(contactor_2_state != LIGHT_UP || contactor_2_state != LIGHT_DOWN)
			_delay_ms(5);
	}
	else if(contactor_1_state == LIGHT_DOWN)
	{
		if(LIGHT_DOWN_EFFECT == LIGHT_DOWN_FIRST_EFFECT)
			FirstEffect_Light_Down_1strip();
		else if(LIGHT_DOWN_EFFECT == LIGHT_DOWN_SECOND_EFFECT)
			SecondEffect_Light_Down_1strip();

		//If another strip is changing compensate difference in timing
		if(contactor_2_state != LIGHT_UP || contactor_2_state != LIGHT_DOWN)
			_delay_ms(5);
	}


	if(contactor_2_state == LIGHT_UP)
	{
		//Run right effect
		if(LIGHT_UP_EFFECT == LIGHT_UP_FIRST_EFFECT)
			FirstEffect_Light_Up_2strip();
		else if(LIGHT_UP_EFFECT == LIGHT_UP_SECOND_EFFECT)
			SecondEffect_Light_Up_2strip();

		//If another strip is changing compensate difference in timing
		if(contactor_1_state != LIGHT_UP || contactor_1_state != LIGHT_DOWN)
			_delay_ms(5);
	}
	else if(contactor_2_state == LIGHT_DOWN)
	{
		if(LIGHT_DOWN_EFFECT == LIGHT_DOWN_FIRST_EFFECT)
			FirstEffect_Light_Down_2strip();
		else if(LIGHT_DOWN_EFFECT == LIGHT_DOWN_SECOND_EFFECT)
			SecondEffect_Light_Down_2strip();

		//If another strip is changing compensate difference in timing
		if(contactor_1_state != LIGHT_UP || contactor_1_state != LIGHT_DOWN)
			_delay_ms(5);
	}

}
