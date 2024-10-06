#include <16F877A.h>
#device ADC=10

#FUSES PUT                   	//Power Up Timer
#FUSES BROWNOUT              	//Reset when brownout detected
#FUSES NOWRT                 	//Program memory not write protected

#use delay(crystal=8MHz)
#use STANDARD_IO( B )
#use FIXED_IO( B_outputs=PIN_B0 )
#define Led	PIN_B0
#define Voltage_Warning	PIN_B1
#define Temperature_Warning	PIN_B2

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)

