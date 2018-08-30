typedef struct _vertex {
	unsigned int index;
	unsigned int visited;
	struct _vertex* next;
	struct _edge* edges;
} vertex;

typedef struct _edge {
	vertex* dest;
	struct _edge* next;
} edge;

vertex* insere(vertex *g, int sourc_index, int dest_index);
vertex* new_vertex(int index);
vertex* find_vertex_by_index(vertex* g, int index);
vertex* add_vertex(vertex* list, vertex* dest);

edge *add_edge(edge* list, vertex* dest);
edge *new_edge(vertex* dest);

edge *get_adjacents(vertex *g, int index);
void destroy_graph(vertex* g);
void print_graph(vertex* g);
void set_visited(vertex* g, int index);