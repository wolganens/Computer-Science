typedef int EVENTO;

#ifndef ALOCA
#define ALOCA 0
#endif

#ifndef FALHA
#define FALHA 1
#endif

#ifndef DESALOCA
#define DESALOCA 2
#endif

typedef struct _metricas {
	int ciclo, n_buracos, n_proc_aguardando, falhas;
	float tam_medio_buracos, uso_memoria;
	struct _metricas *proximo;
} METRICAS;

void registrar_evento(int ciclo, EVENTO tipo, PROCESSO *p, METRICAS* m, char* nome_arquivo);

int conta_buracos(SEGMENTO *memoria_principal);
float uso_memoria_atual(SEGMENTO *memoria_principal);
int conta_processos_aguardando(PROCESSO *processos);
float calc_tam_medio_buracos(SEGMENTO *memoria_principal);
METRICAS** metricas_memoria(SEGMENTO *memoria_principal, int falhas, int ciclo, PROCESSO *processos);

METRICAS** inicializa_metricas();
void escreve_arquivo(FILE* arquivo, METRICAS* m);