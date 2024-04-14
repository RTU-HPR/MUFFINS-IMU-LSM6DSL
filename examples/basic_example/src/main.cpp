#include <Arduino.h>
#include <MUFFINS_LSM6DSL.h>

const int SENSOR_POWER_ENABLE_PIN = 17;
const int WIRE0_SCL = 1;
const int WIRE0_SDA = 0;

LSM6DSL imu;

LSM6DSL::Config config = {
    .wire = &Wire,
    .i2c_address = 0x6B,
    .accel_range = LSM6DS_ACCEL_RANGE_2_G,
    .gyro_range = LSM6DS_GYRO_RANGE_250_DPS,
    .accel_data_rate = LSM6DS_RATE_1_66K_HZ,
    .gyro_data_rate = LSM6DS_RATE_1_66K_HZ};

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(1000);
  }

  pinMode(SENSOR_POWER_ENABLE_PIN, OUTPUT_12MA);
  digitalWrite(SENSOR_POWER_ENABLE_PIN, HIGH);

  if (Wire.setSCL(WIRE0_SCL) && Wire.setSDA(WIRE0_SDA))
  {
    Wire.begin();
  }

  if (!imu.begin(config))
  {
    while (1)
      ;
  }
}

void loop()
{
  imu.read();

  Serial.print("Temperature: ");
  Serial.print(imu.data.temperature);
  Serial.print(" C | Accel (m/s^2) - X: ");
  Serial.print(imu.data.accel_x);
  Serial.print(" Y: ");
  Serial.print(imu.data.accel_y);
  Serial.print(" Z: ");
  Serial.print(imu.data.accel_z);
  Serial.print(" m/s^2 | Gyro (rad/s) - X: ");
  Serial.print(imu.data.gyro_x);
  Serial.print(" Y ");
  Serial.print(imu.data.gyro_y);
  Serial.print(" Z: ");
  Serial.println(imu.data.gyro_z);

  delay(10);
}