#include<stdio.h>
#include<pthread.h>

#define TAM 100
#define NTH 10

int vet[TAM];
int somatotal = 0;
pthread_mutex_t m;

void *func( void* in ) {
	long int *n = (long int*) in;
	int i, somalocal = 0;
	printf("%ld\n", *n);

	for( i = (TAM/NTH)* (*n) ; i < (TAM/NTH)*((*n)+1) ; i++) {
		somalocal += vet[i];
	}
	
	printf("%d\n", somalocal); 
	
	pthread_mutex_lock(&m);
	somatotal += somalocal;
	pthread_mutex_unlock(&m);
	
	return NULL;
}

int main (int argc, char **argv){
	int i, t; 
	int id;
	pthread_t thread[NTH];
	pthread_attr_t attr;

	for(i = 0; i < TAM; i++) {
		vet[i] = 1;
	}
	
	pthread_mutex_init(&m, NULL);
	
	for(t = 0; t < NTH; t++) {
		id = pthread_create(&thread[t],&attr, func, (void *) &t);
		if(id == 0)
			printf("Erro\n");
	}
	for(t = 0; t < NTH; t++) {
		id = pthread_join(thread[t], NULL);
	}
	
	pthread_mutex_destroy(&m);
	printf("Soma total = %d\n", somatotal);
}
