#include <stdlib.h>
#include "estruturas.h"

PROCESSO* insere_ordenado_chegada(PROCESSO *processos, int pid, int chegada, int duracao, int tamanho){
	PROCESSO* percorrer = processos;
	PROCESSO* anterior = NULL;
	PROCESSO* aux = NULL;
	
	PROCESSO* novo_processo = malloc(sizeof(PROCESSO));
	
	if (novo_processo == NULL) {
		printf("Falha ao alocar memória para o processo\n");
		exit(1);
	}
	novo_processo->pid = pid;
	novo_processo->chegada = chegada;
	novo_processo->duracao = duracao;
	novo_processo->tamanho = tamanho;
	novo_processo->tempo_aloc = 0;
	novo_processo->estado = PRONTO;
	novo_processo->proximo = NULL;
	novo_processo->ciclo_aloc = -1;
	
	if (processos == NULL) {
		processos = novo_processo;
		return novo_processo;
	} else {

		while(percorrer != NULL && percorrer->chegada < novo_processo->chegada){
			anterior = percorrer;
			percorrer = percorrer->proximo;
		}
		
		if (anterior == NULL) {
			aux = percorrer;
			novo_processo->proximo = aux;			
			return novo_processo;
		} else {
		
			if (percorrer == NULL) {
				anterior->proximo = novo_processo;
			} else {				
				anterior->proximo = novo_processo;
				novo_processo->proximo = percorrer;
			}
			return processos;
		}
	}
}
void destroi_lista_processos(PROCESSO* processos) {
	PROCESSO* aux = processos;
	PROCESSO* prox = NULL;
	while(aux != NULL) {
		prox = aux->proximo;		
		free(aux);
		aux = prox;
	}
}
void destroi_lista_segmentos(SEGMENTO* memoria_principal) {
	SEGMENTO* aux = memoria_principal;
	SEGMENTO* prox = NULL;
	while(aux != NULL) {
		prox = aux->proximo;		
		free(aux);
		aux = prox;
	}
}
void reseta_processos(PROCESSO* processos) {
	for (PROCESSO* aux = processos ; aux != NULL ; aux = aux->proximo) {
		aux->ciclo_aloc = -1;
		aux->estado = PRONTO;
	}
}
void reseta_memoria(SEGMENTO* memoria_principal, int tam_original) {
	memoria_principal->ocupacao = LIVRE;
	memoria_principal->tamanho = tam_original;
	memoria_principal->inicio = 0;
	destroi_lista_segmentos(memoria_principal->proximo);
	memoria_principal->proximo = NULL;
	memoria_principal->anterior = NULL;
}