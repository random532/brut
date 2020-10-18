/* 'About' tab */
#include "disk.h"

void about() {

	abox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_add (GTK_CONTAINER (tab5), abox);

	GtkWidget *txt = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER (abox), txt);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(txt), FALSE);
	gtk_text_view_set_top_margin(GTK_TEXT_VIEW(txt), 10); 
	
	GtkTextBuffer *txtbuf = gtk_text_view_get_buffer(GTK_TEXT_VIEW (txt));
	gtk_text_buffer_set_text(txtbuf, l.about, strlen(l.about));
	
	gtk_widget_show_all(abox);
}
