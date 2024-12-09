/*aquí no se ponen variables, sino las funciones y los cálculos que haremos*/
#include "funciones.h" /*las comillas dobles buscan la función en un lugar específico*/
#include "Wire.h"
#include "SPI.h"
#include <Arduino.h>

LSM6DS3 SensorOne(I2C_MODE, 0x6A); //definimos la dirección de los sensores (esclavos) 
LSM6DS3 SensorTwo(I2C_MODE, 0x6B);

const float radToDeg = 360.0 / (2.0 * 3.1416); //conversión de radianes a grados
const unsigned long timePeriod = 300;  // Tiempo entre mediciones (ms)

float ax1, ay1, az1, gx1, gy1, gz1;
float ax2, ay2, az2, gx2, gy2, gz2;
float accel_ang_x1, accel_ang_y1, accel_ang_z1;
float accel_ang_x2, accel_ang_y2, accel_ang_z2;
float gyro_ang_x1, gyro_ang_y1, gyro_ang_z1;
float gyro_ang_x2, gyro_ang_y2, gyro_ang_z2;
float ang_x1, ang_y1, ang_z1;
float ang_x2, ang_y2, ang_z2;
float dt;

//función para revisar que se encuentren los sensores y puedan inicializarse
void iniciarSensores() {
  if (!SensorOne.begin()) {
    Serial.println("Problema al iniciar el sensor en 0x6A.");
  } else {
    Serial.println("Sensor en 0x6A iniciado.");
  }

  if (!SensorTwo.begin()) {
    Serial.println("Problema al iniciar el sensor en 0x6B.");
  } else {
    Serial.println("Sensor en 0x6B iniciado.");
  }
}
//función para leer los valores que captan los 2 sensores
void leerSensores() {
  ax1 = SensorOne.readFloatAccelX();
  ay1 = SensorOne.readFloatAccelY();
  az1 = SensorOne.readFloatAccelZ();
  gx1 = SensorOne.readFloatGyroX();
  gy1 = SensorOne.readFloatGyroY();
  gz1 = SensorOne.readFloatGyroZ();

  ax2 = SensorTwo.readFloatAccelX();
  ay2 = SensorTwo.readFloatAccelY();
  az2 = SensorTwo.readFloatAccelZ();
  gx2 = SensorTwo.readFloatGyroX();
  gy2 = SensorTwo.readFloatGyroY();
  gz2 = SensorTwo.readFloatGyroZ();
}

//función para realizar los cálculos necesarios
void calcularAngulos() {
  calcularAccel(ax1, ay1, az1, accel_ang_x1, accel_ang_y1, accel_ang_z1);
  calcularAccel(ax2, ay2, az2, accel_ang_x2, accel_ang_y2, accel_ang_z2);

  dt = (millis() - prevTimeCap) / 1000.0;  // Calcular dt en segundos

  calcularGyro(gx1, gy1, gz1, gyro_ang_x1, gyro_ang_y1, gyro_ang_z1, dt);
  calcularGyro(gx2, gy2, gz2, gyro_ang_x2, gyro_ang_y2, gyro_ang_z2, dt);
}

//aplicacion del filtro digital a los valores lecturados
void aplicarFiltroComplementario() {
  filtroComplementario(gx1, gy1, gz1, accel_ang_x1, accel_ang_y1, accel_ang_z1, ang_x1, ang_y1, ang_z1);
  filtroComplementario(gx2, gy2, gz2, accel_ang_x2, accel_ang_y2, accel_ang_z2, ang_x2, ang_y2, ang_z2);
}
//función para imprimir en el formato "value1 , value 2" que la interfaz de Python leerá
void imprimirResultados() {
  Serial.print(ang_x2 - ang_x1, 2); //se hace una comparación de los ángulos captados por los 2 sensores. y se imprime con 2 decimales
  Serial.print(" , ");
  Serial.print(ang_y2 - ang_y1, 2);
  Serial.println();
}
//función para las conversiones
void calcularAccel(float ax, float ay, float az, float& accel_ang_x, float& accel_ang_y, float& accel_ang_z) {
  if (abs(ax) > 0.001) {
    accel_ang_x = atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * radToDeg;
  } else {
    accel_ang_x = 0.001;
  }

  if (abs(ay) > 0.001) {
    accel_ang_y = atan(-ax / sqrt(pow(ay, 2) + pow(az, 2))) * radToDeg;
  } else {
    accel_ang_y = 0.001;
  }

  if (abs(az) > 0.001) {
    accel_ang_z = atan(sqrt(pow(ax, 2) + pow(ay, 2)) / az) * radToDeg;
  } else {
    accel_ang_z = 0.001;
  }
}
//función de cálculos
void calcularGyro(float gx_sc, float gy_sc, float gz_sc, float& gyro_ang_x, float& gyro_ang_y, float& gyro_ang_z, float dt) {
  gyro_ang_x += dt * gx_sc;
  gyro_ang_y += dt * gy_sc;
  gyro_ang_z += dt * gz_sc;
}

//aplicamos el filtro digital alfa para tener una mejor lectura
void filtroComplementario(float gx_sc, float gy_sc, float gz_sc, float accel_ang_x, float accel_ang_y, float accel_ang_z, float& ang_x, float& ang_y, float& ang_z) {
  ang_x = alfa * (ang_x + gx_sc * dt) + (1.0 - alfa) * accel_ang_x;
  ang_y = alfa * (ang_y + gy_sc * dt) + (1.0 - alfa) * accel_ang_y;
  ang_z = alfa * (ang_z + gz_sc * dt) + (1.0 - alfa) * accel_ang_z;
}