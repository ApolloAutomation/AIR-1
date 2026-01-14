#include "sen5x_number.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace sen5x_number {

static const char *const TAG = "sen5x_number";

void SEN5xNumberConcentration::setup() {
  ESP_LOGCONFIG(TAG, "Setting up SEN5x Number Concentration (EXPERIMENTAL)...");
}

void SEN5xNumberConcentration::dump_config() {
  ESP_LOGCONFIG(TAG, "SEN5x Number Concentration (EXPERIMENTAL):");
  LOG_I2C_DEVICE(this);
  LOG_UPDATE_INTERVAL(this);
  LOG_SENSOR("  ", "PM0.5 Number", this->pm_0_5_number_);
  LOG_SENSOR("  ", "PM1.0 Number", this->pm_1_0_number_);
  LOG_SENSOR("  ", "PM2.5 Number", this->pm_2_5_number_);
  LOG_SENSOR("  ", "PM4.0 Number", this->pm_4_0_number_);
  LOG_SENSOR("  ", "PM10.0 Number", this->pm_10_0_number_);
  LOG_SENSOR("  ", "Typical Particle Size", this->typical_particle_size_);
}

void SEN5xNumberConcentration::update() {
  if (!this->read_data_()) {
    ESP_LOGW(TAG, "Failed to read number concentration data");
    this->status_set_warning();
    return;
  }
  this->status_clear_warning();
}

uint8_t SEN5xNumberConcentration::sht_crc_(uint8_t data1, uint8_t data2) {
  // CRC-8 formula from Sensirion datasheet
  uint8_t crc = 0xFF;
  uint8_t data[2] = {data1, data2};

  for (uint8_t i = 0; i < 2; i++) {
    crc ^= data[i];
    for (uint8_t bit = 8; bit > 0; --bit) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ 0x31;
      } else {
        crc = (crc << 1);
      }
    }
  }
  return crc;
}

bool SEN5xNumberConcentration::read_data_() {
  // Send command 0x0413 (Read Measured Mass and Number Concentrations)
  uint8_t command[2] = {
    static_cast<uint8_t>(SEN5X_CMD_READ_MASS_NUMBER >> 8),
    static_cast<uint8_t>(SEN5X_CMD_READ_MASS_NUMBER & 0xFF)
  };

  if (this->write(command, 2) != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "Failed to send read command");
    return false;
  }

  // Wait for measurement to be ready (typical 20ms for SEN5x)
  delay(20);

  // Read response: 45 bytes (15 values x 3 bytes each: 2 data + 1 CRC)
  uint8_t response[SEN5X_RESPONSE_LENGTH];
  if (this->read(response, SEN5X_RESPONSE_LENGTH) != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "Failed to read response data");
    return false;
  }

  // Parse response with CRC validation
  // Response format (all values are uint16_t with CRC):
  // Bytes 0-2:   PM1.0 mass concentration (µg/m³) - we ignore this
  // Bytes 3-5:   PM2.5 mass concentration (µg/m³) - we ignore this
  // Bytes 6-8:   PM4.0 mass concentration (µg/m³) - we ignore this
  // Bytes 9-11:  PM10.0 mass concentration (µg/m³) - we ignore this
  // Bytes 12-14: PM0.5 number concentration (#/cm³) - NEW
  // Bytes 15-17: PM1.0 number concentration (#/cm³) - NEW
  // Bytes 18-20: PM2.5 number concentration (#/cm³) - NEW
  // Bytes 21-23: PM4.0 number concentration (#/cm³) - NEW
  // Bytes 24-26: PM10.0 number concentration (#/cm³) - NEW
  // Bytes 27-29: Typical particle size (µm) - NEW
  // Bytes 30-44: Additional reserved values

  auto parse_value = [&](uint8_t offset) -> float {
    uint8_t msb = response[offset];
    uint8_t lsb = response[offset + 1];
    uint8_t crc = response[offset + 2];

    if (crc != this->sht_crc_(msb, lsb)) {
      ESP_LOGW(TAG, "CRC check failed for byte offset %d", offset);
      return NAN;
    }

    uint16_t raw = (static_cast<uint16_t>(msb) << 8) | lsb;
    return static_cast<float>(raw);
  };

  // Extract number concentrations (converting from #/cm³ to #/m³)
  // Note: 1 #/cm³ = 1,000,000 #/m³
  if (this->pm_0_5_number_ != nullptr) {
    float value = parse_value(12) / 10.0f; // Scaled by 10 per datasheet
    if (!std::isnan(value)) {
      this->pm_0_5_number_->publish_state(value * 1e6f); // Convert to #/m³
    }
  }

  if (this->pm_1_0_number_ != nullptr) {
    float value = parse_value(15) / 10.0f;
    if (!std::isnan(value)) {
      this->pm_1_0_number_->publish_state(value * 1e6f);
    }
  }

  if (this->pm_2_5_number_ != nullptr) {
    float value = parse_value(18) / 10.0f;
    if (!std::isnan(value)) {
      this->pm_2_5_number_->publish_state(value * 1e6f);
    }
  }

  if (this->pm_4_0_number_ != nullptr) {
    float value = parse_value(21) / 10.0f;
    if (!std::isnan(value)) {
      this->pm_4_0_number_->publish_state(value * 1e6f);
    }
  }

  if (this->pm_10_0_number_ != nullptr) {
    float value = parse_value(24) / 10.0f;
    if (!std::isnan(value)) {
      this->pm_10_0_number_->publish_state(value * 1e6f);
    }
  }

  // Typical particle size in µm
  if (this->typical_particle_size_ != nullptr) {
    float value = parse_value(27) / 1000.0f; // Scaled by 1000 per datasheet
    if (!std::isnan(value)) {
      this->typical_particle_size_->publish_state(value);
    }
  }

  return true;
}

}  // namespace sen5x_number
}  // namespace esphome
