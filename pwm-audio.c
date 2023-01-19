#include "pwm-audio.h"

// Although global variables are usually frown upon
// when developing for microcontrollers their usage
// reduce memory management overhead

uint32_t audio_buffer[2][AUDIO_BUFFER_SIZE] __attribute__((aligned(512)));

uint pwm_audio_slice_num;
uint pwm_audio_channel;
uint pwm_dma_chan;

void setup_pwm_generator()
{
  // Setup PWM generator

  // The 1200 bps AFSK uses 2200Hz for space and 1200Hz for mark (Bell 202).
  // Using 13200Hz as PWM frequency, there will be 11 samples per bit.
  // Also we can implemt those 2 frequencies using a sinusoid of 200Hz as base signal and
  // decimating it by 6 for 1200Hz or 11 for 2200Hz.

  // Set an output pin as PWM and configure it for divide-by-8 clock and 1250 count top.
  // The PWM will not be started.

  gpio_set_function(AUDIO_OUTPUT_PIN, GPIO_FUNC_PWM);
  pwm_audio_slice_num = pwm_gpio_to_slice_num(AUDIO_OUTPUT_PIN);
  pwm_audio_channel = pwm_gpio_to_channel(AUDIO_OUTPUT_PIN);

  pwm_config config = pwm_get_default_config();
  pwm_config_set_clkdiv_int(&config, AUDIO_PWM_DIVIDER);
  pwm_config_set_wrap(&config, AUDIO_PWM_TOP);
  pwm_set_chan_level(pwm_audio_slice_num, pwm_audio_channel, AUDIO_PWM_TOP);
  pwm_init(pwm_audio_slice_num, &config, false);
}

void setup_pwm_generator_dma_channel()
{
  // Next we setup a DMA channel to read from the audio buffer and feed the
  // PWM generator. It will not be started at creation

  pwm_dma_chan = dma_claim_unused_channel(true);

  dma_channel_config pwm_dma_chan_config = dma_channel_get_default_config(pwm_dma_chan);
  // Transfers 32-bits at a time, increment read address so we pick up a new fade value each
  // time, don't increment writes address so we always transfer to the same PWM register.
  channel_config_set_transfer_data_size(&pwm_dma_chan_config, DMA_SIZE_32);
  channel_config_set_read_increment(&pwm_dma_chan_config, true);
  channel_config_set_write_increment(&pwm_dma_chan_config, false);
  // Transfer when PWM slice that is connected to the LED asks for a new value
  channel_config_set_dreq(&pwm_dma_chan_config, DREQ_PWM_WRAP0 + pwm_audio_slice_num);

  dma_channel_configure(
      pwm_dma_chan,                           // Name of DMA channel
      &pwm_dma_chan_config,                   // Configuration structure
      &pwm_hw->slice[pwm_audio_slice_num].cc, // Write to PWM counter compare register
      audio_buffer[0],                        // Read values from fade_a array
      512,                                    // nsamples words to transfer
      true                                    // Don't start yet.
  );
}

void zero_buffers()
{
  for (uint i = 0; i < 2; i++)
    for (uint j = 0; j < AUDIO_BUFFER_SIZE; j++)
      audio_buffer[i][j] = 0;
}

void send_audio(uint nsamples, uint nbuffer, bool irq0, interrupt_handler dma_interrupt_handler)
{

  // To send audio we set the read address to the audio buffer and write the number of samples to the trigger register.

  dma_channel_set_irq0_enabled(pwm_dma_chan, irq0);
  if (irq0)
  {
    irq_set_exclusive_handler(DMA_IRQ_0, *dma_interrupt_handler);
    irq_set_enabled(DMA_IRQ_0, true);
  }

  dma_channel_set_read_addr(pwm_dma_chan, audio_buffer[nbuffer], false);
  dma_channel_set_trans_count(pwm_dma_chan, nsamples, true);
}