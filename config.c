/* Config files tab */
#include "disk.h"

GtkWidget *fc;			/* File choser combo box */
GtkWidget *bt;			/* Save button */
GtkTextBuffer *textbuf;


void save_cb (GtkMenuItem *item, gpointer user_data) {  

	char *cmd;
	char *filename;
	gchar *text;
	int len;
	GtkTextIter start;
	GtkTextIter end;
	
//	gint len;

	/* file location */
	filename = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (fc));
	if(filename == NULL)
		return;

	/* File contents */	
	gtk_text_buffer_get_bounds(textbuf, &start, &end);
	text = gtk_text_buffer_get_text(textbuf, &start, &end, FALSE);

	/*
	 * Save the file.
	 * Since the sudo backend doesn't like multiple pipes,
	 * we just use a tempfile..
	 */
	
	len = strlen(text) + strlen(filename) + 20;
	if(len <= 0) {
		msg("config.c: error in strlen.");
		return;
	}

	cmd = malloc(len);
	if(cmd == NULL) {
		free(text);
		return;
	}

	/* temporary save the file. */
	char *r = random_filename();
	sprintf(cmd, "echo \"%s\" > %s", text, r);
	submit(cmd, 0);

	/* Move the copy. */
	sprintf(cmd, "mv %s %s", r, filename);

	execute_me(cmd, USR);
	free(r);
	free(text);
	return;
}

void fc_entries(GtkWidget *fc) {

	/* cleanup */
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(fc));

	/* System files */
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (fc), NULL, "/boot/loader.conf");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (fc), NULL, "/etc/devd.conf");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (fc), NULL, "/etc/fstab");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (fc), NULL, "/etc/rc.conf");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (fc), NULL, "/etc/sysctl.conf");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (fc), NULL, "/etc/wpa_supplicant.conf");
}

void show( char *filename) {

	/* Show the selected file in the textview. */

	char cmd[CMDSIZE];
	char *content;

	snprintf(cmd, CMDSIZE, "cat %s", filename);
	content = command(cmd);
	if(content == NULL) {
		msg("File not found, or no read access on it.");
		return;
	}
	
	gtk_text_buffer_set_text(textbuf, content, strlen(content));
	gtk_widget_show_all(configbox);
}

void fc_changed(GtkMenuItem *item, gpointer user_data) {

//	if(GTK_IS_TEXT_BUFFER(textbuf))
//		free(textbuf);

	char *filename;
	filename = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (item));
	if(filename == NULL)
		return;
	else
		show(filename);
}

void files_combo(GtkWidget *g) {

	/* 
	 * A combo box with file names.
	 */

	fc = gtk_combo_box_text_new();
	gtk_widget_set_focus_on_click(fc, TRUE);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (fc), 1, 0, 1, 1);
	g_signal_connect (fc, "changed", G_CALLBACK (fc_changed), NULL);

	/* Add disk names */
	fc_entries(fc);
}

void add_topbar() {
	
	/* A grid */
	GtkWidget *g = gtk_grid_new();
//	gtk_grid_insert_column(GTK_GRID(g), 3);
	gtk_box_pack_start(GTK_BOX(configbox), g, FALSE, TRUE, 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(g), FALSE);
	gtk_grid_set_column_spacing(GTK_GRID(g), 7);

	/*
	 * This grid has three entries.
	 */
	 
	 /* 1. A label. */
	 gtk_grid_attach(GTK_GRID (g), gtk_label_new(l.cfchose), 0, 0, 1, 1);
	 
	 /* 2. combo box that lets users chose the config file to view/edit. */
	files_combo(g);

	/* 2. A 'save' button. */
	bt = gtk_button_new_with_mnemonic(l.csave);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (bt), 2, 0, 1, 1);
	g_signal_connect (bt, "clicked", G_CALLBACK (save_cb), NULL);
}

void add_textview() {

	/* Show the file in a scrolled window. */
	
	GtkWidget *tmpbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_container_add(GTK_CONTAINER (configbox), tmpbox);

	
	/* Scrolled Window */
	GtkWidget *scrollw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollw),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	gtk_scrolled_window_set_propagate_natural_height (GTK_SCROLLED_WINDOW(scrollw), TRUE);
	gtk_scrolled_window_set_propagate_natural_width (GTK_SCROLLED_WINDOW(scrollw), TRUE);

	gtk_box_pack_start(GTK_BOX(tmpbox), scrollw, TRUE, TRUE, 0);
	
	/* Text view */
	GtkWidget *txt = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER (scrollw), txt);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(txt), TRUE);
	gtk_text_view_set_top_margin(GTK_TEXT_VIEW(txt), 10); 

	textbuf = gtk_text_view_get_buffer(GTK_TEXT_VIEW (txt));
	gtk_text_buffer_set_text(textbuf, "    ", strlen("    "));
}

void config() {

	/* Cleanup */
	if(GTK_IS_WIDGET(configbox))
			gtk_widget_destroy(configbox);

	/* A top level container. */
	configbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add(GTK_CONTAINER (tab7), configbox);
	
	/* A combo box to chose a file; and a 'safe' button. */
	add_topbar();
	
	/* The config files are displayed here: */
	add_textview();

	gtk_widget_show_all(configbox);
	gtk_widget_hide(bt);
}
