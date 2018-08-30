typedef struct _node {
	int index;
	struct _node *next;
} node;

typedef struct _queue {
	node *start;
	node *end;
} queue;

queue *new_queue();
queue* push(queue *q, int index);

node *new_node(int index);
node* pop(queue *q);
int is_empty(queue *q);


