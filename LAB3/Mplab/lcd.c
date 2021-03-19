//* Liberia basada en la libreira LCD4bits de Pablo Mazariegos

#include <xc.h>
#include <stdint.h>
#include "lcd.h"
#define _XTAL_FREQ 8000000

//funcion para imprimir un caracter
void print_LCD_Char(char caracter){
    RS = 1;  //para enviar direcciones de los caracteres        
    PUERTO(caracter);//llamo a puerto
    EN = 1;//para poder enviar el valor
    __delay_us(5);
    EN = 0;//para saber que ya se envio el valor(caracter)
    __delay_us(5);
    __delay_us(50);
}

void PUERTO(uint8_t x){
    //para darle la direccion al caracter segun el tamaño del mismo 
    if(x & 1){D0=1;}else{D0=0;}
    if(x & 2){D1=1;}else{D1=0;}
    if(x & 4){D2=1;}else{D2=0;}
    if(x & 8){D3=1;}else{D3=0;}
    if(x & 16){D4=1;}else{D4=0;}
    if(x & 32){D5=1;}else{D5=0;}
    if(x & 64){D6=1;}else{D6=0;}
    if(x & 128){D7=1;}else{D7=0;}
   
}
//funcion para enviar datos a la LCD
void comandosLCD(uint8_t x){
    RS=0;//para modificar contraste o algo de la LCD
    PUERTO(x);
    EN=1;//para poder enviar el valor o caracter
    __delay_us(5);
    EN=0;//saber que ya se envio el valor o caracter
    __delay_us(5);
    __delay_ms(2);
}
//limpiar LCD
void LCD_clear(void){
    comandosLCD(0);
    comandosLCD(1);
}//limpiar la lcd
//funcion para iniciar la LCD
void LCD_Init(){//funcion para inicializar la LCD 
    RS=0;
    EN=0;
    PUERTO(0x00);//direcciones que nos proporciona la LCD
   __delay_ms(50);
   comandosLCD(0x02);
   comandosLCD(0x38);
   comandosLCD(0x0C);
   comandosLCD(0x06);
}
//Funcion para configurar el cursor
void LCD_Set_Cursor(uint8_t x,uint8_t y){
	uint8_t a;
	if(x == 1)//instrucciones para saber en que linea se colocara (arriba)
	{
        a = 0x80 + y;//direccion (hexadecimal) y posicion para colocarlo en la fila 
                        //adecuada para irse leyendo adecuadamente 
		comandosLCD(a);
	}
	else if(x == 2)//instruccione para saber en que linea se colocara (abajo)
	{
		a = 0xC0 + y;//direccion(hexadecimal) y posicion para colocarlo en la fila 
                       //adecuada para ire leyendo adecuadamente
		comandosLCD(a);
	}
}
//funcion para enviar un string
void print_LCD_String(char *a){//funcion para poder imprimir texto usando el puntero 
                                //para guardar la direccion del registro o valor de a
	int i;                      
	for(i=0;a[i]!='\0';i++)    
	   print_LCD_Char(a[i]);
}
