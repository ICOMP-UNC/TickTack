#pragma once

#include "rtc.h"
#include "spi_config.h"
#include <libopencm3/stm32/gpio.h>
#include <stdbool.h>
#include <stdio.h>

#define num 4

typedef enum
{
    LEFT,
    RIGHT
} dir_mx;

extern uint8_t CH[];
extern uint8_t NUMS[];
extern char display_global_buffer[];

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

void MAX7219_Set_Led(uint8_t col, uint8_t row, uint8_t value);
void MAX7219_Set_Row(uint8_t row, uint8_t value);
void MAX7219_Write_Char(char c, uint8_t max);
void MAX7219_Create_Char(char* nc, uint8_t max);
void MAX7219_Scroll_Char(char c, uint32_t speed, dir_mx direction);
void MAX7219_Shift_Char(char c, uint32_t speed, dir_mx direction);
void MAX7219_Scroll_String(uint8_t* string, uint32_t speed, dir_mx direction);
void MAX7219_Scroll_NewChar(char* nc, uint32_t speed, dir_mx direction);
void MAX7219_Shift_NewChar(char* nc, uint32_t speed, dir_mx direction);
void MAX7219_Init(uint8_t brightness); // 1 - 15
void MAX7219_Shift_Left(void);
void MAX7219_Shift_Right(void);
void MAX7219_Write_Byte(uint8_t byte);
void MAX7219_Write_Cmd(uint8_t address, uint8_t cmd);
void MAX7219_Clear(void);
void MAX7219_Write_Num(char ten, char unit, uint8_t max);
void MAX7219_Write_Tens(char ten, uint8_t max);
void MAX7219_Write_Units(char unit, uint8_t max);
void MAX7219_Write_N(char ten, uint8_t max, uint8_t r);
void MAX7219_TIME(Time* time);
