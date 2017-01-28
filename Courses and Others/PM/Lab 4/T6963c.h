/*
	T6963c.h - Defines and Function prototypes

	Simple LowLevel T6963c Library without Drawing functions
	for Rect's, Circles, etc...
	The files should be self-explanatory.

	(c) Simon Kueppers. If you find a bug or if you have a 
	question, feel free to Email me:
	simon.kueppers@stlcd.de
*/

#ifndef T6963C_H
#define T6963C_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>

//Pinout
#define T6963C_PORT_DATA 				PORTC	//Dataport
#define	T6963C_DDR_DATA					DDRC
#define T6963C_PIN_DATA					PINC

#define T6963C_PORT_CTRL				PORTB	//Controlport (RW, RD, CD)
#define T6963C_DDR_CTRL					DDRB
#define T6963C_PIN_CTRL					PINB

#define T6963C_PORT_CTRL2				PORTA	//Controlport (CE, RST)
#define T6963C_DDR_CTRL2				DDRA
#define T6963C_PIN_CTRL2				PINA

#define T6963C_WR						PB2		//Controlbits
#define T6963C_RD						PB1
#define T6963C_CD						PB0
#define T6963C_CE						PA7
#define T6963C_RST						PA6

//Physical Description
#define T6963C_ADDR_CGRAML				0x1800	//Lower half of CG (Chars 00-7F)
#define T6963C_ADDR_CGRAMH				T6963C_ADDR_CGRAML + 0x80*8	//Higher half of CG (Chars 80-FF)
#define T6963C_ADDR_GRAPHIC				0x0400
#define T6963C_ADDR_TEXT				0x0000
#define T6963C_TEXT_COLS				30		//40 bytes for 6x8 Font, 30 for 8x8 Font
#define T6963C_TEXT_ROWS				16
#define T6963C_GRPH_COLS				T6963C_TEXT_COLS
#define T6963C_GRPH_ROWS				128
#define T6963C_FONTWIDTH				8

//Options Defines for Init()
#define T6963C_MODE_OR					0x00
#define T6963C_MODE_XOR					0x01
#define T6963C_MODE_AND					0x03
#define T6963C_MODE_TEXTATTR			0x04
#define T6963C_CG_INTERNALROM			0x00
#define T6963C_CG_EXTERNALRAM			0x04

//Mode Defines for Init()
#define T6963C_DISP_OFF					0x00
#define T6963C_CURSOR					0x02
#define T6963C_CURSOR_BLINK				0x03
#define T6963C_TEXT						0x04
#define T6963C_GRAPHIC					0x08
#define T6963C_TEXT_GRAPHIC				0x0C


//Sets Port & Initializes T6963c
void T6963cInit(uint8_t Options, uint8_t Mode);

//Set Cursor-Pattern
void T6963cCursorPattern(uint8_t Height);

//Locates Cursor at Text-Position
void T6963cSetCursorXY(uint8_t X, uint8_t Y);

//Clears Graphic and Text RAM
void T6963cClear(void);

//Sets Addresspointer for reading/writing from/to T6963c
void T6963cSetAddress(uint16_t Address);

//Writes a Single Byte and increments Address
void T6963cWrite(uint8_t Byte);

//Writes a Chunk from OnChip-RAM
void T6963cWriteChunk(uint8_t* pBuffer, uint16_t nBytes);

//Writes a Chunk from OnChip-Flash
void T6963cWriteChunk_P(const uint8_t* pBuffer, uint16_t nBytes);

//Sets a Pixel (7=MSBit, 0=LSBit)
void T6963cSetPixel(uint8_t Bit);

//Resets a Pixel
void T6963cResetPixel(uint8_t Bit);

//Puts a char (Set Addresspointer to T6963C_ADDR_TEXT before!)
void T6963cPutChar(char Char);

//Puts a 0-terminated String from OnChip-RAM. (Set Addresspointer to T6963C_ADDR_TEXT before!)
void T6963cPutString(const char* String);

//Puts a 0-terminated String from OnChip-Flash. (Set Addresspointer to T6963C_ADDR_TEXT before!)
void T6963cPutString_P(const char* String);

void T6963cWriteSingleByte(uint8_t data, uint16_t nBytes);

// such defines, much comfort, very functon

void T6963cWriteAt(uint16_t Address, uint8_t Byte);

void T6963cWriteChunkAt(uint16_t StartAddress, uint8_t* pBuffer, uint16_t nBytes);

void T6963cWriteByteAt(uint16_t StartAddress, uint8_t pBuffer, uint16_t nBytes);

void T6963cWriteChunkAt_P(uint16_t StartAddress, uint8_t* pBuffer, uint16_t nBytes);

void T6963cSetPixelAt(uint16_t Address, uint8_t Bit);

void T6963cSetPixelXY(uint16_t X, uint16_t Y);

void T6963cResetPixelAt(uint16_t Address, uint8_t Bit);

void T6963cResetPixelXY(uint16_t X, uint16_t Y);

void T6963cPutCharAt(uint16_t Address, char Char);

void T6963cPutCharXY(uint16_t X, uint16_t Y, char Char);

void T6963cPutStringAt(uint16_t Address, const char* pString);

void T6963cPutStringXY(uint16_t X, uint16_t Y, const char* pString);

void T6963cPutStringAt_P(uint16_t Address, const char* pString);

void T6963cPutStringXY_P(uint16_t X, uint16_t Y, const char* pString);

#endif //T6963C_H
