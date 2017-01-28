#include <avr/io.h>
#include "MMA8452.h"
#include "led.h"
#include <math.h>

#define MAX_INT 32767
#define SCALE 8

/*
	Initiates the registers
*/
void init_pins()
{
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRD = 0b11110000;

	PORTD = 0;
	PORTA = 0;
	PORTB = 0;
}

/*
	Returns the reverse square root of the number (1 / sqrt(n)).
	This algorithm is called Fast Inverse Squre Root and it was
	used in Quake III Arena.
*/
float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;
	i  = 0x5f3759df - ( i >> 1 );
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );

	return y;
}

/*
	Returns the square root of the number.
*/
float fastsqrt(float val)  {
	union
    {
		int tmp;
		float val;
    }u;
    u.val = val;
    u.tmp -= 1<<23;
    u.tmp >>= 1;
    u.tmp += 1<<29;
    return u.val;
}

/*
	Returns the distance from a point P(x0,y0,z0) to a plane PL described
	by ax + by + cz + d = 0, where a,b,c are coordinates of the normal
	vector.
*/ 
float get_distance(float a, float b, float c, float x0, float y0, float z0)
{
	return ((a * x0) + (b * y0) + (c * z0)) / fastsqrt(a * a + b * b + c * c);
}

int main()
{
	i2c_init();

	MMA8452 accel;

	if(accel.init() == false){ //in case of error PA1 led will light up
		DDRA |= (1 << PA1);
		
		DDRD |= (1 << PD4);
		
		PORTA |= (1 << PA1);
		PORTD = 0;
		
		while(1){
			PORTD |= (1 << PD4);
			_delay_ms(500);
			PORTD &= ~(1 << PD4);
			_delay_ms(500);
		}
	}
	else{
		accel.setDataRate(MMA_800hz);
		accel.setRange(MMA_RANGE_8G);

		float x = 0, y = 0, z = 0;
		/*float xg, yg, zg; //uncomment this for the actual g value for each vector
		//					  a more human readable choice*/
		
		char i, bunch_leds_s, bunch_leds_f;
		int j, jj;
		
		init_pins();
		
		while(1){
			accel.getAcceleration(&x, &y, &z);
			
			z = -z;
		
			//xg =  (float) x/((1 << 12) / (2 * SCALE));
			//yg =  (float) y/((1 << 12) / (2 * SCALE));
			//zg = (float) z/((1 << 12) / (2 * SCALE));
			
			for(j = 0; j < 64; j++){
				//leds[j].distance = get_distance(x, y, z, 
				//								  leds[j].x, 
				//								  leds[j].y, 
				//								  leds[j].z);
				leds[j].distance = ((x * leds[j].x) + 
									(y * leds[j].y) + 
									(z * leds[j].z)) / fastsqrt(x * x + y * y + z * z);
			}
			
			//only one transistor will work at a time
			//for each transistor, the corresponding leds are enlightened
			for(i = PD4; i <= PD7; i++){
				bunch_leds_s = (i - 4) * 16;
				bunch_leds_f = (i - 3) * 16;
				for(j = bunch_leds_s; j < bunch_leds_f; j++){
					if(leds[j].distance < 0 && leds[j].tranzistor == i){
						jj = j % 16;
						if(jj <= 7){
							PORTA |= (1 << leds[j].pin);
							PORTD |= (1 << i);
						}
						else if(jj > 7){
							PORTB |= (1 << leds[j].pin);
							PORTD |= (1 << i);
						}
					}
				}
				_delay_ms(10);
				PORTA = 0;
				PORTB = 0;
				PORTD = 0;
			}
		}
	}
}