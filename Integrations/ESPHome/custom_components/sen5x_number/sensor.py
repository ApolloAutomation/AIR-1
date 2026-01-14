import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_PM25,
    STATE_CLASS_MEASUREMENT,
    ICON_CHEMICAL_WEAPON,
)

DEPENDENCIES = ["i2c"]
CODEOWNERS = ["@apolloautomation"]

sen5x_number_ns = cg.esphome_ns.namespace("sen5x_number")
SEN5xNumberConcentration = sen5x_number_ns.class_(
    "SEN5xNumberConcentration", cg.PollingComponent, i2c.I2CDevice
)

CONF_PM_0_5_NUMBER = "pm_0_5_number"
CONF_PM_1_0_NUMBER = "pm_1_0_number"
CONF_PM_2_5_NUMBER = "pm_2_5_number"
CONF_PM_4_0_NUMBER = "pm_4_0_number"
CONF_PM_10_0_NUMBER = "pm_10_0_number"
CONF_TYPICAL_PARTICLE_SIZE = "typical_particle_size"

# Unit for particle number concentration
UNIT_NUMBER_PER_CUBIC_METER = "#/m³"
UNIT_MICROMETER = "µm"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(SEN5xNumberConcentration),
            cv.Optional(CONF_PM_0_5_NUMBER): sensor.sensor_schema(
                unit_of_measurement=UNIT_NUMBER_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PM25,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_1_0_NUMBER): sensor.sensor_schema(
                unit_of_measurement=UNIT_NUMBER_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PM25,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_2_5_NUMBER): sensor.sensor_schema(
                unit_of_measurement=UNIT_NUMBER_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PM25,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_4_0_NUMBER): sensor.sensor_schema(
                unit_of_measurement=UNIT_NUMBER_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PM25,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_10_0_NUMBER): sensor.sensor_schema(
                unit_of_measurement=UNIT_NUMBER_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PM25,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_TYPICAL_PARTICLE_SIZE): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROMETER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=2,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
        }
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(i2c.i2c_device_schema(0x69))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if CONF_PM_0_5_NUMBER in config:
        sens = await sensor.new_sensor(config[CONF_PM_0_5_NUMBER])
        cg.add(var.set_pm_0_5_number_sensor(sens))

    if CONF_PM_1_0_NUMBER in config:
        sens = await sensor.new_sensor(config[CONF_PM_1_0_NUMBER])
        cg.add(var.set_pm_1_0_number_sensor(sens))

    if CONF_PM_2_5_NUMBER in config:
        sens = await sensor.new_sensor(config[CONF_PM_2_5_NUMBER])
        cg.add(var.set_pm_2_5_number_sensor(sens))

    if CONF_PM_4_0_NUMBER in config:
        sens = await sensor.new_sensor(config[CONF_PM_4_0_NUMBER])
        cg.add(var.set_pm_4_0_number_sensor(sens))

    if CONF_PM_10_0_NUMBER in config:
        sens = await sensor.new_sensor(config[CONF_PM_10_0_NUMBER])
        cg.add(var.set_pm_10_0_number_sensor(sens))

    if CONF_TYPICAL_PARTICLE_SIZE in config:
        sens = await sensor.new_sensor(config[CONF_TYPICAL_PARTICLE_SIZE])
        cg.add(var.set_typical_particle_size_sensor(sens))
