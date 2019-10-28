#include "disk.h"

/* This file contains all combo boxes */


	/*  combo box with partition types 
  * e.g. freebsd-ufs, freebsd-swap
  */
void combo_typ() {
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
	gtk_grid_attach(GTK_GRID (grid2), GTK_WIDGET (combo_types), 0, 3, 1, 1);
}
	
	


	 /* combo box with partitioning schemes */
void combo_d() {
	combo_disks = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, "APM");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, "BSD");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, "BSD64");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, "LDM");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, "GPT");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, "MBR");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, "VTOC8");
	gtk_grid_attach(GTK_GRID (grid2), GTK_WIDGET (combo_disks), 0, 3, 1, 1);
}

	 /* combo box for img tab */
void fchose_combo() {
	
	//create a combo box
	//for our filechoser
	// img writer

	
	combo7 = gtk_combo_box_text_new();

	
	int row=0;
	int len=0;
	GtkWidget *child1;
	GtkWidget *child2;
	const char *string1;
	const char *string2;
		
	char buf[25];

	while(1) {

		child1 = gtk_grid_get_child_at(GTK_GRID (grid1),1 ,row );
		if (child1 != NULL) { // we found a disk!
 	
			string1 = gtk_entry_get_text(GTK_ENTRY (child1) );
			gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo7), NULL, (const gchar *)string1);
			}
			
		else {
			child2 = gtk_grid_get_child_at(GTK_GRID (grid1),2 ,row );
			
			if (child2 != NULL) { // we found a partition!
				
				// build a string that looks like ada0s1p4
				strcpy(buf, string1);
				len = strlen(buf);
				
				buf[len] = 'p';// append p - append string 2 - append 0
				buf[len+1] = '\0';
				

				string2 = gtk_entry_get_text(GTK_ENTRY (child2) );
				strcpy(&buf[len+1], string2);
				gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo7), NULL, buf);

				len=0;
				}
			}
			
	row++;
	if(row > row1)
		break;
	}
gtk_grid_attach(GTK_GRID (grid3), GTK_WIDGET (combo7), 1, 4, 1, 1);
gtk_widget_show(GTK_WIDGET(combo7));

}

 /* 3 disk related combo boxes */
void disk_combo() {
	
	//create three combo boxes
	// combo4 - disks
	// combo5 - partitions
	// combo6 - disks and partitions
	
	combo4 = gtk_combo_box_text_new();
	combo5 = gtk_combo_box_text_new();
	combo6 = gtk_combo_box_text_new();
	
	int row=0;
	int len=0;
	GtkWidget *child1;
	GtkWidget *child2;
	const char *string1;
	const char *string2;
		
	char buf[25];

	while(1) {

		child1 = gtk_grid_get_child_at(GTK_GRID (grid1),1 ,row );
		if (child1 != NULL) { // we found a disk!
 	
			string1 = gtk_entry_get_text(GTK_ENTRY (child1) );
			gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo4), NULL, (const gchar *)string1);
			gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo6), NULL, (const gchar *)string1);
			}
			
		else {
			child2 = gtk_grid_get_child_at(GTK_GRID (grid1),2 ,row );
			
			if (child2 != NULL) { // we found a partition!
				
				// build a string that looks like ada0s1p4
				strcpy(buf, string1);
				len = strlen(buf);
				
				buf[len] = 'p';// append p - append string 2 - append 0
				buf[len+1] = '\0';
				

				string2 = gtk_entry_get_text(GTK_ENTRY (child2) );
				strcpy(&buf[len+1], string2);
				gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo5), NULL, buf);
				gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo6), NULL, buf);
				len=0;
				}
			}
			
	row++;
	if(row > row1)
		break;
	}
		
gtk_grid_attach(GTK_GRID (grid2), GTK_WIDGET (combo4), 0, 2, 1, 1);
gtk_grid_attach(GTK_GRID (grid2), GTK_WIDGET (combo5), 0, 2, 1, 1);
gtk_grid_attach(GTK_GRID (grid2), GTK_WIDGET (combo6), 0, 2, 1, 1);

D printf("disk_combo good!\n");
}

	 /* combo box with file systems */
void fs_combo() {
	combo_fs = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_fs), NULL, "ufs1");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_fs), NULL, "ufs2");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_fs), NULL, "FAT32");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_fs), NULL, "ntfs");
	gtk_grid_attach(GTK_GRID (grid2), GTK_WIDGET (combo_fs), 0, 3, 1, 1);
}


void combo_set_unset() {
	combo_s = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_s), NULL, "active");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_s), NULL, "bootme");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_s), NULL, "bootonce");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_s), NULL, "bootfailed");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_s), NULL, "lenovofix");
	
	gtk_grid_attach(GTK_GRID (grid2), GTK_WIDGET (combo_s), 0, 8, 1, 1);
}
