#include <MUFFINS_LSM6DSL.h>

LSM6DSL::LSM6DSL(String component_name, void (*info_function)(String), void (*error_function)(String))
    : Component_Base(component_name, info_function, error_function)
{
  return;
}

LSM6DSL::~LSM6DSL()
{
  return;
}

bool LSM6DSL::begin(const Config &config)
{
  _config = config;

  // This will always return false
  // The problem is in the library, where the begin function returns false in any case
  _imu.begin_I2C(_config.i2c_address, _config.wire);

  // Set IMU settings
  _imu.setAccelRange(_config.accel_range);
  _imu.setGyroRange(_config.gyro_range);
  _imu.setAccelDataRate(_config.accel_data_rate);
  _imu.setGyroDataRate(_config.gyro_data_rate);

  info("Initialized");
  set_initialized(true);

  return true;
}

bool LSM6DSL::read()
{
  if (!initialized())
  {
    return false;
  }

  sensors_event_t accel_event, gyro_event, temp_event;
  if (!_imu.getEvent(&accel_event, &gyro_event, &temp_event))
  {
    error("Failed to read data");
    return false;
  };

  data.temperature = temp_event.temperature;
  data.accel_x = accel_event.acceleration.x;
  data.accel_y = accel_event.acceleration.y;
  data.accel_z = accel_event.acceleration.z;
  data.gyro_x = gyro_event.gyro.x;
  data.gyro_y = gyro_event.gyro.y;
  data.gyro_z = gyro_event.gyro.z;

  return true;
}