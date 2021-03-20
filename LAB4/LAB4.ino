//declaracion de pines del jugador 1
int led1 = PB_0;
int led2 = PB_1;
int led3 = PB_2;
int led4 = PB_3;
int led5 = PB_4;
int led6 = PB_5;
int led7 = PB_6;
int led8 = PB_7;
//declaracion de pines del jugador 2
int led9 = PD_0;
int led10 = PD_1;
int led11 = PD_2;
int led12 = PD_3;
int led13 = PC_4;
int led14 = PC_5;
int led15 = PC_6;
int led16 = PC_7;
//declaracion de pines para el semaforo
int ledR = RED_LED;
int ledG = GREEN_LED;
int ledB = BLUE_LED;
//leds de ganador
int led17 = PA_6;
int led18 = PA_7;
//***************************************************
//varias variables 
//***************************************************
int avanzar = PUSH2;//puerto para el push2 de la tiva
int avanzar1 = PUSH1;//puerto para el push1 de la tiva
int presionado1 = 0;//variable para el antirrebote
int presionado2 = 0;//variable para el anterrebote
int contador1;//variable del contador1
int contador2;//variable del contador2

void jugador1(void);
void jugador2(void);
void semaforo(void);
void win(void);

void setup() {
  //declaracion de entradas/salidas digitales
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(led5, OUTPUT);
pinMode(led6, OUTPUT);
pinMode(led7, OUTPUT);
pinMode(led8, OUTPUT);

pinMode(led9, OUTPUT);
pinMode(led10, OUTPUT);
pinMode(led11, OUTPUT);
pinMode(led12, OUTPUT);
pinMode(led13, OUTPUT);
pinMode(led14, OUTPUT);
pinMode(led15, OUTPUT);
pinMode(led16, OUTPUT);

pinMode(ledR, OUTPUT);
pinMode(ledG, OUTPUT);
pinMode(ledB, OUTPUT);

pinMode(led17, OUTPUT);
pinMode(led18, OUTPUT);

pinMode(avanzar, INPUT_PULLUP);
pinMode(avanzar1, INPUT_PULLUP);  

jugador1();
jugador2();
semaforo();
win();
}

void loop(){


jugador1();
jugador2();
win();
}


void jugador1(void){
  //secuencia para aumentar el contador
if (digitalRead(avanzar) == LOW){
  presionado1 = 1;//cambia de estado si se presiona el pulsador 1
}
if (digitalRead(avanzar) == HIGH && presionado1 == 1){
  presionado1 = 0;//se reinicia la variable del antirrebote
  contador1++;//el contador aumenta una unidad
  //if (contador1 == 8){
    //contador1 = 0;//se reinicia el contador regresando al led 1
  //}
}
//switch con todos los casos para el contador de decada
//este solo para el jugador 1 
switch (contador1)
  {
    //Enciende los LEDs de acuerdo al contador
    case 0:
      digitalWrite(led1, HIGH); //Enciende el LED 1 y apaga los demas
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;

    case 1:
      digitalWrite(led1, LOW); //Enciende el LED 2 y apaga los demas
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;

    case 2:
      digitalWrite(led1, LOW); //Enciende el LED 3 y apaga los demas
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;

    case 3:
      digitalWrite(led1, LOW); //Enciende el LED 4 y apaga los demas
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;

    case 4:
      digitalWrite(led1, LOW); //Enciende el LED 5 y apaga los demas
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;
      
     case 5:
      digitalWrite(led1, LOW); //Enciende el LED 6 y apaga los demas
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, HIGH);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break; 
       
      case 6:
      digitalWrite(led1, LOW); //Enciende el LED 7 y apaga los demas
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, HIGH);
      digitalWrite(led8, LOW);
      break; 
      
      case 7:
      digitalWrite(led1, LOW); //Enciende el LED 8 y apaga los demas
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, HIGH);
      break; 
  }
}
void jugador2(void){
  //secuencia para aumentar el contador2
if (digitalRead(avanzar1) == LOW){
  presionado2 = 1;//cambia de estado si se presiona el pulsador 2
}
if (digitalRead(avanzar1) == HIGH && presionado2 == 1){
  presionado2 = 0;//se reinicia la variable del antirrebote
  contador2++;//el contador aumenta una unidad
  if (contador2 == 8){
    contador2 = 0;//se reinicia el contador regresando al led 1
  }
}

  //switch con todos los casos para el contador de decada
//este solo para el jugador 2
  switch (contador2){
     //Enciende los LEDs de acuerdo al contador
    case 0:
      digitalWrite(led9, HIGH); //Enciende el LED 9 y apaga los demas
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;

    case 1:
      digitalWrite(led9, LOW); //Enciende el LED 10 y apaga los demas
      digitalWrite(led10, HIGH);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;

    case 2:
      digitalWrite(led9, LOW); //Enciende el LED 11 y apaga los demas
      digitalWrite(led10, LOW);
      digitalWrite(led11, HIGH);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;

    case 3:
      digitalWrite(led9, LOW); //Enciende el LED 12 y apaga los demas
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, HIGH);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;

    case 4:
      digitalWrite(led9, LOW); //Enciende el LED 13 y apaga los demas
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, HIGH);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;
      
     case 5:
      digitalWrite(led9, LOW); //Enciende el LED 14 y apaga los demas
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, HIGH);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break; 
       
      case 6:
      digitalWrite(led9, LOW); //Enciende el LED 15 y apaga los demas
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, HIGH);
      digitalWrite(led16, LOW);
      break; 
      
      case 7:
      digitalWrite(led9, LOW); //Enciende el LED 16 y apaga los demas
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, HIGH);
      break; 
  }
}
void semaforo(void){
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, LOW);
  delay(1000);
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  delay(1000);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, HIGH);
  delay(1000);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
}
void win(void){
if (contador1==8){
  digitalWrite(led17, HIGH);  
}
if (contador2==8){
  led18=HIGH;
}
}
