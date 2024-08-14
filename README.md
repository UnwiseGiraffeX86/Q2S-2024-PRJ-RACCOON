# 🚀 Q2S 2024 Project RACCOON

## 🛰 Project Overview
**Project RACCOON** is a cutting-edge, multi-function environmental PocketQube satellite designed for the **Qube2Space 2024** competition. Our mission is to push the boundaries of space-based environmental monitoring and data collection using advanced sensors and AI-driven analysis. This README provides a detailed overview of our mission objectives, system architecture, and power consumption.

---

## 🎯 Primary Mission: Flight Data Measurement
### Mission Objective:
Measure and store atmospheric temperature and acceleration on three axes throughout the entire flight.

### Mission Details:
- **Parameters Measured**:
  - **Atmospheric Temperature**: Collected using the BME680 sensor.
  - **Acceleration (3 Axes)**: Captured using the ICM-20600 6-DOF IMU.
- **Sampling Frequency**: Minimum of 5 Hz (5 samples per second).
- **Data Storage**: All data is stored on an SD card in `.csv` or `.txt` format for post-flight analysis.
- **Post-Flight Analysis**: Data will be used to calculate altitude and generate graphs, such as acceleration vs. altitude.

---

## 🌟 Secondary Missions

### 1. **ENVIRO** (Environmental Monitoring and Data Collection)
**Objective**: Collect comprehensive atmospheric data to complement the primary mission.

- **Parameters Measured**:
  - **Barometric Pressure**
  - **Humidity**
  - **Air Quality Index (AQI)**
  - **Volatile Organic Compounds (VOC)**
  - **Nitrogen Oxides (NOx)**
  - **Carbon Monoxide (CO)**
  - **Ultraviolet (UV) Light Intensity**
- **Components Used**: BME680, SGP41-D-R4, MQ-7B, GUVA S12SD.
- **Purpose**: Provide valuable data for environmental studies and enrich primary mission data.

### 2. **IMAGINE** (Imaging and Geospatial Observation)
**Objective**: Capture high-resolution and thermal images of Earth from varying altitudes.

- **Parameters Measured**:
  - **High-Resolution Visual Imagery**
  - **Thermal Imagery**
- **Components Used**: OV2640 (camera), AMG8833 (thermal camera).
- **Purpose**: Enhance environmental data with visual and thermal correlations.

### 3. **SENTRY** (Sensor-Based Anomaly Detection Using AI)
**Objective**: Use AI/ML to detect anomalies in environmental data.

- **Parameters Analyzed**:
  - **Temperature**
  - **Pressure**
  - **Humidity**
  - **AQI**
  - **VOC**
  - **NOx**
  - **CO**
  - **UV Intensity**
- **Components Used**: ESP32-S3 for real-time ML processing.
- **ML/AI Features**:
  - **Model**: Anomaly detection trained on historical atmospheric data.
  - **Purpose**: Identify unusual patterns that may indicate anomalies.

---

## ⚡ Power Consumption Overview
| Component                   | Mode                           | Average Power Consumption (mA) |
|-----------------------------|--------------------------------|--------------------------------|
| **ESP32-S3**                 | Active (ML Processing)         | 240                            |
| **BME680**                   | Active                         | 2.1                            |
| **ICM-20600 IMU**            | Active                         | 1.5                            |
| **SGP41-D-R4**               | Active                         | 2.6                            |
| **MQ-7B**                    | Active (Reduced Sampling)      | 30                             |
| **GY NEO6MV2 GPS**           | Active                         | 35                             |
| **RFM96 LoRa Module**        | Sleep (Most of the Time)       | 1µA (negligible)               |
| **OV2640 Camera**            | Active (Every 10 Seconds)      | 1.5                            |
| **AMG8833 Thermal Camera**   | Active (Intermittent)          | 4.5                            |
| **GUVA S12SD UV Sensor**     | Active                         | 0.1                            |
| **Total Average Consumption**|                                | **317.3 mA**                   |

---

## 📋 Final Notes
- **Optimize Sensor Usage**: Intermittent operation and efficient data handling are key to staying within the power budget.
- **Power Management**: The ESP32-S3’s low-power modes will be leveraged to conserve energy during inactive periods.
- **Post-Mission Analysis**: The collected data will be instrumental in generating insights and visuals to fulfill the primary mission and contribute to scientific understanding.

---

## 🛠️ Project Contributors
- **Geala Stefan** - Project Lead
- **Stanescu Serban** - Software & AI/ML Developer
- **Craciunescu Stefan** - Hardware & Electronics Specialist
- **Dumitrescu Ioan Valeriu** - Data Analyst & Visualization Expert
- **Dumitrescu Radu** - CAD & Design Specialist


