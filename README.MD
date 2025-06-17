# Ejemplos de Comunicación ZigBee con Arduino

Este repositorio contiene diversos ejemplos prácticos de cómo utilizar módulos ZigBee para establecer comunicación entre dispositivos Arduino. Cada carpeta corresponde a una prueba específica, abordando desde el envío de datos básicos hasta el control de dispositivos como motores DC y sensores ambientales.

## 📁 Contenido de Carpetas

- **`Prueba_array`**  
  Primer ejemplo para el desarrollo de la comunicación ZigBee. Muestra cómo generar un arreglo de números aleatorios, enviarlos y recibirlos en otro dispositivo.

- **`Prueba_bmp_280`**  
  Ejemplo de cómo leer datos del sensor ambiental BMP280 (temperatura y presión) y enviarlos a través del enlace ZigBee.

- **`Prueba_motor`**  
  Control de un motor DC mediante Arduino. El ejemplo incluye el envío de comandos y estados por ZigBee.

- **`Prueba_sensor_motor`**  
  Combina la lectura de un sensor y el control de un motor DC. Se realiza comunicación entre dos dispositivos para coordinar acciones.

- **`Numero_letra`**  
  Envío de un arreglo que contiene tanto números como letras. Se muestran técnicas para:
  - Transformar números a enteros.
  - Mantener el orden de los datos tipo carácter.
  - Enviar y recibir múltiples datos al mismo tiempo.

## 🔧 Requisitos

- Dos dispositivos Arduino
- Módulos ZigBee (como XBee o similares)
- Sensor BMP280 (para la prueba correspondiente)
- Motor DC (para las pruebas de control)
- Software Arduino IDE

## 💡 Objetivo

Facilitar la comprensión y puesta en práctica de diferentes técnicas de comunicación serial inalámbrica entre Arduinos usando ZigBee. Los ejemplos están pensados para ser modificados y adaptados según las necesidades del usuario.
