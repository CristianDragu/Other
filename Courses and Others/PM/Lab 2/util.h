#ifndef UTIL_H_
#define UTIL_H_

#include "lcd.h"
#include "usart.h"

#include <stdio.h>


/*
 * genereaza caracterele necesare pentru progress bar-uri
 */
inline void LCD_generate_bars()
{
    int bars[6] = {0x00, 0x10, 0x18, 0x1C, 0x1e, 0x1f};

    LCD_writeInstr(LCD_INSTR_CGRAM);

    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 8; j++)
            LCD_writeData(bars[i]);
    }
}

/* 
 * deseneaza un progress bar, folosind caractere formate din *n* bare
 */
inline void drawProgressBar(uint32_t p, uint32_t* p_old, uint8_t lcd_address)
{
    if(p < *p_old)
    {
        // daca s-a micsorat bara de progres trebuie sa stergem niste patratele
        LCD_writeInstr(LCD_INSTR_DDRAM + lcd_address + (p / 5));
        for(uint32_t i = (*p_old / 5); i < (p / 5); i++)
            LCD_writeData(0);
    }
    else
    {
        // daca nu, trebuie sa adaugam
        LCD_writeInstr(LCD_INSTR_DDRAM + lcd_address + (*p_old / 5));
        for(uint32_t i = (*p_old / 5); i < (p / 5); i++)
            LCD_writeData(5);
    }

    // exista un singur caracter cu mai putin de 5 linii verticale
    LCD_writeData(p % 5);

    // umplem restul ecranului cu spatii libere, ca sa nu fie nevoie de clear
    for(uint32_t i = (p / 5); i < 16; i++)
        LCD_writeData(0);

    *p_old = p;
}

/* 
 * deseneaza progress bar-uri pe doua linii ale lcd-ului tinand cont
 * de cele doua valori trimise ca parametri precum si de valoarea maxima
 * a acestora
 */
inline void drawProgressBars(uint32_t value1, uint32_t value2, uint16_t max)
{
    static uint32_t progress_line1_old = 0;
    static uint32_t progress_line2_old = 0;

    uint32_t progress = value1 * 79 / max;

    drawProgressBar(progress, &progress_line1_old, 0);

    progress = value2 * 79 / max;

    drawProgressBar(progress, &progress_line2_old, 0x40);
}

/*
 * initializeaza interfata grafica
 */
inline void UI_init()
{
    LCD_init();
    LCD_generate_bars();
}

/*
 * initializeaza interfata USART pentru printf
 */
inline void printf_init()
{
    static FILE mystdout;
    mystdout.flags = __SWR;
    mystdout.put = USART0_printf;
    
    USART0_init();
    stdout = &mystdout;
}


#endif // UTIL_H_

