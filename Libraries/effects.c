#include <avr/io.h>
#include <util/delay.h>
#include "ws2812_config.h"
#include "light_ws2812.h"
#include "effects.h"
#include "CheckForChange.h"


void Init_WS2811()
{
	//first line port is already changed to output in light_ws2812
	DDRB |= (_BV(SECOND_LINE_PORT));

	Clear(_BV(FIRST_LINE_PORT));
	Clear(_BV(SECOND_LINE_PORT));
}


void Clear(uint8_t pinmask)
{
	uint8_t ledCnt = 0;
	if(pinmask == _BV(FIRST_LINE_PORT))
	{
		ledCnt = FIRST_LED_CNT;
	}
	else if(pinmask == _BV(SECOND_LINE_PORT))
	{
		ledCnt = SECOND_LED_CNT;
	}

	for(uint8_t i=0; i<ledCnt; i++)
	{
		if(pinmask == _BV(FIRST_LINE_PORT))
		{
			firstLed[i].r = 0;
			firstLed[i].g = 0;
			firstLed[i].b = 0;
		}
		else if(pinmask == _BV(SECOND_LINE_PORT))
		{
			secondLed[i].r = 0;
			secondLed[i].g = 0;
			secondLed[i].b = 0;
		}
	}
	if(pinmask == _BV(FIRST_LINE_PORT))
	{
		ws2812_setleds_pin(firstLed, FIRST_LED_CNT, pinmask);
	}
	else if(pinmask == _BV(SECOND_LINE_PORT))
	{
		ws2812_setleds_pin(secondLed, SECOND_LED_CNT, pinmask);
	}
}



void FirstEffect_Light_Up_1strip()
{
	uint8_t i=0, increase = 0;

	if(firstLed[FIRST_LED_CNT-1].r < 255)
	{
		if( (uint8_t)(firstLed[0].r+FADE_FIRST_EFFECT+increase)>firstLed[0].r)
		{
			if(increase<MAX_GAIN_FIRST_EFFECT)
			{
				increase+=GAIN_FIRST_EFFECT;
			}
			else
			{
				increase=MAX_GAIN_FIRST_EFFECT;
			}

			firstLed[0].r+=FADE_FIRST_EFFECT+increase;
			firstLed[0].g+=FADE_FIRST_EFFECT+increase;
			firstLed[0].b+=FADE_FIRST_EFFECT+increase;
		}
		else
		{
			firstLed[0].r =255;
			firstLed[0].g =255;
			firstLed[0].b =255;
		}

		for(i=FIRST_LED_CNT; i>1; i--)
		{
			firstLed[i-1]=firstLed[i-2];
		}

		_delay_ms(DELAY_FIRST_EFFECT);
		ws2812_setleds_pin(firstLed, FIRST_LED_CNT, _BV(FIRST_LINE_PORT)); // (led, i+1)
	}
	if(firstLed[FIRST_LED_CNT-1].r >= 255) contactor_1_state = LIGHT_NUMB_LIGHTED;
}


void FirstEffect_Light_Up_2strip()
{
	uint8_t i=0, increase = 0;

	if(secondLed[SECOND_LED_CNT-1].r < 255)
	{
		if( (uint8_t)(secondLed[0].r+FADE_FIRST_EFFECT+increase)>secondLed[0].r)
		{
			if(increase<MAX_GAIN_FIRST_EFFECT)
			{
				increase+=GAIN_FIRST_EFFECT;
			}
			else
			{
				increase=MAX_GAIN_FIRST_EFFECT;
			}

			secondLed[0].r+=FADE_FIRST_EFFECT+increase;
			secondLed[0].g+=FADE_FIRST_EFFECT+increase;
			secondLed[0].b+=FADE_FIRST_EFFECT+increase;
		}
		else
		{
			secondLed[0].r =255;
			secondLed[0].g =255;
			secondLed[0].b =255;
		}

		for(i=SECOND_LED_CNT; i>1; i--)
		{
			secondLed[i-1]=secondLed[i-2];
		}

		_delay_ms(DELAY_FIRST_EFFECT);
		ws2812_setleds_pin(secondLed, SECOND_LED_CNT, _BV(SECOND_LINE_PORT)); // (led, i+1)
	}
	if(secondLed[SECOND_LED_CNT-1].r >= 255) contactor_2_state = LIGHT_NUMB_LIGHTED;
}



