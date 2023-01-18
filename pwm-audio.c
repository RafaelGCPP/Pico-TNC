 #include "pwm-audio.h"
 
 void setup_pwm_generator()
 {
      // Setup PWM generator
    
    gpio_set_function(AUDIO_OUTPUT_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(AUDIO_OUTPUT_PIN);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv_int(&config, AUDIO_PWM_DIVIDER);
    pwm_config_set_wrap(&config, AUDIO_PWM_TOP);
    pwm_init(slice_num,&config,false);
    
}