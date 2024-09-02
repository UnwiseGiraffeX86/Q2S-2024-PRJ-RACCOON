#include "RF95.h"
#include <cstring> // for std::memset, std::strlen
#include <cstdio>  // for std::sprintf

extern SPI_HandleTypeDef hspi1;

RHMode _mode;
uint16_t _cad_timeout = 10000;
uint8_t LoRa_buff[RH_RF95_FIFO_SIZE] = {0};

#if Header == Header_used
char _txHeaderTo = 0;
#endif

char MODEM_CONFIG_TABLE[5][3] =
    {
        //  1d,     1e,      26
        {0x72, 0x74, 0x00}, // Bw125Cr45Sf128 (the chip default)
        {0x92, 0x74, 0x00}, // Bw500Cr45Sf128
        {0x48, 0x94, 0x00}, // Bw31_25Cr48Sf512
        {0x78, 0xc4, 0x00}, // Bw125Cr48Sf4096
        {0x73, 0x74, 0x00}, // IH_Bw125Cr45Sf128 (the chip default + Implicit header)
};

HAL_StatusTypeDef err;

HAL_StatusTypeDef RF95_write(char reg, char wValue)
{
    char buff[2] = {0};

    buff[0] = W | reg;
    buff[1] = wValue;

    HAL_GPIO_WritePin(LoRa_CS_GPIO_Port, LoRa_CS_Pin, GPIO_PIN_RESET);
    err = HAL_SPI_Transmit(&hspi1, reinterpret_cast<uint8_t *>(&buff), 2, 100);
    HAL_GPIO_WritePin(LoRa_CS_GPIO_Port, LoRa_CS_Pin, GPIO_PIN_SET);

    return err;
}

HAL_StatusTypeDef RF95_write_burst(char reg, uint8_t *data)
{
    int length = 0;
    uint8_t cmd = W | reg;
    HAL_StatusTypeDef err;

    length = std::strlen(reinterpret_cast<const char *>(data));

    HAL_GPIO_WritePin(LoRa_CS_GPIO_Port, LoRa_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &cmd, 1, 100);
    err = HAL_SPI_Transmit(&hspi1, LoRa_buff, length, 100);
    HAL_GPIO_WritePin(LoRa_CS_GPIO_Port, LoRa_CS_Pin, GPIO_PIN_SET);

    return err;
}

char RF95_read(char reg)
{
    char buff = R & reg;

    HAL_GPIO_WritePin(LoRa_CS_GPIO_Port, LoRa_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, reinterpret_cast<uint8_t *>(&buff), 1, 100);
    HAL_SPI_Receive(&hspi1, reinterpret_cast<uint8_t *>(&buff), 1, 100);
    HAL_GPIO_WritePin(LoRa_CS_GPIO_Port, LoRa_CS_Pin, GPIO_PIN_SET);

    return buff;
}

HAL_StatusTypeDef RF95_read_burst(char reg, char *buffer, int length)
{
    buffer[0] = R & reg;
    HAL_StatusTypeDef err;

    HAL_GPIO_WritePin(LoRa_CS_GPIO_Port, LoRa_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, reinterpret_cast<uint8_t *>(buffer), 1, 100);
    err = HAL_SPI_Receive(&hspi1, reinterpret_cast<uint8_t *>(buffer), length, 100);
    HAL_GPIO_WritePin(LoRa_CS_GPIO_Port, LoRa_CS_Pin, GPIO_PIN_SET);

    return err;
}

