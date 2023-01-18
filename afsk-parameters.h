/*
This file define the parameters for implementing AFSK1200 
for the following parameters on the PWM device:

* 132MHz clock frequency
* divide-by-8
* 1250 count period

The output pwm frequency will be 13200Hz

The sine table  will have 66 entries corresponding to a
200Hz sinewave.

It also uses the PWM sampling theorem and limits the amplitude to
0.697, and it is centered around 1.

Thus, it is generated as:

round((1+sin(2*pi*200/13200*n)*0.697)*1250/2)
*/

uint16_t sine200hz[66] = {
  [ 625,  666,  707,  748,  787,  825,
    861,  894,  926,  954,  980, 1002, 
   1021, 1037, 1048, 1056, 1060, 1060,
   1056, 1048, 1037, 1021, 1002,  980,
    954,  926,  894,  861,  825,  787, 
    748,  707,  666,  625,  584,  543,  
    502,  463,  425,  389,  356,  324, 
    296,  270,  248,  229,  213,  202,  
    194,  190,  190,  194,  202,  213,  
    229,  248,  270,  296,  324,  356,  
    389,  425,  463,  502,  543,  584  
};
