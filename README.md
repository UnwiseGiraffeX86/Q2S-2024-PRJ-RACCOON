# Q2S 2024 Project RACCOON

## Project Description
Project RACCOON is a multi-function environmental PocketQube satellite designed for the Qube2Space 2024 competition. This project aims to collect comprehensive data on atmospheric conditions at high altitudes. Equipped with a variety of sensors, Project RACCOON will measure temperature, barometric pressure, humidity, air quality index (AQI), volatile organic compounds (VOC), nitrogen oxides (NOx), carbon monoxide (CO), and capture high-resolution and thermal images. Additionally, it includes a GPS module for geolocation data and a LoRa module for long-range wireless communication. The project will be powered by a Raspberry Pi RP2040, four solar panels, and a LiPo battery with a custom charging circuit.

## Component List

| Component              | Model          | Link                                      |
|------------------------|----------------|-------------------------------------------|
| Temperature Monitoring, Barometric Pressure, Humidity Monitoring, AQI | BME680         | [Link](https://www.digikey.ro/en/products/detail/bosch-sensortec/BME680/7401317) |
| VOC+NOx Sensor         | SGP41 DR4      | [Link](https://www.tme.eu/ro/details/sgp41-d-r4/senzori-de-gaz/sensirion/3-000-060/) |
| CO Sensor              | MQ7            | [Link](https://www.tme.eu/ro/details/mq-7b/senzori-de-gaz/winsen/?brutto=1&currency=USD&gad_source=1&gclid=Cj0KCQjw-uK0BhC0ARIsANQtgGOsI7EkvtdED2ZxLiqlhXaZKtODT48B4xei-8gTNv-doRfv31SX0t4aAt5JEALw_wcB) |
| GPS Module             | GY NEO6MV2     | [Link](https://www.optimusdigital.ro/ro/module-gps/2387-modul-gps-cu-antena-gy-neo6mv2.html) |
| LoRa Module            | SX1276         | [Link](https://www.optimusdigital.ro/ro/module-wireless/2468-modul-wireless-lora-sx1276-433mhz.html) |
| Camera Module          | OV2640         | [Link](https://www.optimusdigital.ro/ro/module-camere/3277-modul-camera-ov2640.html) |
| Thermal Camera Module  | AMG8833        | [Link](https://www.digikey.ro/en/products/detail/panasonic-electronic-components/AMG8833/5850779) |
| Microcontroller        | Raspberry Pi RP2040 | [Link](https://www.tme.eu/ro/details/sc0915/raspberry-pi-minicomputers/raspberry-pi/raspberry-pi-pico/) |
| 6-DOF IMU              | BMI323         | [Link](https://www.digikey.ro/en/products/detail/bosch-sensortec/BMI323/16719593) |

## Notes
- The Raspberry Pi RP2040 will serve as the main microcontroller for the project, providing ample processing power for sensor data acquisition and communication.
- The solar panels will be used to charge the LiPo battery, ensuring continuous power supply during the mission. A custom-designed charging circuit will manage the charging process. The design includes essential components such as a charge controller IC, protection circuitry, and power management components.
- The BMI323 IMU will provide detailed motion sensing and orientation data, enhancing the project's capability to monitor environmental and positional changes.
