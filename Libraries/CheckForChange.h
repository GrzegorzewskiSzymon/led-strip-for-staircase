#ifndef CHECKFORCHANGE_H_
#define CHECKFORCHANGE_H_

//Here select right pins for contactors
#define CONTACTOR_1_INIT PORTD |= (1<<PD5)
#define CONTACTOR_1_CHECK_STATE !(PIND & 1<<PD5)
#define CONTACTOR_2_INIT PORTD |= (1<<PD6)
#define CONTACTOR_2_CHECK_STATE !(PIND & 1<<PD6)

//Diode for debugging
#define LED_INIT DDRD |= (1<<PD7)
#define LED_ON PORTD |= (1<<PD7)
#define LED_OFF PORTD &=~ (1<<PD7)
#define LED_TOG PORTD ^= (1<<PD7)

typedef enum{
	LIGHT_UP=0,
	LIGHT_DOWN,
	LIGHT_NUMB_LIGHTED,
	LIGHT_NUMB_NOT_LIGHTED,
}CONTACTOR_STATE;

void Init_contactors();
void CheckForChange();

uint8_t contactor_2_state;
uint8_t contactor_1_state;

#endif /* CHECKFORCHANGE_H_ */
