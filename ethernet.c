/* Ethernet tab */
#include "disk.h"

void CleanLan() {

	if(GTK_IS_WIDGET (lanbox))
		gtk_widget_destroy(lanbox);
}

void lan() {
	
	CleanLan();
	
	/* A top level container. */
	lanbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add (GTK_CONTAINER (tab10), lanbox);

	gtk_container_add (GTK_CONTAINER (lanbox), gtk_label_new("Not implemented yet!"));
	
	gtk_widget_show_all(lanbox);

}
