#ifndef EFFECTS_H_
#define EFFECTS_H_

//Here change port of ledStrips and number of LEDs
#define FIRST_LINE_PORT PB2
#define FIRST_LED_CNT 80

#define SECOND_LINE_PORT PB1
#define SECOND_LED_CNT 80


#define FADE_FIRST_EFFECT 2 //How much will gain second to first LED
#define GAIN_FIRST_EFFECT 3 //Increase speed of lightning up exery next LED
#define MAX_GAIN_FIRST_EFFECT 20
#define DELAY_FIRST_EFFECT 30 //slows down the effect

#define DELAY_SECOND_EFFECT 40 //slows down the effect


typedef enum{
	LIGHT_UP_FIRST_EFFECT=0,
	LIGHT_UP_SECOND_EFFECT,
	LIGHT_DOWN_FIRST_EFFECT,
	LIGHT_DOWN_SECOND_EFFECT

}SELECTED_EFFECTS;

struct cRGB firstLed[FIRST_LED_CNT+1];
struct cRGB secondLed[SECOND_LED_CNT+1];

void Init_WS2811();

void Clear(uint8_t pinmask);

//This effect work by generating white "rainbow" on first LED
//and then copying it to next one, and next one...
void FirstEffect_Light_Up_1strip();
void FirstEffect_Light_Up_2strip();
void FirstEffect_Light_Down_1strip();
void FirstEffect_Light_Down_2strip();


//This effect switches 3 established values thru the whole strip
void SecondEffect_Light_Up_1strip();
void SecondEffect_Light_Up_2strip();
void SecondEffect_Light_Down_1strip();
void SecondEffect_Light_Down_2strip();

#endif /* EFFECTS_H_ */
