#include "disk.h"


	/* main windows, containers */
GtkWidget	*window;
GtkWidget	*fixed1;
GtkWidget	*fixed2;
GtkWidget	*fixed3;
GtkWidget	*fixed4;

GtkWidget	*scrolled3;
 
	/* the grids */
GtkWidget	*grid1;	/* disk overview */
int row1=0;	 		/* number of rows*/
GtkWidget	*grid2;  /**/
GtkWidget	*grid3;  /**/


GtkTreeView *tree1;	 	/* vendor description */
GtkTreeStore *treestore1;
GtkTreeViewColumn *c1;
GtkTreeViewColumn *c2;

GtkCellRenderer	*cr1;
GtkCellRenderer	*cr2;

GtkTreeView *tree2;	 	/* disk labels */
GtkTreeStore *treestore2;
GtkTreeViewColumn *c3;
GtkTreeViewColumn *c4;

GtkCellRenderer	*cr3;
GtkCellRenderer	*cr4;


GtkTreeIter iter;
GtkTreeIter iter2;

//GtkWidget *label1;


	/* various combo boxes */
GtkWidget *combo1;
GtkWidget *combo4;
GtkWidget *combo5;
GtkWidget *combo6;
GtkWidget *combo7;

GtkWidget	*combo_disks;
GtkWidget	*combo_types;
GtkWidget	*combo_fs;

	 /* text entries */
GtkWidget *entry4;
GtkWidget *entry5;
GtkWidget *entry6;
GtkWidget *entry7;
GtkWidget *entry8;
GtkWidget *entry9;

//GtkWidget	*textview1;
//GtkTextView	*textview2;
//GtkTextBuffer *buffer1;

	 /* file chooser */
GtkWidget	*file1;
GtkWidget	*file2;

GtkBuilder	*builder;



	/* quit */	
void on_button_quit_clicked(GtkButton *b) {	
		gtk_main_quit();
}

	/* Hide all widgets.
  * We can then selectively show the ones
  * that are relevant.  
  * */
  
void hide_all() {

gtk_widget_hide(GTK_WIDGET (combo_disks) );
gtk_widget_hide(GTK_WIDGET (combo_types) );
gtk_widget_hide(GTK_WIDGET (combo_fs) );
gtk_widget_hide(GTK_WIDGET (combo4) );
gtk_widget_hide(GTK_WIDGET (combo5) );
gtk_widget_hide(GTK_WIDGET (combo6) );
gtk_widget_hide(GTK_WIDGET (entry4) );
gtk_widget_hide(GTK_WIDGET (entry5) );
gtk_widget_hide(GTK_WIDGET (entry6) );
gtk_widget_hide(GTK_WIDGET (entry7) );
gtk_widget_hide(GTK_WIDGET (entry8) );
gtk_widget_hide(GTK_WIDGET (entry9) );
}


	/* destroy message box if ok is clicked */
void on_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
gtk_widget_destroy(GTK_WIDGET (dialog));	
}


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
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_fs), NULL, "ufs");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_fs), NULL, "ntfs");
	gtk_grid_attach(GTK_GRID (grid2), GTK_WIDGET (combo_fs), 0, 8, 1, 1);
}


	 /* execute gpart show
	  * put identifyers in front of each entry
	  * return a pointer to modified content 
	  * */
