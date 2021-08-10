/* dmesg  */
#include "brut.h"

#define GREP_MAX 10
GtkWidget *txt;
GtkTextBuffer *textbuf;
GtkWidget *dgrid;
GtkWidget *greptxt;
//GtkWidget *dapply;

void showme (GtkMenuItem *item, gpointer user_data) {    
	
	char cmd[60];
	memset(cmd, 0, 60);
	const char *what = gtk_entry_get_text(GTK_ENTRY (greptxt));
	if((what == NULL) || (strlen(what) > GREP_MAX))
		return;

	if(strlen(what) == 0)
		snprintf(cmd, 6, "dmesg");
	else
		snprintf(cmd, 50, "dmesg | grep \"%s\"", what);
	char *content = command(cmd);
	if(content != NULL)
		gtk_text_buffer_set_text(textbuf, content, strlen(content));
}

void add_grep() {

	dgrid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER (dmesgbox), dgrid);
	gtk_grid_attach(GTK_GRID (dgrid), gtk_label_new("Grep:"), 0, 0, 1, 1);
	
	greptxt = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY (greptxt), GREP_MAX);
	gtk_entry_set_placeholder_text (GTK_ENTRY(greptxt), "e.g. CPU");
	gtk_grid_attach(GTK_GRID (dgrid), GTK_WIDGET (greptxt), 1, 0, 1, 1);
	
	GtkWidget *dapply = gtk_button_new_with_label("Grep");
	gtk_grid_attach(GTK_GRID (dgrid), GTK_WIDGET (dapply), 2, 0, 1, 1);
	g_signal_connect(dapply, "clicked", G_CALLBACK(showme), NULL);
}

void draw_dmesg() {
	
	/* Show dmesg in a scrolled window. */

	/* Scrolled Window */
	GtkWidget *scrollw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollw),
                                    GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_propagate_natural_height (GTK_SCROLLED_WINDOW(scrollw), TRUE);
	gtk_scrolled_window_set_propagate_natural_width (GTK_SCROLLED_WINDOW(scrollw), TRUE);
	gtk_box_pack_start(GTK_BOX(dmesgbox), scrollw, TRUE, TRUE, 10);

	GtkWidget *swbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add(GTK_CONTAINER (scrollw), swbox);
	
	/* Text view */
	txt = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER (swbox), txt);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(txt), TRUE);
	gtk_text_view_set_top_margin(GTK_TEXT_VIEW(txt), 10); 
	gtk_text_view_set_pixels_above_lines(GTK_TEXT_VIEW (txt), 2);

	textbuf = gtk_text_view_get_buffer(GTK_TEXT_VIEW (txt));
	
	char *content = command("dmesg");
	gtk_text_buffer_set_text(textbuf, content, strlen(content));

	gtk_container_add(GTK_CONTAINER (swbox), gtk_label_new("   ")); /* Avoid Scrollbars */
}

void dmesg() {

	/* Cleanup */
	if(GTK_IS_WIDGET(dmesgbox))
			gtk_widget_destroy(dmesgbox);

	/* A top level container. */
	dmesgbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add(GTK_CONTAINER (tab12), dmesgbox);

	/* The 'grep'*/
	add_grep();
	
	/* Text view */
	draw_dmesg();
	gtk_widget_show_all(dmesgbox);
}
