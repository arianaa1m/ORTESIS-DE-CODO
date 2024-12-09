#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <Servo.h>

// Declaración de variables globales
extern Servo myServo;
extern int currentAngle;
extern int targetAngle;
extern int speed;
extern bool manualMode;

// Constantes para el sensor EMG
extern const int emgPin;
extern const int emgThreshold;
extern const int emgMaxValue;

// Declaración de funciones
void setupServo();        // Configuración inicial del servo y del puerto serie
void processSerialInput(); // Procesamiento de los comandos recibidos por serie
void updateManualMode();   // Actualización del ángulo del servo en modo manual
void updateEMGMode();      // Actualización del ángulo del servo en modo EMG

#endif // FUNCIONES_H
