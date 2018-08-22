/****************************************************************************/
//  Function:       Cpp file for TroykaMeteoSensor
//  Hardware:       SHT30, SHT31 and SHT35
//  Arduino IDE:    Arduino-1.8.5
//  Author:         Igor Dementiev
//  Date:           Aug 20,2018
//  Version:        v1.0.0
//  by www.amperka.ru
/****************************************************************************/

#include "TroykaMeteoSensor.h"

enum { HIGH_STATE, MEDIUM_STATE, LOW_STATE};

TroykaMeteoSensor::TroykaMeteoSensor(uint8_t i2cAddr) {
    _i2cAddr = i2cAddr;
}

TroykaMeteoSensor::~TroykaMeteoSensor() {
}

void TroykaMeteoSensor::begin() {
    Wire.begin();
    setRepeatability(HIGH_STATE);
    clockStretchingOff();
}

void TroykaMeteoSensor::reset() {
    _writeReg(SHT_SOFT_RESET);
}

int8_t TroykaMeteoSensor::read() {
    switch (_repeatability) {
        case HIGH_STATE:
            if(_stateClockStretching) {
                _writeReg(SHT_REP_HIGH_CLOCK_STRETCH);
            } else {
                _writeReg(SHT_REP_HIGH);
            }
            break;
        case MEDIUM_STATE:
            if(_stateClockStretching) {
                _writeReg(SHT_REP_MEDIUM_CLOCK_STRETCH);
            } else {
                _writeReg(SHT_REP_MEDIUM);
            }
            break;
        case LOW_STATE:
            if(_stateClockStretching) {
                _writeReg(SHT_REP_LOW_CLOCK_STRETCH);
            } else {
                _writeReg(SHT_REP_LOW);
            }
            break;
    }

    uint8_t data[SHT_DATA_SIZE];

    Wire.requestFrom(_i2cAddr, SHT_DATA_SIZE);

    if (Wire.available() != SHT_DATA_SIZE) {
        return SHT_ERROR_DATA;
    }

    for (int i = 0; i < SHT_DATA_SIZE; i++) {
        data[i] = Wire.read();
    }

    if (data[2] != _checkCRC8(data, 2) || data[5] != _checkCRC8(data + 3, 2)) {
        return SHT_ERROR_CHECKSUM;
    }

    _temperatureC = ((((data[0] * 256.0) + data[1]) * 175.0) / 65535.0) - 45.0;
    _temperatureF = (_temperatureC * 9.0 / 5.0) + 32.0;
    _temperatureK = _temperatureC + SHT_CELSIUS_TO_KELVIN;
    _humidity = ((((data[3] * 256.0) + data[4]) * 100.0) / 65535.0);

    return SHT_OK;
}

void TroykaMeteoSensor::setRepeatability(uint8_t repeatability) {
    switch (repeatability) {
        case HIGH_STATE:
            _repeatability = HIGH_STATE;
            break;
        case MEDIUM_STATE:
            _repeatability = MEDIUM_STATE;
            break;
        case LOW_STATE:
            _repeatability = LOW_STATE;
            break;
        default:
            _repeatability = HIGH_STATE;
            break;
    }
}

void TroykaMeteoSensor::clockStretchingOn() {
    _stateClockStretching = true;
}

void TroykaMeteoSensor::clockStretchingOff() {
    _stateClockStretching = false;
}



void TroykaMeteoSensor::heaterOn() {
    _writeReg(SHT_HEATER_ON);
}

void TroykaMeteoSensor::heaterOff() {
    _writeReg(SHT_HEATER_OFF);
}

void TroykaMeteoSensor::_writeReg(uint16_t data) {
    Wire.beginTransmission(_i2cAddr);
    Wire.write(data >> 8);
    Wire.write(data & 0xFF);
    Wire.endTransmission();  
}

uint8_t TroykaMeteoSensor::_checkCRC8(const uint8_t *data, int len) {
    // CRC-8 formula from page 14 of SHT Datasheet
    const uint8_t polynomial = 0x31;
    uint8_t crc = 0xFF;
    for (uint8_t byte = 0; byte < len; byte++) {
        crc ^= data[byte];
        for ( int bit = 0; bit < 8; bit++ ) {
            crc = (crc & 0x80) ? (crc << 1) ^ polynomial : (crc << 1);
        }
    }
    return crc;
}
