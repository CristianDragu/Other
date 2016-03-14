#include "homework1.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int num_threads;
int resolution;

double calculateDistance(int x, int y) {
    return abs(-1 * x + 2 * y)/sqrt(5);
}

void initialize(image *im) {

}

void render(image *im) {
	int i, j, lengthData = 0;

	omp_set_num_threads(num_threads);

	im->data = (unsigned char**)malloc(resolution * sizeof(unsigned char*));
	for(i = 0; i < resolution; i++)
		im->data[i] = (unsigned char*)malloc(resolution * sizeof(unsigned char));

	#pragma omp parallel for private(i, j) num_threads(num_threads)
	for(i = resolution - 1; i >= 0; i--){
		for(j = 0; j < resolution; j++)
			if(calculateDistance(j * (100.0/resolution) + (100.0/resolution/2), i * (100.0/resolution) + (100.0/resolution/2)) < 3.0)
				im->data[i][j] = 0;
			else
				im->data[i][j] = 255;
	}

}

void writeData(const char * fileName, image *img) {
	FILE *outputImageFile;
	outputImageFile = fopen (fileName, "wb");

	fprintf(outputImageFile, "P5\n");

	fprintf(outputImageFile, "%d %d\n", resolution, resolution);

	fprintf(outputImageFile, "255\n");

	int i, j;

	for(i = resolution - 1; i >= 0; i--)
		fwrite(img->data[i], sizeof(unsigned char), resolution, outputImageFile);

	fclose(outputImageFile);
}