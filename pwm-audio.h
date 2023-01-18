#pragma once

#include <stdint.h>
#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <hardware/dma.h>
#include "afsk-parameters.h"

void setup_pwm_generator();
void setup_pwm_generator_dma_channel();
 
#define AUDIO_BUFFER_SIZE ((32+6)*SAMPLES_PER_BIT)

extern uint32_t audio_buffer[];