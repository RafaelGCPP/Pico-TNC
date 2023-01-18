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
0.637, and it is centered around 1.

Thus, it is generated as:

round((1+sin(2*pi*200/13200*n)*0.637)*1250/2)
*/

uint16_t sine200hz[66] = {
   625,  663,  700,  737,  773,  807,
   840,  871,  900,  926,  949,  970,
   987, 1001, 1012, 1019, 1023, 1023,
  1019, 1012, 1001,  987,  970,  949,
   926,  900,  871,  840,  807,  773,
   737,  700,  663,  625,  587,  550,
   513,  477,  443,  410,  379,  350, 
   324,  301,  280,  263,  249,  238,
   231,  227,  227,  231,  238,  249, 
   263,  280,  301,  324,  350,  379, 
   410,  443,  477,  513,  550,  587
};
