#include <SoftwareSerial.h>

SoftwareSerial XBee(10, 11);  // RX, TX

unsigned long previousMillis = 0;    // Tiempo del último mensaje recibido
const long timeout = 5000;           // Tiempo de espera (5 segundos) para detectar comunicación
bool datosRecibidos = false;         // Bandera para verificar comunicación

void setup() {
  Serial.begin(115200);       // Comunicación con la PC
  XBee.begin(115200);         // Comunicación con el módulo XBee
  Serial.println("Iniciando comunicación...");
}

void loop() {
  // Enviar comandos al Cansat desde el teclado
  if (Serial.available() > 0) {                // Leer datos del teclado
    char comando = Serial.read();              // Leer un carácter

    if (comando == '1' || comando == '2') {    // Validar comando (1 o 2)
      XBee.print('<');
      XBee.print(comando);                     // Enviar el comando
      XBee.println('>');

      Serial.print("Comando enviado: ");
      Serial.println(comando);
    } else {
      Serial.println("Comando no válido. Use 1 o 2.");
    }
  }

  // Recibir datos desde el Cansat
  if (XBee.available() > 0) {
    String respuesta = XBee.readStringUntil('\n');  // Leer la respuesta completa
    Serial.print("Respuesta del Cansat: ");
    Serial.println(respuesta);

    datosRecibidos = true;                     // Marcar que se recibió un mensaje
    previousMillis = millis();                // Reiniciar temporizador
  }

  // Detectar falta de comunicación
  if (millis() - previousMillis >= timeout) {
    if (datosRecibidos) {
      Serial.println("INCOMUNICADO");
      datosRecibidos = false;                 // Reiniciar la bandera
    }
  }
}
