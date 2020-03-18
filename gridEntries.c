#include "disk.h"


	/*combo box with disks and slices */
void create_combo_disks() {

	if(list_of_disks != NULL)
		free(list_of_disks);
	list_of_disks = get_disks();
	if(list_of_disks == NULL) {
		printf("create_combo_box: failed: no disks found!\n");		
		return;
		}

	combo_disks = gtk_combo_box_text_new();
	char *brk;
	char *one_disk = strtok_r( list_of_disks, " ", &brk);

	while( one_disk != NULL ) {
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, one_disk);
		one_disk = strtok_r( NULL, " ", &brk);
		}

	/* add slices to the combo box */
	if(list_of_slices != NULL) {

		brk=NULL;
		char *one_slice = strtok_r( list_of_slices, " ", &brk);

		while( one_slice != NULL ) {
			gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, one_slice);
			one_slice = strtok_r( NULL, " ", &brk);
			}	
	}
}

	/* combo box with partitions */
void create_combo_partitions() {

	combo_partitions = gtk_combo_box_text_new();

	if(list_of_partitions != NULL) {
		char *brk;
		char *one_partition = strtok_r( list_of_partitions, " ", &brk);

		while( one_partition != NULL ) {
			gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_partitions), NULL, one_partition);
			one_partition = strtok_r( NULL, " ", &brk);
			}
	}	
	

}


	 /* combo box with file systems */
void create_combo_filesystems() {
	combo_filesystems = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_filesystems), NULL, "ufs1");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_filesystems), NULL, "ufs2");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_filesystems), NULL, "FAT32");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_filesystems), NULL, "ntfs");
}
	 /* combo box with partitioning schemes */
void create_combo_schemes() {
	combo_schemes = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "APM");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "BSD");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "BSD64");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "LDM");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "GPT (recommended)");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "MBR");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "VTOC8");
}


void create_combo_bootoptions() {
	combo_bootoptions = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_bootoptions), NULL, "active");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_bootoptions), NULL, "bootme");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_bootoptions), NULL, "bootonce");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_bootoptions), NULL, "bootfailed");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_bootoptions), NULL, "lenovofix");

}

void create_combo_types() {
combo_types = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-boot");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "bios-boot");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "efi");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-boot");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-swap");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-ufs");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-vinum");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-zfs");

	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-boot");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-apfs");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-core-storage");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-hfs");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-label");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-raid");	
	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-raid-offline");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-tv-recovery");	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-ufs");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-label32");	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-label64");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-legacy");	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-ccd");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-hammer ");	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-hammer2");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-swap");	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-ufs");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-vinum");	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "ebr");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "fat16");	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "fat32");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "fat32lba");	
	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-data");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-lvm");	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-raid");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-swap");	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "mbr");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "ms-basic-data");	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "ms-ldm-data");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "ms-ldm-metadata");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-ccd");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-cgd");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-ffs");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-lfs");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-raid");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-swap");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "ntfs");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "prep-boot");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "vmware-vmfs");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "vmware-vmkdiag");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "vmware-reserved");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "vmware-vsanhdr");

}

void create_combo_geom() {
	combo_geom = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "create");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "destroy");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "add");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "delete");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "modify");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "resize");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "set");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "unset");
	
/* todo: */
//gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "bootcode");
//gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "file system");

}


void create_text_label() {

	GtkEntryBuffer *buf_label = gtk_entry_buffer_new (NULL, 0);
	gtk_entry_buffer_set_max_length (buf_label, 8);
	text_label = gtk_entry_new_with_buffer (buf_label);
	gtk_entry_set_placeholder_text (GTK_ENTRY(text_label), "label (optional)");

}
void create_text_entries() {
	GtkEntryBuffer *buf_entries = gtk_entry_buffer_new (NULL, 0);
	gtk_entry_buffer_set_max_length (buf_entries, 8);
	text_entries = gtk_entry_new_with_buffer (buf_entries);
	gtk_entry_set_placeholder_text (GTK_ENTRY(text_entries), "entries (optional)");
}
void create_text_size() {
	GtkEntryBuffer *buf_size = gtk_entry_buffer_new (NULL, 0);
	gtk_entry_buffer_set_max_length (buf_size, 8);
	text_size = gtk_entry_new_with_buffer (buf_size);
	gtk_entry_set_placeholder_text (GTK_ENTRY(text_size), "size, e.g. 100M");
}
void create_text_alignment() {
	GtkEntryBuffer *buf_alignment = gtk_entry_buffer_new (NULL, 0);
	gtk_entry_buffer_set_max_length (buf_alignment, 8);
	text_alignment = gtk_entry_new_with_buffer (buf_alignment);
	gtk_entry_set_placeholder_text (GTK_ENTRY(text_alignment), "alignment (optional)");
}

void grid_attach_all() {
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_geom), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_disks), 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_partitions), 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_schemes), 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_types), 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (text_size), 0, 5, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (text_label), 0, 6, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (text_entries), 0, 7, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (text_alignment), 0, 8, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_bootoptions), 0, 9, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_filesystems), 0, 10, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (edit_button), 0, 11, 1, 1);
}
