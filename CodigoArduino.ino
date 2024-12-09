#include "SparkFunLSM6DS3.h"  // Incluye la librería para el sensor LSM6DS3 de SparkFun
#include "Wire.h"              // Incluye la librería para comunicación I2C
#include "SPI.h"               // Incluye la librería para comunicación SPI

// Definición de dos sensores LSM6DS3, uno con dirección 0x6A y otro con dirección 0x6B.
LSM6DS3 SensorOne (I2C_MODE, 0x6A);  // Primer sensor en modo I2C con dirección 0x6A
LSM6DS3 SensorTwo (I2C_MODE, 0x6B);  // Segundo sensor en modo I2C con dirección 0x6B

const float radToDeg = 360.0 / (2.0 * 3.1416);  // Constante para convertir radianes a grados

const unsigned long timePeriod = 300;  // Período entre mediciones en milisegundos (300ms)

// Parámetro para el filtro complementario
const float alfa = 0.95;  // Factor de ponderación entre los datos del acelerómetro y giroscopio

// Variables para almacenar los valores de aceleración y velocidad angular de los sensores
float ax1, ay1, az1, gx1, gy1, gz1;
float ax2, ay2, az2, gx2, gy2, gz2;

// Variables para calcular los ángulos de cada sensor
float accel_ang_x1, accel_ang_y1, accel_ang_z1;
float accel_ang_x2, accel_ang_y2, accel_ang_z2;
float gyro_ang_x1, gyro_ang_y1, gyro_ang_z1;
float gyro_ang_x2, gyro_ang_y2, gyro_ang_z2;
float ang_x1, ang_y1, ang_z1;
float ang_x2, ang_y2, ang_z2;

float dt;  // Variable para almacenar el intervalo de tiempo entre mediciones
unsigned long currTime = 0;  // Variable para almacenar el tiempo actual (en milisegundos)
unsigned long prevTimeCap = 0;  // Variable para almacenar el tiempo de la última medición
int currPeriod = 0;  // Intervalo entre mediciones en milisegundos
int maxPeriod = 0;  // El máximo intervalo de medición registrado
int cont = 0;  // Contador de ciclos del loop

// Función para imprimir los ángulos combinados de los dos sensores
void printCombined() {
  Serial.print(ang_x2 - ang_x1, 2);  // Imprime la diferencia de ángulos en el eje X
  Serial.print( " , " );
  Serial.print(ang_y2 - ang_y1, 2);  // Imprime la diferencia de ángulos en el eje Y
}

// Función para leer los datos de aceleración y velocidad angular de un sensor
void readSensorData(float& ax, float& ay, float& az, float& gx, float& gy, float& gz, LSM6DS3& sensor) {
  // Lee los valores de aceleración en los tres ejes (X, Y, Z)
  ax = sensor.readFloatAccelX();
  ay = sensor.readFloatAccelY();
  az = sensor.readFloatAccelZ();

  // Lee los valores de velocidad angular (giroscopio) en los tres ejes (X, Y, Z)
  gx = sensor.readFloatGyroX();
  gy = sensor.readFloatGyroY();
  gz = sensor.readFloatGyroZ();
}

// Función para calcular los ángulos a partir de los datos del acelerómetro
void calculateAccel(float ax, float ay, float az, float& accel_ang_x, float& accel_ang_y, float& accel_ang_z) {
  // Calcula el ángulo en el eje X usando la función arcotangente
  if (abs(ax) > 0.001) {
    accel_ang_x = atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * radToDeg;
  }
  else {
    accel_ang_x = 0.001;  // Si la aceleración en X es muy pequeña, asigna un valor mínimo
  }

  // Calcula el ángulo en el eje Y
  if(abs(ay) > 0.001) {
    accel_ang_y = atan(-ax / sqrt(pow(ay, 2) + pow(az, 2))) * radToDeg;
  }
  else {
    accel_ang_y = 0.001;  // Asigna un valor mínimo si la aceleración en Y es muy pequeña
  }

  // Calcula el ángulo en el eje Z
  if(abs(az) > 0.001) {
    accel_ang_z = atan(sqrt(pow(ax, 2) + pow(ay, 2)) / az) * radToDeg;
  }
  else {
    accel_ang_z = 0.001;  // Asigna un valor mínimo si la aceleración en Z es muy pequeña
  }
}

