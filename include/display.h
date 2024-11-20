#pragma once

#include "rtc.h"
#include "spi_config.h"
#include <libopencm3/stm32/gpio.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief number used in char encoder loops
 */
#define num 4
/**
 * @brief Reads a specific bit from a value.
 *
 * This macro reads the bit at the specified position from the given value.
 *
 * @param value The value from which to read the bit.
 * @param bit The position of the bit to read.
 * @return The value of the bit (0 or 1).
 */
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

/**
 * @brief Sets a specific bit in a value.
 *
 * This macro sets the bit at the specified position in the given value.
 *
 * @param value The value in which to set the bit.
 * @param bit The position of the bit to set.
 */
#define bitSet(value, bit) ((value) |= (1UL << (bit)))

/**
 * @brief Clears a specific bit in a value.
 *
 * This macro clears the bit at the specified position in the given value.
 *
 * @param value The value in which to clear the bit.
 * @param bit The position of the bit to clear.
 */
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))

/**
 * @brief Writes a specific bit in a value.
 *
 * This macro writes the specified bit value at the specified position in the given value.
 *
 * @param value The value in which to write the bit.
 * @param bit The position of the bit to write.
 * @param bitvalue The value to write to the bit (0 or 1).
 */
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
/**
 * @brief Size for row buffer
 */
#define ROW_BUFFER_SIZE 80
/**
 * @brief Character array
 * Contains so many characters, numbers and symbols in 7x6 format to write with MAX7219
 */
extern uint8_t CH[];

/**
 * @brief Number 6x3 array
 * Contains 6x3 format number (0-9) was desinged to represent two digits in one 8x8 matrix
 * on a 8x32 display
 */
extern uint8_t NUMS[];

/**
 * @brief Buffer used to storage Time struct data to write this in display
 */
extern char display_global_buffer[];
/**
 * @brief Buffer for char enconder functions
 */
extern uint8_t buffer[];
/**
 * @brief Buffer for char enconder functions
 */
extern uint8_t buffer_row[];

/**
 * @brief direction struct for scroll text functions
 */
typedef enum
{
    LEFT,
    RIGHT
} dir_mx;

/**
 * @brief Sets the state of a specific LED.
 *
 * This function sets the state of a specific LED in the matrix.
 *
 * @param col The column of the LED.
 * @param row The row of the LED.
 * @param value The state of the LED (0 for off, 1 for on).
 */
void MAX7219_Set_Led(uint8_t col, uint8_t row, uint8_t value);

/**
 * @brief Sets the value of a specific row.
 *
 * This function sets the value of a specific row in the matrix.
 *
 * @param row The row to set.
 * @param value The value to set the row to.
 */
void MAX7219_Set_Row(uint8_t row, uint8_t value);

/**
 * @brief Writes a character to the display.
 *
 * This function writes a character to the display.
 *
 * @param c The character to write.
 * @param max The maximum number of characters to write.
 */
void MAX7219_Write_Char(char c, uint8_t max);

/**
 * @brief Creates a custom character.
 *
 * This function creates a custom character in the display.
 *
 * @param nc The new character to create.
 * @param max The maximum number of characters to create.
 */
void MAX7219_Create_Char(char* nc, uint8_t max);

/**
 * @brief Scrolls a character across the display.
 *
 * This function scrolls a character across the display at a specified speed and direction.
 *
 * @param c The character to scroll.
 * @param speed The speed at which to scroll the character.
 * @param direction The direction to scroll the character.
 */
void MAX7219_Scroll_Char(char c, uint32_t speed, dir_mx direction);

/**
 * @brief Shifts a character across the display.
 *
 * This function shifts a character across the display at a specified speed and direction.
 *
 * @param c The character to shift.
 * @param speed The speed at which to shift the character.
 * @param direction The direction to shift the character.
 */
void MAX7219_Shift_Char(char c, uint32_t speed, dir_mx direction);

