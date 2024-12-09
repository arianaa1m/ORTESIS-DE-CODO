#include "funciones.h"

void setup() {
  setupServo(); // Llama a la función de configuración del servo
}

void loop() {
  processSerialInput(); // Procesa los comandos 
  updateManualMode();   // Actualiza el ángulo del servo en modo manual
  updateEMGMode();      // Actualiza el ángulo del servo en modo EMG
}
