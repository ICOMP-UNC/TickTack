#pragma once

#include <libopencm3/stm32/i2c.h>
#include <stdio.h>

typedef struct
{
    uint8_t day;    // Día
    uint8_t month;  // Mes
    uint8_t year;   // Año
    uint8_t hour;   // Hora
    uint8_t minute; // Minuto
    uint8_t second; // Segundo
} Time;

extern uint8_t data_tx[8];
extern uint8_t data_rx[2];

// #define DS3231_ADDRESS 0x68 //in datasheet
#define DS3231_ADDRESS 0xD0
#define DS3231_SEC 0x00
#define DS3231_MIN 0x01
#define DS3231_HOUR 0x02
#define DS3231_DAY 0x03
#define DS3231_DATE 0x04
#define DS3231_MONTH 0x05
#define DS3231_YEAR 0x06

void DS3231_Set_Date_Time(uint8_t dy, uint8_t mth, uint8_t yr, uint8_t dw, uint8_t hr, uint8_t mn, uint8_t sc);
void DS3231_Get_Date(uint8_t* day, uint8_t* mth, uint8_t* year, uint8_t* dow);
void DS3231_Get_Time(uint8_t* hr, uint8_t* min, uint8_t* sec);
uint8_t DS3231_Read(uint8_t reg);
uint8_t DS3231_Bin_Bcd(uint8_t binary_value);
uint8_t DS3231_Bcd_Bin(uint8_t bcd_value);

void DS3231_Get_DateTime(Time* time);