char * parse_gpart() {
	
	
	// copy gpart output to temp file
	
	 system("/sbin/gpart show > /tmp/gpart");
	FILE * fp = fopen("/tmp/gpart", "r");
	if (fp == NULL)
		printf("couldnt open file /tmp/gpart\n");

	//fs = filesize
	
	fseek(fp, 0, SEEK_END);
	int fs = ftell(fp);
	rewind(fp);
	
	//create buffer, copy file to buffer
	
	char * 	ptr1 = malloc(fs+1);
	fread(ptr1, 1, fs, fp);	
	fclose(fp);
	
	// parse buffer, output in 2nd buffer
	
	char * ptr2= malloc(fs+100);
	
	int pa=0; // counter of first buffer
	int pb=0; // counter of second buffer
	
	int cnt=0; // some counter
	int buflen = fs-1; // why -1

	int i=1;	// line counter, for debugging only
	int ai=0;	// disk entry counter, for debugging only

	/* 
	/ first task:
	/ - remove double spaces
	/ - label the two numbers at 
	/ the beginning of each line, see gpart show
	/ - remove diskid entries 
	*/
	 
	
	while( pa < buflen) {
		
	// get the first 2 numbers 
	
	while(cnt != 2) {
		if (( (ptr1[pa] >= 0x30 ) &&  (ptr1[pa] <= 0x39 )  )) {
			
			// we found a number, so increase cnt
			cnt++;
			// set an identifier
			if (cnt== 1)
				ptr2[pb] =  '!';
			if (cnt == 2)
				ptr2[pb] =  ':';
			pb++;
			
			//write number in 2nd buffer
			
			while (ptr1[pa] !=  ' ') {
				ptr2[pb] = ptr1[pa];
				pa++;
				pb++; 
				
			}

		}
		// else continue the search
		else
			pa++;
	}
		
	cnt=0;

	// skip space characters
	while(ptr1[pa] == ' ')
		pa++;

	// diskid
	if( (ptr1[pa] == 'd' ) && (ptr1[pa+1] == 'i') && (ptr1[pa+2] == 's') && (ptr1[pa+3] == 'k') && (ptr1[pa+4] == 'i') && (ptr1[pa+5] == 'd')) {
		D printf("diskid found!\n");
		while(1) {
			if ((ptr1[pa] == 0x0A)  &&  (ptr1[pa+1] == 0x0A)  ) {
				// end of diskid enry, so leave
				break;
				}
			pa++;
			}
		// hack: remove size numbers
		while(ptr2[pb] != '!')
				pb--;
		pb--; // remove newline
		}

	if( (ptr1[pa] == 'g' ) && (ptr1[pa+1] == 'p') && (ptr1[pa+2] == 't') && (ptr1[pa+3] == 'i') && (ptr1[pa+4] == 'd')) {
		printf("diskid found!\n");
		while(1) {
			if ((ptr1[pa] == 0x0A)  &&  (ptr1[pa+1] == 0x0A)  ) {
				// end of diskid enry, so leave
				break;
				}
			pa++;
			}
		// hack: remove size numbers
		while(ptr2[pb] != '!')
				pb--;
		pb--; // remove newline
		}

		// disk			
		if (( (ptr1[pa] >=  'a') &&  (ptr1[pa] <= 'z' )  )) {

			// set identifier
			ptr2[pb] =  '$';
			pb++;
			// and copy
			while (ptr1[pa] !=  ' ') {
					ptr2[pb] = ptr1[pa];
					pa++;
					pb++; 
				}
			}
			
// now parse remaining entries

while (ptr1[pa] != 0x0A) {

	// find the next entry
	while(ptr1[pa] == ' ')
		pa++;
						
		// partition number
		if (( (ptr1[pa] >= 0x30 ) &&  (ptr1[pa] <= 0x39 )  )) {

			// set identifier
			ptr2[pb] =  '#';
			pb++;
				
			//and copy
			while (ptr1[pa] !=  ' ') {
				ptr2[pb] = ptr1[pa];
				pa++;
				pb++; 
				}
			}

		// -free-
		else if (ptr1[pa] ==  '-') {
			
			ptr2[pb] =  '=';
			ptr2[pb+1] =  'f';
			ptr2[pb+2] =  'r';
			ptr2[pb+3] =  'e';
			ptr2[pb+4] =  'e';
			pb= pb+5;
			pa = pa+7;
			}

		// type		
		if (( (ptr1[pa] >=  'a') &&  (ptr1[pa] <= 'z' )  )) {

			// set identifier
			ptr2[pb] =  ';';
			pb++;
			// and copy
			while (ptr1[pa] !=  ' ') {
					ptr2[pb] = ptr1[pa];
					pa++;
					pb++; 
				}
			}

		// schemes
		else if (( (ptr1[pa] >=  'A') &&  (ptr1[pa] <= 'Z' )  )) {
			
			// set identifier
			ptr2[pb] =  '%';
			pb++;

			// and copy
			while (ptr1[pa] !=  ' ') {
					ptr2[pb] = ptr1[pa];
					pa++;
					pb++; 
				}
			}
			
		// active		
		else if( ptr1[pa] ==  '[')  {

			// and copy
			while (ptr1[pa] !=  ' ') {
					ptr2[pb] = ptr1[pa];
					pa++;
					pb++; 
				}
			}

		//partition size
		else if ( ptr1[pa] ==  '('  ) {

			// copy
			while (ptr1[pa] !=  ')') {
					ptr2[pb] = ptr1[pa];
					pa++;
					pb++; 
				}
		//	pa++;
			}
			
			pa++;
}		
		
		
	
	// either way, we reached the end of a line
	// use '\n' instead of 0x0A


	ptr2[pb] = '\n';
	pa++;
	pb++;

	// debugging output
	i++;
	D printf("line number: %i\n", i);


	if (ptr1[pa] == 0x0A) { 	//new entry or eof

		ai++;
		D printf("entry: %i, pa=%i, buflen=%i\n", ai, pa, buflen);
		}
	
	}

	// now zero terminate, and print the parsed string
	ptr2[pb-1] ='\0';
	D printf("end reached. size: %i\n-Start-\n%s\n-End-\n", fs, ptr2);
	
	free(ptr1);
	return(ptr2);
	}


	/* popup a message box */
