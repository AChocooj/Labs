//Allison Chocooj --- 18834
//**************************************************************************************************************
// Librerias
//**************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

#define XTAL 16000000

//**************************************************************************************************************
// Variables
//**************************************************************************************************************
uint32_t i = 0; //cambiar nombres
uint32_t j = 0;
uint32_t Parqueos = 0; //display
uint32_t Sensor1 = 0; // sensores
uint32_t Sensor2 = 0;
uint32_t Sensor3 = 0;
uint32_t Sensor4 = 0;
uint8_t Sensores = 0;
//**************************************************************************************************************
// Prototipos de Funciones
//**************************************************************************************************************
void delay(uint32_t msec);
void delay1ms(void);
void Display7(uint32_t numero);

//**************************************************************************************************************
// Funci�n Principal
//**************************************************************************************************************
int main(void)
 {
    // Se setea oscilador externo de 16MHz
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN| SYSCTL_XTAL_16MHZ);  //16MHz

    // Se setea oscilador externo de 16MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    // Se asigna reloj a los puerto
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);


    // Se configuran los puertos como entradas y salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0);

    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);

    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0);
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= GPIO_PIN_7;
    GPIOPinConfigure(GPIO_PD7_U2TX);

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2); // enable uart2
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7); // pines de control del uart
    //habilito el uart
    UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTIntClear(UART2_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX | UART_INT_FE | UART_INT_PE | UART_INT_BE | UART_INT_OE | UART_INT_RI | UART_INT_CTS | UART_INT_DCD | UART_INT_DSR);




       //**********************************************************************************************************
       // Loop Principal
       //**********************************************************************************************************

    while (1)
    {
        Sensor1 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4) && GPIO_PIN_4); // lee el pin y se compara para saber si esta
        Sensor2 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5) && GPIO_PIN_5); // encendido o apagado
        Sensor3 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6) && GPIO_PIN_6);
        Sensor4 = (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_7) && GPIO_PIN_7);

        Sensores = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7) >> 4; // lee el puerto y corre  4

        Parqueos = ((((4 - Sensor4) - Sensor3) - Sensor2) - Sensor1) ; // resta para saber la cantidad de parqueos
        Display7(Parqueos);

        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, Sensores); //leds verdes = 1
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, ~Sensores); // leds rojas = 0

        UARTCharPut(UART2_BASE, Sensor1); // envio al uart
        UARTCharPut(UART2_BASE, Sensor2);
        UARTCharPut(UART2_BASE, Sensor3);
        UARTCharPut(UART2_BASE, Sensor4);
        delay(100);
    }

}

//**************************************************************************************************************
// Funci�n  delay en milisegundos
//**************************************************************************************************************
void delay(uint32_t msec)
{
    for (i = 0; i < msec; i++)
    {
        delay1ms();
    }

}
//**************************************************************************************************************
// Funcion delay de 1 milisegundos
//**************************************************************************************************************
void delay1ms(void)
{
    SysTickDisable();
    SysTickPeriodSet(16000);
    SysTickEnable();

    while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0); //Pg. 138
}

void Display7(uint32_t numero)
{
    switch(numero) // puerto b, enciende las leds
    {
    case 0: GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, 0x3F); break;
    case 1: GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, 0x06); break;
    case 2: GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, 0x5B); break;
    case 3: GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, 0x4F); break;
    case 4: GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, 0x66); break;
    default: break;
    }
}
