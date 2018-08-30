#include <stdio.h>
#include <stdlib.h>

#include "grafo.c"
#include "queue.c"

void bfs(vertex *g) {
	int src_index, dest_index;
	node *start;
	printf("Digite o relacionamento que deseja procurar, formato id ENTER id>:\n");
	fflush(stdin);
	scanf("%d", &src_index);
	scanf("%d", &dest_index);
	
	queue *q = new_queue();
	q = push(q, src_index);	

	while(!is_empty(q)) {		
		start = pop(q);		
		/*printf("Inicio da fila: %d\n", q->start->index);*/
		if (start->index == dest_index) {
			printf("Objetivo alcançado\n");
			getchar();
			break;
		}
		edge *adjacents = get_adjacents(g, start->index);		
		while (adjacents != NULL) {
			if (!adjacents->dest->visited) {				
				q = push(q, adjacents->dest->index);
			}
			adjacents = adjacents->next;
		}
		set_visited(g, start->index);
	}

}

int main(int argc, char const *argv[])
{
	int src, dest, count = 0;
	
	vertex *g = NULL;
	FILE *entrada = fopen("grafo.txt", "r");
	/*Se não der pra abrir o arquivo*/
	if (entrada == NULL) {
		fprintf(stderr, "Falha ao gerar arquivo de teste\n");
        exit(EXIT_FAILURE);
	}

	do{
        fscanf(entrada, "%d %d", &src, &dest);
        count++;
        g = insere(g, src, dest);

	}while(!feof(entrada));	
	
	bfs(g);
	destroy_graph(g);
	return 0;
}