/**
 * @brief Scrolls a string across the display.
 *
 * This function scrolls a string across the display at a specified speed and direction.
 *
 * @param string The string to scroll.
 * @param speed The speed at which to scroll the string.
 * @param direction The direction to scroll the string.
 */
void MAX7219_Scroll_String(uint8_t* string, uint32_t speed, dir_mx direction);

/**
 * @brief Scrolls a new custom character across the display.
 *
 * This function scrolls a new custom character across the display at a specified speed and direction.
 *
 * @param nc The new character to scroll.
 * @param speed The speed at which to scroll the character.
 * @param direction The direction to scroll the character.
 */
void MAX7219_Scroll_NewChar(char* nc, uint32_t speed, dir_mx direction);

/**
 * @brief Shifts a new custom character across the display.
 *
 * This function shifts a new custom character across the display at a specified speed and direction.
 *
 * @param nc The new character to shift.
 * @param speed The speed at which to shift the character.
 * @param direction The direction to shift the character.
 */
void MAX7219_Shift_NewChar(char* nc, uint32_t speed, dir_mx direction);

/**
 * @brief Initializes the MAX7219 display.
 *
 * This function initializes the MAX7219 display with a specified brightness.
 *
 * @param brightness The brightness level (1 - 15).
 */
void MAX7219_Init(uint8_t brightness);

/**
 * @brief Shifts the display content to the left.
 *
 * This function shifts the display content to the left.
 */
void MAX7219_Shift_Left(void);

/**
 * @brief Shifts the display content to the right.
 *
 * This function shifts the display content to the right.
 */
void MAX7219_Shift_Right(void);

/**
 * @brief Writes a byte to the display.
 *
 * This function writes a byte to the display.
 *
 * @param byte The byte to write.
 */
void MAX7219_Write_Byte(uint8_t byte);

/**
 * @brief Writes a command to the MAX7219 display.
 *
 * This function writes a command to the MAX7219 display.
 *
 * @param address The address of the command.
 * @param cmd The command to write.
 */
void MAX7219_Write_Cmd(uint8_t address, uint8_t cmd);

/**
 * @brief Clears the display.
 *
 * This function clears the display.
 */
void MAX7219_Clear(void);

/**
 * @brief Writes a number to the display.
 *
 * This function writes a number to the display, specifying the tens and units.
 * Designed to represent two digits in one 8x8 matrix on a 8x32 matrix
 *
 * @param ten The tens digit.
 * @param unit The units digit.
 * @param max The maximum number of digits to write.
 */
void MAX7219_Write_Num(char ten, char unit, uint8_t max);

/**
 * @brief Writes the tens digit to the display.
 *
 * This function writes the tens digit to the display.
 * Designed to represent two digits in one 8x8 matrix on a 8x32 matrix
 * @param ten The tens digit.
 * @param max The maximum number of digits to write.
 */
void MAX7219_Write_Tens(char ten, uint8_t max);

/**
 * @brief Writes the units digit to the display.
 *
 * This function writes the units digit to the display.
 * Designed to represent two digits in one 8x8 matrix on a 8x32 matrix
 * @param unit The units digit.
 * @param max The maximum number of digits to write.
 */
void MAX7219_Write_Units(char unit, uint8_t max);

/**
 * @brief Writes a number to the display with a specified offset.
 *
 * This function writes a number to the display, specifying the tens digit, maximum digits, and an offset.
 * Designed to represent two digits in one 8x8 matrix on a 8x32 matrix
 * @param ten The tens digit.
 * @param max The maximum number of digits to write.
 * @param r The offset for the digits.
 */
void MAX7219_Write_N(char n, uint8_t max, uint8_t r);

/**
 * @brief Displays the current time on the display.
 *
 * This function displays the current time on the display.
 *
 * @param time A pointer to the Time structure containing the current time.
 */
void MAX7219_TIME(Time* time);