void msg(char * blah) {
	GtkWidget * message = gtk_message_dialog_new(GTK_WINDOW (window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, blah);
	gtk_widget_show(message);
	g_signal_connect(message, "response", G_CALLBACK(on_response), NULL);
	
	}
	
	 /* execute camcontrol devlist
	  * write content to treeview 
	  * */
int camcontrol() {
	
	D printf("camcontrol start\n");
							
	 /* first destroy any previous widgets, cleanup  */
	gtk_tree_store_clear(treestore1);
	
	
	char buf[250];
	int i=0;
	int error=0;
	
	FILE * fp = popen("camcontrol devlist", "r");
	if (fp == NULL) {
		msg("couldnt popen");
		return error;
		}
		
	while( fgets(buf, sizeof buf, fp)) {
		
		 /* this might be a permission denied string.*/
		 if( strcmp(buf, "sh: camcontrol: permission denied") == 0 )
		 {
			 msg(buf);
			 pclose(fp);
			 return 1;
			}
		 
		i=0;	
		while(buf[i] !='<')
			i++;
		
		buf[i]=' ';
				
		while(buf[i] !='>')
			i++;

		buf[i]='\0';
		//and write it to textview colum 2
		gtk_tree_store_append(treestore1 ,&iter, NULL);
		gtk_tree_store_set(treestore1, &iter, 0, buf, -1);
		
		while(buf[i] != ',' )
			i++;

		buf[i]='\0';
		
		while(buf[i] != '(') {
 
			i--;
			if(i==0)  {
				printf("error\n");	
				break;
				}
		}
		i++;
		// and write it to textview colum 1
		gtk_tree_store_set(treestore1, &iter, 1, &buf[i], -1);
	
		

	}
	error = pclose(fp);
	D	printf("camcontrol done\n");	
	return 1;
	}
	
	
	 /* execute glabel show
	  * write content to treeview
	  * */
int glabel() {
	
	// first destroy any previous widgets, cleanup

	gtk_tree_store_clear(treestore2);
	
	D printf("glabel start\n");
	char buf[250];
	int i=0;
	int error=0;
	
	FILE * fp = popen("glabel status", "r");
	if (fp == NULL) {
		msg("couldnt popen");
		return error;
		}

fgets(buf, sizeof buf, fp); // ignore first line

	while( fgets(buf, sizeof buf, fp)) {
		
		i=0;
		if(buf[i] == ' ') {
			while(buf[i] == ' ')
				i++;
}
		while(buf[i] != ' ')
			i++;

		buf[i]='\0';
		//and write it to textview colum 2

		gtk_tree_store_append(treestore2 ,&iter2, NULL);
		gtk_tree_store_set(treestore2, &iter2, 0, buf, -1);
		
		i++;
		
		while(buf[i] == ' ')
			i++;
		while(buf[i] != ' ')
			i++;
		while(buf[i] == ' ')
			i++;
		
		// and write it to textview colum 1
		gtk_tree_store_set(treestore2, &iter2, 1, &buf[i], -1);
	
		}

		
	error = pclose(fp);

	D printf("glabel done\n");
	return 1;

	}
	
	 /* update second tab*/
void	on_buttonview1_clicked(GtkButton *b)
{
	glabel();
	camcontrol();
	
	}
	
	
	 /* execute a command
	  * return with message box
	  * */
	  
int exe(char * cmd) {

	char buf[200];
	
	strcpy(buf, cmd);
	strcat(buf ," 2>&1"); // also capture stderr
	
	FILE * fp = popen(buf, "r");
	if (fp == NULL)
		msg("couldnt popen");
	
	while( fgets(buf, sizeof buf, fp)) {
		//msg(buf);
		}
	msg(buf);
		int suc = pclose(fp)/256;
		printf("%i == exit status of piped process\n\n", suc);
		
	return suc;
}

	 /* third tab:
	  * ckecksum ckeck
	  * execute dd ... */
void on_fwrite1_clicked(GtkButton *b) {
	
	char *fname;
	char *sha;
	char *disk;
	
	int len=0;
	int img=0;
	int error=0;
	
	char buf[300];
	char buf2[10];
	
	
	fname = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (file1));
	if(file1 == NULL) {
		msg("Choose a file first!");
		return;
		}
	
	disk = 	gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo7) );
	if(disk==NULL) {
		msg("Choose a disk/partition!");
		return;
		}
	
	sha = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (file2));	
		if(sha!=NULL) {
		// do a checksum ckeck
		
			FILE * fp=fopen( sha, "r");
			if (fp== NULL)
				msg("pf = 0");
				
			// build the shasum ... command
			fgets(buf2 ,7, fp);

			strcpy(buf, "shasum -s -c ");

			strcat(buf, sha);
			strcat(buf, " ");
			strcat(buf, fname);
			error=exe(buf);
			
			fclose(fp);

		}
		
	if(error == 0) {
	

	len = strlen(fname);
	//check for img
		if( (fname[len-4] == '.') && (fname[len-3] == 'i') && (fname[len-2] == 'm') && (fname[len-1] == 'g') ) {
			img=1;
			}

		else
			msg("File does not end with .img!");
	
	
	// for img files
		if(img == 1) {
			strcpy(buf, "dd if=");
			strcat(buf, fname);
			strcat(buf, " of=/dev/");
			strcat(buf, disk);
			strcat(buf, " bs=1M conv=sync");	
			exe(buf);		
			}
 
	}
	g_free(disk);
	g_free(fname);
	g_free(sha);
		

	gtk_widget_destroy(combo7);
	gtk_file_chooser_unselect_all(GTK_FILE_CHOOSER (file2));
	
	fchose_combo();
}

	/* add missing disks */
