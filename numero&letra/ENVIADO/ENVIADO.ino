#include <SoftwareSerial.h>          // Incluir librería SoftwareSerial para comunicación

SoftwareSerial XBee(10, 11);         // Definir pines de SoftwareSerial: RX = 10, TX = 11

void setup() {
  Serial.begin(115200);              // Iniciar comunicación con la PC para depuración
  XBee.begin(115200);                // Iniciar comunicación con el módulo XBee
  randomSeed(analogRead(0));         // Inicializar la semilla para números aleatorios
}

void loop() {
  // Enviar un número aleatorio cada segundo
  int randomNumber = random(100);    // Generar un número aleatorio entre 0 y 99
  XBee.print('<');                   // Marcador de inicio de transmisión
  XBee.print(randomNumber);          // Enviar el número aleatorio
  XBee.println('>');                 // Marcador de fin de transmisión

  Serial.print("Enviado número aleatorio: ");  // Salida de depuración al Monitor Serial
  Serial.println(randomNumber);

  // Verificar si hay un mensaje escrito en el Monitor Serial
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Leer la entrada del teclado hasta un salto de línea

    XBee.print('<');                 // Marcador de inicio de transmisión
    XBee.print(input);               // Enviar el mensaje escrito
    XBee.println('>');               // Marcador de fin de transmisión

    Serial.print("Enviado mensaje: ");  // Salida de depuración al Monitor Serial
    Serial.println(input);
  }

  delay(1000);                       // Esperar 1 segundo antes de repetir
}