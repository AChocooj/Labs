/*
 * File:   lab3.c
 * Author: Allison Chocooj
 *
 * Created on 4 de febrero de 2021, 04:02 PM
 */
// CONFIG1
#pragma config FOSC = XT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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
#define _XTAL_FREQ 8000000 
//incluir librerias
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "lcd.h"
#include "adc.h"
#include "USART.h"

//funciones 
void configIO(void);
float conversion(uint8_t b);
//variables
char LecturaUSART=0;
uint8_t contador=0;
uint8_t valorADC1;
uint8_t valorADC2;
float Volt1=0.0;
float Volt2=0.0; //para guardar el valor del voltaje de los dos ADC
char datos[20];

//interrupcion del RCIF para la recepcion de datos en USART
void __interrupt() ISR(){
    if(RCIF==1){//Si se levanta la bandera del UART
        RCIF=0;//apaga la bandera del UART
        LecturaUSART=Read_USART();  //guardar el valor recibido
        //comparar el valor con + o -, si es + aumenta el contador, si es - decrementa el contador
        if(LecturaUSART=='+'){contador++;} 
        else if(LecturaUSART=='-'){contador--;}
    }
}

void main(void) {
    configIO();//llamar a la funcion de configurar puertos 
    configura_adc();//llamar a la funcion de condigurar ADC
    USART_Init(9600);//llamar a la funcion de configurar USAR
    LCD_Init();//iniciar la LCD
    LCD_clear();//funcion para limpiar la LCD
    while(1){
        //leer los pines del ADC, y guardar su valor en una variable
        valorADC1 = LecturaADC(0);
        valorADC2 = LecturaADC(1);
        //convertir los valores en binario a voltajes
        Volt1=conversion(valorADC1);
        Volt2=conversion(valorADC2);
        //enviar los datos por USART hacia la pc
        Write_USART_String("V1   V2   contador \n");//enviar los datos del pic a la compu
        sprintf(datos, "%2.1f   %2.1f   %d", Volt1,Volt2,contador);//convertir los valores de voltaje y el contador a un string para que los lea bien la compu
        Write_USART_String(datos);//enviar el string con los valores a la pc
        Write_USART(13);//13 y 10 la secuencia es para dar un salto de linea 
        Write_USART(10);
        LCD_clear();//limpiar la LCD
        LCD_Set_Cursor(1,1);//colocar el cursor en fila=1,columna=1
        print_LCD_String("V1   V2   conta");//enviar un string para mostrar que voltaje es y el contador
        LCD_Set_Cursor(2,0);//colocar el cursor en fila=2, columna =0
        print_LCD_String(datos);//enviar los datos a la LCD
        __delay_ms(500);
    }
    return;
}
void configIO(){
    //configuracion de puertos, todos en salidas y digitales
    TRISB=0;
    TRISA=0;
    TRISE=0;
    ANSEL=0;
    ANSELH=0;
    PORTB=0;
    PORTE=0;
    //configuracion de interrupciones, se habilito la interrupcion RCIF
    INTCONbits.PEIE=1;
    PIE1bits.RCIE=1;
    PIR1bits.RCIF=0;
    INTCONbits.GIE=1;

}

//funcion para convertir los valores  binarios a voltajes.
float conversion(uint8_t b){
    return b*0.0196;    //5 divido 255 para saber el valor del voltaje en binario
}