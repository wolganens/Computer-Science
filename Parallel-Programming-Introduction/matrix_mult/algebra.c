/* 
	algebra.c
	Implementacao das funções
*/

//Funcoes para a alocacao de memoria
#include <stdlib.h>
#include <stdio.h>
#include "algebra.h"

//multiplica uma matriz por uma matriz e retorna uma matriz
//coluna 1 e linha 2 precisam ser iguais
//tamanho da matriz1 = linha1 x coluna1
//tamanho da matriz2 = linha2 x coluna2
//tamanho da matriz retornada = linha1 x coluna2
double* mult_matriz_matriz(int linha1, int coluna1, int linha2, int coluna2, double *matriz1, double *matriz2) {
	int linha = linha1, coluna = coluna2;
	double * res = malloc(linha * coluna * sizeof(double*));
	int i, j, k, x, y, z, tile = 4;

	for(x = 0; x < linha; x += tile) {
		for(z = 0; z < size; z += tile) {
			for(y = 0; y < coluna; y += tile) {
				for(i = x; i < x + tile; i++) {
			        for(k = z; k < z + tile; k += 2) {
						for(j = y; j < y + tile; j++) {
							res[i * size + j] += m[i * size + k] * n[k * size + j];
							res[i * size + j] += m[i * size + (k+1)] * n[(k+1) * size + j];
						}
			        }
				}
			}
		}
	}
	return res;
}