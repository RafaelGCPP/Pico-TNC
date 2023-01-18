#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/interp.h"
#include "hardware/timer.h"
#include "pico/cyw43_arch.h"

#include "pwm-audio.h"
#include "afsk-parameters.h"

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Put your timeout handler code in here
    return 0;
}

int main()
{
    
    // The clock frequency must be set to 132MHz before initializing the serial ports
    
    set_sys_clock_khz(PICO_TNC_CLOCK, true);

    setup_pwm_generator();
    setup_pwm_generator_dma_channel();
    
    
    // Initialize the stdio interface
    
    stdio_init_all();

    // Interpolator example code
    interp_config cfg = interp_default_config();
    // Now use the various interpolator library functions for your use case
    // e.g. interp_config_clamp(&cfg, true);
    //      interp_config_shift(&cfg, 2);
    // Then set the config 
    interp_set_config(interp0, 0, &cfg);

    // Timer example code - This example fires off the callback after 2000ms
    add_alarm_in_ms(2000, alarm_callback, NULL, false);


    puts("Hello, world!");

    return 0;
}