void add_missing() {

	// gpart only shows disks with a scheme
	// we need to add the others too
		
		char *sysdisk;
		size_t syslen;
		int error = sysctlbyname("kern.disks", NULL, &syslen, NULL, 0);
			if (error != 0) 
				D printf("sysctl failed");
				
		sysdisk = malloc(syslen);
		error = sysctlbyname("kern.disks", sysdisk, &syslen, NULL, 0);
			if (error != 0) 
				D printf("sysctl failed");
		
	
	char *token;
	const gchar *p;
	const char s[2]=" ";
	GtkWidget *child;
	int row=0;
	GtkWidget *entry;
	

	token = strtok(sysdisk, s);

	// loop through disks
	while (token != NULL ) {
			
		D printf("token: %s\n", token);
		
		// loop through grid entries
		while(1) {
			child = gtk_grid_get_child_at(GTK_GRID (grid1),1 ,row );
			if (child != NULL) { // we found a disk!
			
				p = gtk_entry_get_text(GTK_ENTRY (child));
				printf("disk: %s\n", p);
				if( strcmp(p, token) == 0) {
					D printf("%s already in grid\n", token);
					break; // no need to add a grid entry
				}

			}
			if(row == row1) {
				//we found nothing, so add this to the grid
				D printf("add %s to grid\n", token);
				
				row1++;
				gtk_grid_insert_row(GTK_GRID (grid1), row1);
				entry = gtk_entry_new();
				gtk_entry_set_width_chars( GTK_ENTRY (entry), 8);
				gtk_editable_set_editable(  GTK_EDITABLE (entry), FALSE);
				gtk_grid_attach(GTK_GRID (grid1), GTK_WIDGET (entry), 1, row1, 1, 1);
				gtk_entry_set_text(GTK_ENTRY(entry), token);
				gtk_widget_show(entry);
				break;
			}
			row++; // next row
			
			}
			// we have a match, so reset, and go o next token
			row=0;		
		token = strtok(NULL, s);
}
	
	
	 free(sysdisk);
	}
	

	 /* update disk overview and combo boxes */
