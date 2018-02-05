#include "data.h"
#include <stdio.h>

void test()
{
	FILE* test;
	test = fopen("datatest.txt", "w");
	fprintf(test, "works\n");
	fclose(test);
}