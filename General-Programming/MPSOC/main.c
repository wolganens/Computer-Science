#include "codigo/grafo.c"
#include <gtk/gtk.h>
#include <string.h>
#include <dirent.h>

#define FF 1

int main(int argc, char **argv) {	
	/*Variaveis para leitura e geração do grafo de aplicação*/
	int envia, recebe,conta_tarefas = 0;
	unsigned int origem, destino,i,j,x = 6,y = 6;
	vertice *orig, *dest;
	/*Todas as aplicações lidas da pasta passada por parâmetro ficam nessa lista abaixo(aplicacoes)*/
	grafo *aplicacoes = NULL;
	/*Variaveis de interface gráfica */
	GtkBuilder *builder;
	GtkWidget *window;	
	GtkWidget *paned;
	GtkWidget *button;
	GtkWidget *view_port;
	GtkWidget *list_box;

	gtk_init (&argc, &argv);

	
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "layout.glade", NULL);	
	window = (GtkWidget*) gtk_builder_get_object (builder, "window1");
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	paned = (GtkWidget*) gtk_builder_get_object (builder, "paned1");
	view_port = (GtkWidget*) gtk_builder_get_object (builder, "viewport1");
	list_box = (GtkWidget*) gtk_builder_get_object (builder, "listbox1");
	/*Caso tenha sido passado o tamanho da matriz por parâmetro...*/
	if (argv[2] != NULL && argv[3] != NULL) {		
		x = atoi(argv[2]);
		y = atoi(argv[3]);		
	}
	/*
	Este código comentado foi uma tentativa de utilizar o GRID do gtk para fazer a
	matriz do mpsoc na interface grafica*/
	// GtkWidget *mpsoc_grid = gtk_grid_new ();
	// gtk_grid_set_row_homogeneous ((GtkGrid*) mpsoc_grid, TRUE);
	// for (i = 0 ; i < x ; i++) {
	// 	gtk_grid_insert_row ((GtkGrid*) mpsoc_grid, i);
	// 	for (j = 0 ; j < y ; j++) {
	// 		gtk_grid_insert_row ((GtkGrid*) mpsoc_grid, j);
	// 		gtk_grid_attach ((GtkGrid*) mpsoc_grid, gtk_label_new ("EP"), j,i, 1, 1);
	// 	}
	// }
 	//    gtk_container_add (GTK_CONTAINER (view_port), mpsoc_grid);

 	/*Variáveis para leitura dos arquivos de teste*/
    char *dir = argv[1];
    char full_file[101];
    DIR *directory;
    struct dirent *file;
    FILE *entrada;
	full_file[100] = '\0';
	
	directory = opendir(dir);
    if(directory == NULL){
        fprintf(stderr, "Failed to open the directory: %s\n", dir);
        exit(EXIT_FAILURE);
    }
    while(1){
        file = readdir(directory);
        if(file == NULL)
            break;        
        if(strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
            continue;
 
        strcpy(full_file, dir);
        if(dir[strlen(dir) - 1] != '/')
            strcat(full_file, "/");
        strcat(full_file, file->d_name);        
 
        entrada = fopen(full_file, "r");
        if(entrada == NULL){
            fprintf(stderr, "Falha ao abrir arquivo: %s\n", file->d_name);
            exit(EXIT_FAILURE);        
        }
        aplicacoes = insere_grafo(aplicacoes, file->d_name);
        /*Para cada arquivo lido, gera um botão e adiciona ele no elemento listbox*/
        button = gtk_button_new_with_label (file->d_name);
        gtk_container_add (GTK_CONTAINER (list_box), button);  

        /*Le o conteúdo dos arquivos linha por linha e vai criando vertices e arestas
        de cada aplicação(arquivo)*/
        while(!feof(entrada)){	        
			fscanf(entrada, "%d[%d,%d%%,%d%%]\n", &origem, &destino, &envia, &recebe);			
			orig = insere_vertice(aplicacoes, origem);
			dest = insere_vertice(aplicacoes, destino);				
			orig->sucessores = cria_aresta(orig, dest, envia);
			dest->sucessores = cria_aresta(dest, orig, recebe);
		}       	
        fclose(entrada);
    }
    /*Exibe todos os componentes da interface gráfica*/
	gtk_widget_show_all (window);
	/*Inicia o loop da interface gráfica*/
	gtk_main ();

	/*Destroi todos os grafos das aplicações e suas tarefas(vértices)*/
	grafo* aux = aplicacoes;
	grafo* remove_aux;
	while (aux != NULL) {
		print_grafo(aux);
		destroi_grafo(aux);
		remove_aux = aux;
		aux = aux->proximo;
		free(remove_aux);
	}	

	return 0;
}