void RF95_Reset(void)
{
    HAL_GPIO_WritePin(LoRa_RESET_GPIO_Port, LoRa_RESET_Pin, GPIO_PIN_RESET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(LoRa_RESET_GPIO_Port, LoRa_RESET_Pin, GPIO_PIN_SET);
}

uint8_t rbuff = 0;
bool RF95_Init(void)
{
    RF95_Reset();

    // Set sleep mode, so we can also set LORA mode:
    RF95_sleep();

    RF95_write(RH_RF95_REG_01_OP_MODE, RH_RF95_MODE_SLEEP | RH_RF95_LONG_RANGE_MODE);
    HAL_Delay(20); // Wait for sleep mode to take over from say, CAD

    // Check we are in sleep mode, with LORA set
    rbuff = RF95_read(RH_RF95_REG_01_OP_MODE);
    if (rbuff != (RH_RF95_MODE_SLEEP | RH_RF95_LONG_RANGE_MODE))
    {
        return false; // No device present?
    }

    // Set up FIFO
    RF95_write(RH_RF95_REG_0E_FIFO_TX_BASE_ADDR, 0);
    RF95_write(RH_RF95_REG_0F_FIFO_RX_BASE_ADDR, 0);

    RF95_setModeIdle();

    // Set up default configuration
    RF95_setModemConfig(Bw125Cr45Sf128); // Radio default
    RF95_setPreambleLength(8);           // Default is 8
    RF95_setFrequency(868.0);
    RF95_setTxPower(13, false);

    return true;
}

bool RF95_setModemConfig(ModemConfigChoice index)
{
    RF95_write(RH_RF95_REG_1D_MODEM_CONFIG1, MODEM_CONFIG_TABLE[index][0]);
    RF95_write(RH_RF95_REG_1E_MODEM_CONFIG2, MODEM_CONFIG_TABLE[index][1]);
    RF95_write(RH_RF95_REG_26_MODEM_CONFIG3, MODEM_CONFIG_TABLE[index][2]);

    return true;
}

void RF95_setPreambleLength(uint16_t bytes)
{
    RF95_write(RH_RF95_REG_20_PREAMBLE_MSB, bytes >> 8);
    RF95_write(RH_RF95_REG_21_PREAMBLE_LSB, bytes & 0xff);
}

bool RF95_setFrequency(float centre)
{
    uint64_t frf = static_cast<uint32_t>(centre * 1000000.0) / static_cast<uint32_t>(RH_RF95_FSTEP);
    RF95_write(RH_RF95_REG_06_FRF_MSB, (frf >> 16) & 0xff);
    RF95_write(RH_RF95_REG_07_FRF_MID, (frf >> 8) & 0xff);
    RF95_write(RH_RF95_REG_08_FRF_LSB, frf & 0xff);

    return true;
}

void RF95_setTxPower(int8_t power, bool useRFO)
{
    if (useRFO)
    {
        if (power > 14)
            power = 14;
        if (power < -1)
            power = -1;
        RF95_write(RH_RF95_REG_09_PA_CONFIG, RH_RF95_MAX_POWER | (power + 1));
    }
    else
    {
        if (power > 23)
            power = 23;
        if (power < 5)
            power = 5;

        if (power > 20)
        {
            RF95_write(RH_RF95_REG_4D_PA_DAC, RH_RF95_PA_DAC_ENABLE);
            power -= 3;
        }
        else
        {
            RF95_write(RH_RF95_REG_4D_PA_DAC, RH_RF95_PA_DAC_DISABLE);
        }

        RF95_write(RH_RF95_REG_09_PA_CONFIG, RH_RF95_PA_SELECT | (power - 5));
    }
}

bool RF95_receive(uint8_t *data)
{
    int len = 0;

    if (_mode == RHModeRx)
    {
        while (!RF95_available())
        {
        }

        if (RF95_Check_PayloadCRCError())
            return false;

        len = RF95_read(RH_RF95_REG_13_RX_NB_BYTES);

        RF95_write(RH_RF95_REG_0D_FIFO_ADDR_PTR, RF95_read(RH_RF95_REG_10_FIFO_RX_CURRENT_ADDR));
        RF95_read_burst(RH_RF95_REG_00_FIFO, reinterpret_cast<char *>(data), len);

        RF95_setModeIdle();
        RF95_Clear_IRQ();

        return true;
    }
    else
        return false;
}

bool RF95_receive_Timeout(uint8_t *buf, uint16_t timeout)
{
    int len = 0;

    if (_mode == RHModeRx)
    {
        if (!RF95_available_Timeout(timeout))
        {
            return false;
        }

        if (RF95_Check_PayloadCRCError())
            return false;

        len = RF95_read(RH_RF95_REG_13_RX_NB_BYTES);

        RF95_write(RH_RF95_REG_0D_FIFO_ADDR_PTR, RF95_read(RH_RF95_REG_10_FIFO_RX_CURRENT_ADDR));
        RF95_read_burst(RH_RF95_REG_00_FIFO, reinterpret_cast<char *>(buf), len);

        RF95_setModeIdle();
        RF95_Clear_IRQ();

        if (RF95_Check_PayloadCRCError())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
        return false;
}

bool RF95_send(uint8_t *data)
{
    int len = std::strlen(reinterpret_cast<char *>(data));

#if Header == Header_used
    uint16_t header_len = sizeof(_txHeaderTo);
#endif

    if (len > RH_RF95_MAX_MESSAGE_LEN)
        return false;

    RF95_waitPacketSent();
    RF95_setModeIdle();

    if (!RF95_waitCAD())
        return false;

    RF95_write(RH_RF95_REG_0D_FIFO_ADDR_PTR, 0);
    RF95_write_burst(RH_RF95_REG_00_FIFO, data);

    RF95_write(RH_RF95_REG_22_PAYLOAD_LENGTH, len);

#if Header == Header_used
    RF95_write(RH_RF95_REG_0D_FIFO_ADDR_PTR, header_len);
    RF95_write_burst(RH_RF95_REG_00_FIFO, data);
#endif

    RF95_setModeTx();
    return true;
}
