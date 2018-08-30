#include <stdio.h>
#include <stdlib.h>
#include "algebra.c" 

int main(int argc, char **argv) {
	int col = atoi(argv[1]);
	int lin = atoi(argv[2]);
	int valor = 2;
	int i, j;
	double *v, *m, *n, *res, *r;

	m = malloc(lin * col * sizeof(double*));
	n = malloc(lin * col * sizeof(double*));
	res = mult_matriz_matriz(lin, col, lin, col, m, n);
	
	free(m); free(n); free(res);

	return 0;

}
