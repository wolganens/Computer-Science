#include <stdio.h>
#include <stdlib.h>

typedef struct _vertice{
	unsigned int id;
	struct _aresta* sucessores;
	struct _vertice* proximo;
} vertice;

typedef struct _aresta {
	int ocupacao_canal;
	vertice* destino;
	struct _aresta* proximo;
} aresta;

typedef struct _grafo{
	int n;
	char nome[30];
	struct _vertice* vertices;
	struct _grafo* proximo;		
} grafo;

vertice* insere_vertice(grafo* aplicacao, unsigned int id);
int existe_vertice(grafo* aplicacao, int v);