// Función para calcular los ángulos a partir de los datos del giroscopio
void calculateGyro(float gx_sc, float gy_sc, float gz_sc, float& gyro_ang_x, float& gyro_ang_y, float& gyro_ang_z, float dt) {
  // Integración simple para calcular el ángulo a partir de la velocidad angular
  gyro_ang_x += dt * (gx_sc);  // Actualiza el ángulo en el eje X
  gyro_ang_y += dt * (gy_sc);  // Actualiza el ángulo en el eje Y
  gyro_ang_z += dt * (gz_sc);  // Actualiza el ángulo en el eje Z
}

// Función para aplicar el filtro complementario que combina datos del acelerómetro y giroscopio
void complementaryFilter(float gx_sc, float gy_sc, float gz_sc, float accel_ang_x, float accel_ang_y, float accel_ang_z, float& ang_x, float& ang_y, float& ang_z) {
  // Fórmula del filtro complementario para combinar los datos de acelerómetro y giroscopio
  ang_x = alfa *(ang_x + gx_sc*dt) + (1.0- alfa) *accel_ang_x;
  ang_y = alfa *(ang_y + gy_sc*dt) + (1.0- alfa) *accel_ang_y;
  ang_z = alfa *(ang_z + gz_sc*dt) + (1.0- alfa) *accel_ang_z;
}

void setup() {
  Serial.begin(115200);  // Inicia la comunicación serial a 115200 baudios
  delay(1000);           // Espera 1 segundo antes de continuar

  // Inicia el sensor 1 y verifica si se ha iniciado correctamente
  if(!SensorOne.begin()) {
    Serial.println( "Problem starting the sensor at 0x6A." );  // Muestra un mensaje de error si no se inicia
  }
  else {
    Serial.println( "Sensor at 0x6A started." );  // Muestra un mensaje de éxito si se inicia correctamente
  }

  // Inicia el sensor 2 y verifica si se ha iniciado correctamente
  if(!SensorTwo.begin()) {
    Serial.println( "Problem starting the sensor at 0x6B." );  // Muestra un mensaje de error si no se inicia
  }
  else {
    Serial.println( "Sensor at 0x6B started." );  // Muestra un mensaje de éxito si se inicia correctamente
  }
}

void loop() {
  currTime = millis();  // Obtiene el tiempo actual en milisegundos

  // Verifica si ha pasado el tiempo establecido (300ms)
  if(currTime - prevTimeCap >= timePeriod) {
    currPeriod = (int)(currTime - prevTimeCap);  // Calcula el período actual
    prevTimeCap = currTime;  // Actualiza el tiempo de la última medición

    if(currPeriod > maxPeriod) {
      maxPeriod = currPeriod;  // Actualiza el máximo período registrado
    }

    // Lee los datos de los dos sensores
    readSensorData(ax1, ay1, az1, gx1, gy1, gz1, SensorOne);
    readSensorData(ax2, ay2, az2, gx2, gy2, gz2, SensorTwo);

    // Calcula los ángulos para cada sensor
    calculateAccel(ax1, ay1, az1, accel_ang_x1, accel_ang_y1, accel_ang_z1);
    calculateAccel(ax2, ay2, az2, accel_ang_x2, accel_ang_y2, accel_ang_z2);

    dt = currPeriod;  // Establece el tiempo de muestreo (en segundos)
    dt /= 1000.0;     // Convierte a segundos

    // Calcula los ángulos para cada sensor usando los datos del giroscopio
    calculateGyro(gx1, gy1, gz1, gyro_ang_x1, gyro_ang_y1, gyro_ang_z1, dt);
    calculateGyro(gx2, gy2, gz2, gyro_ang_x2, gyro_ang_y2, gyro_ang_z2, dt);

    // Aplica el filtro complementario para cada sensor
    complementaryFilter(gx1, gy1, gz1, accel_ang_x1, accel_ang_y1, accel_ang_z1, ang_x1, ang_y1, ang_z1);
    complementaryFilter(gx2, gy2, gz2, accel_ang_x2, accel_ang_y2, accel_ang_z2, ang_x2, ang_y2, ang_z2);

    // Imprime los ángulos combinados de los dos sensores
    printCombined();
    Serial.println();  // Nueva línea después de imprimir los datos
    
    cont++;  // Incrementa el contador de ciclos
  }
}
