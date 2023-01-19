#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>

#include "pwm-audio.h"
#include "afsk-parameters.h"

int main(void)
{
    set_sys_clock_khz(PICO_TNC_CLOCK, true);
    stdio_init_all();
    while (1)
    {
        puts("Hello, world!");

        sleep_ms(5000);
    }
    return 0;
}

void dma_ih(void)
{
    dma_channel_acknowledge_irq0(pwm_dma_chan);
    puts("Interrupted!");
}

int main_test_audio1()
{

    // The clock frequency must be set to 132MHz before initializing the serial ports

    set_sys_clock_khz(PICO_TNC_CLOCK, true);

    setup_pwm_generator();
    setup_pwm_generator_dma_channel();
    zero_buffers();

    // Initialize the stdio interface

    stdio_init_all();

    for (uint i = 0; i < AUDIO_BUFFER_SIZE; i++)
    {
        audio_buffer[0][i] = sine200hz[i % 66];
    }

    while (1)
    {
        puts("Hello, world!");
        send_audio(AUDIO_BUFFER_SIZE, 0, true, dma_ih);
        sleep_ms(5000);
    }
    return 0;
}
