#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <SensirionI2CSgp41.h>
#include "ICM20600.h"
#include "Adafruit_BME680.h"
#include "MQ7.h"
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "RF95.h"

extern uint8_t LoRa_buff[RH_RF95_FIFO_SIZE];

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C
ICM20600 icm(Wire);
SensirionI2CSgp41 sgp41;

// analog
MQ7 mq7(GPIO_NUM_4, 5.0);

// tx rx
// TinyGPSPlus gps;
SoftwareSerial ss(CLK_OUT1, CLK_OUT2);

// time in seconds needed for NOx conditioning
uint16_t conditioning_s = 10;

double dewPointFast(double celsius, double humidity);
void GPS();
void sendData();

void setup()
{
  Wire.begin();

  Serial.begin(9600);
  ss.begin(9600);

  if (!bme.begin())
  {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1)
      ;
  }
  if (!icm.begin())
  {
    Serial.println("ICM20600 initialization failed!");
    while (1)
      ;
  }

  uint16_t error;
  char errorMessage[256];

  sgp41.begin(Wire);

  uint8_t serialNumberSize = 3;
  uint16_t serialNumber[serialNumberSize];

  error = sgp41.getSerialNumber(serialNumber);

  // bme
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  if (error)
  {
    Serial.print("Error trying to execute getSerialNumber(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
  else
  {
    Serial.print("SerialNumber:");
    Serial.print("0x");
    for (size_t i = 0; i < serialNumberSize; i++)
    {
      uint16_t value = serialNumber[i];
      Serial.print(value < 4096 ? "0" : "");
      Serial.print(value < 256 ? "0" : "");
      Serial.print(value < 16 ? "0" : "");
      Serial.print(value, HEX);
    }
    Serial.println();
  }

  uint16_t testResult;
  error = sgp41.executeSelfTest(testResult);
  if (error)
  {
    Serial.print("Error trying to execute executeSelfTest(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
  else if (testResult != 0xD400)
  {
    Serial.print("executeSelfTest failed with error: ");
    Serial.println(testResult);
  }
}

void loop()
{
  GPS();

  // MQ7-B

  int MQ7 = mq7.getPPM();

  // BME680

  if (!bme.performReading())
  {
    Serial.println("Failed to perform reading :(");
    return;
  }

  float temperature = bme.temperature;
  float pressure = bme.pressure / 100.0; // Convert to hPa
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  float humidity = bme.humidity;
  float gas = bme.gas_resistance / 1000.0; // Convert to kOhms
  double dewPoint = dewPointFast(temperature, humidity);

  // ICM
  float ax = icm.getAccelerationX();
  float ay = icm.getAccelerationY();
  float az = icm.getAccelerationZ();
  float gx = icm.getGyroscopeX();
  float gy = icm.getGyroscopeY();
  float gz = icm.getGyroscopeZ();

  // SGP41

  uint16_t error;
  char errorMessage[256];
  uint16_t defaultRh = 0x8000;
  uint16_t defaultT = 0x6666;
  uint16_t srawVoc = 0;
  uint16_t srawNox = 0;

  delay(1000);

  if (conditioning_s > 0)
  {
    // During NOx conditioning (10s) SRAW NOx will remain 0
    error = sgp41.executeConditioning(defaultRh, defaultT, srawVoc);
    conditioning_s--;
  }
  else
  {
    // Read Measurement
    error = sgp41.measureRawSignals(defaultRh, defaultT, srawVoc, srawNox);
  }

  if (error)
  {
    Serial.print("Error trying to execute measureRawSignals(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
  else
  {
    Serial.print("SRAW_VOC:");
    Serial.print(srawVoc);
    Serial.print("\t");
    Serial.print("SRAW_NOx:");
    Serial.println(srawNox);
  }
}

double dewPointFast(double celsius, double humidity)
{
  double a = 17.27;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity / 100.0);
  return (b * temp) / (a - temp);
}

void GPS()
{
  while (ss.available() > 0)
  {
    // get the byte data from the GPS
    byte gpsData = ss.read();
    Serial.write(gpsData);
  }
}

void sendData()
{
  RF95_Init(); // Initialize LoRa module

  strcpy((char *)LoRa_buff, "Test to send"); // Copy the data into the buffer

  RF95_send(LoRa_buff); // Send the data stored in the buffer
}