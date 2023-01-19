#pragma once

#include <stdint.h>
#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <hardware/dma.h>
#include "afsk-parameters.h"

typedef void (*interrupt_handler)(void);


void setup_pwm_generator();
void setup_pwm_generator_dma_channel();
void send_audio(uint nsamples, uint nbuffer, bool irq0, interrupt_handler ih);
void zero_buffers();


#define AUDIO_BUFFER_SIZE ((32 + 6) * SAMPLES_PER_BIT)

extern uint32_t audio_buffer[2][AUDIO_BUFFER_SIZE];
extern uint pwm_dma_chan;
