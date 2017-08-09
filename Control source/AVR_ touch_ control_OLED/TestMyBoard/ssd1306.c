/*
���������� ��� �������������
OLED LCD SSD1306 �������.
���������� ������� ��� CVAVR.
22.12.2015 ��������� �.�.
*/

#include <util/delay.h>
#include "ssd1306.h"
#include "TWI_SW_Master.h"

unsigned char LCD_X, LCD_Y, LCD_INVERSION;

unsigned char GlobalTemp = 0;
unsigned char GlobalChar = 0;

#if IMAGE_INCLUDE
FLASH_VAR(unsigned char image0[]) =
{	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0xC0, 0x40, 0x20, 0x30, 0x10,
	0x18, 0x08, 0x88, 0x4C, 0x04, 0x04, 0x04, 0x06,
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x02, 0x06, 0x04, 0x04, 0x04, 0x0C, 0x88,
	0x08, 0x18, 0x10, 0x20, 0x60, 0x40, 0xC0, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xC0, 0x60, 0x18, 0x08, 0x04,
	0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0,
	0x1C, 0x03, 0xC1, 0x3C, 0x46, 0xA2, 0x70, 0x18,
	0x00, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xE0, 0xE0,
	0xC0, 0x80, 0x08, 0x30, 0xE2, 0x06, 0x0C, 0xF0,
	0x03, 0x0E, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x01,
	0x01, 0x02, 0x04, 0x18, 0x30, 0x60, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
	0x70, 0x0C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
	0x70, 0x80, 0x0F, 0x30, 0xD0, 0x87, 0x18, 0x20,
	0x00, 0x07, 0x0F, 0xDF, 0xFF, 0xFF, 0xFF, 0x1F,
	0x1F, 0x03, 0x60, 0x30, 0x0F, 0x80, 0x60, 0x1F,
	0x84, 0xC0, 0x3F, 0x0B, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03,
	0x1C, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x0F,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x80,
	0xE0, 0xF1, 0x73, 0x34, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0xF8, 0xFF, 0xFF, 0x9F, 0xFF, 0xFE,
	0xC2, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0xF6,
	0xF1, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xF0,
	0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0xF0, 0xF8, 0xBD, 0x0F, 0x07,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xC0, 0xFF, 0xFF, 0x8F, 0x88, 0x88, 0x8B, 0xFF,
	0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
	0xFF, 0x60, 0x60, 0xE0, 0xE0, 0xE0, 0x70, 0x3F,
	0x3F, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xF8, 0x0F, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x0E, 0x38, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0x00, 0x01, 0x07, 0x0F, 0x1E,
	0x3C, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0xF8,
	0xFF, 0xFF, 0x8B, 0x88, 0x88, 0x88, 0x88, 0x88,
	0x9F, 0xFF, 0xFE, 0xC0, 0x00, 0x00, 0x00, 0x7F,
	0x7F, 0x00, 0x00, 0x00, 0x03, 0x07, 0x1F, 0x7C,
	0x78, 0x60, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0,
	0x38, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0x06, 0x0C, 0x18, 0x20,
	0x40, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF,
	0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x09, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x01, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x01, 0x02, 0x06, 0x04, 0x08,
	0x08, 0x18, 0x10, 0x10, 0x20, 0x20, 0x21, 0x20,
	0x20, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
	0x60, 0x20, 0x20, 0x21, 0x21, 0x30, 0x10, 0x10,
	0x18, 0x08, 0x0C, 0x04, 0x06, 0x02, 0x01, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#endif

FLASH_VAR(unsigned char LCD_Buffer[]) =
{
/*0x00, 0x00, 0x00, 0x00, 0x00,// 00
0x00, 0x00, 0x5F, 0x00, 0x00,// 01
0x00, 0x07, 0x00, 0x07, 0x00,// 02
0x14, 0x7F, 0x14, 0x7F, 0x14,// 03
0x24, 0x2A, 0x7F, 0x2A, 0x12,// 04
0x23, 0x13, 0x08, 0x64, 0x62,// 05
0x36, 0x49, 0x55, 0x22, 0x50,// 06
0x00, 0x05, 0x03, 0x00, 0x00,// 07
0x00, 0x1C, 0x22, 0x41, 0x00,// 08
0x00, 0x41, 0x22, 0x1C, 0x00,// 09
0x14, 0x08, 0x3E, 0x08, 0x14,// 0A
0x08, 0x08, 0x3E, 0x08, 0x08,// 0B
0x00, 0x50, 0x30, 0x00, 0x00,// 0C
0x08, 0x08, 0x08, 0x08, 0x08,// 0D
0x00, 0x60, 0x60, 0x00, 0x00,// 0E
0x20, 0x10, 0x08, 0x04, 0x02,// 0F
0x00, 0x00, 0x00, 0x00, 0x00,// 10
0x00, 0x00, 0x5F, 0x00, 0x00,// 11
0x00, 0x07, 0x00, 0x07, 0x00,// 12
0x14, 0x7F, 0x14, 0x7F, 0x14,// 13
0x24, 0x2A, 0x7F, 0x2A, 0x12,// 14
0x23, 0x13, 0x08, 0x64, 0x62,// 15
0x36, 0x49, 0x55, 0x22, 0x50,// 16
0x00, 0x05, 0x03, 0x00, 0x00,// 17
0x00, 0x1C, 0x22, 0x41, 0x00,// 18
0x00, 0x41, 0x22, 0x1C, 0x00,// 19
0x14, 0x08, 0x3E, 0x08, 0x14,// 1A
0x08, 0x08, 0x3E, 0x08, 0x08,// 1B
0x00, 0x50, 0x30, 0x00, 0x00,// 1C
0x08, 0x08, 0x08, 0x08, 0x08,// 1D
0x00, 0x60, 0x60, 0x00, 0x00,// 1E
0x20, 0x10, 0x08, 0x04, 0x02,// 1F*/
0x00, 0x00, 0x00, 0x00, 0x00,// 20 space
0x00, 0x00, 0x5F, 0x00, 0x00,// 21 !
0x00, 0x07, 0x00, 0x07, 0x00,// 22 "
0x14, 0x7F, 0x14, 0x7F, 0x14,// 23 #
0x24, 0x2A, 0x7F, 0x2A, 0x12,// 24 $
0x23, 0x13, 0x08, 0x64, 0x62,// 25 %
0x36, 0x49, 0x55, 0x22, 0x50,// 26 &
0x00, 0x05, 0x03, 0x00, 0x00,// 27 '
0x00, 0x1C, 0x22, 0x41, 0x00,// 28 (
0x00, 0x41, 0x22, 0x1C, 0x00,// 29 )
0x14, 0x08, 0x3E, 0x08, 0x14,// 2a *
0x08, 0x08, 0x3E, 0x08, 0x08,// 2b +
0x00, 0x50, 0x30, 0x00, 0x00,// 2c ,
0x08, 0x08, 0x08, 0x08, 0x08,// 2d -
0x00, 0x60, 0x60, 0x00, 0x00,// 2e .
0x20, 0x10, 0x08, 0x04, 0x02,// 2f /
0x3E, 0x51, 0x49, 0x45, 0x3E,// 30 0
0x00, 0x42, 0x7F, 0x40, 0x00,// 31 1
0x42, 0x61, 0x51, 0x49, 0x46,// 32 2
0x21, 0x41, 0x45, 0x4B, 0x31,// 33 3
0x18, 0x14, 0x12, 0x7F, 0x10,// 34 4
0x27, 0x45, 0x45, 0x45, 0x39,// 35 5
0x3C, 0x4A, 0x49, 0x49, 0x30,// 36 6
0x01, 0x71, 0x09, 0x05, 0x03,// 37 7
0x36, 0x49, 0x49, 0x49, 0x36,// 38 8
0x06, 0x49, 0x49, 0x29, 0x1E,// 39 9
0x00, 0x36, 0x36, 0x00, 0x00,// 3a :
0x00, 0x56, 0x36, 0x00, 0x00,// 3b ;
0x08, 0x14, 0x22, 0x41, 0x00,// 3c <
0x14, 0x14, 0x14, 0x14, 0x14,// 3d =
0x00, 0x41, 0x22, 0x14, 0x08,// 3e >
0x02, 0x01, 0x51, 0x09, 0x06,// 3f ?
0x32, 0x49, 0x79, 0x41, 0x3E,// 40 @
0x7E, 0x11, 0x11, 0x11, 0x7E,// 41 A
0x7F, 0x49, 0x49, 0x49, 0x36,// 42 B
0x3E, 0x41, 0x41, 0x41, 0x22,// 43 C
0x7F, 0x41, 0x41, 0x22, 0x1C,// 44 D
0x7F, 0x49, 0x49, 0x49, 0x41,// 45 E
0x7F, 0x09, 0x09, 0x09, 0x01,// 46 F
0x3E, 0x41, 0x49, 0x49, 0x7A,// 47 G
0x7F, 0x08, 0x08, 0x08, 0x7F,// 48 H
0x00, 0x41, 0x7F, 0x41, 0x00,// 49 I
0x20, 0x40, 0x41, 0x3F, 0x01,// 4a J
0x7F, 0x08, 0x14, 0x22, 0x41,// 4b K
0x7F, 0x40, 0x40, 0x40, 0x40,// 4c L
0x7F, 0x02, 0x0C, 0x02, 0x7F,// 4d M
0x7F, 0x04, 0x08, 0x10, 0x7F,// 4e N
0x3E, 0x41, 0x41, 0x41, 0x3E,// 4f O
0x7F, 0x09, 0x09, 0x09, 0x06,// 50 P
0x3E, 0x41, 0x51, 0x21, 0x5E,// 51 Q
0x7F, 0x09, 0x19, 0x29, 0x46,// 52 R
0x46, 0x49, 0x49, 0x49, 0x31,// 53 S
0x01, 0x01, 0x7F, 0x01, 0x01,// 54 T
0x3F, 0x40, 0x40, 0x40, 0x3F,// 55 U
0x1F, 0x20, 0x40, 0x20, 0x1F,// 56 V
0x3F, 0x40, 0x38, 0x40, 0x3F,// 57 W
0x63, 0x14, 0x08, 0x14, 0x63,// 58 X
0x07, 0x08, 0x70, 0x08, 0x07,// 59 Y
0x61, 0x51, 0x49, 0x45, 0x43,// 5a Z
0x00, 0x7F, 0x41, 0x41, 0x00,// 5b [
0x02, 0x04, 0x08, 0x10, 0x20,// 5c Yen Currency Sign
0x00, 0x41, 0x41, 0x7F, 0x00,// 5d ]
0x04, 0x02, 0x01, 0x02, 0x04,// 5e ^
0x40, 0x40, 0x40, 0x40, 0x40,// 5f _
0x00, 0x01, 0x02, 0x04, 0x00,// 60 `
0x20, 0x54, 0x54, 0x54, 0x78,// 61 a
0x7F, 0x48, 0x44, 0x44, 0x38,// 62 b
0x38, 0x44, 0x44, 0x44, 0x20,// 63 c
0x38, 0x44, 0x44, 0x48, 0x7F,// 64 d
0x38, 0x54, 0x54, 0x54, 0x18,// 65 e
0x08, 0x7E, 0x09, 0x01, 0x02,// 66 f
0x0C, 0x52, 0x52, 0x52, 0x3E,// 67 g
0x7F, 0x08, 0x04, 0x04, 0x78,// 68 h
0x00, 0x44, 0x7D, 0x40, 0x00,// 69 i
0x20, 0x40, 0x44, 0x3D, 0x00,// 6a j
0x7F, 0x10, 0x28, 0x44, 0x00,// 6b k
0x00, 0x41, 0x7F, 0x40, 0x00,// 6c l
0x7C, 0x04, 0x18, 0x04, 0x78,// 6d m
0x7C, 0x08, 0x04, 0x04, 0x78,// 6e n
0x38, 0x44, 0x44, 0x44, 0x38,// 6f o
0x7C, 0x14, 0x14, 0x14, 0x08,// 70 p
0x08, 0x14, 0x14, 0x18, 0x7C,// 71 q
0x7C, 0x08, 0x04, 0x04, 0x08,// 72 r
0x08, 0x54, 0x54, 0x54, 0x20,// 73 s
0x04, 0x3F, 0x44, 0x40, 0x20,// 74 t
0x3C, 0x40, 0x40, 0x20, 0x7C,// 75 u
0x1C, 0x20, 0x40, 0x20, 0x1C,// 76 v
0x3C, 0x40, 0x30, 0x40, 0x3C,// 77 w
0x44, 0x28, 0x10, 0x28, 0x44,// 78 x
0x0C, 0x50, 0x50, 0x50, 0x3C,// 79 y
0x44, 0x64, 0x54, 0x4C, 0x44,// 7a z
0x00, 0x08, 0x36, 0x41, 0x00,// 7b <
0x00, 0x00, 0x7F, 0x00, 0x00,// 7c |
0x00, 0x41, 0x36, 0x08, 0x00,// 7d >
0x10, 0x08, 0x08, 0x10, 0x08,// 7e Right Arrow ->
0x78, 0x46, 0x41, 0x46, 0x78,// 7f Left Arrow <-
0x00, 0x00, 0x00, 0x00, 0x00,// 80
0x00, 0x00, 0x5F, 0x00, 0x00,// 81
0x00, 0x07, 0x00, 0x07, 0x00,// 82
0x14, 0x7F, 0x14, 0x7F, 0x14,// 83
0x24, 0x2A, 0x7F, 0x2A, 0x12,// 84
0x23, 0x13, 0x08, 0x64, 0x62,// 85
0x36, 0x49, 0x55, 0x22, 0x50,// 86
0x00, 0x05, 0x03, 0x00, 0x00,// 87
0x00, 0x1C, 0x22, 0x41, 0x00,// 88
0x00, 0x41, 0x22, 0x1C, 0x00,// 89
0x14, 0x08, 0x3E, 0x08, 0x14,// 8A
0x08, 0x08, 0x3E, 0x08, 0x08,// 8B
0x00, 0x50, 0x30, 0x00, 0x00,// 8C
0x08, 0x08, 0x08, 0x08, 0x08,// 8D
0x00, 0x60, 0x60, 0x00, 0x00,// 8E
0x20, 0x10, 0x08, 0x04, 0x02,// 8F
0x00, 0x00, 0x00, 0x00, 0x00,// 90
0x00, 0x00, 0x5F, 0x00, 0x00,// 91
0x00, 0x07, 0x00, 0x07, 0x00,// 92
0x14, 0x7F, 0x14, 0x7F, 0x14,// 93
0x24, 0x2A, 0x7F, 0x2A, 0x12,// 94
0x23, 0x13, 0x08, 0x64, 0x62,// 95
0x36, 0x49, 0x55, 0x22, 0x50,// 96
0x00, 0x05, 0x03, 0x00, 0x00,// 97
0x00, 0x1C, 0x22, 0x41, 0x00,// 98
0x00, 0x41, 0x22, 0x1C, 0x00,// 99
0x14, 0x08, 0x3E, 0x08, 0x14,// 9A
0x08, 0x08, 0x3E, 0x08, 0x08,// 9B
0x00, 0x50, 0x30, 0x00, 0x00,// 9C
0x08, 0x08, 0x08, 0x08, 0x08,// 9D
0x00, 0x60, 0x60, 0x00, 0x00,// 9E
0x20, 0x10, 0x08, 0x04, 0x02,// 9F
0x00, 0x00, 0x00, 0x00, 0x00,// A0
0x00, 0x00, 0x5F, 0x00, 0x00,// A1
0x00, 0x07, 0x00, 0x07, 0x00,// A2
0x14, 0x7F, 0x14, 0x7F, 0x14,// A3
0x24, 0x2A, 0x7F, 0x2A, 0x12,// A4
0x23, 0x13, 0x08, 0x64, 0x62,// A5
0x36, 0x49, 0x55, 0x22, 0x50,// A6
0x00, 0x05, 0x03, 0x00, 0x00,// A7
0x7E, 0x4B, 0x4A, 0x4B, 0x42,// A8			// OLD 0x00, 0x1C, 0x22, 0x41, 0x00,// A8
0x00, 0x41, 0x22, 0x1C, 0x00,// A9
0x14, 0x08, 0x3E, 0x08, 0x14,// AA
0x08, 0x08, 0x3E, 0x08, 0x08,// AB
0x00, 0x50, 0x30, 0x00, 0x00,// AC
0x08, 0x08, 0x08, 0x08, 0x08,// AD
0x00, 0x60, 0x60, 0x00, 0x00,// AE
0x20, 0x10, 0x08, 0x04, 0x02,// AF
// 0x3E, 0x51, 0x49, 0x45, 0x3E,// B0
0x00, 0x06, 0x09, 0x09, 0x06,
0x00, 0x42, 0x7F, 0x40, 0x00,// B1
0x42, 0x61, 0x51, 0x49, 0x46,// B2
0x21, 0x41, 0x45, 0x4B, 0x31,// B3
0x18, 0x14, 0x12, 0x7F, 0x10,// B4
0x27, 0x45, 0x45, 0x45, 0x39,// B5
0x3C, 0x4A, 0x49, 0x49, 0x30,// B6
0x01, 0x71, 0x09, 0x05, 0x03,// B7
0x38, 0x56, 0x54, 0x56, 0x18,// B8 �
0x06, 0x49, 0x49, 0x29, 0x1E,// B9
0x00, 0x36, 0x36, 0x00, 0x00,// BA
0x00, 0x56, 0x36, 0x00, 0x00,// BB
0x08, 0x14, 0x22, 0x41, 0x00,// BC
0x14, 0x14, 0x14, 0x14, 0x14,// BD
0x00, 0x41, 0x22, 0x14, 0x08,// BE
0x02, 0x01, 0x51, 0x09, 0x06,// BF
0x7E, 0x11, 0x11, 0x11, 0x7E,// C0 �	CP-1251 table
0x7F, 0x49, 0x49, 0x49, 0x31,// C1 �
0x7F, 0x49, 0x49, 0x49, 0x36,// C2 �
0x7F, 0x01, 0x01, 0x01, 0x03,// C3 �
0x60, 0x3E, 0x21, 0x21, 0x7F,// C4 �
0x7F, 0x49, 0x49, 0x49, 0x41,// C5 �
0x77, 0x08, 0x7F, 0x08, 0x77,// C6 �
0x22, 0x41, 0x49, 0x49, 0x36,// C7 �
0x7F, 0x10, 0x08, 0x04, 0x7F,// C8 �
0x7F, 0x10, 0x09, 0x04, 0x7F,// C9 �
0x7F, 0x08, 0x14, 0x22, 0x41,// CA �
0x40, 0x3E, 0x01, 0x01, 0x7F,// CB �
0x7F, 0x02, 0x0C, 0x02, 0x7F,// CC �
0x7F, 0x08, 0x08, 0x08, 0x7F,// CD �
0x3E, 0x41, 0x41, 0x41, 0x3E,// CE �
0x7F, 0x01, 0x01, 0x01, 0x7F,// CF �
0x7F, 0x09, 0x09, 0x09, 0x06,// D0 �
0x3E, 0x41, 0x41, 0x41, 0x22,// D1 �
0x01, 0x01, 0x7F, 0x01, 0x01,// D2 �
0x27, 0x48, 0x48, 0x48, 0x3F,// D3 �
0x1E, 0x21, 0x7F, 0x21, 0x1E,// D4 �
0x63, 0x14, 0x08, 0x14, 0x63,// D5 �
0x3F, 0x20, 0x20, 0x3F, 0x60,// D6 �
0x07, 0x08, 0x08, 0x08, 0x7F,// D7 �
0x7F, 0x40, 0x7F, 0x40, 0x7F,// D8 �
0x3F, 0x20, 0x3F, 0x20, 0x7F,// D9 �
0x01, 0x7F, 0x48, 0x48, 0x30,// DA �
0x7F, 0x48, 0x30, 0x00, 0x7F,// DB �
0x00, 0x7F, 0x48, 0x48, 0x30,// DC �
0x22, 0x41, 0x49, 0x49, 0x3E,// DD �
0x7F, 0x08, 0x3E, 0x41, 0x3E,// DE �
0x46, 0x29, 0x19, 0x09, 0x7F,// DF �
0x20, 0x54, 0x54, 0x54, 0x78,// E0 �
0x3C, 0x4A, 0x4A, 0x4A, 0x30,// E1 �
0x7C, 0x54, 0x54, 0x28, 0x00,// E2 �
0x7C, 0x04, 0x04, 0x04, 0x04,// E3 �
0x60, 0x38, 0x24, 0x24, 0x7C,// E4 �
0x38, 0x54, 0x54, 0x54, 0x18,// E5 �
0x6C, 0x10, 0x7C, 0x10, 0x6C,// E6 �
0x00, 0x44, 0x54, 0x54, 0x28,// E7 �
0x7C, 0x20, 0x10, 0x08, 0x7C,// E8 �
0x7C, 0x21, 0x12, 0x09, 0x7C,// E9 �
0x7C, 0x10, 0x28, 0x44, 0x00,// EA �
0x40, 0x38, 0x04, 0x04, 0x7C,// EB �
0x7C, 0x08, 0x10, 0x08, 0x7C,// EC �
0x7C, 0x10, 0x10, 0x10, 0x7C,// ED �
0x38, 0x44, 0x44, 0x44, 0x38,// EE �
0x7C, 0x04, 0x04, 0x04, 0x7C,// EF �
0x7C, 0x14, 0x14, 0x14, 0x08,// F0 �
0x38, 0x44, 0x44, 0x44, 0x00,// F1 �
0x04, 0x04, 0x7C, 0x04, 0x04,// F2 �
0x0C, 0x50, 0x50, 0x50, 0x3C,// F3 �
0x08, 0x14, 0x7C, 0x14, 0x08,// F4 �
0x44, 0x28, 0x10, 0x28, 0x44,// F5 �
0x3C, 0x20, 0x20, 0x3C, 0x60,// F6 �
0x0C, 0x10, 0x10, 0x10, 0x7C,// F7 �
0x7C, 0x40, 0x7C, 0x40, 0x7C,// F8 �
0x3C, 0x20, 0x3C, 0x20, 0x7C,// F9 �
0x04, 0x7C, 0x50, 0x50, 0x20,// FA �
0x7C, 0x50, 0x20, 0x00, 0x7C,// FB �
0x00, 0x7C, 0x50, 0x50, 0x20,// FC �
0x28, 0x44, 0x54, 0x54, 0x38,// FD �
0x7C, 0x10, 0x38, 0x44, 0x38,// FE �
0x48, 0x54, 0x34, 0x14, 0x7C // FF �
};

FLASH_VAR(unsigned char BigNum[15][96]) =
{ //0
{0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x00},
 //1
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0,
0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 //2
{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xC1, 0xC0, 0xC0, 0xC0,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
0x03, 0x03, 0x83, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},
   //3
{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xC1, 0xC0, 0xC0, 0xC0,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x81, 0x83, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x87,
0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},
  //4
{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},
  //5
{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0x81, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x81, 0x83, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x87,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},
 //6
{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0x81, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x87,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},
  //7
{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},
  //8
{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xE1,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0x87, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x87,
0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},
    //9
{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},
  //:    10
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x7E, 0x7E, 0x7E, 0x7E, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  // .   11
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 //space   12
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 //�������    13
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x11, 0x11, 0x11, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

};

void LCD_init(void)
{
	TWI_SW_Init();

	LCD_Sleep(0);
	_delay_ms(10);
	LCD_Commmand(COMAND, SSD1306_SETDISPLAYCLOCKDIV);
	LCD_Commmand(COMAND, 0x80);
	LCD_Commmand(COMAND, SSD1306_SETMULTIPLEX);
	LCD_Commmand(COMAND, 0x3F);
	LCD_Commmand(COMAND, SSD1306_SETDISPLAYOFFSET);
	LCD_Commmand(COMAND, 0x00);
	LCD_Commmand(COMAND, SSD1306_SETSTARTLINE | 0x00);
	// We use internal charge pump
	LCD_Commmand(COMAND, SSD1306_CHARGEPUMP);
	LCD_Commmand(COMAND, 0x14);

	// Horizontal memory mode
	LCD_Commmand(COMAND, SSD1306_SEGREMAP | 0x00);
	LCD_Commmand(COMAND, SSD1306_COMSCANINC);

	// LCD_Commmand(COMAND, SSD1306_SEGREMAP | 0x01);
	// LCD_Commmand(COMAND, SSD1306_COMSCANDEC);

	LCD_Commmand(COMAND, SSD1306_SETCOMPINS);
	LCD_Commmand(COMAND, 0x12);

	LCD_Commmand(COMAND, SSD1306_MEMORYMODE);
	LCD_Commmand(COMAND, SSD1306_HORIZONTAL_ADDRESSING);
	// Max contrast
	LCD_Commmand(COMAND, SSD1306_SETCONTRAST);
	LCD_Commmand(COMAND, 0x80);

	LCD_Commmand(COMAND, SSD1306_SETPRECHARGE);
	LCD_Commmand(COMAND, 0xF1);

	LCD_Commmand(COMAND, SSD1306_SETVCOMDETECT);
	LCD_Commmand(COMAND, 0x40);

	LCD_Commmand(COMAND, SSD1306_DISPLAYALLON_RESUME);
	// Non-inverted display
	LCD_Mode(0);
	// Turn display back on
	LCD_Sleep(1);

	LCD_Clear();
	LCD_Goto(0,0);

	_delay_ms(120);
}

void LCD_Contrast(char set_contrast)
{
  LCD_Commmand(COMAND, SSD1306_DISPLAYOFF);
  _delay_ms(10);
  LCD_Commmand(COMAND, SSD1306_SETCONTRAST);
  LCD_Commmand(COMAND, set_contrast);
  LCD_Commmand(COMAND, SSD1306_DISPLAYON);
}

void LCD_Mode(unsigned char set_mode)
{
 if(set_mode==0){ LCD_Commmand(COMAND, SSD1306_NORMALDISPLAY); }
 if(set_mode==1){ LCD_Commmand(COMAND, SSD1306_INVERTDISPLAY); }
}

void LCD_Sleep(char set)
{
  if(set==0){LCD_Commmand(COMAND,SSD1306_DISPLAYOFF);}
  if(set==1){LCD_Commmand(COMAND,SSD1306_DISPLAYON);}
}

void LCD_Commmand(unsigned char ControByte, unsigned char DataByte)
{
	TWI_SW_Start();
	TWI_SW_Write(SSD1306_ADDRESS);
	TWI_SW_Write(ControByte);
	TWI_SW_Write(DataByte);
	TWI_SW_Stop();
}

void LCD_Goto(unsigned char x, unsigned char y)
{
	LCD_X = x;
	LCD_Y = y;

	// ���������  � ���������
	LCD_Commmand(COMAND, 0xB0 + y);			//���������� ����� ������ ���������
	LCD_Commmand(COMAND, x & 0xf);			//���������� ������ ����� �������
	LCD_Commmand(COMAND,0x10 | (x >> 4));	//���������� ������� ����� �������
}

void LCD_Goto2X(unsigned char x, unsigned char y)
{
	LCD_X = x;
	LCD_Y = y;

	// ���������  � ���������
	LCD_Commmand(COMAND, 0xB0 + y);				//���������� ����� ������ ���������
	LCD_Commmand(COMAND, 2*x & 0xf);			//���������� ������ ����� �������
	LCD_Commmand(COMAND, 0x10 | (2*x >> 4));	//���������� ������� ����� �������
}

void LCD_Clear(void)
{
	unsigned short i;
	unsigned short x=0;
	unsigned short y=0;
	LCD_Goto(0, 0);

	for (i = 0; i < (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8); i++) //(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8)
	{
		LCD_Char(' ');
		x++;
		if(x > SSD1306_LCDWIDTH)
		{
			x = 0;
			y++;
			LCD_Goto(0, y);
		}
	}
	LCD_X = SSD1306_DEFAULT_SPACE;
	LCD_Y = 0;
}

void LCD_PageClear(uint8_t page)
{
	for (uint8_t i = 0; i < 128; i++)
	{
		LCD_Goto(i, page);
		LCD_Commmand(DATA, 0x00);	
	}
}

void LCD_Char(unsigned int c)
{
	unsigned char x = 0;
	GlobalTemp = c;
	TWI_SW_Start();
	TWI_SW_Write(SSD1306_ADDRESS);
	TWI_SW_Write(DATA);//data mode
	for (x = 0; x < 5; x++) {
		if (LCD_INVERSION)
		{
			//TWI_SW_Write(~read_byte_flash(LCD_Buffer[c * 5 + x]));
			TWI_SW_Write(~read_byte_flash(LCD_Buffer[(c - 0x20) * 5 + x]));
		}
		else
		{
			//TWI_SW_Write(read_byte_flash(LCD_Buffer[c * 5 + x]));
			TWI_SW_Write(read_byte_flash(LCD_Buffer[(c - 0x20) * 5 + x]));
		}
	}
	if (LCD_INVERSION) TWI_SW_Write(0xFF);
	else TWI_SW_Write(0x00);
	//TWI_SW_Write(0x00);  //������ � ���� ����� ����� ���������
	TWI_SW_Stop();    // stop transmitting

	LCD_X += SSD1306_DEFAULT_SPACE;//8;
	if(LCD_X > SSD1306_LCDWIDTH) {
		LCD_X = SSD1306_DEFAULT_SPACE;
	}
}

void LCD_BigNum(unsigned char num)
{
  unsigned char x = 0;
  unsigned char z = 0;

  unsigned char y_s = LCD_Y;

	if(num!=46&&num!=32&&num!=32&&num!=67) {
		num = num - 48; }
	else {
		if(num == 46) { num = 11; }  // .
		if(num == 32) { num = 12; }  //space
		if(num == 67) { num = 13; }  //�������
	}

  TWI_SW_Start();
  TWI_SW_Write(SSD1306_ADDRESS);
  TWI_SW_Write(DATA);//data mode
  for (x = 0; x < 96; x++)
	{
	  TWI_SW_Write(read_byte_flash(BigNum[num][x]));
     if(z>=23)
     {
    	 TWI_SW_Stop();			// stop transmitting
       LCD_Goto(LCD_X,LCD_Y+1);

       z=0;
       TWI_SW_Start();
       TWI_SW_Write(SSD1306_ADDRESS);
       TWI_SW_Write(DATA);		//data mode
     }else{z++;}

     }
  TWI_SW_Stop();				// stop transmitting

	LCD_X += 23;
    LCD_Goto(LCD_X,y_s);
    if(LCD_X>SSD1306_LCDWIDTH)
	{
		LCD_X = SSD1306_DEFAULT_SPACE;
	}
}

void LCD_CharBig(unsigned int c)
{
	unsigned char x = 0;
	unsigned int m = 0;

	TWI_SW_Start();
	TWI_SW_Write(SSD1306_ADDRESS);
	TWI_SW_Write(DATA);					//data mode
	for (x = 0; x < 5; x++) {
		m = read_byte_flash(LCD_Buffer[c * 5 + x]);
		TWI_SW_Write(m);
		TWI_SW_Write(m);
	}
	TWI_SW_Write(0x00);  				//������ � ���� ����� ����� ���������
	TWI_SW_Stop();    					// stop transmitting
	LCD_X += 11;
	if(LCD_X > SSD1306_LCDWIDTH) {
		LCD_X = SSD1306_DEFAULT_SPACE;
	}
}

void LCD_Printf(char* buf, unsigned char size, unsigned char inversion) //������� ������ �� ������
{
	LCD_INVERSION = inversion;
	while (*buf != 0) {

		if(size == 0) {
			if((LCD_X > SSD1306_LCDWIDTH) || (LCD_X < 5)) {
				LCD_X = SSD1306_DEFAULT_SPACE; }
			LCD_Char(*buf++);
		}
		/*if(size == 1) {
			if((LCD_X > SSD1306_LCDWIDTH) || (LCD_X < 5)) {
			   LCD_X = SSD1306_DEFAULT_SPACE; }
			LCD_CharBig(*buf++);
		}*/
		if(size == 2) {
			if((LCD_X > SSD1306_LCDWIDTH) || (LCD_X < 24)) {
			   LCD_X = SSD1306_DEFAULT_SPACE; }
			   LCD_BigNum(*buf++);
		}
	}
}

#if IMAGE_INCLUDE
void LCD_DrawImage(unsigned char num_image)
{
	unsigned int i;
	unsigned char x=0;
	unsigned char y=0;
	LCD_Goto(0, 0);

	for (i = 0; i < (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8); i++) {
		if(num_image==0) {
			LCD_Commmand(DATA, read_byte_flash(image0[i]));
		}

		x++;
		if(x >= SSD1306_LCDWIDTH) {
			x = 0;
			y++;
			LCD_Goto(0, y);
		}
	}
}
#endif

void LCD_Volume(unsigned char val)
{
	static uint8_t lastValue = 0;
	if (val > 127) val = 127;

	if (val > lastValue)
	{	
		for (int i = lastValue; i < val; i++)
		{
			LCD_Goto(i, 7);
			LCD_Commmand(DATA, 0xFF);
		}
	} 
	if (val < lastValue)
	{
		for (int i = lastValue; i > val; i--)
		{
			LCD_Goto(i, 7);
			LCD_Commmand(DATA, 0x00);
		}
	}
	lastValue = val;
}

