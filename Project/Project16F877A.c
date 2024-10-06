#include <Tarea116F877A.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

char dato;                                           // Variable de lectura de cada caracter
char Received_Token[12];                                  // Variable donde se almacena la cadena de caractere
int estado; 

int16 velocidad=250;
int16 change=20;
void main()
{
   port_b_pullups(0xFF);
   setup_timer_2(T2_DIV_BY_16,124,1);      //1.0 ms overflow, 1.0 ms interrupt

   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   set_pwm1_duty((int16)0);
   set_pwm2_duty((int16)0);
   
   //printf("Hi\n");
   while(TRUE)
   {
   if(input(Voltage_Warning)==1 || input(Temperature_Warning)==1){
   set_pwm1_duty((int16)0);
   set_pwm2_duty((int16)0);   
   }
   if(input(Voltage_Warning)==1){
   output_high(Led);
   } else {
   output_low(Led);
   }
   
   if(kbhit(PORT1))                            // Verificacion si ha llegado un dato por el puerto serial
      {
         fgets(Received_Token, PORT1);                    // Lee la cadena de caracteres y la almacena el la variable Received_Token      
         dato = fgetc(PORT1);                        // Recibe los caracteres leidos por PORTB1
         switch(&Received_Token)                          // Compara las cadenas de caracteres recibidas
         {
            case "subir":
            estado=1;
            set_pwm1_duty((int16)0);
            set_pwm2_duty(velocidad);
            printf("Subiendo\n");
            break;
         
            case "bajar":
            estado=0;
            set_pwm1_duty(velocidad);
            set_pwm2_duty((int16)0);
            printf("Bajando\n");
            break;
         
            case "parar":
            estado=2;
            set_pwm1_duty((int16)0);
            set_pwm2_duty((int16)0);
            printf("Detenido\n");
            break;
         
            case "acelerar":
            if (velocidad+change>=500){
            velocidad=500;
            printf("No puede acelerar más %ld \n", velocidad); 
            } 
            else {
            velocidad+=change;
            printf("Acelerando %ld \n", velocidad); 
            }

            if (estado==1) {
            set_pwm1_duty((int16)0);
            set_pwm2_duty(velocidad);         
            } else if (estado==0){
            set_pwm1_duty(velocidad);
            set_pwm2_duty((int16)0);
            }
            break;
            
            case "desacelerar":            
            if (velocidad<=change){
            velocidad=0;
            printf("No puede desacelerar más %ld \n", velocidad);
            } 
            else {
            velocidad-=change;
            printf("Deascelerando %ld \n", velocidad); 
            }

            if (estado==1) {
            set_pwm1_duty((int16)0);
            set_pwm2_duty(velocidad);         
            } else if (estado==0){
            set_pwm1_duty(velocidad);
            set_pwm2_duty((int16)0);
            }
            break;

         }   
      }
   }   
}
