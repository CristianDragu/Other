#include "homework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int num_threads;
int resize_factor;

void readInput(const char * fileName, image *img) {

	FILE *inputImageFile;
	int i, j;

	inputImageFile = fopen(fileName, "rb");

	fgets(img->pType, sizeof(img->pType), inputImageFile);

    char c = getc(inputImageFile);
    while (c == '#') {
    while (getc(inputImageFile) != '\n') ;
         c = getc(inputImageFile);
    }

    ungetc(c, inputImageFile);

	fscanf(inputImageFile, "%d%d", &img->width, &img->height);

	fscanf(inputImageFile, "%d", &img->maxValColor);

	while (fgetc(inputImageFile) != '\n') ;

	if(strcmp(img->pType, "P6")) {
		img->pixelByte = 1;
		img->data = (unsigned char**)malloc(img->height * sizeof(unsigned char*));
		for(i = 0; i < img->height; i++)
			img->data[i] = (unsigned char*)malloc(img->width * sizeof(unsigned char));
		for(i = 0; i < img->height; i++)
			fread(img->data[i], sizeof(unsigned char), img->width, inputImageFile);
	}
	else{
		img->pixelByte = 3;
		img->data = (unsigned char**)malloc(img->height * sizeof(unsigned char*));
		for(i = 0; i < img->height; i++)
			img->data[i] = (unsigned char*)malloc(3 * img->width * sizeof(unsigned char));
		for(i = 0; i < img->height; i++)
			fread(img->data[i], sizeof(unsigned char), img->width * 3, inputImageFile);
	}

	fclose(inputImageFile);

}

void writeData(const char * fileName, image *img) {
	FILE *outputImageFile;

	outputImageFile = fopen (fileName, "wb");

	fprintf(outputImageFile, "%s\n", img->pType);

	fprintf(outputImageFile, "%d %d\n", img->width, img->height);

	fprintf(outputImageFile, "%d\n", img->maxValColor);

	int i;

	for(i = 0; i < img->height; i++)
		fwrite(img->res[i], img->width * img->pixelByte * sizeof(unsigned char), 1, outputImageFile);

	fclose(outputImageFile);
}