void FirstEffect_Light_Down_1strip()
{
	uint8_t i=0, decrease = 0;

	if(firstLed[0].r)
	{
		if( (uint8_t)(firstLed[FIRST_LED_CNT-1].r-FADE_FIRST_EFFECT-decrease)<firstLed[FIRST_LED_CNT-2].r)
		{
			if(decrease<MAX_GAIN_FIRST_EFFECT)
			{
				decrease+=GAIN_FIRST_EFFECT;
			}
			else
			{
				decrease=MAX_GAIN_FIRST_EFFECT;
			}

			firstLed[FIRST_LED_CNT-1].r-=(FADE_FIRST_EFFECT+decrease);
			firstLed[FIRST_LED_CNT-1].g-=(FADE_FIRST_EFFECT+decrease);
			firstLed[FIRST_LED_CNT-1].b-=(FADE_FIRST_EFFECT+decrease);
		}
		else
		{
			firstLed[FIRST_LED_CNT-1].r =0;
			firstLed[FIRST_LED_CNT-1].g =0;
			firstLed[FIRST_LED_CNT-1].b =0;
		}

		for(i=1; i<FIRST_LED_CNT; i++)
		{
			firstLed[i-1]=firstLed[i];
		}

		_delay_ms(DELAY_FIRST_EFFECT);
		ws2812_setleds_pin(firstLed, FIRST_LED_CNT, _BV(FIRST_LINE_PORT)); // (led, i+1)
	}

	if(firstLed[0].r == 0) contactor_1_state = LIGHT_NUMB_NOT_LIGHTED;

}


void FirstEffect_Light_Down_2strip()
{
	uint8_t i=0, decrease = 0;

	if(secondLed[0].r)
	{
		if( (uint8_t)(secondLed[SECOND_LED_CNT-1].r-FADE_FIRST_EFFECT-decrease)<secondLed[SECOND_LED_CNT-2].r)
		{
			if(decrease<MAX_GAIN_FIRST_EFFECT)
			{
				decrease+=GAIN_FIRST_EFFECT;
			}
			else
			{
				decrease=MAX_GAIN_FIRST_EFFECT;
			}

			secondLed[SECOND_LED_CNT-1].r-=(FADE_FIRST_EFFECT+decrease);
			secondLed[SECOND_LED_CNT-1].g-=(FADE_FIRST_EFFECT+decrease);
			secondLed[SECOND_LED_CNT-1].b-=(FADE_FIRST_EFFECT+decrease);
		}
		else
		{
			secondLed[SECOND_LED_CNT-1].r =0;
			secondLed[SECOND_LED_CNT-1].g =0;
			secondLed[SECOND_LED_CNT-1].b =0;
		}

		for(i=1; i<SECOND_LED_CNT; i++)
		{
			secondLed[i-1]=secondLed[i];
		}

		_delay_ms(DELAY_FIRST_EFFECT);
		ws2812_setleds_pin(secondLed, SECOND_LED_CNT, _BV(SECOND_LINE_PORT)); // (led, i+1)
	}
	if(secondLed[0].r == 0) contactor_2_state = LIGHT_NUMB_NOT_LIGHTED;
}



void SecondEffect_Light_Up_1strip()
{
	struct cRGB colors[3];
	colors[0].r = 25;	colors[0].g = 25;	colors[0].b = 25;
	colors[1].r = 90;	colors[1].g = 90;	colors[1].b = 90;
	colors[2].r = 255;	colors[2].g = 255;	colors[2].b = 255;
//	colors[3].r = 90;	colors[3].g = 90;	colors[3].b = 90;
//	colors[4].r = 255;	colors[4].g = 255;	colors[4].b = 255;

	uint8_t i = 0;
	for(i = 0; firstLed[i].r != colors[2].r  && i<(FIRST_LED_CNT-1); i++){}// Finding right spot to start
	if(i == FIRST_LED_CNT-1)
	{
		firstLed[2].r = colors[0].r;
		firstLed[2].g = colors[0].g;
		firstLed[2].b = colors[0].b;

		firstLed[1].r = colors[1].r;
		firstLed[1].g = colors[1].g;
		firstLed[1].b = colors[1].b;

		firstLed[0].r = colors[2].r;
		firstLed[0].g = colors[2].g;
		firstLed[0].b = colors[2].b;
	}
	for(uint8_t j=FIRST_LED_CNT; j>1; j--)
	{
		firstLed[j-1]=firstLed[j-2];
	}

	_delay_ms(DELAY_SECOND_EFFECT);
	ws2812_setleds_pin(firstLed, FIRST_LED_CNT, _BV(FIRST_LINE_PORT)); // (led, i+1)


	if(firstLed[FIRST_LED_CNT-1].r == colors[1].r) contactor_1_state = LIGHT_NUMB_LIGHTED;
}



