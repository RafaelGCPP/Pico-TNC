#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/interp.h"
#include "hardware/timer.h"
#include "pico/cyw43_arch.h"
#include "hardware/pwm.h"
#include "afsk-parameters.h"

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Put your timeout handler code in here
    return 0;
}

int main()
{
    
    // The clock frequency must be set to 132MHz before initializing the serial ports
    // The 1200 bps AFSK uses 2200Hz for space and 1200Hz for mark. Using 13200Hz as PWM frequency,
    // there will be 11 samples per bit.
    // Also we can implemt those 2 frequencies using a sinusoid of 200Hz as base signal and 
    // decimating it by 6 for 1200Hz or 11 for 2200Hz.
    
    set_sys_clock_khz(PICO_TNC_CLOCK, true);

    // Setup PWM generator
    
    gpio_set_function(AUDIO_OUTPUT_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(AUDIO_OUTPUT_PIN);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv_int(&config, AUDIO_PWM_DIVIDER);
    pwm_config_set_wrap(&config, AUDIO_PWM_TOP);
    pwm_init(slice_num,&config,false);
    

    
    
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