void resize(image *in, image * out) { 

	int widthImg = in->width;
	int heightImg = in->height;
	int i, j, ii, jj;
	unsigned int sum, sumr, sumg, sumb;

	out->pixelByte = in->pixelByte;
	strcpy(out->pType, in->pType);
	out->width = (int)in->width / resize_factor;
	out->height = (int)in->height / resize_factor;
	out->maxValColor = in->maxValColor;

	omp_set_num_threads(num_threads);

	if(strcmp(in->pType, "P6") == 0)
		if(resize_factor % 2 == 1){
			heightImg -= (heightImg % resize_factor);
			widthImg -= (widthImg % resize_factor);
			out->res = (unsigned char**)malloc(out->height * sizeof(unsigned char*));
			#pragma omp parallel for private(i) num_threads(num_threads)
			for(i = 0; i < out->height; i++)
				out->res[i] = (unsigned char*)calloc(out->width * 3, sizeof(unsigned char));
			#pragma omp parallel for private(i, j, sumr, sumg, sumb) collapse(2) num_threads(num_threads)
			for(i = 0; i < heightImg; i += 3) {
				for(j = 0; j < widthImg * 3; j += 9){
					sumr = in->data[i][j]    * 1 + in->data[i][j + 3]     * 2 + in->data[i][j + 6]     * 1 
						+ in->data[i + 1][j] * 2 + in->data[i + 1][j + 3] * 4 + in->data[i + 1][j + 6] * 2
						+ in->data[i + 2][j] * 1 + in->data[i + 2][j + 3] * 2 + in->data[i + 2][j + 6] * 1;
					sumg = in->data[i][j + 1]    * 1 + in->data[i][j + 4]     * 2 + in->data[i][j + 7]     * 1 
						+ in->data[i + 1][j + 1] * 2 + in->data[i + 1][j + 4] * 4 + in->data[i + 1][j + 7] * 2
						+ in->data[i + 2][j + 1] * 1 + in->data[i + 2][j + 4] * 2 + in->data[i + 2][j + 7] * 1;
					sumb = in->data[i][j + 2]    * 1 + in->data[i][j + 5]     * 2 + in->data[i][j + 8]     * 1 
						+ in->data[i + 1][j + 2] * 2 + in->data[i + 1][j + 5] * 4 + in->data[i + 1][j + 8] * 2
						+ in->data[i + 2][j + 2] * 1 + in->data[i + 2][j + 5] * 2 + in->data[i + 2][j + 8] * 1;
					sumr /= 16;
					sumg /= 16;
					sumb /= 16;
					out->res[i / 3][j / 3] = sumr;
					out->res[i / 3][j / 3 + 1] = sumg;
					out->res[i / 3][j / 3 + 2] = sumb;
				}
			}
		}
		else{
			heightImg -= (heightImg % resize_factor);
			widthImg -= (widthImg % resize_factor);
			out->res = (unsigned char**)malloc(out->height * sizeof(unsigned char*));
			#pragma omp parallel for private(i) num_threads(num_threads)
			for(i = 0; i < out->height; i++)
				out->res[i] = (unsigned char*)calloc(out->width * 3, sizeof(unsigned char));
			#pragma omp parallel for private(i, j, ii, jj, sumr, sumg, sumb) collapse(2) num_threads(num_threads)
			for(i = 0; i < heightImg; i += resize_factor) {
				for(j = 0; j < widthImg * 3; j += (resize_factor * 3)){
					sumr = 0;
					sumg = 0;
					sumb = 0;
					for(ii = i; ii < i + resize_factor; ii++)
						for(jj = j; jj < j + (resize_factor * 3); jj += 3) {
							sumr += in->data[ii][jj];
							sumg += in->data[ii][jj + 1];
							sumb += in->data[ii][jj + 2];
						}
					out->res[i / resize_factor][j / resize_factor] = sumr / (resize_factor * resize_factor);
					out->res[i / resize_factor][j / resize_factor + 1] = sumg / (resize_factor * resize_factor);
					out->res[i / resize_factor][j / resize_factor + 2] = sumb / (resize_factor * resize_factor);
				}
			}
		}
	else{
		if(resize_factor % 2 == 1){
			heightImg -= (heightImg % resize_factor);
			widthImg -= (widthImg % resize_factor);
			out->res = (unsigned char**)malloc(out->height * sizeof(unsigned char*));
			#pragma omp parallel for private(i) num_threads(num_threads)
			for(i = 0; i < out->height; i++)
				out->res[i] = (unsigned char*)calloc(out->width, sizeof(unsigned char));

			#pragma omp parallel for private(i, j, sum) collapse(2) num_threads(num_threads)
			for(i = 0; i < heightImg; i += resize_factor)
				for(j = 0; j < widthImg; j += resize_factor) {
					sum = in->data[i][j]     * 1 + in->data[i][j + 1]     * 2 + in->data[i][j + 2]     * 1 
						+ in->data[i + 1][j] * 2 + in->data[i + 1][j + 1] * 4 + in->data[i + 1][j + 2] * 2
						+ in->data[i + 2][j] * 1 + in->data[i + 2][j + 1] * 2 + in->data[i + 2][j + 2] * 1;
					out->res[i / resize_factor][j / resize_factor] = sum / 16;
				}
		}
		else{
			heightImg -= (heightImg % resize_factor);
			widthImg -= (widthImg % resize_factor);
			out->res = (unsigned char**)malloc(out->height * sizeof(unsigned char*));
			#pragma omp parallel for private(i) num_threads(num_threads)
			for(i = 0; i < out->height; i++)
				out->res[i] = (unsigned char*)calloc(out->width, sizeof(unsigned char));

			#pragma omp parallel for private(i, j, ii, jj, sum) shared(in, out, resize_factor) collapse(2) num_threads(num_threads)
			for(i = 0; i < heightImg; i += resize_factor)
				for(j = 0; j < widthImg; j += resize_factor) {
					sum = 0;
					for(ii = i; ii < i + resize_factor; ii++)
						for(jj = j; jj < j + resize_factor; jj++)
							sum += in->data[ii][jj];
					out->res[i / resize_factor][j / resize_factor] = sum / (resize_factor * resize_factor);
				}
		}
	}

}