/* First tab - control panel */
#include "disk.h"

/* 
 * These callback functions switch the current tab.
 */
 
void disk_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 1);
}

void user_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 2);
}

void groups_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 3);
}

void time_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 4);
}

void about_cb(GtkMenuItem *item, gpointer page) {
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 5);
}

void tasks_cb(GtkMenuItem *item, gpointer page) {
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 6);
}

void system_cb(GtkMenuItem *item, gpointer page) {
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 7);
}

void devices_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 8);
}

void wlan_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 9);
}

void lan_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 10);
}

void audio_cb(GtkMenuItem *item, gpointer page) {  
	gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 11);
}

/* Hardware widget */
void attach_hardware(GtkWidget *g) {

	/* Title */
	GtkWidget *hw = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_grid_attach(GTK_GRID(g), hw, 0, 0, 1, 1);
	gtk_container_add(GTK_CONTAINER(hw), gtk_label_new(l.chardware));

	/* Disks */
	GtkWidget *d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.cdisks);
	g_signal_connect(d, "activate-link", G_CALLBACK (disk_cb), NULL);
	gtk_container_add(GTK_CONTAINER(hw), d);
	
	/* Devices */
	d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.cdevices);
	g_signal_connect(d, "activate-link", G_CALLBACK (devices_cb), NULL);
	gtk_container_add(GTK_CONTAINER(hw), d);
}

/* Time widget */
void attach_time(GtkWidget *g) {

	GtkWidget *c_disk = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_grid_attach(GTK_GRID(g), c_disk, 1, 1, 1, 1);
	gtk_container_add(GTK_CONTAINER(c_disk), gtk_label_new(l.ctime1));

	/* Time */
	GtkWidget *d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.ctime2);
	g_signal_connect(d, "activate-link", G_CALLBACK (time_cb), NULL);
	gtk_container_add(GTK_CONTAINER(c_disk), d);

	/* Tasks */
	GtkWidget *t = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(t), l.ctasks);
	g_signal_connect(t, "activate-link", G_CALLBACK (tasks_cb), NULL);
	gtk_container_add(GTK_CONTAINER(c_disk), t);

}

/* Account widget */
void attach_accounts(GtkWidget *g) {

	GtkWidget *c_disk = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_grid_attach(GTK_GRID(g), c_disk, 0, 1, 1, 1);
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

/* System widget */
void attach_system(GtkWidget *g) {

	/* Title */
	GtkWidget *csys = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_grid_attach(GTK_GRID(g), csys, 1, 0, 1, 1);
	gtk_container_add(GTK_CONTAINER(csys), gtk_label_new(l.csystem));

	/* Audio */
	GtkWidget *d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.caudio);
	g_signal_connect(d, "activate-link", G_CALLBACK (audio_cb), NULL);
	gtk_container_add(GTK_CONTAINER(csys), d);

	/* Config */
	d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.cconfigfiles);
	g_signal_connect(d, "activate-link", G_CALLBACK (system_cb), NULL);
	gtk_container_add(GTK_CONTAINER(csys), d);
	
	/* About */
	d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.cabout);
	g_signal_connect(d, "activate-link", G_CALLBACK (about_cb), NULL);
	gtk_container_add(GTK_CONTAINER(csys), d);	
}

void attach_network(GtkWidget *g) {

	/* Title */
	GtkWidget *cnet = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_grid_attach(GTK_GRID(g), cnet, 2, 0, 1, 1);
	gtk_container_add(GTK_CONTAINER(cnet), gtk_label_new(l.cnetwork));

	/* Wireless */
	GtkWidget *d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.cwlan);
	g_signal_connect(d, "activate-link", G_CALLBACK (wlan_cb), NULL);
	gtk_container_add(GTK_CONTAINER(cnet), d);

	/* Ethernet */
	d = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(d), l.clan);
	g_signal_connect(d, "activate-link", G_CALLBACK (lan_cb), NULL);
	gtk_container_add(GTK_CONTAINER(cnet), d);
}

void control() {

	if(GTK_IS_WIDGET (controlbox))
		gtk_widget_destroy(controlbox);

	/* A top level container. */
	controlbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add (GTK_CONTAINER (tab0), controlbox);

	/* Control Panel Label. */
	GtkWidget *t = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL (t), l.ctitle);
//	gtk_container_add(GTK_CONTAINER (controlbox), gtk_label_new("       "));
	gtk_container_add(GTK_CONTAINER (controlbox), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));
	gtk_container_add(GTK_CONTAINER (controlbox), t);
	gtk_container_add(GTK_CONTAINER (controlbox), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));

	/* Grid view. */
	GtkWidget *g = gtk_grid_new();
	gtk_grid_insert_column(GTK_GRID(g), 2); // XXX: needed?
	gtk_box_pack_start(GTK_BOX(controlbox), g, FALSE, TRUE, 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(g), TRUE);
	gtk_grid_set_column_spacing(GTK_GRID(g), 20);
	gtk_grid_set_row_spacing(GTK_GRID(g), 40);

	/* Grid entries. */
	attach_hardware(g);
	attach_time(g);
	attach_accounts(g);
	attach_system(g);
	attach_network(g);

	gtk_widget_show_all(controlbox);
}
