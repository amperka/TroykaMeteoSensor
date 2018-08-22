/****************************************************************************/
//  Function:       Header file for TroykaMeteoSensor
//  Hardware:       SHT30, SHT31 and SHT35
//  Arduino IDE:    Arduino-1.8.5
//  Author:         Igor Dementiev
//  Date:           Aug 20,2018
//  Version:        v1.0.0
//  by www.amperka.ru
/****************************************************************************/

#include <Arduino.h>
#include <Wire.h>

#ifndef TROYKA_METEO_SENSOR_H_
#define TROYKA_METEO_SENSOR_H_

#define JUMPER_OFF                      0x44
#define JUMPER_ON                       0x45

#define SHT_REP_HIGH_CLOCK_STRETCH      0x2C06
#define SHT_REP_MEDIUM_CLOCK_STRETCH    0x2C0D
#define SHT_REP_LOW_CLOCK_STRETCH       0x2C10
#define SHT_REP_HIGH                    0x2400
#define SHT_REP_MEDIUM                  0x240B
#define SHT_REP_LOW                     0x2416
#define SHT_HEATER_ON                   0x306D
#define SHT_HEATER_OFF                  0x3066
#define SHT_SOFT_RESET                  0x30A2
#define SHT_READ_STATUS                 0xF32D

#define SHT_OK                          0
#define SHT_ERROR_DATA                  -1
#define SHT_ERROR_CHECKSUM              -2

#define SHT_DATA_SIZE                   6
#define SHT_CELSIUS_TO_KELVIN           273.15

class TroykaMeteoSensor
{
public:
    TroykaMeteoSensor(uint8_t i2cAddr = JUMPER_OFF);
    ~TroykaMeteoSensor();
    void begin();
    void reset();
    int8_t read();
    void setRepeatability(uint8_t repeatability);
    void clockStretchingOn();
    void clockStretchingOff();
    void heaterOn();
    void heaterOff();
    float getTemperatureC() const { return _temperatureC; }
    float getTemperatureF() const { return _temperatureF; }
    float getTemperatureK() const { return _temperatureK; }
    float getHumidity() const { return _humidity; }
private:
    void _writeReg(uint16_t data);
    uint8_t _checkCRC8(const uint8_t *data, int len);
    uint8_t _i2cAddr;
    uint8_t _repeatability;
    bool _stateClockStretching;
    float _temperatureC;
    float _temperatureF;
    float _temperatureK;
    float _humidity;

};

#endif  // TROYKA_METEO_SENSOR_H_
