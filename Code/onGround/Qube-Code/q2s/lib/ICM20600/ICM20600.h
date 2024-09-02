#ifndef ICM20600_H
#define ICM20600_H

#include <Wire.h>

#define ICM20600_ADDRESS 0x68 // Default I2C address for ICM20600
#define WHO_AM_I 0x75         // WHO_AM_I register
#define PWR_MGMT_1 0x6B       // Power management register 1
#define ACCEL_XOUT_H 0x3B     // Acceleration X-axis high byte
#define GYRO_XOUT_H 0x43      // Gyroscope X-axis high byte

class ICM20600
{
public:
    ICM20600(TwoWire &wire, uint8_t address = ICM20600_ADDRESS);

    bool begin();
    void initialize();
    float getGyroscopeX();
    float getGyroscopeY();
    float getGyroscopeZ();
    float getAccelerationX();
    float getAccelerationY();
    float getAccelerationZ();

private:
    TwoWire *wire;
    uint8_t address;

    int16_t read16Bit(uint8_t reg);
    void writeByte(uint8_t reg, uint8_t data);
    uint8_t readByte(uint8_t reg);
};

#endif
