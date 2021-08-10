#include "disk.h"
#include "../brut.h"

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
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "bootcode");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_geom), NULL, "file system");
	g_signal_connect (combo_geom, "changed", G_CALLBACK (on_geom_changed), NULL);
}

void create_combo_disks() {
	combo_disks = gtk_combo_box_text_new();
	g_signal_connect(combo_disks, "changed", G_CALLBACK(on_disks_changed), NULL);
}

void create_combo_partitions() {
	combo_partitions = gtk_combo_box_text_new();
	g_signal_connect(combo_partitions, "changed", G_CALLBACK(on_partitions_changed), NULL);
}

void create_combo_bootcode() {
	combo_bootcode = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_bootcode), NULL, "Partition");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_bootcode), NULL, "Disk");
	g_signal_connect (combo_bootcode, "changed", G_CALLBACK (on_bootcode_changed), NULL);
}

void create_combo_schemes() {
	combo_schemes = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "APM");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "BSD");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "BSD64");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "LDM");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "GPT");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "MBR");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_schemes), NULL, "VTOC8");
	g_signal_connect(combo_schemes, "changed", G_CALLBACK(on_scheme_changed), NULL);
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
}

void add_types( char *scheme) {
	
	if( strncmp(scheme, "GPT", 3) == 0) {
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-boot");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-swap");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-ufs");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-vinum");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-zfs");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "ms-basic-data");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "ms-ldm-data");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "ms-ldm-metadata");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "bios-boot");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "efi");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-boot");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-apfs");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-core-storage");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-hfs");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-label");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-raid");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-raid-offline");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-tv-recovery");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-ufs");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-data");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-lvm");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-raid");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-swap");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "vmware-vmfs");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "vmware-vmkdiag");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-label32");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-label64");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-legacy");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-ccd");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-hammer ");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-hammer2");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-swap");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-ufs");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "dragonfly-vinum");			
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-ccd");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-cgd");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-ffs");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-lfs");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-raid");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "netbsd-swap");
	}
	else if( strncmp(scheme, "MBR", 3) == 0) {
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "apple-boot");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "ebr");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "fat16");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "fat32");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "fat32lba");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "ntfs");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-data");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-lvm");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-raid");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "linux-swap");	
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "vmware-vmfs");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "vmware-vmkdiag");	
	}
	else if( strncmp(scheme, "BSD", 3) == 0) {
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-boot"); // ?
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-swap");
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-ufs"); 
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-vinum"); // ?
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_types), NULL, "freebsd-zfs");
	}
	else { /* whatever, add all */
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
}

void create_combo_filesystems() {
	combo_filesystems = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_filesystems), NULL, "ufs2");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_filesystems), NULL, "FAT32");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_filesystems), NULL, "ntfs");
	g_signal_connect (combo_filesystems, "changed", G_CALLBACK (on_fs_changed), NULL);
}

void create_text_label() {
	GtkEntryBuffer *buf_label = gtk_entry_buffer_new (NULL, 0);
	gtk_entry_buffer_set_max_length (buf_label, ENTRY_MAX);
	text_label = gtk_entry_new_with_buffer (buf_label);
	gtk_entry_set_placeholder_text (GTK_ENTRY(text_label), "label (optional)");
}

void create_text_entries() {
	GtkEntryBuffer *buf_entries = gtk_entry_buffer_new (NULL, 0);
	gtk_entry_buffer_set_max_length (buf_entries, ENTRY_MAX);
	text_entries = gtk_entry_new_with_buffer (buf_entries);
	gtk_entry_set_placeholder_text (GTK_ENTRY(text_entries), "entries (optional)");
}

void create_text_size() {
	GtkEntryBuffer *buf_size = gtk_entry_buffer_new (NULL, 0);
	gtk_entry_buffer_set_max_length (buf_size, ENTRY_MAX);
	text_size = gtk_entry_new_with_buffer (buf_size);
	gtk_entry_set_placeholder_text (GTK_ENTRY(text_size), "size, e.g. 100M");
}

void create_text_alignment() {
	GtkEntryBuffer *buf_alignment = gtk_entry_buffer_new (NULL, 0);
	gtk_entry_buffer_set_max_length (buf_alignment, ENTRY_MAX);
	text_alignment = gtk_entry_new_with_buffer (buf_alignment);
	gtk_entry_set_placeholder_text (GTK_ENTRY(text_alignment), "alignment (optional)");
}

void create_toggle_buttons() {
	toggle_soft = gtk_check_button_new_with_label("Softupdates");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_soft), TRUE);
	toggle_journal = gtk_check_button_new_with_label("Journaling");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_journal), TRUE);
	toggle_fast = gtk_check_button_new_with_label("fast");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_fast), TRUE);
	toggle_comp = gtk_check_button_new_with_label("enable-compression");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_comp), TRUE);
}

void grid_attach_all() {
	
	editor_sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	editor_label = gtk_label_new("      ");
	//gtk_label_set_pattern(GTK_LABEL (editor_label), "_______");
	
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (editor_sep), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (editor_label), 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_geom), 0,	2, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_bootcode), 0,	3, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_disks), 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_partitions), 0, 5, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_schemes), 0, 6, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_types), 0, 7, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_bootoptions), 0, 8, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (combo_filesystems), 0, 9, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (text_label), 0, 10, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (text_size), 0, 11, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (text_entries), 0, 12, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (text_alignment), 0, 13, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (toggle_soft), 0, 14, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (toggle_journal), 0, 15, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (toggle_fast), 0, 16, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (toggle_comp), 0, 17, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (gfile), 0, 18, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (toggle_ask), 0, 19, 1, 1);
	gtk_grid_attach(GTK_GRID (thegrid), GTK_WIDGET (edit_button), 0, 20, 1, 1);
}
