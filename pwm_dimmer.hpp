#ifndef DIMMER_HPP
#define DIMMER_HPP
#include "mbed.h"

extern Pwm Leds[];
extern InterruptIn botton;
void set_timer();
void change_way();
void change_intensity();
void blink_blue();
void blink_orange();
void stop_blink();
void rise_blue();
void fall_orange();

#endif