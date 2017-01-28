/*
 * lab1.c
 */

#include "lcd.h"
#include "usart.h"
#include <string.h>

#include <avr/io.h>
#include <util/delay.h>


#define MORSE_LUNG  3
#define MORSE_SCURT 1

/* Literele alfabetului in cod Morse */
char* morse_alphabet[] = {
    "13",
    "3111",
    "3131",
    "311",
    "1",
    "1131",
    "331",
    "1111",
    "11",
    "1333",
    "313",
    "1311",
    "33",
    "31",
    "333",
    "1331",
    "3313",
    "131",
    "111",
    "111",
    "3",
    "113",
    "1113",
    "133",
    "3113",
    "3133",
    "3311"
};


void exemplu_usart(const char* msg)
{
    USART0_print(msg);
    _delay_ms(10);
}

void task1_usart()
{
	int apasat = 0;
    /* TODO task 1 USART */
    /* Configurare butoane */
	DDRB &= ~(1 << PB0);

	/* Activez rezistenta de pull-up pentru pinul PB0. */
	PORTB |= (1 << PB0);

    /* Main loop */
    while(1)
    {
	
		if ((PINB & (1 << PB0)) == 0 && apasat == 0){
			exemplu_usart("Apasat");
			apasat = 1;
		}
		if((PINB & (1 << PB0)) == 1 && apasat == 1){
			exemplu_usart("Lasat");
			apasat = 0;
		}	
			
        /* Trimite "PB0 apasat" pe USART o singura data! */

        /* Trimite "PB0 lasat" pe USART o singura data! */

        /* Trimite "PB1 apasat" pe USART o singura data! */

        /* Trimite "PB1 lasat" pe USART o singura data! */

        /* Much debounce, such delay. Wow! */
        _delay_ms(65);
    }
}

void task2_usart()
{
	int apasat = 0;
    /* TODO task 2 USART */

    /* Configurare butoane */

	DDRB &= ~(1 << PB0);

	/* Activez rezistenta de pull-up pentru pinul PB0. */
	PORTB |= (1 << PB0);
	
    //* Configurarea stdout */
    FILE mystdout;
	mystdout.flags = __SWR;
	mystdout.put = USART0_printf;
    /* Main loop */
    while(1)
    {
	
		if ((PINB & (1 << PB0)) == 0 && apasat == 0){
			fprintf(&mystdout, "A");
			fprintf(&mystdout, "p");
			fprintf(&mystdout, "a");
			fprintf(&mystdout, "s");
			fprintf(&mystdout, "a");
			fprintf(&mystdout, "t");
			apasat = 1;
		}
		if((PINB & (1 << PB0)) == 1 && apasat == 1){
			fprintf(&mystdout, "L");
			fprintf(&mystdout, "a");
			fprintf(&mystdout, "s");
			fprintf(&mystdout, "a");
			fprintf(&mystdout, "t");
			apasat = 0;
		}	
		
        /* Trimite "PB0 apasat" pe USART o singura data! */

        /* Trimite "PB0 lasat" pe USART o singura data! */

        /* Trimite "PB1 apasat" pe USART o singura data! */

        /* Trimite "PB1 lasat" pe USART o singura data! */

        /* Much debounce, such delay. Wow! */
        _delay_ms(5);
    }

}

/**
 * Apelati functia pentru a obtine un ton lung/scurt,
 * folosind macro-urile MORSE_LUNG si MORSE_SCURT
 */
void speaker_morse(int tip)
{
    int delay = 10;
    int i;
    DDRD |= (1 << PD5);     /* PD5 trebuie sa fie output */

    for (i = 0; i < tip * 50 / delay; i++)
    {
        PORTD ^= (1 << PD5); /* Alternam starea iesirii */
        _delay_ms(1);
    }
}

void task3_usart()
{
	DDRD |= (1 << PD5);
	PORTD &= ~(1 << PD5);
    /* TODO task 3 USART */
int i;int poz;
    /* Configurare porturi folosite */
	
    /* Main loop */
    char c;
    while(1)
    {
        /* Cititm caracter de pe seriala */
		c = USART0_receive();
        /* Daca este o litera a alfabetului, redam sunetul corespunzator din morse */
		poz = c - 97;
		
		for(i = 0; i < strlen(morse_alphabet[poz]); i++){
			if(morse_alphabet[poz][i] == '3')
				speaker_morse(150);
			else
				speaker_morse(50);
			_delay_ms(20);
		}
    }
}


void exemplu_lcd()
{
    LCD_print("Hello World!");

    while(1);
}

void task1_lcd()
{
    /* TODO task 1 LCD */

    /* Configurare butoane */
	DDRB &= ~(1 << PB0);
	PORTB |= (1 << PB0);
	DDRB &= ~(1 << PB1);
	PORTB |= (1 << PB1);
    /* Initializari */
	LCD_print("Hello World!");
    /* Main loop */
    while(1)
    {
        /* Implementati logica de deplasare a mesajului de pe display */
		if (PINB & (1 << PB0)){
			
		}
		else if (PINB & (1 << PB1)){
			
		}
        /* Much debounce, such delay. Wow! */
        _delay_ms(5);
    }
}

void task2_lcd()
{
    /* TODO task 2 LCD */

    /* Main loop */
    while(1)
    {
        /* Citim caracterul de pe seriala si il afisam pe display */

        /* Tineti cont de pozitia de inceput si final a fiecarei linii in memoria
         * controller-ului
         */
    }
}

void bonus_lcd()
{
    /* TODO bonus LCD */

    /* Configurare butoane */

    /* Definire caracter custom */
    uint8_t chuck[] = {
        0x00,   // .....
        0x0e,   // .***.
        0x0e,   // .***.
        0x04,   // ..*..
        0x0e,   // .***.
        0x04,   // ..*..
        0x0e,   // .***.
        0xa     // .*.*.
    };
    /* Scrieti caracterul custom in memoria CGRAM, linie cu linie */

    /* Main loop */
    while(1)
    {
        /* Deplasati-l pe Chuck pe ecran */

        /* Much debounce, such delay. Wow! */
        _delay_ms(5);
    }
}

int main()
{
    //USART
    USART0_init();

  //exemplu_usart();
  //task1_usart();
  //task2_usart();
    task3_usart();

    //LCD
    LCD_init();

//  exemplu_lcd();
//  task1_lcd();
//  task2_lcd();
//  bonus_lcd();

    return 0;
}

