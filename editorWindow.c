#include "disk.h"

void destroy_editor (GtkMenuItem *item, gpointer user_data) {    
	window_editor=NULL;
}

void editor() {

/* 
 * we want a window with a box,
 * the box contains a grid,
 * the grid has one column, and 18 or so rows
 */
	window_editor = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window_editor), "Editor");
	gtk_container_set_border_width (GTK_CONTAINER (window_editor), 30);
	g_signal_connect(window_editor, "destroy", G_CALLBACK(destroy_editor), NULL);

	/* vbox */
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add (GTK_CONTAINER (window_editor), box);

	/* grid */
	thegrid = gtk_grid_new();
	gtk_container_add (GTK_CONTAINER (box), thegrid);
	gtk_grid_insert_column(GTK_GRID(thegrid), 0);
	
	int rows = 0;
	while(rows <= 19) {	/* XXX: hardcoded? */
		gtk_grid_insert_row (GTK_GRID(thegrid), rows);
		rows++;
	}

	/* various combo boxes */
	create_combo_schemes();
	create_combo_types();
	create_combo_disks();
	create_combo_partitions();
	create_combo_filesystems();
	create_combo_bootoptions();
	create_combo_geom();
	create_combo_bootcode();
	create_text_label();
	create_text_entries();
	create_text_alignment();
	create_text_size();

	/* toggle buttons */
	toggle_soft = gtk_check_button_new_with_label("Softupdates");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_soft), TRUE);
	toggle_journal = gtk_check_button_new_with_label("Journaling");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_journal), TRUE);
	toggle_fast = gtk_check_button_new_with_label("fast");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_fast), TRUE);
	toggle_comp = gtk_check_button_new_with_label("enable-compression");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_comp), TRUE);

	/* file chooser */
	gfile = gtk_file_chooser_button_new( "bootcode", GTK_FILE_CHOOSER_ACTION_OPEN);

	/* apply button */
	edit_button = gtk_button_new_with_mnemonic(l.apply);
	g_signal_connect (edit_button, "clicked", G_CALLBACK (on_edit_clicked), NULL);

	/* attach everything to grid */
	grid_attach_all();

	/* adjust position */
	gint x = 0, y = 0, width, height;
	gtk_window_get_position (GTK_WINDOW(window), &x, &y);
	gtk_window_get_size(GTK_WINDOW (window), &width, &height);
	/* XXX: get border width, and add it too! */
	guint border = gtk_container_get_border_width(GTK_CONTAINER(window));
	x = x + width + border;
	gtk_window_move( GTK_WINDOW(window_editor), x, y);
	gtk_window_set_default_size(GTK_WINDOW (window_editor), 230, 300);
	
	gtk_widget_show(GTK_WIDGET (window_editor));
	gtk_widget_show(box);
	gtk_widget_show(thegrid);
	
	/* user will only see those two for now */
	gtk_widget_show(GTK_WIDGET (combo_geom));
	gtk_widget_show(GTK_WIDGET(edit_button));
}

void hide_widgets() {
gtk_widget_hide(GTK_WIDGET (combo_schemes) );
gtk_widget_hide(GTK_WIDGET (combo_disks) );
gtk_widget_hide(GTK_WIDGET (combo_types) );
gtk_widget_hide(GTK_WIDGET (combo_partitions) );
gtk_widget_hide(GTK_WIDGET (combo_filesystems) );
gtk_widget_hide(GTK_WIDGET (combo_bootoptions) );
gtk_widget_hide(GTK_WIDGET (combo_bootcode) );
gtk_widget_hide(GTK_WIDGET (text_entries) );
gtk_widget_hide(GTK_WIDGET (text_label) );
gtk_widget_hide(GTK_WIDGET (text_size) );
gtk_widget_hide(GTK_WIDGET (text_alignment) );
gtk_widget_hide(GTK_WIDGET (toggle_soft) );
gtk_widget_hide(GTK_WIDGET (toggle_journal) );
gtk_widget_hide(GTK_WIDGET (toggle_fast) );
gtk_widget_hide(GTK_WIDGET (toggle_comp) );
gtk_widget_hide(GTK_WIDGET (gfile) );
}
