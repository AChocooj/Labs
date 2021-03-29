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
void printDirectory(void);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while(!Serial){
  ;//Esperamos a que se conecte el puerto
}
SPI.setModule(0);//Configuracion para la inicializacion del SPI
Serial.print("Inicializando la memoria SD...");
if (!SD.begin(4)){
  Serial.println("Inicializacion fallida...!");//inicializacion fallida de la SD
  return;
}
Serial.println("Inicializacion correcta :D");
root = SD.open("/");//directorio de la rama de la SD
printDirectory(root, 0);//llamamos al directorio de la SD
}
void loop() {
  // put your main code here, to run repeatedly: 
if (Serial.available()>0){
  Byte = Serial.read();
  if (Byte == '1'){//seleccionaria el primer archivo que tenga
    myFile = SD.open("YOSHI.txt");//debe de ir el nombre del archivo 
    if (myFile){
      while (myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
    }
    else{
      Serial.println("error al abrir el .txt");
    }
  }
if (Byte == '2'){
  myFile = SD.open("BOWSER.txt");//segundo archivo
  if(myFile){
    while (myFile.available()){
      Serial.write(myFile.read());
    }
    myFile.close();
  }
  else{
    Serial.println("error al abrir el .txt");
  }
}
if(Byte == '3'){
  myFile = SD.open("MARIO.txt");//tercer archivo
  if(myFile){
    while (myFile.available()){
      Serial.write(myFile.read());
    }
    myFile.close();
  }
  else{
    Serial.println("error al abrir el .txt");
  }
} 
}
}
/*La funcion del vector de interrupciones y las subrutinas
  para el directorio de la SD */
void printDirectory(File dir, int numTabs){
  while(true){
    File entry = dir.openNextFile();
    if(!entry){//no más archivos
      break;
    }
    for (uint8_t i=0; i<numTabs; i++){
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()){
      Serial.println("/");
      printDirectory(entry, numTabs+1);
    }
    else{
      //moestarara el tamaño de los archivos 
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
