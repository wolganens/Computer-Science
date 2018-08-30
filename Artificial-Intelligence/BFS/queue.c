#include "queue.h"
#include <stdlib.h>

queue *new_queue() {
	queue *q = malloc(sizeof(queue));
	q->start = NULL;
	q->end = NULL;
	return q;
}

node *new_node(int index) {
	node *n = malloc(sizeof(node));
	n->index = index;
	n->next = NULL;
	return n;
}

node* pop(queue *q) {	
	node *aux = q->start;
	if (is_empty(q)) {		
		printf("Fila vazia\n");
		exit(1);
	}
	/*Se o inicio e o fim da fila apontam para o mesmo nó,
	então há apenas um elemento na fila*/	
	if (q->start == q->end) {		
		q->start = q->end = NULL;
	} else {
		q->start = q->start->next;	
	}	
	return aux;
}

queue* push(queue *q, int index) {
	/*Se a fila está vazia, o inicio e o fim apontam para o novo nó*/
	node *n = malloc(sizeof(node));
	n->index = index;
	n->next = NULL;

	if (is_empty(q)) {
		q->start = n;		
	} else {
		q->end->next = n;
	}
	q->end = n;
	return q;
}

int is_empty(queue *q)  {	
	return q->start == NULL && q->end == NULL;
}