#include "funciones.h"
#include <Arduino.h>

Servo myServo;
int currentAngle = 135; // Ángulo inicial del servo
int targetAngle = 135;  // Ángulo objetivo en modo manual
int speed = 10;         // Velocidad del movimiento en modo manual (ms por paso)
bool manualMode = true; // Modo activo: true = Manual, false = EMG

const int emgPin = A0;      // Pin analógico del sensor EMG
const int emgThreshold = 30; // Umbral para activar movimiento
const int emgMaxValue = 1023; // Valor máximo del EMG

void setupServo() {
  Serial.begin(9600);      // Inicializa la comunicación serie
  myServo.attach(9);       // Conecta el servo al pin digital 9
  myServo.write(currentAngle); // Establece el ángulo inicial del servo
}

//Procesa los comandos recibidos por la comunicación serie.
void processSerialInput() {
  if (Serial.available() > 0) { // Comprueba si hay datos disponibles en el puerto serie
    String input = Serial.readStringUntil('\n'); // Lee la entrada hasta el salto de línea
    input.trim(); // Elimina espacios en blanco al principio y al final

    // Cambia el modo de operación basado en el comando recibido
    if (input.startsWith("MODE:")) {
      String mode = input.substring(5);
      if (mode == "MANUAL") {
        manualMode = true;
      } else if (mode == "EMG") {
        manualMode = false;
      }
    }

    // Procesa los comandos en modo manual
    if (manualMode) {
      if (input.startsWith("ANGLE:")) {
        int angle = input.substring(6).toInt(); // Extrae el ángulo del comando
        if (angle >= 45 && angle <= 135) { // Comprueba si el ángulo está en el rango permitido
          targetAngle = angle; // Establece el nuevo ángulo objetivo
        }
      } else if (input.startsWith("SPEED:")) {
        int newSpeed = input.substring(6).toInt(); // Extrae la velocidad del comando
        if (newSpeed > 0) { // Comprueba si la velocidad es válida
          speed = newSpeed; // Establece la nueva velocidad
        }
      }
    }
  }
}

//Actualiza el ángulo del servo en modo manual de forma suave.
void updateManualMode() {
  if (manualMode && currentAngle != targetAngle) {
    if (currentAngle < targetAngle) {
      currentAngle++; // Incrementa el ángulo actual
    } else if (currentAngle > targetAngle) {
      currentAngle--; // Decrementa el ángulo actual
    }
    myServo.write(currentAngle); // Actualiza el ángulo del servo
    delay(speed); // Espera un tiempo determinado por la velocidad
  }
}

//Actualiza el ángulo del servo basado en las señales del sensor EMG.
void updateEMGMode() {
  if (!manualMode) {
    int emgValue = analogRead(emgPin); // Lee el valor del sensor EMG

    if (emgValue > emgThreshold) { // Comprueba si el valor EMG supera el umbral
      // Escala el valor EMG a un rango de 45° a 135°
      int newAngle = map(emgValue, emgThreshold, emgMaxValue, 45, 135);
      newAngle = constrain(newAngle, 45, 135); // Asegura que el ángulo esté dentro del rango permitido
      myServo.write(newAngle); // Actualiza el ángulo del servo
      delay(10); // Espera un corto período antes de la siguiente lectura
    }
  }
}