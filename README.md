# controlled-led-strip-for-staircase

This simple project controls up to two led strips (Ws2812b or Ws2811)
lightening up and down is initialized by changing state on right pins, 
with can be used in simple wall bistable buttons.

Originally works on popular Atmega328p 8MHz but also tested on Atmega168 8MHz, Atmega88 8MHz,  
Atmega32A 8MHz. 

Pins to connect buttons are selected in CheckForChange.h

Ws281x pins are selected in effects.h

Selecting the type of Led strips is done in light_ws2812.h 
by setting right reset time.