void on_gpart_refresh_clicked(GtkButton *b) {

	printf("gpart_refresh_clicked()\n");
	// first destroy any previous widgets, cleanup
	GList *children, *iter;
	
	children = gtk_container_get_children(GTK_CONTAINER(grid1));
	for(iter = children; iter != NULL; iter = g_list_next(iter))
	gtk_widget_destroy(GTK_WIDGET(iter->data));
  
	g_list_free(children);
	
	
	//reset combo
	hide_all();	
	

	// go
	char *ptr;
	ptr = parse_gpart();
	if (ptr == NULL)
		msg("couldnt parse gpart output!");
		

	// count the lines
	int i=0;
	int lines=1;
	
	while(ptr[i] != '\0') {
		if(ptr[i] == '\n')
			lines++;
	
		i++;	
	}
	D printf("lines: %i\n", lines);
	
	
	i=0;
	int row=0;
	int colum=1;
	int width=15;
	int len=0;
	char buf[30];
	int end=0;
	GtkWidget* entry;
	
	// we need at max this many rows in our grid, +1
	gtk_grid_insert_row(GTK_GRID (grid1), lines+1);
	
	/* parse entries
	 * identifyers are:
	* ! number 1 -
	* : number 2 -
	* # partition
	* $ disk -
	* ( size -
	* % scheme -
	* = free space -
	* ; type -
	* [ active
	*/
 
	while(1) {

		// disk ada
		if (ptr[i] ==  '$') {
			colum=1;
			width=8;
		}
		
		
		// number (=partition)
		else if( ptr[i] ==  '#') {
			colum=2;
			width=4;
		}
		
		// free space on disk
		else if( ptr[i] ==  '=') {
			colum=3;
			width=12;
	}
			
		// partition type
		else if(ptr[i] == ';' ) {
			colum=3;
			width=12;			
			}
	
		// partition scheme
		else if(ptr[i]  == '%' ) {
			colum=3;
			width=12;
			}
		
		// size is in brackets
		else if( ptr[i] ==  '(') {
			colum = 4;
			width=7;
			
			}
			
		// active
		else if(ptr[i] == '[' ) {
			colum=5;
			width=5;			
			}

		// for code safety, unidentified object
		else {
			//printf("else %c,%c,%c,\n", ptr[i], ptr[i+1], ptr[i+2]);
			colum = 99;
			//break;
			}
			
		i++; //skip identifyer;
		
		// len = length of the entry. i is either a char or a number or -

		while(1) {
			
			if (ptr[len+i] == '\0' ) {
				D printf("ups\n");
				end = 1;
				break;
				}
				
			if( (ptr[len+i] != ';' ) && (ptr[i+len] != '[') && (ptr[len+i]  != '#' ) && (ptr[len+i]  != '%' ) && ( ptr[len+i] !=  '(') && ( ptr[len+i] !=  '=')  && (ptr[len+i] !=  '$') &&  (ptr[len+i] !=  '!') && (ptr[len+i] !=  ':') )
				{
				len++;
				}

			else
			break;
			}
			
		if(colum != 99 ) {
//		printf("%c,%c,%c,%c\n", ptr[i], ptr[i+1], ptr[i+2], ptr[i+3]);
		
		// and zero terminate	
		strncpy(buf, &ptr[i], len);
		if(buf[len-1] == '\n' )
			buf[len-1] = '\0';
		else
			buf[len] = '\0';
		
		D printf("Grid entry: %s!len:%i\n", buf, len);

		// write in the grid

			entry = gtk_entry_new();
			gtk_entry_set_width_chars(GTK_ENTRY (entry), width);
			gtk_editable_set_editable(  GTK_EDITABLE (entry), FALSE);
			gtk_grid_attach(GTK_GRID (grid1), GTK_WIDGET (entry), colum, row, 1, 1);
			gtk_entry_set_text(GTK_ENTRY (entry), buf);
		}
		
		i=i+len;
		//printf(" Next:%c,%c,%c,\n", ptr[i], ptr[i+1], ptr[i+2]);
		//i++; // next word
		len=0; //reset

		// colum 4, partition size is last entry
		if(colum==4) 
			row++;
			//printf("row increased:\n", row);
			//i--;
			if(end == 1)
				break;
			//}
		}
		
	row1 = row;

	gtk_widget_show_all(scrolled3);
	free(ptr);
	
	add_missing();
	// for testing
	disk_combo();
	}


	 /* display the relevant choices
	  * for the gpart command
	  *  */
void on_gpart_combo_changed(GtkWidget *b)  {
	

	char *string;
	string = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo1));
	if(string == NULL)
		return;
		
	hide_all();
		
	if(strcmp(string, "destroy ") == 0) {
		D printf("Destroy\n");
		gtk_widget_show(GTK_WIDGET (combo4));		
		}

	else if(strcmp(string, "create") == 0) {
		gtk_widget_show(GTK_WIDGET (combo6) );
		gtk_widget_show(GTK_WIDGET(combo_disks));
		gtk_widget_show(GTK_WIDGET(entry5));
		//gtk_widget_show(GTK_WIDGET(entry7));
		}
	
	else if(strcmp(string, "add") == 0) {
		gtk_widget_show(GTK_WIDGET (combo4));
		gtk_widget_show(GTK_WIDGET (combo_types));
		gtk_widget_show(GTK_WIDGET (entry4));
		gtk_widget_show(GTK_WIDGET (entry6));
		gtk_widget_show(GTK_WIDGET(entry7));
		}
		
	else if(strcmp(string, "modify") == 0) {
		gtk_widget_show(GTK_WIDGET (combo5));
		gtk_widget_show(GTK_WIDGET (combo_types));
		gtk_widget_show(GTK_WIDGET(entry7));
		}
	
	
	else if(strcmp(string, "delete") == 0) {
		gtk_widget_show( GTK_WIDGET (combo5));
		}	
		
	else if(strcmp(string, "set") == 0) {
		gtk_widget_show(GTK_WIDGET (combo6));
		gtk_widget_show(GTK_WIDGET(entry8));
		}	
		
	else if(strcmp(string, "unset") == 0) {
		gtk_widget_show(GTK_WIDGET(combo6));
		gtk_widget_show(GTK_WIDGET(entry8));
		}		 
		
	else if(strcmp(string, "resize") == 0) {
		gtk_widget_show(GTK_WIDGET(combo5));
		gtk_widget_show(GTK_WIDGET (entry4));
		gtk_widget_show(GTK_WIDGET (entry6));
		}	
	
	else if(strcmp(string, "bootcode") == 0) {
		gtk_widget_show(GTK_WIDGET(combo6));
		gtk_widget_show(GTK_WIDGET (entry9));
		}
		
		
	else if(strcmp(string, "file system") == 0) {
		gtk_widget_show(GTK_WIDGET(combo6));
		gtk_widget_show(GTK_WIDGET(combo_fs));
	}
	
	g_free(string);
}

		 /* build a gpart command and execute it*/
