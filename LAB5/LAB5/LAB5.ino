/*Allison Chocooj 
18834
MOSI - pin 11
MISO - pin 12 
CLK - pin 13 
CS - pin 4
*/

#include <SPI.h>
#include <SD.h>

File myFile;
File root;
int Byte = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while(!Serial){
  ;//Esperamos a que se conecte el puerto
}
SPI.setModule(0);//Configuracion para la inicializacion del SPI
Serial.print("Inicializando la memoria SD...");
pinMode(10, OUTPUT);//pin 10 como salida

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
