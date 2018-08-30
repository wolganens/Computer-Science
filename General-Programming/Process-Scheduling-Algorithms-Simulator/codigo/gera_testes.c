#include <stdio.h>
#include <string.h>
#include "random.c"

// Gera um arquivo com N processos
char* gera_teste(int n) {
	int i,chegada,duracao,tamanho;
	char* nome_arquivo = malloc(100*sizeof(char));
	char* buffer = malloc(50*sizeof(char));
	struct tm *sTm;
	time_t now = time (0);
	
	nome_arquivo[99] = '\0';
	nome_arquivo[49] = '\0';
    
    sTm = gmtime (&now);
	strftime (buffer, 20 * sizeof(char), "%Y-%m-%d %H:%M:%S", sTm);
	
	strcpy(nome_arquivo, "./testes/");
	strcat(nome_arquivo, buffer);
	free(buffer);
	
	FILE *arquivo_teste = fopen(nome_arquivo, "a");

	if (arquivo_teste == NULL) {
		fprintf(stderr, "Falha ao gerar arquivo de teste");
        exit(EXIT_FAILURE);
	}
	for ( i = 0 ; i < n ; i++) {
		//TEMPO	DE	EXECUÇÃO	entre	20	e	50	ciclos
		duracao = random_in_range(20, 51);
		//TAMANHO	entre	50	e	200KB
		tamanho = random_in_range(50, 201);
		chegada = random_in_range(0, n + 1);
		fprintf(arquivo_teste, "%d %d %d %d\n", i, chegada, duracao, tamanho);
	}
	fclose(arquivo_teste);
	return nome_arquivo;
}
