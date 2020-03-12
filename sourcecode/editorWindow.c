#include "disk.h"

void editor() {

/* window -> box -> grid */


	window_editor = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window_editor), "Editor");

	gtk_container_set_border_width (GTK_CONTAINER (window_editor), 30);

	/* adjust position */
	gint x = 0;
	gint y = 0;
	gtk_window_get_position (GTK_WINDOW(window), &x, &y);
	x=x+590;
	gtk_window_move( GTK_WINDOW(window_editor), x, y);

	/* vbox */
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add (GTK_CONTAINER (window_editor), box);

	/* grid */
	thegrid = gtk_grid_new();
	gtk_container_add (GTK_CONTAINER (box), thegrid);
	gtk_grid_insert_column(GTK_GRID(thegrid), 0);
	
int rows = 0;
	while(rows <= 13) {
	gtk_grid_insert_row (GTK_GRID(thegrid), rows);
	rows++;
	}

create_combo_schemes();
create_combo_types();
create_combo_disks();
create_combo_partitions();
create_combo_filesystems();
create_combo_bootoptions();
create_combo_geom();
create_text_label();
create_text_entries();
create_text_alignment();
create_text_size();
edit_button = gtk_button_new_with_mnemonic ("_Edit");

grid_attach_all();
g_signal_connect (edit_button, "clicked", G_CALLBACK (on_edit_clicked), NULL);
g_signal_connect (combo_geom, "changed", G_CALLBACK (on_geom_changed), NULL);


gtk_widget_show_all(window_editor);
gtk_window_resize(GTK_WINDOW(window_editor), 230, 300);
hide_widgets();
}


void hide_widgets() {
gtk_widget_hide(GTK_WIDGET (combo_schemes) );
gtk_widget_hide(GTK_WIDGET (combo_disks) );
gtk_widget_hide(GTK_WIDGET (combo_types) );
gtk_widget_hide(GTK_WIDGET (combo_partitions) );
gtk_widget_hide(GTK_WIDGET (combo_filesystems) );
gtk_widget_hide(GTK_WIDGET (combo_bootoptions) );
gtk_widget_hide(GTK_WIDGET (text_entries) );
gtk_widget_hide(GTK_WIDGET (text_label) );
gtk_widget_hide(GTK_WIDGET (text_size) );
gtk_widget_hide(GTK_WIDGET (text_alignment) );

}
