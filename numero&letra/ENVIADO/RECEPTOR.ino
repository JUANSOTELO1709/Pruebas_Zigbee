#include <SoftwareSerial.h>         // Incluir librería SoftwareSerial para comunicación
 
SoftwareSerial XBee(10, 11);        // RX = 10, TX = 11
 
bool started = false;               // Verdadero cuando se detecta el marcador de inicio
bool ended = false;                 // Verdadero cuando se detecta el marcador de fin
char incomingByte;                  // Almacenamiento para cada byte leído
char msg[50];                       // Array para ensamblar el mensaje entrante (aumentado para texto)
byte index = 0;                     // Posición actual en el array
 
void setup() {
  Serial.begin(115200);             // Iniciar comunicación con la PC para depuración
  XBee.begin(115200);               // Iniciar comunicación con el módulo XBee
}
 
void loop() {
  while (XBee.available() > 0) {    // Comprobar si hay datos disponibles del XBee
    incomingByte = XBee.read();     // Leer el byte entrante
 
    if (incomingByte == '<') {      // Detectar inicio del mensaje
      started = true;
      index = 0;
      msg[index] = '\0';            // Limpiar el buffer
    }
    else if (incomingByte == '>') { // Detectar fin del mensaje
      ended = true;
      break;                        // Dejar de leer, procesar el mensaje
    }
    else if (started && index < 49) {  // Almacenar el byte en el array msg si el mensaje ha comenzado
      msg[index] = incomingByte;
      index++;
      msg[index] = '\0';            // Terminar la cadena con nulo
    }
  }
 
  if (started && ended) {           // Si se recibió un mensaje completo, procesarlo
    Serial.print("Recibido: ");     // Salida de depuración al Monitor Serial
    Serial.println(msg);            // Mostrar el mensaje recibido (número o texto)

    // Procesar números (si el mensaje es un número)
    if (isDigit(msg[0])) {          // Verificar si el primer carácter es un dígito
      int value = atoi(msg);        // Convertir el buffer a un entero
      if (value == 1) {
        Serial.println("Motor a la derecha");
      } else if (value == 2) {
        Serial.println("Motor a la izquierda");
      }
    }

    started = false;                // Reiniciar para el próximo mensaje
    ended = false;
  }
}