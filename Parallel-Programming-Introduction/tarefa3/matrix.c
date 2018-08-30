#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

double * mult(int rows, int columns, double *a , double *b) {
	int i, j, k;
	double aux;
	
	double *r = malloc(rows * columns * sizeof(double));
	for (i = 0; i < rows; i++)	{
		for (j = 0; j < columns; j++) {
			aux = 0;
			for (k = 0 ; k < columns ; k++) {
				aux+= a[i * columns + k] * b[k * columns + j];
			}
			r[i * columns + j] = aux;
		}
	}
	return r;
}
int main(int argc, char const *argv[]) {
	int rows 	= atoi(argv[1]);
	int columns = atoi(argv[2]);
	int i,j;
	double *r;
	srand(time(NULL));
	double *a  = malloc(rows * columns * sizeof(double));
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			a[i * columns + j] = (double) rand();
		}
	}
	double *b  = malloc(rows * columns * sizeof(double));
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			a[i * columns + j] = (double) (1 + rand() % rows - 1);
			b[i * columns + j] = (double) (1 + rand() % rows - 1);
		}
	}
	/*printf("\n");
	printf("\n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			printf("%lf ", a[i * columns + j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			printf("%lf ", b[i * columns + j]);
		}
		printf("\n");
	}*/
	r = mult(rows, columns, a, b);
	/*printf("\n");
	printf("\n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			printf("%lf ", r[i * columns + j]);
		}
		printf("\n");
	}*/
	free(a);
	free(b);
	free(r);
	return 0;
}