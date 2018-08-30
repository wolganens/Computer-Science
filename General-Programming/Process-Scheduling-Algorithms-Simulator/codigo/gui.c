void gui_init(){	
	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title ((GtkWindow *)window, "Simulador de Alocação de Memória");
	gtk_window_set_resizable ((GtkWindow *)window, 0);
	gtk_window_set_default_size ((GtkWindow *)window, 900, 1024);	
	gtk_widget_show_all (window);	
}