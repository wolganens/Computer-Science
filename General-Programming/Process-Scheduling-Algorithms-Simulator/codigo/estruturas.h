#ifndef LIVRE
#define LIVRE NULL
#endif

#ifndef AGUARDANDO
#define AGUARDANDO 2
#endif

#ifndef PRONTO
#define PRONTO 1
#endif

#ifndef ALOCADO
#define ALOCADO 4
#endif

typedef int ENDERECO;

typedef struct _processo {
	int pid, tamanho, chegada, duracao, estado, ciclo_aloc;
	double tempo_aloc;
	struct _processo *proximo;
} PROCESSO;

typedef struct _segmento {
	PROCESSO* ocupacao;
	int tamanho, inicio;
	struct _segmento* proximo, *anterior;
} SEGMENTO;
