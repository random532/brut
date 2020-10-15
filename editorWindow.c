#include "disk.h"


void editor() {

	/* The editor is a grid. */
	thegrid = gtk_grid_new();
	gtk_container_add (GTK_CONTAINER (box), thegrid);
	gtk_grid_insert_column(GTK_GRID (thegrid), 0);
	
	int rows = 0;
	while(rows <= 20) {	/* XXX: hardcoded? */
		gtk_grid_insert_row (GTK_GRID(thegrid), rows);
		rows++;
	}

	/* Various combo boxes */
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

	/* Toggle buttons */
	toggle_soft = gtk_check_button_new_with_label("Softupdates");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_soft), TRUE);
	toggle_journal = gtk_check_button_new_with_label("Journaling");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_journal), TRUE);
	toggle_fast = gtk_check_button_new_with_label("fast");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_fast), TRUE);
	toggle_comp = gtk_check_button_new_with_label("enable-compression");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_comp), TRUE);

	/* File chooser */
	gfile = gtk_file_chooser_button_new( "bootcode", GTK_FILE_CHOOSER_ACTION_OPEN);

	/* apply button */
	edit_button = gtk_button_new_with_mnemonic(l.apply);
	g_signal_connect (edit_button, "clicked", G_CALLBACK (on_edit_clicked), NULL);

	/* Attach everything to grid. */
	grid_attach_all();

	gtk_widget_show(thegrid); //XXX: needed?
	
	/* user will only see those for now */
	gtk_widget_show(GTK_WIDGET (editor_sep));
	gtk_widget_show(GTK_WIDGET (editor_label));
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
