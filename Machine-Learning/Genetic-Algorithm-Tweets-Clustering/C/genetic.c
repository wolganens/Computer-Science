#include "genetic.h"
#include <omp.h>

float individual_fitness(int *membership_matrix, float *diss_matrix, int n_documents, int n_clusters) {
	int s, k, l, v;
	float fitness = 0.0;

	for (v = 0 ; v < n_clusters ; v++) {
		float pv = 0.0;
		for (s = 0 ; s < n_documents ; s++) {
			pv += (membership_matrix[s * n_clusters + v]);
		}
		if (pv == 0) {
			pv = 0.0001;
		}
		pv = pv / n_documents;
		float denominator = 2.0 * pv * n_documents;
		float temp = 0.0;		
		for (k = 0 ; k < n_documents ; k++) {
			for (l = 0 ; l < n_documents ; l++) {
				temp += ( membership_matrix[k * n_clusters + v] * membership_matrix[l * n_clusters + v] * diss_matrix[k * n_documents + l]);
			}
		}
		fitness += temp/denominator;
	}
	return fitness;
}
individual * new_population(individual *old_population, int n_documents, int pop_size, int n_clusters, float *diss_matrix) {
	int i = 0;	
	individual *population = malloc(pop_size * sizeof(individual));
	if (population == NULL) {
		printf("Falha ao alocar nova população\n");
		exit(-1);
	}
	omp_set_num_threads(8);
	#pragma omp parallel for	
	for (i = 0 ; i < (int) pop_size/2 ; i++) {
		individual parent_a = selection(old_population, 5, n_documents, pop_size);
		individual parent_b = selection(old_population, 5, n_documents, pop_size);
		individual *sons = crossover(&parent_a, &parent_b, n_documents, n_clusters);
		sons[0].fitness = individual_fitness(sons[0].membership_matrix, diss_matrix, n_documents, n_clusters);
		sons[1].fitness = individual_fitness(sons[1].membership_matrix, diss_matrix, n_documents, n_clusters);

		population[i] = sons[0];
		population[i + (int) pop_size/2] = sons[1];		
	}	
	#pragma omp barrier
	return population;
}
individual selection(individual *old_population, int sample_size, int n_documents, int pop_size) {
	int i, best = 99999, best_i, rand_index;
	/*Sorteia sample_size vezes o indice de um individuio da população
	e verifica se ele é o de menor fitness*/
	for (i = 0 ; i < sample_size ; i++) {

		rand_index = random_in_range(0, pop_size);

		if (old_population[rand_index].fitness < best) {
			best = old_population[rand_index].fitness;
			best_i = rand_index;
		}
	}

	return old_population[best_i];
}
individual * crossover(individual *parent_a, individual *parent_b, int n_documents, int n_clusters) {
	/*índice onde os indivíduos "pais" serão cortados para gerar os "filhos"*/
	unsigned int cutt_index_1 = random_in_range((int) n_documents * 0.1, (int) n_documents * 0.95);
	unsigned int cutt_index_2 = random_in_range((int) n_documents * 0.1, (int) n_documents * 0.95);
	unsigned int greater, lesser;
	if (cutt_index_1 >= cutt_index_2) {
		greater = cutt_index_1;
		lesser = cutt_index_2;
	} else {
		greater = cutt_index_2;
		lesser = cutt_index_1;
	}
	int i, j;
	/*Matriz de membership dos dois descendentes*/
	int * new_membership_matrix_a = calloc(n_documents * n_clusters, sizeof(int));
	if (new_membership_matrix_a == NULL) {
		printf("Falha ao alocar matriz A\n");
		exit(-1);
	}
	int * new_membership_matrix_b = calloc(n_documents * n_clusters, sizeof(int));
	if (new_membership_matrix_a == NULL) {
		printf("Falha ao alocar matriz B\n");
		exit(-1);
	}
	for (i = 0 ; i < lesser ; i++) {
		for (j = 0 ; j < n_clusters ; j ++) {
			new_membership_matrix_a[i * n_clusters + j] = parent_a->membership_matrix[i * n_clusters + j];
			new_membership_matrix_b[i * n_clusters + j] = parent_b->membership_matrix[i * n_clusters + j];
		}
	}
	for (i = lesser ; i < greater ; i++){

		for (j = 0 ; j < n_clusters ; j ++) {
			new_membership_matrix_a[i * n_clusters + j] = parent_b->membership_matrix[i * n_clusters + j];
			new_membership_matrix_b[i * n_clusters + j] = parent_a->membership_matrix[i * n_clusters + j];
		}

	}
	for (i = greater ; i < n_documents ; i++) {

		for (j = 0 ; j < n_clusters ; j ++) {
			new_membership_matrix_a[i * n_clusters + j] = parent_a->membership_matrix[i * n_clusters + j];
			new_membership_matrix_b[i * n_clusters + j] = parent_b->membership_matrix[i * n_clusters + j];
		}
	}
	individual * sons =malloc(2 * sizeof(individual));
	if (sons == NULL) {
		printf("Falha ao alocar memória para os descendentes\n");
		exit(-1);
	}
	sons[0].membership_matrix = new_membership_matrix_a;

	sons[1].membership_matrix = new_membership_matrix_b;
	sons[0] = mutation(sons[0], n_documents, n_clusters);
	sons[1] = mutation(sons[1], n_documents, n_clusters);
	return sons;
}
individual best_from_population(individual* population, int pop_size) {
	int i, best_i = 0;
	float best_fitness = 999999;
	for (i = 0 ; i < pop_size ; i++) {
		if (population[i].fitness < best_fitness) {
			best_fitness = population[i].fitness;
			best_i = i;
		}
	}
	return population[best_i];
}

individual worst_from_population(individual* population, int pop_size) {
	int i, worst_i = 0;
	float worst_fitness = 999999;
	for (i = 0 ; i < pop_size ; i++) {
		if (population[i].fitness < worst_fitness) {
			worst_fitness = population[i].fitness;
			worst_i = i;
		}
	}
	return population[worst_i];
}
individual mutation(individual ind, int n_documents, int n_clusters) {
	int i, j;
	for (i = 0 ; i < n_documents ; i++) {
		double mutation_rate = genrand64_real1();
		if (mutation_rate < 0.01) {

			int new_cluster_index = random_in_range(0, n_clusters);
			for (j  = 0 ; j < n_clusters ; j++) {
				if (ind.membership_matrix[i * n_clusters + j] == 1) {
					ind.membership_matrix[i * n_clusters + j] = 0;
				}
				if (j == new_cluster_index) {
					ind.membership_matrix[i * n_clusters + j] = 1;
				}
			}
		}
	}
	return ind;
}