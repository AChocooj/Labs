
 /* File:   lab2.c
 * Author: Allison Chocooj 
 *
 * Created on 28 de enero de 2021, 05:25 PM*/
//******************************************************************************
// Importación de Librerías
//******************************************************************************
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16f887.h>
#include "PORTB.h"
#include "ADC.h"
#include "Multiplexado.h"

//******************************************************************************
// Palabra de configuración
//******************************************************************************
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
//******************************************************************************
// Variables
//******************************************************************************
#define _XTAL_FREQ 8000000
#define trans1 PORTEbits.RE0
#define trans2 PORTEbits.RE1 //definicion para los transistores

//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void Setup(void); 
void __interrupt() inter(void); //funcion para la interrupcion 


char con1 = 0;//valor del contador
char valor_adc;
char adc_mas_sig;//variables para el adc 
char adc_menos_sig;
char multiple1;//variable para las multiplexacioens
char multiple2;
char bandera = 1;
//tabla para los numero y letras del display 
char tabla [16]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111,0b01110111,0b01111100,0b00111001,0b01011110,0b01111001,0b01110001};

//******************************************************************************
// Configuración
//******************************************************************************
void Setup(void){
    ADCON0 = 0b01010101; // habilito el ADC 
    ANSEL = 0b00000000; //AN0 como analógico
    TRISA = 0b00000000; // que peurto quiero que sea analogico
    
    TRISB = 0b00000011; // RB0 Y RB1 como entrada y las demas salidas
    ANSELH = 0b00000000;
    
    //configuracion de salidas digitales
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0b00000000;
    PORTC = 0b00000000;
    PORTD = 0b00000000; 
    PORTE = 0b00000000;
    
}

void __interrupt() inter(void){
  if (INTCONbits.T0IF == 1){ //reviso la interrupcion del timer 
        TMR0 = 100;
        if(trans1 == 1){//si el primer transistor es 1, apago el primero y enciendo el segundo 
            trans1 = 0;
            trans2 = 1; //encendemos el transistor 2
            PORTC = multiple2; //y todo el puerto c es para el segundo display
                
            }else{
                trans1 = 1;//si no apago el segundo y enciendo el primero 
                trans2 = 0;
                PORTC = multiple1;//y todo el porto c es para el segundo display 
             }
    INTCONbits.T0IF	 = 0;//y apago la bandera del timer 0
  }
  if(PIR1bits.ADIF == 1){ //reviso la interrupcion del ADC 
      bandera = 1; //si la bandera es 1 hago la jugada
  
     asm("MOVF    ADRESH, W");//muevo el valor del adc al registro w
     asm("MOVWF   _valor_adc");//luego lo muevo el valor del adc 
     asm("MOVWF   _adc_menos_sig");//muevo el valor a una variable que es del menos significativo 
 
     asm("SWAPF   ADRESH,  W");//muevo el valor del adc al registro w 
     asm("ANDLW   0b00001111");//hago un and para hacer una mascara y
     asm("MOVWF   _adc_mas_sig");//mover a el valor del adc a los bits mas significativos
    
     asm("MOVF    _adc_menos_sig, W");//muevo el valor del adc al registro w
     asm("ANDLW   0b00001111");//hago un and para hacer un mascara y 
     asm("MOVWF   _adc_menos_sig"); //mover el valor del adc a los bits menos significativos
     PIR1bits.ADIF = 0; //limpio la bandera
  } 
  if(INTCONbits.RBIF == 1){//reviso la interrupcion del puerto b para los botones
      if(PORTBbits.RB0 == 1){//si el boton1 es igual a 1 aumenta el contador
                con1++;
      }
      if(PORTBbits.RB1 == 1){//si el boton2 es igual a 1 el decrementa el contador
                con1--;                  
            }
      }
      INTCONbits.RBIF = 0;//apago y limpio la bandera
  }  

//******************************************************************************
// Ciclo principal
//******************************************************************************
void main(void) { 
    Setup();//llamo mi funcion de configuracion 
    Timer0();//llamo a la funcion del timer 0
    config_PORTB();//llamo a la funcion de las interrupciones en el puerto B 
    //**************************************************************************
    // Loop principal
    //************************************************************************** 
    while(1){
    config_ADC(bandera); // mando a llamar a la funcion del ADC, mi libreria que cree 
    multiple2 = tabla[adc_mas_sig]; // a mi variable de multiplexacion le asigno dentro de mi tabla el valor 
                                    //mas significativo de mi adc 
    multiple1 = tabla[adc_menos_sig];// a mi variable de multiplexacion le asigno dentro de mi tabla el valor 
                                    //menos significativo de mi adc 
    PORTD = con1;//a mi puerto D le asigno el valor del contador de 8 bits
    if(valor_adc > con1){//cuando el valor del adc sea mayor al del contador 
        PORTCbits.RC7 = 1;//enciendo la alarma que esta en el puerto C7 
    }else{                  //de lo contrario se mantiene apagado
        PORTCbits.RC7 = 0;
    }
  }
}
