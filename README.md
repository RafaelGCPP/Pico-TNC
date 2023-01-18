# Pico-TNC
A Raspberry Pi Pico W based TNC.

# Goals

- Use PWM with DMA to generate audio
- Implement KISS serial and net
- Implement direwolf's audio decoding capabilities
- Implement a full TNC, with serial or telnet console for standalone operation
- Read GPS messages for APRS

## Current stage

Right now in really early development, exploring how to generate the AFSK 1200bps audio.

# AFSK 1200 bps operation

The Pico will be clocked to 132MHz so that the PWM frequency can be made 13200Hz, which
is 11 times higher than space (1200Hz) and 6 times higher than mark (2200Hz). Then we can 
use a sine table with 66 values (corresponding to 200Hz) to generate every sample, in MFSK.

Each bit will consist on eleven 16-bit samples, and for perfect reconstruction the amplitude 
is limited to 0.637 as per [1]: 

> The theorem states that any bandlimited baseband signal within ±0.637 can be represented by a 
pulsewidth modulation (PWM) waveform with unit amplitude. The theorem states that any bandlimited 
baseband signal within ±0.637 can be represented by a pulsewidth modulation (PWM) waveform with unit 
amplitude. The number of pulses in the waveform is equal to the number of Nyquist samples and the peak 
constraint is independent of whether the waveform is two-level or three-level.

## PWM module configuration

The PWM will be configured to use divide-by-8 and 1250 counts per period, resulting in 13200Hz 
frequency, and will be driven by a DMA transfer from the sample buffer. The sample buffer assumes 
the following packet structure:

- 1 flag byte 
- 28 bytes for the address field
- 2 bytes for control
- 1 byte for protocol ID
- 256 bytes for info
- 2 bytes FCS 
- 1 flag byte

Those are maximum expected field sizes, and total 291 bytes. Bit stuffing will be implemented 
during conversion from the bit stream buffer to the sample buffer. 

Each 32 bits of the bit stream buffer will be converted to 11 samples and are subject to up to 6 
bits of stuffing, thus the sample buffer must support up to 418 16-bit samples.



# References
[1] J. Huang, K. Padmanabhan and O. M. Collins, "The Sampling Theorem With Constant Amplitude Variable Width Pulses," 
in _IEEE Transactions on Circuits and Systems I: Regular Papers_, vol. 58, no. 6, pp. 1178-1190, June 2011, doi: 10.1109/TCSI.2010.2094350.
