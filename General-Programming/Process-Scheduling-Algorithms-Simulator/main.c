//#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "codigo/gera_testes.c"
#include "codigo/estruturas.c"
#include "codigo/algoritmos.c"

//#include "codigo/gui.c"

#ifndef N
#define N 100
#endif
// void on_janela_principal_destroy()
// {
//     gtk_main_quit();
// }

int main(int argc, char *argv[]) {
	if(argc != 2){
        fprintf(stderr, "Modo de utilização: %s <tamanho da memória>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
	srand(time(NULL));
	double *tempos;
	double t_espera[3], t_aloc[3];
	
	int tam_memoria = atoi(argv[1]), i, pid, chegada, duracao, tamanho;
	
	
	PROCESSO* processos = NULL;	
	SEGMENTO* mem_principal = malloc(sizeof(SEGMENTO));
	
	mem_principal->tamanho = tam_memoria;
	mem_principal->inicio = 0;
	mem_principal->ocupacao = LIVRE;
	mem_principal->proximo = NULL;
	mem_principal->anterior = NULL;
	
	//Gera um arquivo de teste com N processos	
	char* arquivo_teste = gera_teste(N);
	FILE *entrada = fopen(arquivo_teste, "r");
	if (entrada == NULL) {
		fprintf(stderr, "Falha ao gerar arquivo de teste");
        exit(EXIT_FAILURE);
	}	
	do{
        fscanf(entrada, "%d %d %d %d\n", &pid, &chegada, &duracao, &tamanho);        
        processos = insere_ordenado_chegada(processos,pid,chegada,duracao, tamanho);         
	}while(!feof(entrada));

	//First-Fit código = 0
	tempos = init(mem_principal, processos, tam_memoria, 0, arquivo_teste, N);
	t_espera[0] = tempos[0];
	t_aloc[0] = tempos[1];	
	reseta_processos(processos);
	reseta_memoria(mem_principal, tam_memoria);
	free(tempos);
	
	//Best-Fit código = 1
	tempos = init(mem_principal, processos, tam_memoria, 1, arquivo_teste, N);
	t_espera[1] = tempos[0];
	t_aloc[1] = tempos[1];
	reseta_processos(processos);
	reseta_memoria(mem_principal, tam_memoria);
	free(tempos);
	
	//Worst-Fit código = 2
	tempos = init(mem_principal, processos, tam_memoria, 2, arquivo_teste, N);	
	t_espera[2] = tempos[0];
	t_aloc[2] = tempos[1];
	destroi_lista_segmentos(mem_principal);
	destroi_lista_processos(processos);
	escreve_metricas_tempo(t_espera, t_aloc, arquivo_teste);
	free(tempos);
	fclose(entrada);
	free(arquivo_teste);
	return 0;
}