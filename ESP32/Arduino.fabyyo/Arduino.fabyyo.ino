#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "SPI.h"

LSM6DS3 SensorOne (I2C_MODE, 0x6A);
LSM6DS3 SensorTwo (I2C_MODE, 0x6B);

const float radToDeg = 360.0 / (2.0 * 3.1416);
const unsigned long timePeriod = 50;  // period between measurements (ms)

//Complementary filter
const float alfa = 0.95;

// Raw values from accelerometer and gyro
float ax1, ay1, az1, gx1, gy1, gz1;
float ax2, ay2, az2, gx2, gy2, gz2;

// To calculate angles
float accel_ang_x1, accel_ang_y1, accel_ang_z1;
float accel_ang_x2, accel_ang_y2, accel_ang_z2;
float gyro_ang_x1, gyro_ang_y1, gyro_ang_z1;
float gyro_ang_x2, gyro_ang_y2, gyro_ang_z2;
float ang_x1, ang_y1, ang_z1;
float ang_x2, ang_y2, ang_z2;


float dt;
unsigned long currTime = 0;
unsigned long prevTimeCap = 0;
int currPeriod = 0;
int maxPeriod = 0;

int cont = 0;

void printCombined() {
  Serial.print(ang_x2 - ang_x1, 2);
  Serial.print( " , " );
  Serial.print(ang_y2 - ang_y1, 2);
}

// Read accelerations and angular velocities
void readSensorData(float& ax, float& ay, float& az, float& gx, float& gy, float& gz, LSM6DS3& sensor) {
  ax = sensor.readFloatAccelX();
  ay = sensor.readFloatAccelY();
  az = sensor.readFloatAccelZ();

  gx = sensor.readFloatGyroX();
  gy = sensor.readFloatGyroY();
  gz = sensor.readFloatGyroZ();
}

void calculateAccel(float ax, float ay, float az, float& accel_ang_x, float& accel_ang_y, float& accel_ang_z) {
  // Always check i f the axis has the same direction as the gravity
  if (abs(ax) > 0.001) {
    accel_ang_x = atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * radToDeg;
  }
  else {
    accel_ang_x = 0.001;
  }

  if(abs(ay) > 0.001) {
    accel_ang_y = atan(-ax / sqrt(pow(ay, 2) + pow(az, 2))) * radToDeg;
  }
  else {
    accel_ang_y = 0.001;
  }

  if(abs(az) > 0.001) {
    accel_ang_z = atan(sqrt(pow(ax, 2) + pow(ay, 2)) / az) * radToDeg;
  }
  else {
    accel_ang_z = 0.001;
  }
}


void calculateGyro(float gx_sc, float gy_sc, float gz_sc, float& gyro_ang_x, float& gyro_ang_y, float& gyro_ang_z, float dt) {
// Integración simple
  gyro_ang_x += dt * (gx_sc);
  gyro_ang_y += dt * (gy_sc);
  gyro_ang_z += dt * (gz_sc);
}

void complementaryFilter(float gx_sc, float gy_sc, float gz_sc, float accel_ang_x, float accel_ang_y, float accel_ang_z, float& ang_x, float& ang_y, float& ang_z) {
  ang_x = alfa *(ang_x + gx_sc*dt) + (1.0- alfa) *accel_ang_x;
  ang_y = alfa *(ang_y + gy_sc*dt) + (1.0- alfa) *accel_ang_y;
  ang_z = alfa *(ang_z + gz_sc*dt) + (1.0- alfa) *accel_ang_z;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Check sensor addresses
  if(!SensorOne.begin()) {
    Serial.print ln( "Problem starting the sensor at 0x6A." );
  }
  else {
    Serial.print ln( "Sensor at 0x6A started." );
  }

  if(!SensorTwo.begin()) {
    Serial.print ln( "Problem starting the sensor at 0x6B." );
  }
  else {
    Serial.print ln( "Sensor at 0x6B started." );
  }
}


void loop() {
  currTime = millis();

  if(currTime - prevTimeCap >= timePeriod) {
    currPeriod = (int)(currTime - prevTimeCap);
    prevTimeCap = currTime;

    if(currPeriod > maxPeriod) {
      maxPeriod = currPeriod;
    }

    readSensorData(ax1, ay1, az1, gx1, gy1, gz1, SensorOne);
    readSensorData(ax2, ay2, az2, gx2, gy2, gz2, SensorTwo);

    calculateAccel(ax1, ay1, az1, accel_ang_x1, accel_ang_y1, accel_ang_z1);
    calculateAccel(ax2, ay2, az2, accel_ang_x2, accel_ang_y2, accel_ang_z2);

    dt = currPeriod;
    dt /= 1000.0;

    calculateGyro(gx1, gy1, gz1, gyro_ang_x1, gyro_ang_y1, gyro_ang_z1, dt);
    calculateGyro(gx2, gy2, gz2, gyro_ang_x2, gyro_ang_y2, gyro_ang_z2, dt);

    complementaryFilter(gx1, gy1, gz1, accel_ang_x1, accel_ang_y1, accel_ang_z1, ang_x1, ang_y1, ang_z1);
    complementaryFilter(gx2, gy2, gz2, accel_ang_x2, accel_ang_y2, accel_ang_z2, ang_x2, ang_y2, ang_z2);

    printCombined();
    Serial.print ln();
    
    cont++;
  }
}