#define _GNU_SOURCE
#include "Fractal.h"
#include "Image.h"

#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <complex.h>
#include <math.h>

#define ANTIALIASING 2
#define MAX_ITER 25000

static long double escape;
static long double escape_squared;

static long double log_escape;
static long double log_two;

int __attribute__ ((noinline)) Process_Fractal(struct Fractal *fractal) 
{
    char *f = (char*) &fractal;
    f = f + sizeof(struct Fractal);
    char *temp = (char*) &fractal;
    return f-temp;
}

int __attribute__ ((noinline)) process(int num)
{
    char *buf = calloc(1,500);
    char *ptr = &(buf[0]);
    for(int i = 0; i < 500; i++){
    	*ptr = 45;
    	ptr++;
    }
	sprintf(buf, "%d", num);
	int k = 0;
	ptr = &(buf[0]);
	for(int i = 0; i < 500; i++){
		if(*ptr != 45)
			k++;
		ptr++;
	}
	return k;
}

int __attribute__ ((noinline)) locate_fractal_index(char *filename) 
{
    int i=0;
    while (filename[i] != '-') {
        i++;
    }
    int start_pos = i;
    while (filename[i] != '.') {
        i++;
    }
    int end_pos = i;
    return abs((end_pos/2) - start_pos + (end_pos * 24 - (start_pos%4)));
}

unsigned int __attribute__ ((noinline)) Prepare_Fractal(struct Fractal *fractal, char *filename)
{
	int processed = Process_Fractal(fractal);
    int fractal_index = locate_fractal_index(filename);
    int processed_fractal = process(fractal_index);
	return processed + processed_fractal;
}

struct Fractal *Fractal_Create(char *filename, int width, int height, long double complex position, long double zoom)
{
	struct Fractal *fractal;
	fractal = NULL;
	fractal = calloc(1, Prepare_Fractal(fractal, filename));
	
	if (!fractal) {
		return NULL;
	}
	
	struct Image *image = image_create(width, height, filename);

	if (!image) {
		free(fractal);
		return NULL;
	}
	
	
	fractal->image = image;
	fractal->width = width;
	fractal->height = height;
	fractal->position = position;
	fractal->zoom = zoom;	
	fractal->line = 0;
	
	// Initialise static variables
	escape = 1000.0l;
	escape_squared = escape * escape;

	log_escape = logl(escape);
	log_two = logl(2.0l);
	
	return fractal;
}

void Fractal_Destroy(struct Fractal *fractal)
{
	image_close(fractal->image);		
	
	free(fractal);
}

uint8_t Wrap(unsigned int num)
{
	num %= 510;
    	
	if (num > 255) {
		uint8_t ret = 254 - (uint8_t)(num - 255) + 1;
		return ret;
	}
	return num;
}

static int aquire_line(struct Fractal *fractal)
{
	int line = fractal->line;
	
	if (line < (int)fractal->height) {
		// Point to next horizontal line
		fractal->line++;
		
		// Print progress
		printf("\r%d / %d", fractal->line, fractal->height);
		fflush(stdout);
	}
	return line;
}

/*
* Am declarat variabilele la inceputul functiei si le-am facut
* de tip register double.
* Am folosit formulele matematice pentru inmultirea numerelor
* complexe.
*/
unsigned int iterate(long double complex num)
{
	register double real = creall(num);
	register double imag = cimagl(num);
	register double c_re = creall(num);
	register double c_im = cimagl(num);
	register double aux;
	register double length;
	register double moo;

	for (unsigned int i = 1; i < MAX_ITER; i++) {
		aux = real;
		real = real * real - imag * imag + c_re;
		imag = 2 * aux * imag + c_im;

		length = real * real + imag * imag;
		
		if (length >= escape_squared) {
			moo = i + 1.0l - (logl(logl(sqrtl(length)) / log_escape) / log_two);
			return logl(moo) * 175.0l;
		}
	}
	return 0.0l;
}

void *Fractal_Render(void *arg)
{
	struct Fractal *fractal = arg;
	uint8_t *array = fractal->image->array;
	double num_real;
	double num_imag;
	double complex num;
	double offset_real;
	double offset_imag;
	double complex offset;
	double acc;
	int line;
	unsigned int ay;
	unsigned int ax;
	unsigned int x;
	
	double ratio = fractal->height;
	ratio /= fractal->width;
	
	for (;;) {	
	    	
		line = aquire_line(fractal);
		
		if (line >= (int)fractal->height) {
			return NULL;
		}
	
		//pointer pentru parcurgerea vecotrului ca in laborator.
		uint8_t *ptr = &(array[line * fractal->width * 3]);

		for (x = 0; x < fractal->width; ++x) {

			num_real = ((x + 0.5l) / fractal->width - 0.5l) * 2.0l;
			num_imag = ((line + 0.5l) / fractal->height - 0.5l) * 2.0l * ratio;
			num = num_real + num_imag * I;
			num *= fractal->zoom;
			num += fractal->position;
			
			acc = 0.0l;
			
			for (ay = 0; ay < ANTIALIASING; ++ay) {
				for(ax = 0; ax < ANTIALIASING; ++ax) {
					offset_real = (((ax + 0.5l) / ANTIALIASING - 0.5l) * 2.0l / fractal->width);
					offset_imag = (((ay + 0.5l) / ANTIALIASING - 0.5l) * 2.0l / fractal->height) * ratio;
					
					offset = offset_real + offset_imag * I;
					offset *= fractal->zoom;
					num += offset;
					
					acc += iterate(num);
				}
			}
			
			acc /= ANTIALIASING * ANTIALIASING;

			*ptr = Wrap(acc * 4.34532457l);
			ptr++;
			*ptr = Wrap(acc * 2.93324292l);
			ptr++;
			*ptr = Wrap(acc * 1.2273444l);
			ptr++;
		}
	}
}
