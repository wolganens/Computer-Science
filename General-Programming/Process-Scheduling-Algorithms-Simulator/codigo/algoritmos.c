#include "event_logs.c"
#include "algoritmos.h"

#define ANSI_COLOR_GREEN   "\x1b[32;1m"
#define ANSI_COLOR_BLUE    "\x1b[34;1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char* nome_arquivo;
int tam_mem_principal;
int alg;
METRICAS** m_metricas;
int ocorreu_evento = 0;
char comando;

double* init(SEGMENTO *memoria_principal, PROCESSO *processos, int tam_memoria, int algoritmo, char* caso_teste, int n) {
	// Variaveis de controle
	int ciclo = 0, falhas = 0;
	double *tempos;	
	//Matriz de métricas, uma lista para cada algoritmo
	m_metricas = inicializa_metricas();
	// Variaveis globais
	tam_mem_principal = tam_memoria;
	alg = algoritmo;
	nome_arquivo = caso_teste;
	// Processo a ser alocado e o segmento em que foi alocado
	PROCESSO *processo;
	SEGMENTO *endereco;
	// Encerra apenas quando todos os processos forem alocados
	while(restam_execucoes(processos)){
		ocorreu_evento = 0;
		// Verifica se tem algum processo a ser desalocado no ciclo atual
	    desaloca_processo_ciclo(memoria_principal, ciclo, falhas);
	    // Se houverem lacunas adjacentes(lado a lado) mescla elas
	    junta_lacunas_adjacentes(memoria_principal);
		processo = NULL;
		endereco = NULL;
		// Verifica se chegou algum processo no ciclo autal
    	processo = busca_processo_ciclo(processos, ciclo);
		if (processo != NULL) {
			// Se chegou um processo, de acordo com o algoritmo, insere ele na memoria
			clock_t inicio, fim;
			double total;
			inicio = clock();			
			switch(algoritmo) {
				case FIRST_FIT:
					endereco = first_fit(memoria_principal, processo);
					break;
				case BEST_FIT:
					endereco = best_fit(memoria_principal, processo);
					break;
				case WORST_FIT:
					endereco = worst_fit(memoria_principal, processo);
					break;
				default:
					fprintf(stderr, "Algoritmo inválido");
					exit(1);
					break;
			}
			if (endereco == NULL) {
				// Se não retornou um endereço, então não coube na memória.
				processo->estado = AGUARDANDO;
				falhas++;
			} else {
				// Insere o processo na memória e divide o que sobrar em outro segmento
				insere_divide(memoria_principal, endereco, processo, ciclo, falhas);
				fim = clock();
				total = ((double) (fim - inicio)) / CLOCKS_PER_SEC;				
				processo->tempo_aloc = total;				
			}
		}
		if (ocorreu_evento) {
			if (falhas > 0) {
				metricas_memoria(memoria_principal, falhas, ciclo, processos);
			}
			ocorreu_evento = 0;
		}
		ciclo++;
	}
	escreve_metricas(m_metricas, nome_arquivo);
	tempos = captura_metricas_tempo(processos, n);	
	destroi_metricas(m_metricas);
	// if (comando == 'c') {
	// 	imprime_memoria(memoria_principal, ciclo, processo);
	// 	switch(algoritmo) {
	// 		case FIRST_FIT:			
	// 			printf("Fim do algorítmo First Fit");
	// 			break;
	// 		case BEST_FIT:
	// 			printf("Fim do algorítmo Best Fit");
	// 			break;
	// 		case WORST_FIT:
	// 			printf("Fim do algorítmo Worst Fit");
	// 			break;
	// 		default:
	// 			fprintf(stderr, "Algoritmo inválido");
	// 			exit(1);
	// 			break;
	// 	}		
	// }
	return tempos;
}
int restam_execucoes(PROCESSO *processos) {
	for(PROCESSO *aux = processos; aux != NULL ; aux = aux->proximo){
		if (aux->ciclo_aloc == -1) {
			return 1;
		}
	}
	return 0;
}
void junta_lacunas_adjacentes(SEGMENTO* memoria_principal) {	
	SEGMENTO *junta, *proximo;
	for(SEGMENTO *aux = memoria_principal ; aux != NULL ; aux = aux->proximo){
		if (aux->ocupacao == LIVRE && (aux->proximo != NULL && aux->proximo->ocupacao == LIVRE)) {
			junta = aux;
			proximo = aux->proximo;
			junta->tamanho = junta->tamanho + proximo->tamanho;
			junta->proximo = proximo->proximo;
			aux = junta;
			free(proximo);
			ocorreu_evento = 1;
		}
	}
}
void imprime_memoria(SEGMENTO* memoria_principal, int ciclo, PROCESSO *processo) {	
	system("clear");	
	printf(ANSI_COLOR_RESET "Ciclo atual: %d\n", ciclo);
	if (processo == NULL) {
		printf(ANSI_COLOR_RESET "Nenhum processo neste ciclo\n");
	} else {
		printf(ANSI_COLOR_RESET "Processo %d - tamanho: %d\n", processo->pid, processo->tamanho);
	}	
	printf(ANSI_COLOR_RESET "==========================\n \t MEM \n==========================\n");	
	for(SEGMENTO *aux = memoria_principal; aux != NULL ; aux = aux->proximo){
		if (aux->ocupacao == LIVRE) {			
			printf(ANSI_COLOR_GREEN "\t T:%d \n\t LIVRE\n==========================\n", aux->tamanho);
		} else {
			printf(ANSI_COLOR_BLUE "\t T:%d \n\t P%d \n==========================\n", aux->tamanho, aux->ocupacao->pid);
		}
	}
	printf(ANSI_COLOR_RESET "Pressione [ENTER] para avançar o ciclo.\nPressione\"c\" seguido de [ENTER] para ir para o final:\n");
	comando = getchar();
}
PROCESSO* busca_processo_ciclo(PROCESSO *processos, int ciclo) {
	for(PROCESSO *aux = processos; aux != NULL ; aux = aux->proximo){
		if (aux->chegada <= ciclo){
			if (aux->estado == PRONTO) {
				return aux;
			} else if (aux->estado == AGUARDANDO) {
				aux->estado = PRONTO;				
				continue;
			}
		}		
	}
}
void desaloca_processo_ciclo(SEGMENTO *memoria_principal, int ciclo, int falhas) {	
	for(SEGMENTO *aux = memoria_principal ; aux != NULL ; aux = aux->proximo){
		if (aux->ocupacao != LIVRE && (aux->ocupacao->ciclo_aloc + aux->ocupacao->duracao) == ciclo) {
			if (comando != 'c') {
				imprime_memoria(memoria_principal, ciclo, aux->ocupacao);
			}
			aux->ocupacao = LIVRE;
			ocorreu_evento = 1;
		}
	}
}
SEGMENTO *first_fit(SEGMENTO *memoria_principal, PROCESSO* processo){
	SEGMENTO *aux;	
	for(aux = memoria_principal ; aux != NULL ; aux = aux->proximo){
		if (aux->tamanho >= processo->tamanho && aux->ocupacao == LIVRE) {			
			return aux;
		}
	}
	return NULL;
}
SEGMENTO *best_fit(SEGMENTO *memoria_principal, PROCESSO* processo){
	SEGMENTO *aux, *melhor = NULL;   
    for(aux = memoria_principal ; aux != NULL ; aux = aux->proximo){
    	if (aux->tamanho >= processo->tamanho && aux->ocupacao == LIVRE) {
    		melhor = aux;
    		break;
    	}
    }
    for(;aux != NULL ; aux = aux->proximo){
    	if (aux->tamanho >= processo->tamanho && aux->ocupacao == LIVRE) {
    		if(aux->tamanho < melhor->tamanho) {
    			melhor = aux;
    		}
    	}
    }
    return melhor;
}
SEGMENTO *worst_fit(SEGMENTO *memoria_principal, PROCESSO* processo){	
	SEGMENTO *aux, *melhor = NULL;
    for(aux = memoria_principal ; aux != NULL ; aux = aux->proximo){
    	if (aux->tamanho >= processo->tamanho && aux->ocupacao == LIVRE) {
    		melhor = aux;
    		break;
    	}
    }
    for(;aux != NULL ; aux = aux->proximo){
    	if (aux->tamanho >= processo->tamanho && aux->ocupacao == LIVRE) {
    		if(aux->tamanho > melhor->tamanho) {
    			melhor = aux;
    		}
    	}
    }
    return melhor;
}
void insere_divide(SEGMENTO *memoria_principal, SEGMENTO *endereco, PROCESSO *processo, int ciclo, int falhas) {	
	int resto_memoria = (endereco->tamanho - processo->tamanho);	
	processo->ciclo_aloc = ciclo;
	processo->estado = ALOCADO;

	endereco->ocupacao = processo;
	endereco->tamanho = processo->tamanho;
	ocorreu_evento = 1;
	if (resto_memoria > 0) {
		SEGMENTO *novo = malloc(sizeof(SEGMENTO));
		novo->tamanho = resto_memoria;
		novo->inicio = (endereco->inicio + processo->tamanho);
		novo->ocupacao = LIVRE;
		novo->anterior = endereco;
		if (endereco->proximo == NULL) {
			novo->proximo = NULL;
		} else {
			novo->proximo = endereco->proximo;
		}
		endereco->proximo = novo;
	}
	if (comando != 'c') {
		imprime_memoria(memoria_principal, ciclo, processo);
	}
}
int conta_buracos(SEGMENTO *memoria_principal) {
	int cont = 0;
	for (SEGMENTO* aux = memoria_principal ; aux != NULL ; aux = aux->proximo) {
		if (aux->ocupacao == LIVRE) {
			cont++;
		}
	}
	return cont;
}
float uso_memoria_atual(SEGMENTO *memoria_principal) {
	int uso_memoria = 0;	
	for (SEGMENTO *aux = memoria_principal ; aux != NULL ; aux = aux->proximo) {
		if (aux->ocupacao != LIVRE) {
			uso_memoria+= aux->tamanho;
		}
	}	
	return ((float)uso_memoria/(float)tam_mem_principal) * 100;
}
int conta_processos_aguardando(PROCESSO *processos) {
	int cont = 0;
	for (PROCESSO *aux = processos ; aux != NULL ; aux = aux->proximo) {
		if (aux->estado == AGUARDANDO) {
			cont++;
		}
	}
	return cont;
}
float calc_tam_medio_buracos(SEGMENTO *memoria_principal) {
	int tam_buracos = 0;	
	if (conta_buracos(memoria_principal) == 0) {
		return 0;
	}
	for (SEGMENTO *aux = memoria_principal ; aux != NULL ; aux = aux->proximo) {
		if (aux->ocupacao == LIVRE) {
			tam_buracos+= aux->tamanho;
		}
	}	
	return (float)tam_buracos/(float)conta_buracos(memoria_principal);
}

METRICAS** metricas_memoria(SEGMENTO *memoria_principal, int falhas, int ciclo, PROCESSO *processos) {
	METRICAS* nova_metrica = malloc(sizeof(METRICAS)), *aux;

	if (nova_metrica == NULL) {
		fprintf(stderr,"Falha ao alocar memória para métricas");
		exit(1);
	}

	nova_metrica->ciclo = ciclo;
	nova_metrica->n_buracos = conta_buracos(memoria_principal);
	nova_metrica->falhas = falhas;
	nova_metrica->n_proc_aguardando = conta_processos_aguardando(processos);
	nova_metrica->tam_medio_buracos = calc_tam_medio_buracos(memoria_principal);
	nova_metrica->uso_memoria = uso_memoria_atual(memoria_principal);
	nova_metrica->proximo = NULL;

	if (m_metricas[alg] == NULL) {
		m_metricas[alg] = nova_metrica;
		return m_metricas;
	}
	for (aux = m_metricas[alg] ; aux->proximo != NULL ; aux = aux->proximo) {}
	aux->proximo = nova_metrica;
	return m_metricas;
}