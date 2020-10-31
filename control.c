/* First tab related code */
#include "disk.h"


void disk_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 1);
}
void time_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 4);
}

void groups_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 2);
}

void user_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 3);
}


void attach_disk(GtkWidget *g) {

	GtkWidget *c_disk = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_grid_attach(GTK_GRID(g), c_disk, 0, 0, 1, 1);

	gtk_container_add(GTK_CONTAINER(c_disk), gtk_label_new(l.chardware));

	GtkWidget *d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.cdisks);
	g_signal_connect(d, "activate-link", G_CALLBACK (disk_cb), NULL);
	gtk_container_add(GTK_CONTAINER(c_disk), d);

}

void attach_time(GtkWidget *g) {

	GtkWidget *c_disk = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_grid_attach(GTK_GRID(g), c_disk, 0, 2, 1, 1);

	gtk_container_add(GTK_CONTAINER(c_disk), gtk_label_new(l.ctime1));

	GtkWidget *d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.ctime2);
	g_signal_connect(d, "activate-link", G_CALLBACK (time_cb), NULL);

	gtk_container_add(GTK_CONTAINER(c_disk), d);

}

void attach_user(GtkWidget *g) {

	GtkWidget *c_disk = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_grid_attach(GTK_GRID(g), c_disk, 1, 0, 1, 1);

	gtk_container_add(GTK_CONTAINER(c_disk), gtk_label_new(l.caccount));

	GtkWidget *d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.cuser);
	g_signal_connect(d, "activate-link", G_CALLBACK (user_cb), NULL);
	gtk_container_add(GTK_CONTAINER(c_disk), d);
	
	d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.cgroups);
	g_signal_connect(d, "activate-link", G_CALLBACK (groups_cb), NULL);
	gtk_container_add(GTK_CONTAINER(c_disk), d);
	
}

void control() {
		
	/* A top level container. */
	controlbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add (GTK_CONTAINER (tab0), controlbox);

	/* Control Panel Label. */
	GtkWidget *t = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL (t), l.ctitle);
	gtk_container_add(GTK_CONTAINER (controlbox), gtk_label_new("       "));
	gtk_container_add(GTK_CONTAINER (controlbox), t);

	/* Grid view. */
	GtkWidget *g = gtk_grid_new();
	gtk_grid_insert_column(GTK_GRID(g), 2);
	gtk_box_pack_start(GTK_BOX(controlbox), g, FALSE, TRUE, 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(g), TRUE);
	gtk_grid_set_column_spacing(GTK_GRID(g), 20);
	gtk_grid_set_row_spacing(GTK_GRID(g), 40);

	/* Grid entries. */
	attach_disk(g);
	attach_time(g);
	attach_user(g);

	gtk_widget_show_all(controlbox);
}
