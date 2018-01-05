#include <16F628a.h>         //Se indica el micro que se va a utilizar.

#use delay (clock=4000000)  //Se indica la velocidad del XTAL=4MHz.

#fuses XT, NOWDT  //Se indican los fuses activos/inactivos.

#Byte TRISA = 0x85
#Byte PORTA = 0x05
#Byte TRISB = 0x86
#Byte PORTB = 0x06
#DEFINE Incremento PIN_A0
#DEFINE Decremento PIN_A1
#DEFINE S1 PIN_A2
#DEFINE S2 PIN_A3
#DEFINE S3 PIN_B4
#DEFINE S4 PIN_B1
#DEFINE S5 PIN_B2
#DEFINE S6 PIN_B3
int a=1;
int cont=0;
int16 g=249;


#int_EXT
void control(){
output_high(PIN_B5);
SET_TIMER0(g);
}

#int_TIMER0
void timer0(){
   output_low(PIN_B5);
   output_high(S1);
   output_high(S6);
   SET_TIMER1(64148);
   delay_us(400);
   output_low(S1);
   output_low(S6);
   cont++;
   
}
#int_TIMER1
void timer1(){
   if(cont==1){
   output_high(S1);
   output_high(S2);
   SET_TIMER1(64148);
   delay_us(400);
   cont++;
   output_low(S1);
   output_low(S2);  
   }
   else if(cont==2){
   output_high(S2);
   output_high(S3);
   SET_TIMER1(64148);
   delay_us(400);
   cont++;
   output_low(S2);
   output_low(S3);
   
   }
   else if(cont==3){
   output_high(S3);
   output_high(S4);
   SET_TIMER1(64148);
   delay_us(400);
   output_low(S3);
   output_low(S4);
   cont++;

   }
   else if(cont==4){
   output_high(S4);
   output_high(S5);
   SET_TIMER1(64148);
   delay_us(400);
   output_low(S4);
   output_low(S5);
   cont++;
   }else if(cont==5){
   output_high(S5);
   output_high(S6);
   delay_us(400);
   output_low(S5);
   output_low(S6);
   cont=0;   
   }
   
}


void main ()
{
//Entradas y salidas
TRISA = 0b00011; //1 = ENTRADA, 0 = SALIDA
TRISB = 0b00000001; //1 = ENTRADA, 0 = SALIDA
output_low(S1);
output_low(S2);
output_low(S3);
output_low(S4);
output_low(S5);
output_low(S6);
output_low(PIN_B5);
setup_timer_0(RTCC_INTERNAL |RTCC_DIV_64 |RTCC_8_BIT );
enable_interrupts(INT_TIMER0);//habilitamos la interrupcion que deseamos
enable_interrupts(GLOBAL);

setup_timer_1 ( T1_INTERNAL | T1_DIV_BY_2);//Setup timer: Reloj interno, preescaler= 2
enable_interrupts(INT_TIMER1);//habilitamos la interrupcion que deseamos
enable_interrupts(GLOBAL);

enable_interrupts(int_ext);      //activar interrupcion externa
ext_int_edge(L_TO_H);         //configuracion:interrupcion cuando señal esta en flanco de subida
enable_interrupts(GLOBAL);      //todas las interrupciones desactivadas

while(TRUE){

if(input(Incremento)==1){               //¿se ha pulsado up?
   while(input(Incremento)==1){}
   if(a==18){
   g=130;
   a=18;
   }else{
   g=g-7;
   a++;}
}

if(input(Decremento)==1){               //¿se ha pulsado down?
   while(input(Decremento)==1){}
    
   if(a==1){
   a=1;
   g=249;
   }
   else{
   g=g+7;
   a--; 
   }
}

}

}
