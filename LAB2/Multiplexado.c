#include <stdint.h>
#include <pic16f887.h>
#include "Multiplexado.h"

void Timer0(void){ //Interrupciones cada 5 ms
  OPTION_REG = 0x84;//
  TMR0		 = 100;// se usa una calculadora 
  INTCON	 = 0b11101000;//GIE,PEIE, T0IE, RBIE --> Activas interrupciones globales 
}
