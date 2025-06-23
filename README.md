# Apollo AIR-1

![air-1-image](https://github.com/user-attachments/assets/09e5b0a2-0585-4480-8433-8d6efd9c7a69)

Key Features of the AIR-1 Sensor:

SCD40: CO2 and includes temperature and humidity sensing capabilities. 

SEN55: Particulate matter (PM1, PM2.5, PM10), VOCs, NOx, humidity, and temperature. 

DPS310: Barometric air pressure and temperature.

Dimensions & Design: 

The AIR-1 measures just 61mm x 61mm x 30mm, and we have focused on efficient heat management within this small package to maintain sensor accuracy. This includes a thoughtful PCB layout and case design, incorporating ventilation and strategic component placement. 

YAML Files:
- AIR-1.yaml: This file is a minimal config. It doesn't have the bluetooth or OTA components. Use this if you are looking to add BLE proxy or BLE tracking.
- AIR-1_BLE.yaml: This file contains BLE proxy code. We use it as an automated test during our build process. But can be an example for adding BLE proxy to your device.
- AIR-1_Factory.yaml: This is the firmware flashed by us on new devices. It contains the components for ESP improve, allowing easy adoption in Home Assistant. When you load the device in ESPHome addon, it will grab the firmware from AIR-1.yaml which no longer has the improve.



Links:

Discord (Support/feedback/discussion/future products): [https://dsc.gg/ApolloAutomation] \
Shop: [https://apolloautomation.com](https://apolloautomation.com/products/air-1) \
Wiki: [https://wiki.apolloautomation.com](https://wiki.apolloautomation.com/) \
3D Files: [https://www.printables.com/model/932001-apollo-automation-air-1-air-quality-sensor-for-hom](https://www.printables.com/model/932001-apollo-automation-air-1-air-quality-sensor-for-hom)
