#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace sen5x_number {

// EXPERIMENTAL: Custom component for SEN5x particle NUMBER concentration
// Uses undocumented I2C command 0x0413 to read both mass and number concentrations
// Reference: Sensirion_SEN5x_Read_Mass_and_Number_Concentrations.pdf

class SEN5xNumberConcentration : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_pm_0_5_number_sensor(sensor::Sensor *pm_0_5_number) { pm_0_5_number_ = pm_0_5_number; }
  void set_pm_1_0_number_sensor(sensor::Sensor *pm_1_0_number) { pm_1_0_number_ = pm_1_0_number; }
  void set_pm_2_5_number_sensor(sensor::Sensor *pm_2_5_number) { pm_2_5_number_ = pm_2_5_number; }
  void set_pm_4_0_number_sensor(sensor::Sensor *pm_4_0_number) { pm_4_0_number_ = pm_4_0_number; }
  void set_pm_10_0_number_sensor(sensor::Sensor *pm_10_0_number) { pm_10_0_number_ = pm_10_0_number; }
  void set_typical_particle_size_sensor(sensor::Sensor *typical_size) { typical_particle_size_ = typical_size; }

 protected:
  sensor::Sensor *pm_0_5_number_{nullptr};
  sensor::Sensor *pm_1_0_number_{nullptr};
  sensor::Sensor *pm_2_5_number_{nullptr};
  sensor::Sensor *pm_4_0_number_{nullptr};
  sensor::Sensor *pm_10_0_number_{nullptr};
  sensor::Sensor *typical_particle_size_{nullptr};

  bool read_data_();
  uint8_t sht_crc_(uint8_t data1, uint8_t data2);

  // SEN5x I2C command: Read Measured Mass and Number Concentrations
  static const uint16_t SEN5X_CMD_READ_MASS_NUMBER = 0x0413;
  static const uint8_t SEN5X_RESPONSE_LENGTH = 45; // 15 values x 3 bytes (2 data + 1 CRC)
};

}  // namespace sen5x_number
}  // namespace esphome
