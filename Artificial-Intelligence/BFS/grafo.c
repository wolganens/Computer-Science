#include <stdlib.h> /*malloc*/
#include "grafo.h"

vertex* insere(vertex *g, int sourc_index, int dest_index) {
	vertex* sourc;
	vertex* dest;
	/*Se o grafo estiver vazio, cria os dois vértices e adiciona a conexão*/
	if (g == NULL) {		
		sourc = new_vertex(sourc_index);
		dest = new_vertex(dest_index);
		/*Adiciona na lista de vértices do grafo a source e o destino,
		como o grafo esta vazio, a source vira o primeiro elemento*/
		g = add_vertex(sourc, dest);
		
	} else {		
		/*Busca os vértices de source e destino dentro do grafo*/
		sourc = find_vertex_by_index(g, sourc_index);
		dest = find_vertex_by_index(g, dest_index);		
		
		/*Se os vértices não estão no grafo, insere eles*/
		if (sourc == NULL) {
			sourc = new_vertex(sourc_index);
			add_vertex(g, sourc);
		}
		if (dest == NULL) {
			dest = new_vertex(dest_index);
			add_vertex(g, dest);
		}
	}
	/*Adiciona na lista de adjacencia da source, o vértice destino*/
	sourc->edges = add_edge(sourc->edges, dest);
	dest->edges = add_edge(dest->edges, sourc);

	return g;
}

vertex* new_vertex(int index) {
	
	vertex *v = malloc(sizeof(vertex));
	v->index = index;
	v->visited = 0;
	v->next = NULL;
	v->edges = NULL;

	return v;
}

edge* new_edge(vertex* dest) {
	edge* e = malloc(sizeof(edge));
	e->dest = dest;
	e->next = NULL;
	return e;
}

vertex* add_vertex(vertex* list, vertex* dest) {		
	vertex* aux = list;
	while (aux->next != NULL) {
		aux = aux->next;
	}		
	aux->next = dest;

	printf("%d adicionado\n",  dest->index);
	return list;
}
edge *add_edge(edge* list, vertex* dest) {
	edge* e = new_edge(dest);	
	edge* aux = list;
	if (list == NULL) {
		list = e;
	} else {
		while (aux->next != NULL) {
			aux = aux->next;
		}		
		aux->next = e;
	}
	return list;	
}

vertex* find_vertex_by_index(vertex* g, int index) {	
	vertex *aux = g;
	while (aux->next != NULL) {		
		if (aux->index == index) {	
			return aux;
		}			
		aux = aux->next;		
	}
	return NULL;
}
void destroy_graph(vertex* g) {
	vertex* aux = g;
	edge* aux2 = aux->edges;
	while (aux->next != NULL) {
		g = aux;		
		aux = aux->next;
		while(aux2->next != NULL) {
			aux->edges = aux2;
			aux2 = aux2->next;
			free(aux->edges);
		}
		free(g);
	}
}
void print_graph(vertex* g) {
	/*Auxiliar apontando para o grafo*/
	vertex* aux = g;
	edge* aux2;
	while(aux->next != NULL) {	
		printf("Vértice: %d\n", aux->index);
		aux2 = aux->edges;
		while(aux2->next != NULL) {
			printf("\t%d\n", aux2->dest->index);			
			aux2 = aux2->next;
		}
		aux = aux->next;
	}
}
edge* get_adjacents(vertex *g, int index) {
	vertex *aux = g;	
	while (aux->next != NULL) {
		if (aux->index == index) {
			return aux->edges;			
		}
		aux = aux->next;
	}
}
void set_visited(vertex* g, int index) {
	vertex *aux = g;	
	while (aux->next != NULL) {
		if (aux->index == index) {
			aux->visited = 1;
		}
		aux = aux->next;
	}	
}