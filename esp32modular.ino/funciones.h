/*Aquí vienen los defin, los nombres de las funciones y las variables globales*/
#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "SparkFunLSM6DS3.h" //incluimos la libreria del sensor

//definimos el nombre de los 2 sensores a usarse
extern LSM6DS3 SensorOne;
extern LSM6DS3 SensorTwo;

/* variables globales*/ 
extern const float radToDeg;
extern const unsigned long timePeriod;  // tiempo entre mediciones (ms)
extern float ax1, ay1, az1, gx1, gy1, gz1;
extern float ax2, ay2, az2, gx2, gy2, gz2;
extern float accel_ang_x1, accel_ang_y1, accel_ang_z1;
extern float accel_ang_x2, accel_ang_y2, accel_ang_z2;
extern float gyro_ang_x1, gyro_ang_y1, gyro_ang_z1;
extern float gyro_ang_x2, gyro_ang_y2, gyro_ang_z2;
extern float ang_x1, ang_y1, ang_z1;
extern float ang_x2, ang_y2, ang_z2;
extern float dt;

/* funciones */
void iniciarSensores();
void leerSensores();
void calcularAngulos();
void aplicarFiltroComplementario();
void imprimirResultados();
void calcularAccel(float ax, float ay, float az, float& accel_ang_x, float& accel_ang_y, float& accel_ang_z);
void calcularGyro(float gx_sc, float gy_sc, float gz_sc, float& gyro_ang_x, float& gyro_ang_y, float& gyro_ang_z, float dt);
void filtroComplementario(float gx_sc, float gy_sc, float gz_sc, float accel_ang_x, float accel_ang_y, float accel_ang_z, float& ang_x, float& ang_y, float& ang_z);

#endif //terminamos con un endif si o si. NO OLVIDAR