float individual_fitness(int *membership_matrix, float *diss_matrix, int n_documents, int n_clusters);
individual * new_population(individual *old_population, int n_documents, int pop_size, int n_clusters, float *diss_matrix);
individual selection(individual *old_population, int sample_size, int n_documents, int pop_size);
individual best_from_population(individual* population, int pop_size);
individual worst_from_population(individual* population, int pop_size);
individual * crossover(individual *parent_a, individual *parent_b, int n_documents, int n_clusters);
individual mutation(individual ind, int n_documents, int n_clusters);