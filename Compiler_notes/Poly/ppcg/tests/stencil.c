#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define M 16
#define N 32
int main() {
    int A[M][N];
    for (int i=0; i<N; i++) {
        A[0][i] = i;
    }
	clock_t start, end;
	start = clock();
#pragma scop
    for(int i=0; i<M-1; i++) {
        for(int j=0; j<N; j++) {
            A[i+1][j] = 0.125 * ((j>=1?6*A[i][j-1]:0)+ A[i][j] + (j<N-1?A[i][j+1]:0));
        }
    }
#pragma endscop

    for(int i=0; i<M-1; i++) {
        for(int j=0; j<N; j++) {
            printf("%d", A[i][j]);
            int mod = A[i][j] / 10;
            if(mod) printf(" ");
            else printf("  ");
        }
        printf("\n");
    }

	end = clock();
	
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("time spent: %f\n", time_spent);
	return EXIT_SUCCESS;
}