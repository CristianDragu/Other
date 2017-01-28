// Dragu Cristian 332CC
#include <stdio.h>
#include <math.h>

struct punct{
	int x, y;
};
typedef struct punct Punct;

int CalcDist(Punct p, Punct r);
Punct getNewPoint();

int main(){

	Punct p = {0, 0}, r = {100, 100};

	int raza = CalcDist(p, r);

	printf("%d", raza);

	if(p.x == 0 && p.y == 0)
		p = getNewPoint();

	return 0;
}

int CalcDist(Punct p, Punct r){
	
	return (int)sqrt(pow(p.x - r.x, 2) + pow(p.y - r.y, 2));

}

Punct getNewPoint(){

	Punct p = {1, 1};
	return p;

}
