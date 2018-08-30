#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "random.c"
#include "individual.h"
#include "genetic.c"

#ifndef POP_SIZE
#define POP_SIZE 1024
#endif

#ifndef N_CLUSTERS
#define N_CLUSTERS 25
#endif

#ifndef N_DOCUMENTS
#define N_DOCUMENTS 251
#endif
#ifndef MAX_ITERATIONS
#define MAX_ITERATIONS 150
#endif

unsigned int iterations = 0;

float * get_dissimilarity_matrix() {
	float * dissim_matrix = malloc(N_DOCUMENTS * N_DOCUMENTS * sizeof(float));
	int i,j, test = 0;	
	/*Leitura do arquivo com os valores de dissimilaridade*/
	FILE* dissim_matrix_file = fopen("dissim_matrix.txt", "r");
	if (!dissim_matrix_file) {
		printf("Erro ao abrir arquivo da matriz de dissimilaridade\n");
		exit(-1);
	}
	/*Le cada valor de dissimilaridade do arquivo e armazena na matriz*/
	for (i = 0 ; i < N_DOCUMENTS ; i++) {
		for ( j = 0 ; j < N_DOCUMENTS ; j++) {
			test = fscanf(dissim_matrix_file, "%f", &(dissim_matrix[i * N_DOCUMENTS + j]));
		}
	}
	fclose(dissim_matrix_file);
	return dissim_matrix;
}

int main(int argc, char const *argv[])
{
	int i, j, k;
	unsigned int iterations = 0;
	float best_fitness = 9999;
	srand((unsigned int)time(NULL));
	float * dissim_matrix = get_dissimilarity_matrix();	
	
	individual *best_individual = malloc(sizeof(individual));
	best_individual->fitness = 0;
	best_individual->membership_matrix = calloc(N_DOCUMENTS * N_CLUSTERS, sizeof(int));
	individual *population = (malloc(POP_SIZE * sizeof(individual)));
	if (population == NULL) {
		printf("Falha ao alocar memória para a população inicial\n");
		exit(-1);
	}
	
	/*População inicial randomica*/
	for (i = 0 ; i < POP_SIZE ; i++) {
		/*Alocação de memória para a matriz de membership_matrix do individuo*/
		int * membership_matrix = calloc(N_DOCUMENTS * N_CLUSTERS, sizeof(int));
		if (membership_matrix == NULL) {
			printf("Falha ao alocar matriz 1\n");
			exit(-1);
		}

		for(j = 0; j < N_DOCUMENTS; j++) {		
			int document_cluster = random_in_range(0, N_CLUSTERS);			
			membership_matrix[j * N_CLUSTERS + document_cluster] = 1;
		}
		population[i].membership_matrix = membership_matrix;
		population[i].fitness = individual_fitness(membership_matrix, dissim_matrix, (int) N_DOCUMENTS, (int) N_CLUSTERS);
	}
	while (iterations < (int) MAX_ITERATIONS) {
		int worst_from_new_index = 0, best_from_old_index = 0, best_from_new_index = 0;
		float best_fitness_old = 9999, worst_fitness_new = 0;
		
		individual *old_population = population;
		/*for (i = 0 ; i < POP_SIZE ; i++) {
			for (j = 0 ; j < N_DOCUMENTS ; j++) {
				for (k = 0 ; k < N_CLUSTERS ; k++) {
					printf("%d ", population[i].membership_matrix[j * N_CLUSTERS + k]);
				}
				printf("\n");
			}
		}		*/
		population = new_population(old_population, (int) N_DOCUMENTS, (int) POP_SIZE, (int) N_CLUSTERS, dissim_matrix);
		
		for (i = 0 ; i < POP_SIZE ; i++) {
			/*Encontra o melhor indivíduo da antiga população, para substituí-lo pelo pior da nova*/
			if (old_population[i].fitness < best_fitness_old) {
				best_fitness_old = population[i].fitness;
				best_from_old_index = i;
			}
			/*Encontra o pior indivíduo da nova geração, para ser substituído pelo melhor da antiga*/
			if (population[i].fitness > worst_fitness_new){
				worst_fitness_new = population[i].fitness;
				worst_from_new_index = i;
			}
			if (population[i].fitness < best_fitness) {				
				best_fitness = population[i].fitness;
				best_from_new_index = i;
				iterations = 0;				
			}
		}
		/*Elitismo*/
		for (i = 0 ; i < N_DOCUMENTS * N_CLUSTERS; i++) {
			population[worst_from_new_index].membership_matrix[i] = old_population[best_from_old_index].membership_matrix[i];
		}		
		if (iterations == 0 && best_individual != NULL) {
			for (i = 0 ; i < N_DOCUMENTS * N_CLUSTERS; i++) {
				best_individual->membership_matrix[i] = population[best_from_new_index].membership_matrix[i];
			}
			best_individual->fitness = population[best_from_new_index].fitness;
		}
		population[worst_from_new_index].fitness = old_population[best_from_old_index].fitness;
		/*Libera a memória utilizada pela população antiga com excessão do melhor individuo, pois este
		precisa ser mantido já que foi copiado para a nova (elitismo)*/		
		for (i = 0 ; i < POP_SIZE ; i++) {			
			if (old_population[i].membership_matrix != NULL) {				
				free(old_population[i].membership_matrix);
				old_population[i].membership_matrix = NULL;
			}			
		}
		if (old_population != NULL) {					
			free(old_population);
			old_population = NULL;
		}
		printf("%f\n", best_fitness);
		iterations++;
	}
	FILE* output_file = fopen("solution.txt", "w");
	if (!output_file) {
		printf("Erro ao abrir arquivo de saída\n");
		exit(-1);
	}
	for (i = 0 ; i < N_DOCUMENTS ; i++) {
		for (j = 0 ; j < N_CLUSTERS ; j++) {
			fprintf(output_file, "%d ", best_individual->membership_matrix[i * N_CLUSTERS + j]);
		}
		fprintf(output_file, "\n");
	}
	fclose(output_file);
	free(best_individual->membership_matrix);
	free(best_individual);
	/*Libera a memória alocada para a população inicial*/
	/*for (i = 0 ; i < POP_SIZE ; i++) {
		if (population[i].membership_matrix != NULL) {
			free(population[i].membership_matrix);			
		}
		if (population != NULL){
			free(population);			
		}
	}*/
	if (dissim_matrix != NULL) {
		free(dissim_matrix);
	}
	return 0;	
}