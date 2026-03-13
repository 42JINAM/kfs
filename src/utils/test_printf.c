#include "utils.h"

void test_printf(void) 
{
	int a = 1;
	int b = 2;

	char c = 'c';
	char d = 'd';
	printf("printf c: %c\n", 'c');
	printf("printf s: %s\n", "string");
	
	printf("int a ==========\n");
	printf("printf p: %p \n", a);
	printf("printf x: %x \n", a);
	printf("printf X: %X \n", a);
		
	printf("int b ==========\n");
	printf("printf p: %p \n", b);
	printf("printf x: %x \n", b);
	printf("printf X: %X \n", b);

	printf("char c ==========\n");
	printf("printf p: %p \n", c);
	printf("printf x: %x \n", c);
	printf("printf X: %X \n", c);
	
	printf("char d ==========\n");
	printf("printf p: %p \n", d);
	printf("printf x: %x \n", d);
	printf("printf X: %X \n", d);

}