/*
This file define the parameters for implementing AFSK1200 
for the following parameters on the PWM device:

* 132MHz clock frequency
* divide-by-8
* 1250 count period

The output pwm frequency will be 13200Hz

The sine table  will have 66 entries corresponding to a
200Hz sinewave.

It also uses the PWM sampling theorem and limits the amplitude to
0.637, and it is centered around 1.

Thus, it is generated as:

round((1+sin(2*pi*200/13200*n)*0.637)*1250/2)
*/
#pragma once

extern uint16_t sine200hz[66];

#define PICO_TNC_CLOCK 132000
#define AUDIO_OUTPUT_PIN 16
#define AUDIO_PWM_DIVIDER 8
#define AUDIO_PWM_TOP 1250
#define SAMPLES_PER_BIT 11
