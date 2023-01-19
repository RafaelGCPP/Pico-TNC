#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>

#include "pwm-audio.h"
#include "afsk-parameters.h"

int main()
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
        send_audio(AUDIO_BUFFER_SIZE, 0, false, NULL);
        sleep_ms(10000);
    }
    return 0;
}
