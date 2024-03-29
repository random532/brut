/* Main window  */
#include "brut.h"

/* Functions */

void add_menubox();
void add_log(GtkWidget *);
void add_tabs();
GtkWidget *back_button();
void back_clicked(GtkWidget *, gpointer);
void on_tabs_changed(GtkMenuItem *, gpointer);
void top_window();
// int main(int argc, char *);


void top_window() {
	/* main window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Brut - Control Panel");
	gtk_widget_set_size_request (window, 800, 500); /* width, height */
	gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void on_tabs_changed(GtkMenuItem *item, gpointer user_data) {

	/* Redraw current tab. */

	gint n = gtk_notebook_get_current_page(GTK_NOTEBOOK (tabs));
	const gchar *tab = gtk_notebook_get_tab_label_text(GTK_NOTEBOOK (tabs), gtk_notebook_get_nth_page(GTK_NOTEBOOK (tabs), n));
	
	if(tab == NULL)
		return;

	/* Show or hide the "back" button. */
	if(strcmp(tab, l.tabcontrol) == 0)
		gtk_widget_hide(bback);
	else
		gtk_widget_show(bback);

	/* Draw the changed tab. */
	if(strcmp(tab, l.tabcontrol) == 0)
		control();
	else if(strcmp(tab, l.tabdisks) == 0)
		disk();
	else if(strcmp(tab, l.tabgroup) == 0)
		groups();
	else if(strcmp(tab, l.tababout) == 0)
		about();
	else if(strcmp(tab, l.tabuser) == 0)
		users();
	else if(strcmp(tab, l.tabtime) == 0)
		timetab();
	else if(strcmp(tab, l.tabtasks) == 0)
		tasks();
	else if(strcmp(tab, l.tabconfig) == 0)
		config();
	else if(strcmp(tab, l.tabdevices) == 0)
		devices();
	else if(strcmp(tab, l.tabwlan) == 0)
		wireless();
	else if(strcmp(tab, l.tabaudio) == 0)
		audio();
	else if(strcmp(tab, l.tablan) == 0)
		lan();
	else if(strcmp(tab, l.tabdmesg) == 0)
		dmesg();


	/* Clear log info. */
	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW (logwindow)), "      ", 6);
}

void add_tabs() {
	
	/* 
	 * Add tabs to the main window. 
	 * The tabs are empty for now.
	 */
	
	tabs = gtk_notebook_new();

	gtk_notebook_set_show_border(GTK_NOTEBOOK (tabs), FALSE);
	gtk_notebook_set_show_tabs(GTK_NOTEBOOK (tabs), FALSE);
	gtk_notebook_set_scrollable(GTK_NOTEBOOK (tabs), TRUE);

	gtk_container_add (GTK_CONTAINER (fixed), tabs);

	tab0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab6 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab7 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab8 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab9 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab10 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab11 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	tab12 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

	gtk_container_set_border_width(GTK_CONTAINER (tab1), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab2), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab3), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab4), 10);
//	gtk_container_set_border_width(GTK_CONTAINER (tab5), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab6), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab7), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab8), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab9), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab10), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab11), 10);
	gtk_container_set_border_width(GTK_CONTAINER (tab12), 10);

	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab0, gtk_label_new(l.tabcontrol));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab1, gtk_label_new(l.tabdisks));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab3, gtk_label_new(l.tabuser));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab2, gtk_label_new(l.tabgroup));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab4, gtk_label_new(l.tabtime));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab5, gtk_label_new(l.tababout));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab6, gtk_label_new(l.tabtasks));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab7, gtk_label_new(l.tabconfig));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab8, gtk_label_new(l.tabdevices));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab9, gtk_label_new(l.tabwlan));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab10, gtk_label_new(l.tablan));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab11, gtk_label_new(l.tabaudio));
	gtk_notebook_append_page(GTK_NOTEBOOK (tabs), tab12, gtk_label_new(l.tabdmesg));

	g_signal_connect_after(G_OBJECT (tabs), "switch-page", G_CALLBACK(on_tabs_changed), NULL);
}

void add_log(GtkWidget *t) {
		
	/* 
	 * Some debug info text at the bottom of a tab.
	 */

	GtkWidget *textbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	logwindow = gtk_text_view_new();
	
	gtk_container_add (GTK_CONTAINER (t), textbox);
	gtk_container_add(GTK_CONTAINER (textbox), logwindow);
	
	gtk_text_view_set_editable(GTK_TEXT_VIEW(logwindow), FALSE);
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER (gtk_text_view_get_buffer(GTK_TEXT_VIEW(logwindow))), "      ", 6);
}

void back_clicked(GtkWidget *b, gpointer p) {
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 0);
}

GtkWidget *back_button() {

//	GtkWidget *image = gtk_image_new_from_file("image.jpg");
//	GtkWidget *button = gtk_button_new();
//	gtk_button_set_image(GTK_BUTTON (button), image);
	GtkWidget *button = gtk_button_new_with_label(l.mback);
	gtk_container_add (GTK_CONTAINER (menubox), button);
	g_signal_connect(button, "clicked", G_CALLBACK(back_clicked), NULL);
	return button;
}

void add_menubox() {
	
	/* 
	 * Menu box has two (horizontal) items. 
	 * A menubar, and a "back" button.
	 */

	menubox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 50);
	gtk_box_pack_start(GTK_BOX(fixed), menubox, FALSE, TRUE, 0);
	gtk_box_reorder_child(GTK_BOX(fixed), menubox, 0);

	add_menubar();

	bback = back_button();

	gtk_widget_show_all(menubox);
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

	/* The box contains 3 items:
	 * a menu bar, Tabs (aka GtkNotebook), and a debug info.
	 */
	add_menubox();
	add_tabs();
	add_log(fixed);

	/*  Let the user see everything. */
	gtk_widget_show_all(window);
	gtk_widget_hide(bback);

	/* and go! */
	gtk_main();
	return EXIT_SUCCESS;
}

void update_view() {

	/* 
	 * Restore the GUI elements. 
	 */

	gint n = gtk_notebook_get_current_page(GTK_NOTEBOOK (tabs));
	const gchar *tab = gtk_notebook_get_tab_label_text(GTK_NOTEBOOK (tabs), gtk_notebook_get_nth_page(GTK_NOTEBOOK (tabs), n));

	if(strcmp(tab, l.tabdisks) == 0) {
		redraw_disks();
	}
		
	else if(strcmp(tab, l.tabgroup) == 0) {
		gtk_widget_destroy(groupbox);
		groups();
	}

	else if(strcmp(tab, l.tabuser) == 0) {
		gtk_widget_destroy(userbox);
		users();
	}

	else if(strcmp(tab, l.tabconfig) == 0) {
		gtk_widget_destroy(configbox);
		config();
	}
	else if(strcmp(tab, l.tabdevices) == 0) {
		gtk_widget_destroy(devbox);
		devices();
	}
	else if(strcmp(tab, l.tabwlan) == 0) {
		AfterRootCmd();
	}
	else if(strcmp(tab, l.tabdmesg) == 0) {
		gtk_widget_destroy(dmesgbox);
		dmesg();
	}

	else
		printf("redraw nothing?!\n");
}
