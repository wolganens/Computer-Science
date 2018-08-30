#include <stdio.h>

#ifndef FIRST_FIT
#define FIRST_FIT 0
#endif

#ifndef BEST_FIT
#define BEST_FIT 1
#endif

#ifndef WORST_FIT
#define WORST_FIT 2
#endif

int restam_execucoes(PROCESSO *processos);
void junta_lacunas_adjacentes(SEGMENTO* memoria_principal);
void desaloca_processo_ciclo(SEGMENTO *memoria_principal, int ciclo, int falhas);
PROCESSO* busca_processo_ciclo(PROCESSO *processos, int ciclo);
void imprime_memoria(SEGMENTO* memoria_principal, int ciclo, PROCESSO *processo);
SEGMENTO *first_fit(SEGMENTO *memoria_principal, PROCESSO* processo);
SEGMENTO *best_fit(SEGMENTO *memoria_principal, PROCESSO* processo);
SEGMENTO *worst_fit(SEGMENTO *memoria_principal, PROCESSO* processo);
double* init(SEGMENTO *memoria_principal, PROCESSO *processos, int tam_memoria, int algoritmo, char* caso_teste, int n);
void insere_divide(SEGMENTO *memoria_principal, SEGMENTO *endereco, PROCESSO *processo, int ciclo, int falhas);
