#include <stdio.h>
#include "random.c"

typedef struct _bloco {
	int tam,tam_proc,pid;
} BLOCO;

void ff(BLOCO* memoria, int tam_processo, int pid){
	unsigned int i;
	for (i = 0 ; i < 10 ; i++) {
		if (memoria[i].tam >= tam_processo && memoria[i].pid == -1) {
			memoria[i].pid = pid;
			memoria[i].tam_proc = tam_processo;
			break;
		}
	}
}
void bf(BLOCO* memoria, int tam_processo, int pid){
	int m_pid = -1, m_tam, i;
	for (i = 0 ; i < 10 ; i++) {
		if (memoria[i].tam >= tam_processo && memoria[i].pid == -1) {
			m_pid = pid;
			m_tam = memoria[i].tam;
			break;
		}
	}
	for (; i < 10 ; i++) {
		if (memoria[i].tam >= tam_processo && memoria[i].pid == -1 && memoria[i].tam < m_tam) {
			m_pid = pid;
			m_tam = memoria[i].tam;
		}
	}
	if (m_pid == -1) {
		printf("Não há espaço para alocar o processo\n");
		return;
	}
	memoria[i].pid = pid;
	memoria[i].tam_proc = tam_processo;
}
void wf(BLOCO* memoria, int tam_processo, int pid){
	int m_pid, m_tam, i;
	for (i = 0 ; i < 10 ; i++) {
		if (memoria[i].tam >= tam_processo && memoria[i].pid == -1) {
			m_pid = pid;
			m_tam = memoria[i].tam;
			break;
		}
	}
	for (; i < 10 ; i++) {
		if (memoria[i].tam >= tam_processo && memoria[i].pid == -1 && memoria[i].tam > m_tam) {
			m_pid = pid;
			m_tam = memoria[i].tam;
		}
	}
	if (m_pid == -1) {
		printf("Não há espaço para alocar o processo\n");
		return;
	}
	memoria[i].pid = pid;
	memoria[i].tam_proc = tam_processo;
}
int main(int argc, char const *argv[]){
	BLOCO memoria[10];
	int pid = 0, tam_processo,i;
	char algoritmo;
	srand(time(NULL));

	printf("Insira o algoritmo desejado: (f)irst fit, (b)est fit ou (w)orst fit\n");
	algoritmo = getchar();

	for (i = 0 ; i < 10 ; i++){
		BLOCO novo;		
		novo.tam = random_in_range(100,801);
		novo.tam_proc = 0;
		novo.pid = -1;
		memoria[i] = novo; 
	}
	while(1){
		printf("Insira o tamanho do processo %d\n", pid);
		scanf("%d", &tam_processo);
		if(tam_processo == 0) {
			break;
		}
		switch(algoritmo){
			case 'f':
				ff(memoria, tam_processo, pid);
				break;
			case 'b':
				bf(memoria, tam_processo, pid);
				break;
			case 'w':
				wf(memoria, tam_processo, pid);
				break;
			default:
				printf("Algoritmo inválido!\n");
				exit(1);
		}		
		pid++;
	}
	printf("Blocos:\n");	
	for ( i = 0 ; i < 10 ; i++) {
		printf("Tamanho do bloco = %d - PID: %d tam: %d\n", memoria[i].tam, memoria[i].pid, memoria[i].tam_proc);
	}
	return 0;
}
