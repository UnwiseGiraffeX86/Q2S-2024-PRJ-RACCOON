# Q2S 2024 Project RACCOON

## Project Description
Project RACCOON is a multi-function environmental PocketQube satellite designed for the Qube2Space 2024 competition. This project aims to collect comprehensive data on atmospheric conditions at high altitudes. Equipped with a variety of sensors, Project RACCOON will measure temperature, barometric pressure, humidity, air quality index (AQI), volatile organic compounds (VOC), nitrogen oxides (NOx), carbon monoxide (CO), and capture high-resolution and thermal images. Additionally, it includes a GPS module for geolocation data and a LoRa module for long-range wireless communication. The project will be powered by a Raspberry Pi RP2040, four solar panels, and a LiPo battery with a custom charging circuit.

## Component List

| Component              | Model          | Link                                      | Price (€) |
|------------------------|----------------|-------------------------------------------|-----------|
| Temperature Monitoring, Barometric Pressure, Humidity Monitoring, AQI | BME680         | [Link](https://www.digikey.ro/en/products/detail/bosch-sensortec/BME680/7401317) | 12.81       |
| VOC+NOx Sensor         | SGP41 DR4      | [Link](https://www.tme.eu/ro/details/sgp41-d-r4/senzori-de-gaz/sensirion/3-000-060/) | 10.41        |
| CO Sensor              | MQ7            | [Link](https://www.optimusdigital.ro/ro/senzori-de-gaz/8673-senzor-de-gaz-monoxid-de-carbon-mq-7.html) | 4.77        |
| GPS Module             | GY NEO6MV2     | [Link](https://www.optimusdigital.ro/ro/module-gps/2387-modul-gps-cu-antena-gy-neo6mv2.html) | 15        |
| LoRa Module            | SX1276         | [Link](https://www.optimusdigital.ro/ro/module-wireless/2468-modul-wireless-lora-sx1276-433mhz.html) | 10        |
| Camera Module          | OV2640         | [Link](https://www.optimusdigital.ro/ro/module-camere/3277-modul-camera-ov2640.html) | 20        |
| Thermal Camera Module  | AMG8833        | [Link](https://www.digikey.ro/en/products/detail/panasonic-electronic-components/AMG8833/5850779) | 50        |
| Microcontroller        | Raspberry Pi RP2040 | [Link](https://www.raspberrypi.org/products/raspberry-pi-pico/) | 4         |
| Solar Panels (x4)      | 5V 1W each     | [Link](https://www.optimusdigital.ro/ro/solare/14185-panou-solar-5v-1w.html) | 12 (3 each)|
| LiPo Battery           | 3.7V 1000mAh   | [Link](https://www.optimusdigital.ro/ro/acumulatori-litiu/287-acumulator-li-po-37v-1000mah.html) | 8         |
| Charging Circuit       | Custom Design  | -                                         | 10        |

## Total Estimated Cost: 157.99 €

## Notes
- The Raspberry Pi RP2040 will serve as the main microcontroller for the project, providing ample processing power for sensor data acquisition and communication.
- The solar panels will be used to charge the LiPo battery, ensuring continuous power supply during the mission. A custom-designed charging circuit will manage the charging process. The design includes essential components such as a charge controller IC, protection circuitry, and power management components.
