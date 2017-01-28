#include "util.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>


/* intreruperea de comparatie cu OCR1A */
ISR(TIMER1_COMPA_vect)
{
	PORTD &= ~(1 << PD4);
}

ISR(TIMER1_OVF_vect) {
	PORTD |= (1 << PD4);
}

ISR(TIMER1_CAPT_vect){
	PORTD ^= (1 << PD4);
}

ISR(PCINT1_vect) {

	if ((PINB & (1 << PB0)) == 0) {

		OCR1A -= 1000;
		if(OCR1A < 0)
			OCR1A = 0;
	}
	
	if ((PINB & (1 << PB1)) == 0) {
		OCR1A += 1000;
		if(OCR1A > 20600)
			OCR1A = 0;
	}


}


/* initializeaza intrarile si iesirile */
void IO_init()
{
    // LED-ul verde/albastru este pus ca iesire
    DDRD |= (1 << PD4);
	DDRB |= (1 << PB3);
    
    // butoanele sunt puse ca intrare, cu rezistenta de pull-up
    DDRB &= ~((1 << PB0) | (1 << PB1));
	
    PORTB |= ((1 << PB0) | (1 << PB1));
}

/* initializeaza timer-ul 1 */
void timer1_init()
{
    // pragul initial de comparare
    OCR1A = 49152;
    ICR1 = 32768;
    // activeaza intreruperea de comparare cu OCR1A
    TIMSK1 = (1 << OCIE1A) | (1 << TOIE1) | (1 << ICIE1);
    
    TCCR1B = (5 << CS10) | (1 << WGM13) | (1 << WGM12);
	
}


int main(void)
{
    // initializari si testare interfeta afisare/debug
    UI_init();
    printf_init();
    printf("USART ok\n");

    // codul relevant laboratorului incepe aici
    sei();

    timer1_init();
    IO_init();
	
	PCMSK1 |= (1 << PCINT8);
	PCMSK1 |= (1 << PCINT9);
	
	PCICR |= (1 << PCIE0);
	PCICR |= (1 << PCIE1);
	

    while(1)
    {
        drawProgressBars(TCNT1, OCR1A, 0xFFFF); // pentru afisare, ignorati
		
        //_delay_ms(10);
		
    }
    
    return 0;
}

