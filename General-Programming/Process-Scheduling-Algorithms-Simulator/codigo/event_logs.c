#include "event_logs.h"
#include <unistd.h>
#include "gnuplot_i.c"

void escreve_metricas(METRICAS** m_metricas, char* nome_arquivo) {
	gnuplot_ctrl * h;
	h = gnuplot_init();
	gnuplot_cmd(h, "set term pngcairo size 1288,768");
	gnuplot_cmd(h, "set decimalsign \".\"");
	gnuplot_cmd(h, "set size ratio -1");
	gnuplot_cmd(h, "set style fill solid border -1");	
	gnuplot_cmd(h, "set xrange [0:*]");	
	char arquivo_log_str[100];
	char log_ff[150], log_bf[150], log_wf[150], saida_grafico[100], comando_plot[300];
	int i;
	arquivo_log_str[149] = '\0';
	strcpy(arquivo_log_str, nome_arquivo);

	strcpy(log_ff, arquivo_log_str);
	strcat(log_ff, "-FF.log");

	strcpy(log_bf, arquivo_log_str);
	strcat(log_bf, "-BF.log");

	strcpy(log_wf, arquivo_log_str);
	strcat(log_wf, "-WF.log");
	
	METRICAS *aux = m_metricas[0];
	FILE* arquivo_log_ff = fopen(log_ff, "a");
	if (arquivo_log_ff == NULL) {
		fprintf(stderr, "\nImpossível abrir arquivo de log\n");
	}
	escreve_arquivo(arquivo_log_ff, aux);
	fclose(arquivo_log_ff);
	
	aux = m_metricas[1];
	FILE* arquivo_log_bf = fopen(log_bf, "a");
	if (arquivo_log_bf == NULL) {
		fprintf(stderr, "\nImpossível abrir arquivo de log\n");
	}
	escreve_arquivo(arquivo_log_bf, aux);
	fclose(arquivo_log_bf);
	
	aux = m_metricas[2];
	FILE* arquivo_log_wf = fopen(log_wf, "a");
	if (arquivo_log_wf == NULL) {
		fprintf(stderr, "\nImpossível abrir arquivo de log\n");
	}
	escreve_arquivo(arquivo_log_wf, aux);
	fclose(arquivo_log_wf);
		
	sprintf(saida_grafico, "set output \"%s%s\"", arquivo_log_str, "-USO-MEM.png");
	
	gnuplot_cmd(h, saida_grafico);	
	gnuplot_cmd(h, "set title \"Ocupacao da Memoria\"");
	gnuplot_cmd(h, "set ylabel \"%% de Ocupacao\"");
	gnuplot_cmd(h, "set xlabel \"Ciclos de Execucao\"");	
	
	sprintf(comando_plot, "plot \"%s\" using 1:3 w l smooth acspline lc \"red\" title \"FF\",  \"%s\" using 1:3 w l smooth acspline lc \"green\" title \"BF\",  \"%s\" using 1:3 w l smooth acspline lc \"blue\" title \"WF\"", log_ff,log_bf,log_wf);

	gnuplot_cmd(h, comando_plot);	
	sprintf(saida_grafico, "set output \"%s%s\"", arquivo_log_str, "-P-AGUARD.png");

	gnuplot_cmd(h, saida_grafico);

	gnuplot_cmd(h, "set title \"Número de Processos Aguardando\"");
	gnuplot_cmd(h, "set ylabel \"# Processos Aguardando\"");
	gnuplot_cmd(h, "set boxwidth 3.5");
	
	sprintf(comando_plot, "plot \"%s\" using 1:4 w boxes lc \"red\" title \"FF\",  \"%s\" using 1:4 w boxes lc \"green\" title \"BF\",  \"%s\" using 1:4 w boxes lc \"blue\" title \"WF\"", log_ff,log_bf,log_wf);

	gnuplot_cmd(h, comando_plot);
	gnuplot_cmd(h, "set size ratio 1 -1");
	sprintf(saida_grafico, "set output \"%s%s\"", arquivo_log_str, "-BURACOS.png");
	gnuplot_cmd(h, saida_grafico);	
	gnuplot_cmd(h, "set title \"Número Médio de Lacunas\"");
	gnuplot_cmd(h, "set ylabel \"# Lacunas\"");	
	gnuplot_cmd(h, "set style fill solid border -1");	
	gnuplot_cmd(h, "set xrange [0:*]");
	
	sprintf(comando_plot, "plot \"%s\" using 1:2 w boxes  lc \"red\" title \"FF\",  \"%s\" using 1:2 w boxes  lc \"green\" title \"BF\",  \"%s\" using 1:2 w boxes lc \"blue\" title \"WF\"", log_ff,log_bf,log_wf);

	gnuplot_cmd(h, comando_plot);
	gnuplot_cmd(h, "set size ratio 1 -1");
	sprintf(saida_grafico, "set output \"%s%s\"", arquivo_log_str, "-FALHAS.png");
	gnuplot_cmd(h, saida_grafico);	
	gnuplot_cmd(h, "set title \"Número de Falhas\"");
	gnuplot_cmd(h, "set ylabel \"# Falhas\"");	
	
	sprintf(comando_plot, "plot \"%s\" using 1:5 w l lw 2 lc \"red\" title \"FF\",  \"%s\" using 1:5 w l lw 2 lc \"green\" title \"BF\",  \"%s\" using 1:5 w l lw 2 lc \"blue\" title \"WF\"", log_ff,log_bf,log_wf);

	gnuplot_cmd(h, comando_plot);

	sprintf(saida_grafico, "set output \"%s%s\"", arquivo_log_str, "-TAM-BURACOS.png");	
	gnuplot_cmd(h, saida_grafico);	
	gnuplot_cmd(h, "set title \"Tamanho Médio das Lacunas\"");
	gnuplot_cmd(h, "set ylabel \"Tam Médio\"");	
	
	sprintf(comando_plot, "plot \"%s\" using 1:6 w l smooth acspline lc \"red\" title \"FF\",  \"%s\" using 1:6 w l smooth acspline lc \"green\" title \"BF\",  \"%s\" using 1:6 w l smooth acspline lc \"blue\" title \"WF\"", log_ff,log_bf,log_wf);

	gnuplot_cmd(h, comando_plot);

	gnuplot_close(h) ;
	
}
void escreve_arquivo(FILE* arquivo, METRICAS* m) {
	/*
	Escreve no arquivo de log:
	int Ciclo
	EVENTO tipo de evento(ver event_logs.h), 
	int id do processo envolvido no evento, 	
	int n_buracos, uso_memoria, n_proc_aguardando, falhas;
	float tam_medio_buracos;
	*/	
	while(m != NULL) {		
		fprintf(arquivo, "%d\t%d\t%.2f\t%d\t%d\t%.2f\n", 
			m->ciclo,				
			m->n_buracos,
			m->uso_memoria,
			m->n_proc_aguardando,
			m->falhas,
			m->tam_medio_buracos
		);		
		m = m->proximo;
	}
}
double* captura_metricas_tempo(PROCESSO* processos, int n) {
	int t_total_espera = 0;
	double t_total_aloc = 0;
	double *tempos = malloc(2 * sizeof(double));
	for (PROCESSO *aux = processos ; aux != NULL ; aux = aux->proximo) {
		t_total_espera+= (aux->ciclo_aloc - aux->chegada);
		t_total_aloc+= aux->tempo_aloc;	
	}
	tempos[0] = (double) t_total_espera / n;
	tempos[1] = t_total_aloc / n;	
	return tempos;
}
void escreve_metricas_tempo(double* t_espera, double* t_aloc, char* nome_arquivo) {
	gnuplot_ctrl * h;
	h = gnuplot_init();
	gnuplot_cmd(h, "set term pngcairo size 1288,768");
	gnuplot_cmd(h, "set decimalsign \".\"");
	gnuplot_cmd(h, "set size square");
	gnuplot_cmd(h, "set style fill solid border -1");	
	gnuplot_cmd(h, "set xrange [0:*]");

	char saida_grafico[150], comando_plot[300], log_file[150];	
	sprintf(log_file, "%s-T_ESPERA.log", nome_arquivo);
	FILE* t_log_file = fopen(log_file, "a");
	
	fprintf(t_log_file, "0 FF %.2f\n", t_espera[0]);
	fprintf(t_log_file, "1 BF %.2f\n", t_espera[1]);
	fprintf(t_log_file, "2 WF %.2f\n", t_espera[2]);

	fclose(t_log_file);
	
	sprintf(saida_grafico, "set output \"%s%s\"", nome_arquivo, "-T_ESPERA.png");
	gnuplot_cmd(h, saida_grafico);
	gnuplot_cmd(h, "set style line 1 lc \"red\"");
	gnuplot_cmd(h, "set style line 2 lc \"green\"");
	gnuplot_cmd(h, "set style line 3 lc \"blue\"");
	gnuplot_cmd(h, "set style fill solid");
	gnuplot_cmd(h, "set boxwidth 0.9 ");
	gnuplot_cmd(h, "set title \"Tempo Médio de Espera para Alocação\"");
	gnuplot_cmd(h, "set ylabel \"Tempo Médio\"");	
	sprintf(comando_plot, "plot \"%s\" every ::0::0 using 1:3:xtic(2) with boxes ls 1 title \"FF\", \"%s\" every ::1::1 using 1:3:xtic(2) with boxes ls 2 title \"BF\", \"%s\" every ::2::2 using 1:3:xtic(2) with boxes ls 3 title \"WF\"", log_file, log_file,log_file);
	gnuplot_cmd(h, comando_plot);

	gnuplot_close(h) ;
	gnuplot_cmd(h, saida_grafico);
	
	
	sprintf(log_file, "%s-T_MED_ALOC.log", nome_arquivo);

	t_log_file = fopen(log_file, "a");
	
	fprintf(t_log_file, "FF %f\n", t_aloc[0]);
	fprintf(t_log_file, "BF %f\n", t_aloc[1]);
	fprintf(t_log_file, "WF %f\n", t_aloc[2]);

	fclose(t_log_file);
	

}
METRICAS** inicializa_metricas() {
	int i = 0;
	METRICAS** m = malloc(3 * sizeof(METRICAS));
	for ( i = 0 ; i < 3 ; i++) {
		m[i] = NULL;
	}
	return m;
}
void destroi_metricas(METRICAS** m_metricas) {
	int i;	
	METRICAS* prox = NULL;
	METRICAS* aux = NULL;
	for ( i = 0 ; i < 3 ; i++) {
		aux = m_metricas[i];
		prox = NULL;
		while(aux != NULL) {
			prox = aux->proximo;		
			free(aux);
			aux = prox;
		}
	}
	free(m_metricas);
}