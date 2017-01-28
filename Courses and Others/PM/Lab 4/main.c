/*
 *  main.c
 */

#include "T6963c.h"
#include "game.h"

#include <avr/interrupt.h>
#include <util/delay.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


const char* ADC_name[] = {"Temp", "Light", "Acc X", "Acc Y", "Acc Z", "Btn"};


#define XCHANNEL		2
#define YCHANNEL		3
#define ZCHANNEL		4

// TODO 2 hint
#define AREF 5

//TODO 3
// determine the 0g value for the Y axis and an acceptable threshold for movement
double valref = 1.6;

#define PAD_INCREMENT	2


#ifdef ADC_USE_IRQ

#define ADC_INIT_CHANNEL 0

int ADC_value[sizeof(ADC_name) / sizeof(ADC_name[0])];

ISR(ADC_vect)
{
	//TODO 5
}

#endif

void ADC_init(void)
{
#ifndef ADC_USE_IRQ
	//TODO 2
	// enable ADC with:
	// *reference AVCC with external capacitor at AREF pin
	// *without left adjust of conversion result
	// *no auto-trigger
	// *no interrupt
	// *prescaler at 128
	
	ADMUX |= (1<< REFS0);
	ADCSRA |= (1<< ADEN) | (7 << ADPS0) ;
#else
	//TODO 5
	// enable ADC with interrupt
#endif
}

int ADC_get(uint8_t channel)
{
#ifndef ADC_USE_IRQ
	//TODO 2
	// start ADC conversion on "channel"
	// wait for completion
	// return the result
	
	ADMUX &= ~(1 << MUX0);
	ADMUX &= ~(1 << MUX1);
	ADMUX &= ~(1 << MUX2);
	ADMUX &= ~(1 << MUX3);
	ADMUX &= ~(1 << MUX4);
	
	ADMUX |= (channel << MUX0);
	
	ADCSRA |= (1 << ADSC);
	while(((1 << ADSC) & ADCSRA) == 1) {
	
	}
	
	return ADC;
#else
	//TODO 5
#endif

    (void)channel;
    return 0;
}

double ADC_voltage(int raw)
{
	(void)raw;
	// TODO 2
	// returnati conversia datelor ADC raw in volti
	return ((double)(raw * 5)) / 1023.0;
}

void ADC_show(void)
{
	//TODO 1
	// print ADC channels 0-5 starting at line 0, column 0
	// use ADC_name[] for the name of the channel
	int i;
	
	for (i=0; i<6; i++) {
		char str[20];
		T6963cPutStringXY(0, i, ADC_name[i]);
		sprintf(str, "%lf", ADC_voltage(ADC_get(i)));
		T6963cPutStringXY(strlen(ADC_name[i]) + 1, i, str);
		
	}
	
}

int main(void)
{
	DDRC = 0xFF; 
	PORTC = 0xFF;
	_delay_ms(100);

	//XOR mode, internal CG, Text and Graphic, Blinking Cursor	
	T6963cInit(T6963C_MODE_XOR | T6963C_CG_INTERNALROM, T6963C_TEXT_GRAPHIC);

	ADC_init();

	/* Initialize game */
	init_game();

	sei();

	while(1)
	{
		ADC_show();

		/******* Game Logic *******/

		/* Erase old moving components */
		// erase ball
		draw_ball(x, y, 0);
		// erase pad
		draw_pad(x_pad, y_pad, 0);

		/* Update pad position */
		//TODO 3
		if ( (ADC_voltage(ADC_get(3)) - valref) < -1.2)
			x_pad -= 1;
		else if ( (ADC_voltage(ADC_get(3)) - valref) > 1.2)
			x_pad += 1;
		
		
		
		
		
		// update pad position based on acceleration on Y axis

		// put pad in limits of playing area
		if(x_pad < X1_LIMIT + 1) x_pad = X1_LIMIT + 1;
		if(x_pad > X2_LIMIT - PAD_LENGTH) x_pad = X2_LIMIT - PAD_LENGTH;

		/* Check for win/loss condition */
		if(win > 0)
		{
			T6963cPutStringXY_P(0, 10, PSTR("YOU WIN"));
			_delay_ms(1000);
			init_game();
		}
		else if(win < 0)
		{
			T6963cPutStringXY_P(0, 10, PSTR("YOU LOSE"));
			_delay_ms(1000);
			init_game();
		}
		else
			T6963cPutStringXY_P(0, 10, PSTR("        "));

		/* Calculate the new speed and coordinates */
		// modify positions according to speed
		float oldx = x;
		float oldy = y;
		x += xspeed;
		y += yspeed;

		// check if ball hit pad
		int result;
		if((result = check_pad(x, y, x_pad, y_pad)) >= 0)
		{
			yspeed *= -1;
			float angle = (result * M_PI/2)/ PAD_LENGTH - M_PI/4;

			float xs, ys;

			xs = xspeed * cos(angle) - yspeed * sin(angle);
			ys = xspeed * sin(angle) + yspeed * cos(angle);

			xspeed = xs;
			yspeed = ys;
		}

		// check margins -> bounce
		switch(check_margins(x,y))
		{
			case HIT_VERT:
				x = oldx;
				y = oldy;
				yspeed *= -1;
				break;

			case HIT_HORIZ:
				x = oldx;
				y = oldy;
				xspeed *= -1;
				break;

			case HIT_LOST:
				win = -1;
				break;
		}

		// check bricks -> don't bounce
		check_bricks(x, y);

		if(remaining_bricks == 0)
			win = 1;

		draw_ball(x, y, 1);
		draw_pad(x_pad, y_pad, 1);

		_delay_ms(25);
	}

	return 0;
}
