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
int led9 = PF_0;
int led10 = PF_1;
int led11 = PF_2;
int led12 = PF_3;
int led13 = PF_4;
int led14 = PD_0;
int led15 = PD_1;
int led16 = PD_2;

int avanzar = PUSH2;//puerto para el push2 de la tiva
int avanzar1 = PUSH1;//puerto para el push1 de la tiva
int presionado1 = 0;//variable para el antirrebote
int presionado2 = 0;//variable para el anterrebote
int contador1;//variable del contador1
int contador2;//variable del contador2


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

pinMode(avanzar, INPUT_PULLUP);
pinMode(avanzar1, INPUT_PULLUP);  
}

void loop(){
  //secuencia para aumentar el contador
if (digitalRead(avanzar) == LOW){
  presionado1 = 1;//cambia de estado si se presiona el pulsador
}
if (digitalRead(avanzar) == HIGH && presionado1 == 1){
  presionado1 = 0;//se reinicia la variable del antirrebote
  contador1++;//el contador aumenta una unidad
  if (contador1 > 7){
    contador1 = 0;//se reinicia el contador regresando al led 1
  }
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
