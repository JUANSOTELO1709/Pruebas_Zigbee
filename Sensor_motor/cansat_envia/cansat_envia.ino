#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>

Adafruit_BMP280 bmp;
SoftwareSerial XBee(10, 11);  // RX, TX

const int motorPin1 = 8;
const int motorPin2 = 9;

char incomingByte;
bool started = false, ended = false;
char msg[5];                  // Buffer para almacenar el comando
byte index = 0;

unsigned long previousMillisComando = 0;  // Para el temporizador de comunicación
const long timeoutComando = 5000;         // Tiempo máximo de espera para comunicación (5 segundos)

bool sensorActivo = false;                // Indica si el sensor BMP280 está funcionando

void setup() {
  Serial.begin(115200);
  XBee.begin(115200);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);

  // Inicializar el BMP280
  if (bmp.begin(0x76)) {
    sensorActivo = true;
    Serial.println("Sensor BMP280 activo.");
  } else {
    sensorActivo = false;
    Serial.println("Error: Sensor BMP280 no detectado.");
  }
}

void loop() {
  // **Enviar datos del sensor si está activo**
  if (sensorActivo) {
    float temp = bmp.readTemperature();
    float presion = bmp.readPressure();
    float altitud = bmp.readAltitude(1013.25);

    // Enviar datos del sensor
    XBee.print('<');
    XBee.print("Temp:"); XBee.print(temp);    XBee.print(',');
    XBee.print("Presion:"); XBee.print(presion); XBee.print(',');
    XBee.print("Altura:"); XBee.print(altitud);
    XBee.println('>');
  } else {
    XBee.println("NO HAY COMUNICACIÓN");  // Si el sensor no está activo
  }

  // **Procesar comandos recibidos**
  bool comandoRecibido = false;  // Bandera para registrar si se recibe un comando

  while (XBee.available() > 0) {
    incomingByte = XBee.read();

    if (incomingByte == '<') {        // Detectar inicio del mensaje
      started = true;
      index = 0;
      msg[index] = '\0';
    }
    else if (incomingByte == '>') {  // Detectar fin del mensaje
      ended = true;
      break;
    }
    else if (started && index < 4) {  // Almacenar el comando
      msg[index++] = incomingByte;
      msg[index] = '\0';
    }
  }

  if (started && ended) {
    Serial.print("Comando recibido: ");
    Serial.println(msg);

    if (strcmp(msg, "1") == 0) {      // Encender motor
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      Serial.println("Motor encendido");
      XBee.println("MOTOR ACTIVO");
    } 
    else if (strcmp(msg, "2") == 0) { // Apagar motor
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      Serial.println("Motor apagado");
      XBee.println("MOTOR APAGADO");
    }

    comandoRecibido = true;                     // Indicar que llegó un comando
    previousMillisComando = millis();          // Reiniciar el temporizador
    started = false;
    ended = false;
  }

  // **Verificar si no llegan comandos dentro del tiempo permitido**
  if (millis() - previousMillisComando >= timeoutComando && !comandoRecibido) {
    XBee.println("NO HAY COMUNICACIÓN");       // Avisar de la falta de comandos
    previousMillisComando = millis();         // Reiniciar el temporizador para evitar múltiples envíos
  }

  delay(1000);  // Retraso para evitar saturar la transmisión
}
