#pragma once

#include <libopencm3/stm32/i2c.h>
#include <stdio.h>

/**
 * @brief DS3231_I2C_ADDRESS (from datasheet)
 */
#define DS3231_ADDRESS 0x68

/**
 * @brief DS3231 Second register (from datasheet)
 */
#define DS3231_SEC 0x00
/**
 * @brief DS3231 Minute register (from datasheet)
 */
#define DS3231_MIN 0x01
/**
 * @brief DS3231 Hour register (from datasheet)
 */
#define DS3231_HOUR 0x02
/**
 * @brief DS3231 Day register (from datasheet)
 */
#define DS3231_DAY 0x03
/**
 * @brief DS3231 Date register (from datasheet)
 */
#define DS3231_DATE 0x04
/**
 * @brief DS3231 Month register (from datasheet)
 */
#define DS3231_MONTH 0x05
/**
 * @brief DS3231 Year register (from datasheet)
 */
#define DS3231_YEAR 0x06

#define DS3231_A2_DATE 0x0D
#define DS3231_A2_HR 0x0C
#define DS3231_A2_MIN 0x0B

/**
 * @brief Structure to hold date and time information.
 */
typedef struct
{
    uint8_t day;    /**< Day of the month (1-31) */
    uint8_t month;  /**< Month of the year (1-12) */
    uint8_t year;   /**< Year (0-99) */
    uint8_t hour;   /**< Hour of the day (0-23) */
    uint8_t minute; /**< Minute of the hour (0-59) */
    uint8_t second; /**< Second of the minute (0-59) */
} Time;

/**
 * @brief Data to send array
 * This variable is an array where will be stored all the data to send to DS3231
 * It has 8 positions because the larger data to send are 8 bytes
 */
extern uint8_t data_tx[8];
/**
 * @brief Data to receive array
 * This variable is an array where will be stored all the received data to DS3231
 * It has 1 position because only one byte will be received per transfer
 */
extern uint8_t data_rx[1];

/**
 * @brief Function to configurate DS3231 with actual date and time
 * This function receives date and time and transfer it to module to corresponding register by i2c transfer
 * @param dy    day
 * @param mth   month
 * @param yr    year
 * @param dw    day of the week
 * @param hr    hour
 * @param mn    minute
 * @param sc    second
 *
 */
void DS3231_Set_Date_Time(uint8_t dy, uint8_t mth, uint8_t yr, uint8_t dw, uint8_t hr, uint8_t mn, uint8_t sc);

/**
 * @brief Get the Date values from DS3231 by i2c transfer and store it in the pointer taked as a parametter
 * @param day    day
 * @param mth    month
 * @param year   year
 * @param dow    day of the week
 */
void DS3231_Get_Date(uint8_t* day, uint8_t* mth, uint8_t* year, uint8_t* dow);
/**
 * @brief Get the Time values from DS3231 by i2c transfer and store it in the pointer taked as a parametter
 * @param hr    hour
 * @param min    minute
 * @param sec    second
 */
void DS3231_Get_Time(uint8_t* hr, uint8_t* min, uint8_t* sec);

/**
 * @brief Reads a speceifed register from DS3231 and returns its value
 * This function is used in other functions to more complex readings
 * @param reg register will be readed
 * @return the data from that register
 */
uint8_t DS3231_Read(uint8_t reg);

/**
 * @brief Converts a number from binary to Bcd
 * @param binary_value BIN number to be converted
 * @return BCD converted value
 */
uint8_t DS3231_Bin_Bcd(uint8_t binary_value);
/**
 * @brief Converts a number from Bcd to Binary
 * @param bcd_value Bcd number to be converted
 * @return Bin converted value
 */
uint8_t DS3231_Bcd_Bin(uint8_t bcd_value);
/**
 * @brief Reads the registers by i2c from DS3231 and storage all in time struct
 * @param time Time struct to storage Date and Time
 */
void DS3231_Get_DateTime(Time* time);

void DS3231_Set_Alarm2(uint8_t hr, uint8_t mn);
void DS323_write_command(uint8_t reg, uint8_t cmd);
uint8_t ds3231_read_register(uint8_t reg);
