#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"


grafo* insere_grafo(grafo* aplicacoes, char* nome) {
    grafo* novo = malloc(sizeof(grafo));
    if (novo == NULL) {
        printf("Falha ao alocar memória para o grafo\n");
        exit(EXIT_FAILURE);
    }
    strcpy(novo->nome, nome);
    novo->vertices = NULL;
    novo->proximo = NULL;
    if (aplicacoes == NULL) {
        aplicacoes = novo;
    } else {
        grafo* aux = aplicacoes;
        novo->proximo = aux;
        aplicacoes = novo;        
    }
    return novo;
}
vertice* cria_vertice(unsigned int id){
    vertice* novo = malloc(sizeof(vertice));
    if (novo == NULL) {
        printf("Falha ao alocar memória para o vertice\n");
        exit(EXIT_FAILURE);
    }
    novo->id = id;
    novo->sucessores = NULL;
    novo->proximo = NULL;
    return novo;
}
vertice* insere_vertice(grafo* aplicacao, unsigned int id) {
    if(!existe_vertice(aplicacao,id)) {
        printf("Inserindo vertice %d na aplicacao %s\n", id, aplicacao->nome);
        vertice *v = cria_vertice(id);
        vertice *aux;
        if (aplicacao->vertices == NULL) {
            aplicacao->vertices = v;
            return v;
        } else {            
            for (aux = aplicacao->vertices ; aux->proximo != NULL ; aux = aux->proximo){};
            aux->proximo = v;            
            return v;
        }
        aplicacao->n = aplicacao->n + 1;
    } else {
        vertice* aux;
        for (aux = aplicacao->vertices ; aux != NULL; aux = aux->proximo){
            if (aux->id == id) {
                return aux;
            }
        }
    }
}
aresta* cria_aresta(vertice* origem, vertice* destino, int ocupacao) {
    unsigned int aresta_existe = 0;
    aresta* novo = malloc(sizeof(aresta));
    if (novo == NULL) {
        printf("Falha ao alocar memória para a aresta\n");
        exit(EXIT_FAILURE);
    }
    novo->ocupacao_canal = ocupacao;
    novo->destino = destino;
    novo->proximo = NULL;
    if (origem->sucessores == NULL) {
        origem->sucessores = novo;
        return novo;
    } else {
        aresta *aux = origem->sucessores;
        novo->proximo = aux;
        origem->sucessores = novo;
        return novo;
    }
}
int existe_vertice(grafo* aplicacao, int v) {
    vertice* aux;
    for (aux = aplicacao->vertices ; aux != NULL; aux = aux->proximo){
        if (aux->id == v) {
            return 1;
        }
    }
    
    return 0;
}
void destroi_grafo(grafo* aplicacao){
    vertice* v_aux,*v_remove;
    aresta* a_aux, *a_remove;
    for(v_aux = aplicacao->vertices ; v_aux != NULL ; v_aux = v_aux->proximo){
        for(a_aux = v_aux->sucessores ; a_aux != NULL ; a_aux = a_aux->proximo){
            a_remove = a_aux;
            free(a_remove);
        }
        v_remove = v_aux;
        free(v_remove);
    }
}
void print_grafo(grafo* aplicacao) {
    vertice* vertices;
    aresta* arestas;
    printf("APLICAÇÃO: %s\n", aplicacao->nome);
    for (vertices = aplicacao->vertices ; vertices != NULL; vertices = vertices->proximo) {        
        printf("Vertice: %u\n\tArestas: ", vertices->id);
        for(arestas = vertices->sucessores; arestas != NULL ; arestas = arestas->proximo){
            printf("%u ", arestas->destino->id);
        }
        printf("\n");
    }
}