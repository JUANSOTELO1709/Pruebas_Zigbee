#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>

Adafruit_BMP280 bmp;
SoftwareSerial XBee(10, 11);  // RX, TX

char incomingByte;
char msg[50];                // Almacenamiento para el mensaje
byte index = 0;
bool started = false, ended = false;

// Pines del motor
const int motorPin1 = 8;
const int motorPin2 = 9;

void setup() {
  Serial.begin(115200);
  XBee.begin(115200);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  if (!bmp.begin(0x76)) {
    Serial.println("Error inicializando BMP280");
    while (1);
  }
}

void loop() {
  // Leer datos del sensor BMP280
  float temp = bmp.readTemperature();
  float presion = bmp.readPressure();
  float altitud = bmp.readAltitude(1013.25);

  // Transmitir datos del sensor
  XBee.print('<');
  XBee.print(temp);    XBee.print(',');
  XBee.print(presion); XBee.print(',');
  XBee.print(altitud);
  XBee.println('>');

  // Verificar si se recibió un comando
  while (XBee.available() > 0) {
    incomingByte = XBee.read();

    if (incomingByte == '<') {
      started = true;
      index = 0;
      msg[index] = '\0';
    }
    else if (incomingByte == '>') {
      ended = true;
      break;
    }
    else if (started && index < 49) {
      msg[index++] = incomingByte;
      msg[index] = '\0';
    }
  }

  if (started && ended) {
    Serial.print("Comando recibido: ");
    Serial.println(msg);

    if (strcmp(msg, "MOTOR_ON") == 0) {   // Encender el motor
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      Serial.println("Motor encendido");
    } else if (strcmp(msg, "MOTOR_OFF") == 0) {  // Apagar el motor
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      Serial.println("Motor apagado");
    }

    started = false;
    ended = false;
  }

  delay(1000);  // Enviar datos cada segundo
}
