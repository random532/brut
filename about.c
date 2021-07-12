/* 'About' tab */
#include "disk.h"


void about() {

	if(GTK_IS_WIDGET(abox))
		gtk_widget_destroy(abox);

	/* Top level box */
	abox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add (GTK_CONTAINER (tab5), abox);
	gtk_container_add(GTK_CONTAINER (abox), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));		

	/* System information. */
	char *systeminfo = command("uname -prs");
	
	if(systeminfo != NULL) {
		GtkWidget *xbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
		gtk_container_add (GTK_CONTAINER (abox), xbox);
		
		gtk_container_add(GTK_CONTAINER (xbox), gtk_label_new("Version: "));
		gtk_container_add(GTK_CONTAINER (xbox), gtk_label_new(systeminfo));
		free(systeminfo);
		
		gtk_container_add(GTK_CONTAINER (abox), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));		
	}

	/* Text view */
	GtkWidget *txt = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER (abox), txt);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(txt), FALSE);
	gtk_text_view_set_top_margin(GTK_TEXT_VIEW(txt), 10); 
	
	GtkTextBuffer *txtbuf = gtk_text_view_get_buffer(GTK_TEXT_VIEW (txt));
	gtk_text_buffer_set_text(txtbuf, l.about, strlen(l.about));
	
	/* Show everything. */
	gtk_widget_show_all(abox);
}