void on_gpart_submit_clicked(GtkButton *b) {
	
	
	printf("gpart_submit()\n");
	// submit changes by means of:
	// consruct a gpart command
	// execute it
	// return string in msg box
	
	char cmd[200] ="/sbin/gpart ";
	int i=0;
	char part[20]="------------";
	int len=0;
	

	const gchar *action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo1) );
	if(action == NULL)
		return;
	
	/* big loop  */		
	if(strcmp(action, "destroy ") == 0) {
		
		 /* construct the gpart command  */
		strcat(cmd, action);
		g_free((void *)action);	
		strcat(cmd, " -F ");
		
		/* append disk */
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo4) );
		if(action != NULL) {
			strcat(cmd, action);
			g_free((void *)action);		
		}

		exe(cmd);
		}

	else if(strcmp(action, "create") == 0) {
		
		 /* construct the gpart command  */
		strcat(cmd, action);
		g_free((void *)action);	
		
		//append scheme
		strcat(cmd, " -s ");
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_disks) );
		if(action == NULL) {
			msg("choose a scheme.");
			goto end;
			}
			
		strcat(cmd, action);
		g_free((void *)action);		


		// append number
		action = gtk_entry_get_text( GTK_ENTRY(entry5) );
		len = strlen(action);
		if (len != 0) {
			strcat(cmd, " -n ");
			strcat(cmd, action);
			}
			
		//append disk
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo6) );
		strcat(cmd, " ");
		
		// if we create on a partition, we need
		// to replace p with s, as in ada2s1
		// therefore this hack:
		
		strcpy(part, action);
		len=0;
		while(part[len]  !=  '-') {
			len++;
			}
		len--;
		len--;
		i=len;

		while( (part[i] >= 0x30 ) &&  (part[i] <= 0x39 )  ) 
			i--;
		
		if (part[i] == 'p') // we have a partition
			{
			D printf("creating on partition, %c, i=%c\n", part[i-1], part[i]);
			if ( (part[i-1] >= 0x30 ) &&  (part[i-1] <= 0x39 ) ) {
				part[i]='s';
			}
			}
		strcat(cmd, part);
		g_free((void *)action);	
		
		exe(cmd);
		}
	
	else if(strcmp(action, "add") == 0) {
		
		// append action
		strcat(cmd, action);
		g_free((void *)action);	
				
		//append size
		action = gtk_entry_get_text(GTK_ENTRY (entry4));
		len = strlen(action);
		if (len != 0) {
			strcat(cmd, " -s ");
			strcat(cmd, action);
			}

		//append align
		action = gtk_entry_get_text(GTK_ENTRY (entry6));
		len = strlen(action);
		if (len != 0) {
			strcat(cmd, " -a ");
			strcat(cmd, action);
			}
	
		//append label
		action = gtk_entry_get_text(GTK_ENTRY (entry7));
		len = strlen(action);
		if (len != 0) {
			strcat(cmd, " -l ");
			strcat(cmd, action);
			}

		// append types
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_types) );
		if (action == NULL) {
				msg("choose a type.");
				goto end;
			}
		strcat(cmd, " -t ");
		strcat(cmd, action);

		g_free((void *)action);	

		//append disks
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo4) );
		if (action == NULL) {
			msg("choose a target.");
			goto  end;
		}
			strcat(cmd, " ");
			strcat(cmd, action);


		g_free((void *)action);	


		exe(cmd);
		}
		
	else if(strcmp(action, "modify") == 0) {

		// append action
		strcat(cmd, action);	
		g_free((void *)action);	
		
		
		//append label
		action = gtk_entry_get_text(GTK_ENTRY (entry7));
		len = strlen(action);
		if (len != 0) {
			strcat(cmd, " -l ");
			strcat(cmd, action);
			}
		
	
		//append index
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo5) );
		if(action == NULL) {
			goto end;
			}
		strcpy(part, action);
		
		printf(" string:%s \n", part);
		//extract partition number
		strcat(cmd, " -i ");
		len=0;
		while(part[len]  !=  '-') {
			len++;
			}
		len--;
		len--;
		D printf(" string:%s , len:%i\n", part, len);
		i=len;

		while( (part[i] >= 0x30 ) &&  (part[i] <= 0x39 )  ) {
			i--;
		}
		
		strcat(cmd, &part[i+1]);
		
		part[i]='\0';
		g_free((void *)action);	

		// append types
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_types) );
		if (action == NULL) {
			msg("choose a type.");
			goto end;
		}
			
		strcat(cmd, " -t ");
		strcat(cmd, action);
		
		g_free((void *)action);	

		//append disk
		strcat(cmd, " ");
		strcat(cmd, part);


		exe(cmd);
		}
	
	else if(strcmp(action, "delete") == 0) {

		// append action
		strcat(cmd, action);	
		g_free((void *)action);	

		//append index
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo5) );
		if(action == NULL) {
			msg("choose a target");
			goto end;
		}
		strcpy(part, action);
		
		D printf(" string:%s \n", part);
		//extract partition number
		strcat(cmd, " -i ");
		len=0;
		while(part[len]  !=  '-') {
			len++;
			}
		len--;
		len--;
		i=len;

		while( (part[i] >= 0x30 ) &&  (part[i] <= 0x39 )  ) {
			i--;
		}
		
		strcat(cmd, &part[i+1]);
		
		part[i]='\0';
		g_free((void *)action);	

		//append disk
		strcat(cmd, " ");
		strcat(cmd, part);
	
			exe(cmd);
		}	
		
	else if( (strcmp(action, "set") == 0) || (strcmp(action, "unset") == 0) ) {
		
		strcat(cmd, action);
		g_free((void *)action);	
				
		//append index
		
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo6) );
		if(action == NULL) {
			msg("choose a target");
			goto end;
			}
			
		g_free((void *)action);	
		strcpy(part, action);
		
		//extract partition number
		strcat(cmd, " -i ");
		len=0;
		while(part[len]  !=  '-') {
			len++;
			}
		len--;
		len--;
		printf(" resizing2::%s , len:%i\n", part, len);
		i=len;

		while( (part[i] >= 0x30 ) &&  (part[i] <= 0x39 )  ) {
			i--;
		}
		
		strcat(cmd, &part[i+1]);
		part[i]='\0';
		
		//append attributes
		action = gtk_entry_get_text(GTK_ENTRY (entry8));
		len = strlen(action);
		if (len != 0) {
			strcat(cmd, " -a ");
			strcat(cmd, action);
			}
			
			
		//append disk
		strcat(cmd, " ");
		strcat(cmd, part);
		
		exe(cmd);
		}	
		
		
	else if(strcmp(action, "resize") == 0) {
		
		strcat(cmd, action);
		g_free((void *)action);	

		//append index
		
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo5) );
		if(action == NULL ) {
			msg("choose a target.");
			goto end;
			}
			
		strcpy(part, action);
		
		D printf(" resizing:%s \n", part);
		//extract partition number
		strcat(cmd, " -i ");
		len=0;
		while(part[len]  !=  '-') {
			len++;
			}
		len--;
		len--;
		D printf(" resizing2::%s , len:%i\n", part, len);
		i=len;

		while( (part[i] >= 0x30 ) &&  (part[i] <= 0x39 )  ) {
			i--;
		}
		
		strcat(cmd, &part[i+1]);
		part[i]='\0';
		
		D printf(" resizing2:%s\n", cmd);
		
		//append size
		strcat(cmd, " -s ");
		
		action = gtk_entry_get_text(GTK_ENTRY (entry4));
		len = strlen(action);
		if (len != 0) 
			strcat(cmd, action);
		
		D printf(" resizing2:%s\n", cmd);
		
		//append align
		action = gtk_entry_get_text(GTK_ENTRY (entry6));
		len = strlen(action);
		if (len != 0) {
			strcat(cmd, " -a ");
			strcat(cmd, action);
			} 
			
		//append disk
		strcat(cmd, " ");
		strcat(cmd, part);

		D printf(" resizing2:%s\n", cmd);
		exe(cmd);
		}	
	
	else if(strcmp(action, "bootcode") == 0) {

		
		strcat(cmd, action);
		g_free((void *)action);	
		
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo6) );
		if(action == NULL) {
			msg("chose a target.");
			goto end;
			}
			
	
	// if we create on a partition, we need -i,
	// else just write -b bootfile ada1
		
		strcpy(part, action);
		len=0;
		while(part[len]  !=  '-') {
			len++;
			}
		len--;
		len--;
		i=len;

	while( (part[i] >= 0x30 ) &&  (part[i] <= 0x39 )  ) 
		i--;
		
	if (part[i] == 'p') // we have a partition
			{

		// append partition code
	
		action = gtk_entry_get_text(GTK_ENTRY (entry9));
		len=strlen(action);
		if (len !=0 ) {
			strcat(cmd, " -p ");	
			strcat(cmd, action);
			}
		//append index and disk
		//append index
		
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo6) );
		strcpy(part, action);
		
		D printf(" bootcoding:%s \n", part);
		//extract partition number
		strcat(cmd, " -i ");
		len=0;
		while(part[len]  !=  '-') {
			len++;
			}
		len--;
		len--;
		i=len;

		while( (part[i] >= 0x30 ) &&  (part[i] <= 0x39 )  ) {
			i--;
		}
		
		strcat(cmd, &part[i+1]);
		part[i]='\0';
				
		//append disk
		strcat(cmd, " ");
		strcat(cmd, part);

		exe(cmd);
		
			}
			
	else { //disk, so..
		
		// append bootcode		
		action = gtk_entry_get_text(GTK_ENTRY (entry9));
			if (len !=0 ) {
			strcat(cmd, " -b ");	
			strcat(cmd, action);
			}	
		// append disk
		strcat(cmd, " ");
		strcat(cmd, part);
		}
			

		
		exe(cmd);
	}
	
	
	else if(strcmp(action, "file system") == 0) {
		
		action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_fs) );
		if(action == NULL)
			msg("chose a file system type!");
			
		else if(strcmp(action, "ufs") == 0) {
			
			g_free((void *)action);
			strcpy(cmd, "newfs -U ");
			action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo6) );
			if(action == NULL) {
				msg("choose a target.");
				goto end;
			}
			strcat(cmd, action);
			exe(cmd);
			g_free((void *)action);
		}
		else if(strcmp(action, "ntfs") == 0) {
			
			g_free((void *)action);
			strcpy(cmd, "mkntfs ");
			action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo6) );
			if(action == NULL) {
				msg("choose a target.");
				goto end;
			}
			strcat(cmd, action);
			exe(cmd);
			g_free((void *)action);
		}

	
	}
	
