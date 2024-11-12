#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <time.h>
#define X 500
#define Y 500
void MartixInit(int a[][Y], int count) {
	for(int i=0; i<X; i++) {
		for(int j=0; j<Y; j++) {
			a[i][j] = count++;
		}
	}
}

void MartixPrint(int a[][Y]) {
	for(int i=0; i<X; i++) {
		for(int j=0; j<Y; j++) {
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	int a[X][Y];
	int b[X][Y];
	MartixInit(a, 1);
	MartixInit(b, 10);
	int c[X][Y];
	
	clock_t start, end;
	start = clock();
#pragma scop
	for (int i = 0; i < X; ++i)
		for (int j = 0; j < Y; ++j)
			for(int k=0; k < X; ++k)
					c[i][j] += a[i][k]*b[k][j];
#pragma endscop
	end = clock();
	
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	MartixPrint(c);
	printf("time spent: %f\n", time_spent);
	return EXIT_SUCCESS;
}