void SecondEffect_Light_Up_2strip()
{
	struct cRGB colors[3];
	colors[0].r = 25;	colors[0].g = 25;	colors[0].b = 25;
	colors[1].r = 90;	colors[1].g = 90;	colors[1].b = 90;
	colors[2].r = 255;	colors[2].g = 255;	colors[2].b = 255;
//	colors[3].r = 90;	colors[3].g = 90;	colors[3].b = 90;
//	colors[4].r = 255;	colors[4].g = 255;	colors[4].b = 255;

	uint8_t i = 0;
	for(i = 0; secondLed[i].r != colors[2].r  && i<(SECOND_LED_CNT-1); i++){}// Finding right spot to start
	if(i == SECOND_LED_CNT-1)
	{
		secondLed[2].r = colors[0].r;
		secondLed[2].g = colors[0].g;
		secondLed[2].b = colors[0].b;

		secondLed[1].r = colors[1].r;
		secondLed[1].g = colors[1].g;
		secondLed[1].b = colors[1].b;

		secondLed[0].r = colors[2].r;
		secondLed[0].g = colors[2].g;
		secondLed[0].b = colors[2].b;


	}
	for(uint8_t j=SECOND_LED_CNT; j>1; j--)
	{
		secondLed[j-1]=secondLed[j-2];
	}

	_delay_ms(DELAY_SECOND_EFFECT);
	ws2812_setleds_pin(secondLed, SECOND_LED_CNT, _BV(SECOND_LINE_PORT)); // (led, i+1)


	if(firstLed[FIRST_LED_CNT-1].r == colors[1].r) contactor_1_state = LIGHT_NUMB_LIGHTED;
}


void SecondEffect_Light_Down_1strip()
{
	struct cRGB colors[4];
	colors[0].r = 90;	colors[0].g = 90;	colors[0].b = 90;
	colors[1].r = 25;	colors[1].g = 25;	colors[1].b = 25;
	colors[2].r = 0;	colors[2].g = 0;	colors[2].b = 0;
//	colors[3].r = 90;	colors[3].g = 90;	colors[3].b = 90;
//	colors[4].r = 255;	colors[4].g = 255;	colors[4].b = 255;
	uint8_t i = 0;

	for(i = FIRST_LED_CNT-1; firstLed[i].r != colors[2].r && i; i--){}// Finding right spot to start
	if(i == 0)
	{
		firstLed[FIRST_LED_CNT-1].r = colors[2].r;
		firstLed[FIRST_LED_CNT-1].g = colors[2].g;
		firstLed[FIRST_LED_CNT-1].b = colors[2].b;

		firstLed[FIRST_LED_CNT-2].r = colors[1].r;
		firstLed[FIRST_LED_CNT-2].g = colors[1].g;
		firstLed[FIRST_LED_CNT-2].b = colors[1].b;

		firstLed[FIRST_LED_CNT-3].r = colors[0].r;
		firstLed[FIRST_LED_CNT-3].g = colors[0].g;
		firstLed[FIRST_LED_CNT-3].b = colors[0].b;
	}

	for(uint8_t j=1; j<FIRST_LED_CNT; j++)
	{
		firstLed[j-1]=firstLed[j];
	}

	_delay_ms(DELAY_SECOND_EFFECT);
	ws2812_setleds_pin(firstLed, FIRST_LED_CNT, _BV(FIRST_LINE_PORT)); // (led, i+1)
}

void SecondEffect_Light_Down_2strip()
{
	struct cRGB colors[4];
	colors[0].r = 90;	colors[0].g = 90;	colors[0].b = 90;
	colors[1].r = 25;	colors[1].g = 25;	colors[1].b = 25;
	colors[2].r = 0;	colors[2].g = 0;	colors[2].b = 0;
//	colors[3].r = 90;	colors[3].g = 90;	colors[3].b = 90;
//	colors[4].r = 255;	colors[4].g = 255;	colors[4].b = 255;
	uint8_t i = 0;

	for(i = SECOND_LED_CNT-1; secondLed[i].r != colors[2].r && i; i--){}// Finding right spot to start
	if(i == 0)
	{
		secondLed[SECOND_LED_CNT-1].r = colors[2].r;
		secondLed[SECOND_LED_CNT-1].g = colors[2].g;
		secondLed[SECOND_LED_CNT-1].b = colors[2].b;

		secondLed[SECOND_LED_CNT-2].r = colors[1].r;
		secondLed[SECOND_LED_CNT-2].g = colors[1].g;
		secondLed[SECOND_LED_CNT-2].b = colors[1].b;

		secondLed[SECOND_LED_CNT-3].r = colors[0].r;
		secondLed[SECOND_LED_CNT-3].g = colors[0].g;
		secondLed[SECOND_LED_CNT-3].b = colors[0].b;
	}

	for(uint8_t j=1; j<SECOND_LED_CNT; j++)
	{
		secondLed[j-1]=secondLed[j];
	}

	_delay_ms(DELAY_SECOND_EFFECT);
	ws2812_setleds_pin(secondLed, SECOND_LED_CNT, _BV(SECOND_LINE_PORT)); // (led, i+1)
}
