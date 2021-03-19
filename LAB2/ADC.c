#include <stdint.h>
#include <pic16f887.h>
#include "ADC.h"
#define _XTAL_FREQ 8000000

void config_ADC(uint8_t bandera){
    INTCON	 = 0b11101000;//GIE,PEIE, T0IE, RBIE --> Activas es un registro global de las interrupciones
    PIR1bits.ADIF = 0;//estara en 1 cuando la conversión se complete del ADC 
    PIE1bits.ADIE = 1;//habilito la interrupcion de adc 
    ADCON1bits.ADFM = 0; //se justifica los bits a la izquierda para los mas significativos
    if(bandera == 1){
        __delay_us(10);
        bandera = 0;
        ADCON0bits.GO = 1;
        }
    /*si la bandera del ADC es uno le doy un delay de 10 microsegundos para que la conversion del pic no 
     * falle luego apago la bandera que siempre debo de apagar para luego encerndero de nuevo el adc para 
     * seguir con las converisones*/
}
