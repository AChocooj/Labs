#include <stdint.h>
#include <pic16f887.h>
#include "PORTB.h"

void config_PORTB(void){
    INTCON	 = 0b11101000;//GIE,PEIE, T0IE, RBIE --> Activas
    //se habilitan las interrupciones 
    IOCBbits.IOCB0 =1; // Habilito las interrupciones del puerto b0
    IOCBbits.IOCB1 =1; // Habilito las interrupciones del puerto b1
}
