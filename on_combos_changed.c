#include "disk.h"

void on_toplevel_changed() {

	/* update a disk view */
	
	char *string;
	string = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_toplevel));
	if(string == NULL) {
		/* gtk_combo_box_remove_all() creates a signal for each removed entry */
		/* this function is called multiple times */
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
		tree = create_treeview();
		populate_treeview();
		gtk_widget_show(tree);
	}
	else {
		/* display a particular disk */
		tree1 = create_treeview1();
		populate_treeview1(string); /* do we need to check return value? */
		gtk_widget_show(tree1);
		free(string);
	}
}

void toplevel_entries() {
	
	/* cleanup */
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combo_toplevel));
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
	}

	else if(strcmp(string, "destroy") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_disks));
	}
	else if(strcmp(string, "add") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_disks));
		gtk_widget_show(GTK_WIDGET (text_size));
		gtk_widget_show(GTK_WIDGET (text_alignment));
	}
	else if(strcmp(string, "delete") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_partitions));
	}
	else if(strcmp(string, "modify") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_partitions));
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
		
	/* hide all options */
	gtk_widget_hide(GTK_WIDGET (toggle_soft));
	gtk_widget_hide(GTK_WIDGET (toggle_journal));
	gtk_widget_hide(GTK_WIDGET (toggle_fast));
	gtk_widget_hide(GTK_WIDGET (toggle_comp));

	/* ... but show relevant ones */
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

void on_disks_changed() {
	
	/* 
	 * If "gpart add" then show only partition types that fit 
	 * onto the scheme.
	 */
	 
	 	const gchar *gdisk = get_combo_box_disk(0);
	if( gdisk == NULL)
		return;
	char *string;
	string = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_geom));
	if(string == NULL)
		return;
	if( strncmp(string, "add", 3) != 0 )
		return;	

	char *scheme = get_scheme(gdisk);
	if(scheme == NULL) {
		msg("Error fetching partitioning scheme. Weird.");
		gtk_widget_destroy(thegrid);
		editor();
		return;
	}
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combo_types) );
	add_types(scheme);
	if(( strncmp(scheme, "GPT", 3) == 0 ) || ( strncmp(scheme, "BSD", 3) == 0 ) )
		gtk_widget_show(GTK_WIDGET (text_label));
	else
		gtk_widget_hide(GTK_WIDGET (text_label) );
	free(scheme);
	gtk_widget_show(GTK_WIDGET (combo_types));
}


void on_partitions_changed() {
	
	/* 
	 * If "gpart modify" then show only partition types that fit 
	 * onto the scheme.
	 */
	  
	char *string;
	string = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_geom));
	if(string == NULL)
		return;
	if( strncmp(string, "modify", 6) != 0 )
		return;
		
	char *gpartition = get_combo_box_partition(0);
	if(gpartition == NULL)
		return;
	find_p(gpartition);
	char *scheme = get_scheme(gpartition);
	if(scheme == NULL) {
		msg("error fetching partitioning scheme.Weird.");
		gtk_widget_destroy(thegrid);
		editor();
		return;
	}
	free(gpartition);
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combo_types) );
	add_types(scheme);
	if(( strncmp(scheme, "GPT", 3) == 0 ) || ( strncmp(scheme, "BSD", 3) == 0 ) )
		gtk_widget_show(GTK_WIDGET (text_label));
	else
		gtk_widget_hide(GTK_WIDGET (text_label) );
	free(scheme);
	gtk_widget_show(GTK_WIDGET (combo_types));
	
}

void on_scheme_changed() {
	
	/**/
	const gchar *gscheme = get_combo_box_scheme();
	if (gscheme == NULL)
		return;

	if(strncmp(gscheme, "GPT", 3) == 0)
		gtk_widget_show(text_entries);
	else
		gtk_widget_hide(text_entries);
}
