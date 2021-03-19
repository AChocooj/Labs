#include <xc.h> 
#include <stdint.h>  
#include "adc.h"
#define _XTAL_FREQ 8000000

void configura_adc(){  
    ADCON0bits.ADCS=1;//registros para habilitar el ADC 
    ADCON1=0;//habilitar el ADC 
}
uint8_t LecturaADC(uint8_t x){
    switch(x){
        case 0: TRISAbits.TRISA0=1; ANSELbits.ANS0=1; ADCON0bits.CHS=0; break;
        case 1: TRISAbits.TRISA1=1; ANSELbits.ANS1=1; ADCON0bits.CHS=1; break;
        case 2: TRISAbits.TRISA2=1; ANSELbits.ANS2=1; ADCON0bits.CHS=2; break;
        case 3: TRISAbits.TRISA3=1; ANSELbits.ANS3=1; ADCON0bits.CHS=3; break;
        case 4: TRISAbits.TRISA5=1; ANSELbits.ANS4=1; ADCON0bits.CHS=4; break;
        case 5: TRISEbits.TRISE0=1; ANSELbits.ANS5=1; ADCON0bits.CHS=5; break;
        case 6: TRISEbits.TRISE2=1; ANSELbits.ANS6=1; ADCON0bits.CHS=6; break;
        case 7: TRISEbits.TRISE3=1; ANSELbits.ANS7=1; ADCON0bits.CHS=7; break;
        case 8: TRISBbits.TRISB2=1; ANSELHbits.ANS8=1; ADCON0bits.CHS=8; break;
        case 9: TRISBbits.TRISB3=1; ANSELHbits.ANS9=1; ADCON0bits.CHS=9; break;
        case 10: TRISBbits.TRISB1=1; ANSELHbits.ANS10=1; ADCON0bits.CHS=10; break;
        case 11: TRISBbits.TRISB4=1; ANSELHbits.ANS11=1; ADCON0bits.CHS=11; break;
        case 12: TRISBbits.TRISB0=1; ANSELHbits.ANS12=1; ADCON0bits.CHS=12; break;
        case 13: TRISBbits.TRISB5=1; ANSELHbits.ANS13=1; ADCON0bits.CHS=13; break;
        default: return 0;
    }//dependiendo de que puerto quiera usar es el que lee y se mete en la variable x
    //se hizo un case para una mejor visualizacion de cada puerto que se puede utilizar
    //al ser una libreria se definieron para todos los peurtos de ADC que tiene el pic
    ADCON0bits.ADON=1;//inicia la bandera 
    __delay_us(20);
    ADCON0bits.GO=1;//para mandarlo al resultado
    resultado:
    if(ADCON0bits.GO_DONE==1){goto resultado;}
    else {ADCON0bits.ADON=0; return ADRESH;}
}
