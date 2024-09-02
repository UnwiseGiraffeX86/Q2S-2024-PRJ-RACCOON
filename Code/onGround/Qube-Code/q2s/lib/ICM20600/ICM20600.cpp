#include "ICM20600.h"

ICM20600::ICM20600(TwoWire &wire, uint8_t address)
    : wire(&wire), address(address) {}

bool ICM20600::begin()
{
    wire->begin();
    uint8_t whoAmI = readByte(WHO_AM_I);
    if (whoAmI != 0x11)
    { // Expected WHO_AM_I response for ICM20600
        return false;
    }
    initialize();
    return true;
}

void ICM20600::initialize()
{
    // Wake up the sensor by clearing the sleep bit
    writeByte(PWR_MGMT_1, 0x00);
    // Additional sensor configuration can go here
}

float ICM20600::getGyroscopeX()
{
    return read16Bit(GYRO_XOUT_H);
}

float ICM20600::getGyroscopeY()
{
    return read16Bit(GYRO_XOUT_H + 2);
}

float ICM20600::getGyroscopeZ()
{
    return read16Bit(GYRO_XOUT_H + 4);
}

float ICM20600::getAccelerationX()
{
    return read16Bit(ACCEL_XOUT_H);
}

float ICM20600::getAccelerationY()
{
    return read16Bit(ACCEL_XOUT_H + 2);
}

float ICM20600::getAccelerationZ()
{
    return read16Bit(ACCEL_XOUT_H + 4);
}

int16_t ICM20600::read16Bit(uint8_t reg)
{
    wire->beginTransmission(address);
    wire->write(reg);
    wire->endTransmission(false);
    wire->requestFrom(address, (uint8_t)2);
    int16_t value = (wire->read() << 8) | wire->read();
    return value;
}

void ICM20600::writeByte(uint8_t reg, uint8_t data)
{
    wire->beginTransmission(address);
    wire->write(reg);
    wire->write(data);
    wire->endTransmission();
}

uint8_t ICM20600::readByte(uint8_t reg)
{
    wire->beginTransmission(address);
    wire->write(reg);
    wire->endTransmission(false);
    wire->requestFrom(address, (uint8_t)1);
    return wire->read();
}
