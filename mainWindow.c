/* includes and definitions */
#include "disk.h"

void top_window() {
	/* main window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Lazy Admin");
	gtk_widget_set_size_request (window, 800, 450); /* width, height */
	gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void on_tabs_changed(GtkMenuItem *item, gpointer user_data) {

	/* 
	 * Tabs changed. So redraw them.
	 */
	 
	gint n = gtk_notebook_get_current_page(GTK_NOTEBOOK (tabs));
	const gchar *tab = gtk_notebook_get_tab_label_text(GTK_NOTEBOOK (tabs), gtk_notebook_get_nth_page(GTK_NOTEBOOK (tabs), n));
	
	if(tab == NULL)
		return;
	else if(strcmp(tab, "Disks") == 0) {
		if(diskbox) {
			gtk_widget_destroy(diskbox);
			tree = NULL;
			tree1 = NULL;
		}
		disk();
	}

	else if(strcmp(tab, l.tabgroup) == 0) {
		if(groupbox)
			gtk_widget_destroy(groupbox);
		groups();
	}
	else if(strcmp(tab, l.tababout) == 0) {
		if(abox)
			gtk_widget_destroy(abox);
		about();
	}
	else if(strcmp(tab, l.tabuser) == 0) {
		if(userbox)
			gtk_widget_destroy(userbox);
		users();
	}
}

void add_tabs() {
	
	/* Add (empty) tabs to the main window. */
	
	tabs = gtk_notebook_new();
	gtk_notebook_set_show_border(GTK_NOTEBOOK (tabs), FALSE);
	gtk_container_add (GTK_CONTAINER (fixed), tabs);

	tab0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	//tab4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	
	gtk_container_set_border_width(GTK_CONTAINER (tab1), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab2), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab3), 10);
	//gtk_container_set_border_width(GTK_CONTAINER (tab4), 10);

	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab0, gtk_label_new("Control"));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab1, gtk_label_new("Disks"));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab2, gtk_label_new(l.tabgroup));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab3, gtk_label_new(l.tabuser));
	//gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab4, gtk_label_new("Empty"));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab5, gtk_label_new(l.tababout));
	
	g_signal_connect_after(G_OBJECT (tabs), "switch-page", G_CALLBACK(on_tabs_changed), NULL);
}

int main(int argc, char *argv[]) {
	
	/* default options */
	opt.language = LANG_EN;
	opt.confirm=FALSE;
	if(opt.fontsize[0] == '\0')
		strncpy(opt.fontsize, "12", 2);

	/* parse command line options */
	int options;
	long fsize;
	
	while((options = getopt(argc, argv, ":l:f:c")) != -1){
      switch(options){
		 case 'c':
			opt.confirm=TRUE;
			break;
         case 'l':
			if (strncmp(optarg, "de", 2) == 0 )
				opt.language = LANG_DE;
			else if (strncmp(optarg, "en", 2) == 0 )
				opt.language = LANG_EN;
			break;
		case 'f':
			fsize = strtol(optarg, NULL, 0);
			if( (fsize<15) && (fsize>7) )
				sprintf(opt.fontsize,"%ld", fsize);
			else
				printf("invalid font size. Going back to default size.\n");
			break;
          }
	}

	/* setup language strings */
	if(opt.language == LANG_DE)
		de_lang();
	else
		en_lang();

	/* gtk */
	gtk_init(&argc, &argv);

	/* disable annoying bell */
	g_object_set(gtk_settings_get_default(), "gtk-error-bell", FALSE, NULL);


	/*
	 * Here we draw the main window.
	 * The main window contains a box. 
	 */
	top_window();
	fixed = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add (GTK_CONTAINER (window), fixed);

	/* The box has a menu bar, and Tabs: */
	add_menubar();
	add_tabs();
	
	/*  Let the user see everything. */
	gtk_widget_show_all(window);

	/* and go! */
	gtk_main();
	return EXIT_SUCCESS;
}
