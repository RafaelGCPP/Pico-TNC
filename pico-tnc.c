#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/interp.h"
#include "hardware/timer.h"
#include "pico/cyw43_arch.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"

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
    
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                    CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB,
                    132 * MHZ,
                    132 * MHZ);
    
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
