#include <stdio.h>

typedef struct images {
	char pType[3];
	int pixelByte;
	int width;
	int height;
	int maxValColor;
	unsigned char **data;
	unsigned char **res;
} image;