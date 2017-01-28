// Dragu Cristian 332CC
#include <stdio.h>

void func1(int param);
void func2();
void func3();

int main(int argc, char *argv[])
{
	printf("Hello, world\n");
	func1(2);
	func2();
	func3();
	return 0;
}

void func1(int param)
{
	if ( param>=0 ) func2();
	else
	if ( param == -2 ) func1(-1);
}

void func2()
{
	func1(-1);
	func3();
}

void func3()
{
	printf("I'm three!!!");
}