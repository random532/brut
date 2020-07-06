#include "disk.h"

void on_toplevel_changed() {
	char *string;
	string = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_toplevel));
	if(string == NULL) {
		/* gtk_combo_box_remove_all() creates a signal each time it removes an entry */
		/* so that this function gets called multiple times */
		//msg("Error! gtk_combo_box_text_get_active_text is empty!");
		return;
	}
	/* we don't need these any more */
	if(tree != NULL) {
		gtk_widget_destroy(tree);
		tree = NULL;
	}
	if(tree1 != NULL) {
		gtk_widget_destroy(tree1);
		tree1 = NULL;
	}
	
	/* what did user select? */
	if(strncmp(string, l.overview, 25) == 0) {
		/* display an overview of all disks */
		free(string);
		tree = disk_treeview();
		fill_treeview();
		gtk_widget_show(tree);
	}
	else {
		/* display a particular disk */
		tree1 = make_treeview();
		fill_treeview1(string);
		gtk_widget_show(tree1);
		free(string);
	}
}

void toplevel_entries() {

	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combo_toplevel));
		/* we always want this option */
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_toplevel), 0, l.overview);
	
	/* refresh the list of disks */
	if(all_disks != NULL)
		free(all_disks);
	all_disks = get_disks();
	if(all_disks == NULL) {
		msg("no disks found!");		
		return;
	}

	/* add each disk to the combo box */
	char *brk;
	char *one_disk = strtok_r( all_disks, " ", &brk);

	while( one_disk != NULL ) {
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_toplevel), NULL, one_disk);
		one_disk = strtok_r( NULL, " ", &brk);
	}
}

void on_geom_changed() {

	char *string;
	string = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_geom));
	if(string == NULL)
		return;
	
	/* update disk information */
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combo_disks));
	add_geoms();
	add_slices();
	add_partitions();	
		
	/* show only relevant widgets */
	hide_widgets();
	
	if(strcmp(string, "create") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_disks));
		gtk_widget_show(GTK_WIDGET (combo_schemes));
		gtk_widget_show(GTK_WIDGET (text_entries));
		}

	else if(strcmp(string, "destroy") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_disks));
		}
	else if(strcmp(string, "add") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_disks));
		gtk_widget_show(GTK_WIDGET (combo_types));
		gtk_widget_show(GTK_WIDGET (text_size));
		gtk_widget_show(GTK_WIDGET (text_label));
		gtk_widget_show(GTK_WIDGET (text_alignment));
		}
	else if(strcmp(string, "delete") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		}
	else if(strcmp(string, "modify") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		gtk_widget_show(GTK_WIDGET (combo_types));
		gtk_widget_show(GTK_WIDGET (text_label));
		}
	else if(strcmp(string, "set") == 0) { 
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		gtk_widget_show(GTK_WIDGET (combo_bootoptions));
		}
	else if(strcmp(string, "unset") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		gtk_widget_show(GTK_WIDGET (combo_bootoptions));
		}
	else if(strcmp(string, "resize") == 0) { 
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		gtk_widget_show(GTK_WIDGET (text_size));
		gtk_widget_show(GTK_WIDGET (text_alignment));
		}
	else if(strcmp(string, "bootcode") == 0) { 
		gtk_widget_show(GTK_WIDGET (combo_bootcode));
		gtk_widget_show(GTK_WIDGET (gfile));
		}
	else if(strcmp(string, "file system") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		gtk_widget_show(GTK_WIDGET (combo_filesystems));
		gtk_widget_show(GTK_WIDGET (text_label));
		}
}

void on_fs_changed() {

	char *string;
	string = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_filesystems));
	if(string == NULL)
		return;
		
		/* hide all widgets */
	gtk_widget_hide(GTK_WIDGET (toggle_soft));
	gtk_widget_hide(GTK_WIDGET (toggle_journal));
	gtk_widget_hide(GTK_WIDGET (toggle_fast));
	gtk_widget_hide(GTK_WIDGET (toggle_comp));

		/* show relevant widgets */
	if(strcmp(string, "ufs2") == 0) {
		gtk_widget_show(GTK_WIDGET (toggle_soft));
		gtk_widget_show(GTK_WIDGET (toggle_journal));
		}

	else if(strcmp(string, "ntfs") == 0) {
		gtk_widget_show(GTK_WIDGET (toggle_fast));
		gtk_widget_show(GTK_WIDGET (toggle_comp));
		}
}

void on_bootcode_changed() {
	char *string;
	string = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_bootcode));
	if(string == NULL)
		return;
		/* hide all widgets */
	gtk_widget_hide(GTK_WIDGET (combo_disks));
	gtk_widget_hide(GTK_WIDGET (combo_partitions));
	
	if(strcmp(string, "Partition") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_partitions));
	}
	else if(strcmp(string, "Disk") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_disks));
	}
}