end:
	on_gpart_refresh_clicked(GTK_BUTTON (window));
				
	}

	 /* create the main window and update the pointers */
int main(int argc, char *argv[]) {


	gtk_init(&argc, &argv);
	
	
	builder = gtk_builder_new_from_resource("/glade2.glade");
	
	if(builder==NULL)
		exit(1);
		
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_builder_connect_signals(builder, NULL);
	
	 
	/* fill our pointers */
	fixed1 = 	GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	fixed2 = 	GTK_WIDGET(gtk_builder_get_object(builder, "fixed2"));
	fixed3 = 	GTK_WIDGET(gtk_builder_get_object(builder, "fixed3"));	

	grid1 =	GTK_WIDGET(gtk_builder_get_object(builder, "grid1"));
	grid2 =	GTK_WIDGET(gtk_builder_get_object(builder, "grid2"));
	grid3 =	GTK_WIDGET(gtk_builder_get_object(builder, "grid3"));
	
	tree1 =	GTK_TREE_VIEW(gtk_builder_get_object(builder, "tree1"));
	treestore1 = GTK_TREE_STORE(gtk_builder_get_object(builder, "treestore1"));
	c1 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "c1"));
	c2 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "c2"));
	cr1 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr1"));
	cr2 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr2"));
	
	gtk_tree_view_column_add_attribute(c1, cr1, "text", 0);
	gtk_tree_view_column_add_attribute(c2, cr2, "text", 1);
	
	tree2 =	GTK_TREE_VIEW(gtk_builder_get_object(builder, "tree2"));
	treestore2 = GTK_TREE_STORE(gtk_builder_get_object(builder, "treestore2"));
	c3 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "c3"));
	c4 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "c4"));
	cr3 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr3"));
	cr4 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr4"));
	
	gtk_tree_view_column_add_attribute(c3, cr3, "text", 0);
	gtk_tree_view_column_add_attribute(c4, cr4, "text", 1);	

	combo1 =	GTK_WIDGET(gtk_builder_get_object(builder, "combo5"));
	entry4 =	GTK_WIDGET(gtk_builder_get_object(builder, "entry4"));
	entry5 =	GTK_WIDGET(gtk_builder_get_object(builder, "entry5"));
	entry6 =	GTK_WIDGET(gtk_builder_get_object(builder, "entry6"));
	entry7 =	GTK_WIDGET(gtk_builder_get_object(builder, "entry7"));
	entry8 =	GTK_WIDGET(gtk_builder_get_object(builder, "entry8"));
	entry9 =	GTK_WIDGET(gtk_builder_get_object(builder, "entry9"));
	scrolled3 = GTK_WIDGET(gtk_builder_get_object(builder, "scrolled3"));
	
	file1 =	GTK_WIDGET(gtk_builder_get_object(builder, "fchose1"));
	file2 =	GTK_WIDGET(gtk_builder_get_object(builder, "fchose2"));
	

	combo_d();
	combo_typ();
	camcontrol();
	glabel();
	fs_combo();

	
	gtk_widget_show(window);
	
	gtk_widget_hide(GTK_WIDGET (combo_disks));
	gtk_widget_hide(GTK_WIDGET (combo_types));
	gtk_widget_hide(GTK_WIDGET (combo_fs));
	gtk_widget_hide(GTK_WIDGET (entry4));
	gtk_widget_hide(GTK_WIDGET (entry5));
	gtk_widget_hide(GTK_WIDGET (entry6));


	on_gpart_refresh_clicked(GTK_BUTTON (combo5));

	fchose_combo();
	

	gtk_main();
	 
	
	return EXIT_SUCCESS;
}
