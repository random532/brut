/* Time tab related code */
#include "disk.h"

void timetab() {
		
	/* A top level container. */
	timebox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add (GTK_CONTAINER (tab4), timebox);

	gtk_container_add(GTK_CONTAINER (timebox), gtk_label_new("Not done yet."));

	gtk_widget_show_all(timebox);
}
