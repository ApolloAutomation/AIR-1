# Apollo AIR-1

[![Apollo AIR-1](https://img.youtube.com/vi/Tqq4Si1y34c/hqdefault.jpg)](https://www.youtube.com/watch?v=Tqq4Si1y34c)


Key Features of the AIR-1 Sensor:

MiCS-4514 Below have individual gas % readout: CO, C2H5OH (Alcohol), H2, NO2, and NH3

SCD40: CO2 and includes temperature and humidity sensing capabilities. 

SEN55: Particulate matter (PM1, PM2.5, PM10), VOCs, NOx, humidity, and temperature. 

DPS368: Barometric air pressure and temperature.

Dimensions & Design: 

The AIR-1 measures just 61mm x 61mm x 30mm, and we have focused on efficient heat management within this small package to maintain sensor accuracy. This includes a thoughtful PCB layout and case design, incorporating ventilation and strategic component placement. 

YAML Files (in Integrations/ESPHome):
- AIR-1.yaml: This is the standard firmware and the one most people should use. It includes OTA updates (with a Firmware Update entity) and a Bluetooth Proxy, which is controlled by the "Bluetooth Proxy" switch and is off by default. This is also the image devices receive when they update over the air.
- AIR-1_BLE.yaml: This is the legacy BLE build for devices that originally shipped with the Bluetooth Proxy always on. It is the same firmware as AIR-1.yaml, except the Bluetooth Proxy switch defaults to on and it updates from its own firmware-ble manifest, so those devices keep proxying after an update.
- AIR-1_Factory.yaml: This is the firmware flashed by us on new devices and used by the web installer for first flashes. It contains the components for ESP improv (serial and Bluetooth), allowing easy Wi-Fi setup and adoption in Home Assistant, plus our factory test. Once the device updates over the air, it receives the AIR-1.yaml firmware, which no longer has improv.
- Core.yaml: Shared configuration included by all of the files above (sensors, light, Bluetooth Proxy, Firmware Channel and the firmware version number). You don't flash this file directly.
- Predicted_Room.yaml: Included from Core.yaml. Adds optional Estimated Room Temperature/Humidity sensors (called Predicted Room in older firmware) that correct for the enclosure's self-heating, plus their tuning settings. Everything in it is disabled by default.
- reduce_filter.yaml: Included from Core.yaml. The filter behind the "Reduce DB Reporting" switch: when it is on, a sensor only reports when its value changes meaningfully or a periodic heartbeat is due. You don't flash this file directly.

Firmware Channels:
- The device has a "Firmware Channel" setting with two options: Stable and Beta. It controls where the Firmware Update entity looks for new firmware.
- Stable (the default) receives releases built from the main branch.
- Beta receives builds from the beta branch as soon as changes are merged there. Expect newer features and fixes, but less testing. You can switch back to Stable at any time.

Contributing:
- Please open pull requests against the beta branch (the default branch), not main. Changes are tested in beta and then merged to main for the Stable release.

Links:

Discord (Support/feedback/discussion/future products): [https://dsc.gg/ApolloAutomation] \
Shop: [https://apolloautomation.com](https://apolloautomation.com/products/air-1) \
Wiki: [https://wiki.apolloautomation.com](https://wiki.apolloautomation.com/) \
3D Files: [https://www.printables.com/model/932001-apollo-automation-air-1-air-quality-sensor-for-hom](https://www.printables.com/model/932001-apollo-automation-air-1-air-quality-sensor-for-hom)
