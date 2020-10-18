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

	gint n = gtk_notebook_get_current_page(GTK_NOTEBOOK (tabs));
	const gchar *tab = gtk_notebook_get_tab_label_text(GTK_NOTEBOOK (tabs), gtk_notebook_get_nth_page(GTK_NOTEBOOK (tabs), n));
	if(tab == NULL)
		return;
	if(strcmp(tab, l.tabgroup) == 0) {
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
		
	tab1= gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	
	gtk_container_set_border_width(GTK_CONTAINER (tab1), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab2), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab3), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab4), 10);

	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab1, gtk_label_new("Disks"));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab2, gtk_label_new(l.tabgroup));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab3, gtk_label_new(l.tabuser));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab4, gtk_label_new("Empty"));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab5, gtk_label_new(l.tababout));
	
	g_signal_connect_after(G_OBJECT (tabs), "switch-page", G_CALLBACK(on_tabs_changed), NULL);
}


void scrolled() {
	
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_ALWAYS, GTK_POLICY_AUTOMATIC); 
	gtk_box_pack_start(GTK_BOX(box), scrolled_window, FALSE, TRUE, 0);
	gtk_scrolled_window_set_propagate_natural_height (GTK_SCROLLED_WINDOW(scrolled_window), TRUE);
	gtk_scrolled_window_set_propagate_natural_width (GTK_SCROLLED_WINDOW(scrolled_window), TRUE);
}

void main_combo() {
	combo_toplevel = gtk_combo_box_text_new();
		
	/* options*/
	gtk_widget_set_focus_on_click(combo_toplevel, TRUE);
	/* location */
	gtk_grid_attach(GTK_GRID (grid), GTK_WIDGET (combo_toplevel), 0, 0, 1, 1);
	/* signals */
	g_signal_connect (combo_toplevel, "changed", G_CALLBACK (on_toplevel_changed), NULL);

	/* add entries to the box */
	toplevel_entries();
}

void add_grid() {
	
	grid = gtk_grid_new();
	gtk_grid_insert_column(GTK_GRID(grid), 3);
	gtk_box_pack_start(GTK_BOX(tab1), grid, FALSE, TRUE, 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), FALSE);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 7);
	
	/*
	 * This grid has two entries.
	 * 1. a combo box that lets users chose whether to display
	 * an overview of all disks, or contents of a specific disk.
	 */
	main_combo();

	/* 2. A refresh button. */
	b = gtk_button_new_with_mnemonic(l.mrefresh);
	gtk_grid_attach(GTK_GRID (grid), GTK_WIDGET (b), 1, 0, 1, 1);
	g_signal_connect (b, "clicked", G_CALLBACK (redraw_cb), NULL);

}

void add_box() {
	
	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_container_add(GTK_CONTAINER (tab1), box);
	
	/* A window with scrollbars. */
	scrolled();
	
	GtkWidget *s1 = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	gtk_container_add(GTK_CONTAINER (box), s1);
	
}

void add_text() {
		
	textbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_add (GTK_CONTAINER (tab1), textbox);

	logwindow = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER (textbox), logwindow);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(logwindow), FALSE);
	//gtk_text_view_set_top_margin(GTK_TEXT_VIEW(logwindow), 10); 
	logs = gtk_text_view_get_buffer(GTK_TEXT_VIEW (logwindow));
	gtk_text_buffer_set_text(logs, "      ", 6);
}

int main(int argc, char *argv[]) {
	
	/* default settings */
	int lang = LANG_EN; /* default language */
	confirm=0;	/* ask for confirmation */
	if(fontsize[0] == '\0') /* initialize font size*/
		strncpy(fontsize, "12", 2);

	/* parse command line options */
	int opt;
	long fsize;
	
	while((opt = getopt(argc, argv, ":l:f:c")) != -1){
      switch(opt){
		 case 'c':
			confirm=1;
			break;
         case 'l':
			if (strncmp(optarg, "de", 2) == 0 )
				lang = LANG_DE;
			else if (strncmp(optarg, "en", 2) == 0 )
				lang = LANG_EN;
			break;
		case 'f':
			fsize = strtol(optarg, NULL, 0);
			if( (fsize<15) && (fsize>7) )
				sprintf(fontsize,"%ld", fsize);	
			else
				printf("invalid font size. Going back to default size.\n");
			break;
          }
	}
	/* set language */
	if(lang == LANG_DE)
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
	
	/* First tab - disks. It has three boxes. */
	add_grid();
	add_box();
	add_text();
	
	/* Populate the scrolled window once. */
	gtk_combo_box_set_active( GTK_COMBO_BOX (combo_toplevel), 0);
	
	/*  Let the user see everything. */
	gtk_widget_show_all(window);

	/* At last, add the editor. */
	editor();

	/* and go! */
	gtk_main();
	return EXIT_SUCCESS;
}
