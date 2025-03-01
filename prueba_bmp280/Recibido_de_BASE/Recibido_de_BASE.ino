#include <SoftwareSerial.h>

SoftwareSerial XBee(10, 11);  // RX, TX

void setup() {
  Serial.begin(115200);       // Comunicación con la PC
  XBee.begin(115200);         // Comunicación con el módulo XBee
}

void loop() {
  // Enviar comandos al Cansat desde el teclado
  if (Serial.available() > 0) {                // Leer datos del teclado
    char comando = Serial.read();              // Leer un carácter

    if (comando == '1' || comando == '2') {    // Validar comando (1 o 2)
      XBee.print('<');
      XBee.print(comando);                     // Enviar el comando
      XBee.println('>');

      Serial.print("Enviado: ");
      Serial.println(comando);
    } else {
      Serial.println("Comando no válido. Use 1 o 2.");
    }
  }

  // Recibir respuesta del Cansat
  if (XBee.available() > 0) {                  // Verificar si hay datos entrantes
    String respuesta = XBee.readStringUntil('\n');  // Leer la respuesta completa
    Serial.print("Respuesta del Cansat: ");
    Serial.println(respuesta);
  }
}
