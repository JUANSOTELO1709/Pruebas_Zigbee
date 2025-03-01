#include <SoftwareSerial.h>

// Configuración del módulo XBee
SoftwareSerial XBee(10, 11);  // RX, TX

char incomingByte;
char msg[50];                // Almacenamiento para el mensaje
byte index = 0;
bool started = false, ended = false;

void setup() {
  Serial.begin(115200);       // Para depuración en PC
  XBee.begin(115200);         // Comunicación con módulo XBee
}

void loop() {
  while (XBee.available() > 0) {
    incomingByte = XBee.read();

    if (incomingByte == '<') {   // Marcador de inicio
      started = true;
      index = 0;
      msg[index] = '\0';
    }
    else if (incomingByte == '>') {  // Marcador de fin
      ended = true;
      break;
    }
    else if (started && index < 49) {  // Almacenar los datos
      msg[index++] = incomingByte;
      msg[index] = '\0';
    }
  }

  if (started && ended) {
    Serial.print("Recibido: ");
    Serial.println(msg);

    // Separar datos por comas
    char *token = strtok(msg, ",");
    if (token != nullptr) {
      float temp = atof(token);
      token = strtok(nullptr, ",");
      float presion = (token != nullptr) ? atof(token) : 0;
      token = strtok(nullptr, ",");
      float altitud = (token != nullptr) ? atof(token) : 0;

      // Mostrar datos procesados
      Serial.print("Temperatura: "); Serial.print(temp); Serial.println(" °C");
      Serial.print("Presión: "); Serial.print(presion); Serial.println(" Pa");
      Serial.print("Altura: "); Serial.print(altitud); Serial.println(" m");
    }

    started = false;
    ended = false;
  }
}
