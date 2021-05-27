/*Allison Chocooj*/
/*Carné 18834*/
/*********************************
  ESP32 Web Server
  Ejemplo de creación de Web server 
  Basándose en los ejemplos de: 
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://electropeak.com/learn
**********************************/
//********************************
// Librerías
//********************************
#include <WiFi.h>
#include <WebServer.h>
//********************************
// Variables globales
//********************************
// SSID & Password
const char* ssid = "TIGO-28EB";  // Enter your SSID here
const char* password = "4D9697500669";  //Enter your Password here
uint8_t Botones[4];
uint8_t Lugares = 0;
WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)
uint8_t LED1pin = 2;
bool LED1status = LOW;
//********************************
// Configuración
//********************************
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);
  pinMode(LED1pin, OUTPUT);
  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);
  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
  server.on("/", handle_OnConnect); 
  server.on("/datos", handle_Data); // handler para enviar datos
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}
//********************************
// loop principal
//********************************
void loop() {
  server.handleClient();          //Inicia servidor
  if (Serial2.available())        //Inicia lectura del UART
    {   
      digitalWrite(2, 1);         //Encendera las led siempre que se reciba datos por UART
        for (int i = 0; i<=3; i++)//Lee 4 bytes y almacenan en un array
        {
          Botones[i] = Serial2.read(); 
        }
        Lugares = (((4 - Botones[0])- Botones[1])- Botones[2])- Botones[3];  //Se realiza el calculo de cuantos parqueos hay
    }
    digitalWrite(2, 0);         //apaga led de lectura UART
}
//********************************
// Handler de Inicio página
//********************************
void handle_OnConnect() {
  server.send(200, "text/html", SendHTML());
}
//********************************
// Handlers
//********************************
void handle_Data() {                          //se envia la data y se concatena los datos a enviar
  server.send(200, "application/json", data_json());
}
//********************************
// Procesador de HTML
//********************************
String SendHTML(void) {
  String ptr = "<!DOCTYPE html>\n";
  ptr = "<html>\n";
  ptr += "<body>\n";
 // ----------------formato del titulo, color,tamaño,centrado,fondo------------------
  ptr +="<body>\n";
  ptr +="<body style=\"background-color:#FA8072;\">\n";
  ptr +="</body>\n";

  ptr +="<style>\n";
  ptr +="h1 {\n";
  ptr +="  text-align: center;\n";
  ptr +="  font-size: 300%;\n";
  ptr +="}\n";
  ptr +="h3 {\n";
  ptr +="  text-align: center;\n";
  ptr +="  font-size: 300%;\n";
  ptr +="}\n";
  ptr +="</style>\n";
  ptr += "<h1>Estacionamientos Cobancito</h1>\n";
  ptr += "<h3>Aca se pueden ver los estados de los parqueos</h3>\n";
//--------------------------------------------------------------------------------------
//----------------------------------espaciados-------------------------------------------------
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
//------------------------------------------------------------------------------------------------
//---------------------------------cuadros para los parqueos-----------------------------------------------
  ptr += "<canvas id=\"Parqueo 1\" width=\"200\" height=\"200\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"Parqueo 2\" width=\"200\" height=\"200\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"Parqueo 3\" width=\"200\" height=\"200\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"Parqueo 4\" width=\"200\" height=\"200\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
//------------------------------------------------------------------------------------------------
//----------------------------------espaciados-------------------------------------------------
   ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
   ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<canvas id=\"0\" width=\"75\" height=\"75\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
//------------------------------------------------------------------------------------------------
//------------------------------variable cantidad para el disp_play------------------------------
  ptr += "<canvas id=\"Cantidad\" width=\"900\" height=\"60\" style=\"border:0px solid #000000;\">\n";
  ptr += "</canvas>\n";
  ptr += "<script>\n";
  
  //------------------funcion para los botones----------------
  ptr += "function boton(n_parqueo, valor){\n";
  ptr += "var canvas = document.getElementById(n_parqueo);\n";
  ptr += "var ctx = canvas.getContext(\"2d\");\n";
  ptr += "if (valor == 0){\n";
  ptr += "ctx.fillStyle = \"#7CFC00\";\n";
  ptr += "};\n";
  ptr += "if (valor == 1){\n";
  ptr += "ctx.fillStyle = \"#fc0303\";\n";
  ptr += "};\n";
  ptr += "ctx.fillRect(0,0,200,100);\n";
  ptr += "ctx.fillStyle = \"#000000\";\n";
  ptr += "ctx.font = \"40px Calibri\";\n";
  ptr += "ctx.strokeText(n_parqueo, 10, 50);\n";
  ptr += "};\n";
  //------------------------------------------------------------------
  //------------cuadro para mostrar la variable de disponibles en el displ_ay---------------
  ptr += "function Estacionamiento(cantidad){\n";
  ptr += "var canvas = document.getElementById(\"Cantidad\");\n";
  ptr += "var ctx = canvas.getContext(\"2d\");\n";
  ptr += "ctx.fillStyle = \"#FA8072\";\n";
  ptr += "ctx.fillRect(0,0,825,40);\n";
  ptr += "ctx.fillStyle = \"#000000\";\n";
  ptr += "ctx.font = \"40px Calirbi\";\n";
  ptr += "ctx.fillText(\"Disponibles: \" + cantidad.toString(), 0,30);\n";
  ptr += "};\n";
  //------------------------------------------------------------------
 // -----------------------funcion para mandar las cosas al webserber------
  ptr += "Estacionamiento(4);\n";
  ptr += "boton(\"Parqueo 1\", 0);\n";
  ptr += "boton(\"Parqueo 2\", 0);\n";
  ptr += "boton(\"Parqueo 3\", 0);\n";
  ptr += "boton(\"Parqueo 4\", 0);\n";
  ptr += "var sendHttpRequest = function(){\n";
  ptr += "var xhr = new XMLHttpRequest();\n";
  ptr += "xhr.open(\"GET\", \"http://192.168.0.22/datos\");\n";
  ptr += "xhr.responseType = \'json\';\n";

 // --------------------funcion para escoger en que cuadro mostrar el lugar-------------
  ptr += "xhr.onload = function() {\n";
  ptr += "  console.log(xhr.response);\n";
  ptr += "Estacionamiento(xhr.response.Espacios);\n";
  ptr += "boton(\"Parqueo 1\", xhr.response.lugar1);\n";
  ptr += "boton(\"Parqueo 2\", xhr.response.lugar2);\n";
  ptr += "boton(\"Parqueo 3\", xhr.response.lugar3);\n";
  ptr += "boton(\"Parqueo 4\", xhr.response.lugar4);\n"; 
  ptr += "};\n";
  ptr += "xhr.send();\n"; 
  ptr += "return xhr.response;\n";
  ptr += "};\n"; 
  ptr += "setInterval(function(){\n";
  ptr += "sendHttpRequest();\n";
  ptr += "},1);\n";
  ptr += "</script>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
//********************************
// Handler de not found
//********************************
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
String data_json(void){
  String dato_json = "{\"lugar1\":";
          dato_json += Botones[0];
          dato_json += ",";
          dato_json += "\"lugar2\":";
          dato_json += Botones[1];
          dato_json += ",";
          dato_json += "\"lugar3\":";
          dato_json += Botones[2];
          dato_json += ",";
          dato_json += "\"lugar4\":";
          dato_json += Botones[3];
          dato_json += ",";
          dato_json += "\"Espacios\":";
          dato_json += Lugares;
          dato_json += "}";
  return dato_json;
}
