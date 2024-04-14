#pragma once
#include <Arduino.h>
#include <MUFFINS_Component_Base.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM6DSL.h>

class LSM6DSL : public Component_Base
{
public:
  struct Config
  {
    TwoWire *wire;
    int i2c_address;
    lsm6ds_accel_range_t accel_range;
    lsm6ds_gyro_range_t gyro_range;
    lsm6ds_data_rate_t accel_data_rate;
    lsm6ds_data_rate_t gyro_data_rate;
  };

  struct Data
  {
    float temperature;
    float accel_x;
    float accel_y;
    float accel_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
  } data;

private:
  Adafruit_LSM6DSL _imu;
  // Local config object
  Config _config;

public:
  /**
   * @brief Construct a new LSM6DSL object
   */
  LSM6DSL(String component_name = "LSM6DSL", void (*info_function)(String) = nullptr, void (*error_function)(String) = nullptr);

  /**
   * @brief Destroy the LSM6DSL object
   */
  ~LSM6DSL();

  bool begin(const Config &config);

  bool read();
};