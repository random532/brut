#include "disk.h"

/* on_button_clicked functions */

	/* quit */	
void on_button_quit_clicked(GtkButton *b) {	
		gtk_main_quit();
}


	/* destroy message box if ok is clicked */
void on_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
	gtk_widget_destroy(GTK_WIDGET (dialog));	
}


	 /* update second tab*/
void on_buttonview1_clicked(GtkButton *b)
{
	glabel();
	camcontrol();
	
	}
	
	
	 /* img tab:
	  * do a ckecksum ckeck
	  * then execute dd */
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


	 /* update disk overview and combo boxes */
void on_gpart_refresh_clicked(GtkButton *b) {

	D printf("gpart_refresh_clicked()\n");

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
	* ! number 1
	* : number 2
	* # partition
	* $ disk 
	* ( size 
	* % scheme 
	* = free space 
	* ; type
	* [ attribute
	* * Corrupt
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
			width=8;			
			}

		// corrupt
		else if(ptr[i] == '*' ) {
			colum=6;
			width=8;			
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
				
			if( (ptr[len+i] != ';' ) && (ptr[i+len] != '[') && (ptr[len+i]  != '#' ) && (ptr[len+i]  != '%' ) && ( ptr[len+i] !=  '(') && ( ptr[len+i] !=  '=')  && (ptr[len+i] !=  '$') &&  (ptr[len+i] !=  '!') && (ptr[len+i] !=  ':') && (ptr[len+i] != '*') )
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
		
		D printf("Grid entry: %s!len:%i -", buf, len);

		// write in the grid

			entry = gtk_entry_new();
			gtk_entry_set_width_chars(GTK_ENTRY (entry), width);
			gtk_editable_set_editable(  GTK_EDITABLE (entry), FALSE);
			gtk_grid_attach(GTK_GRID (grid1), GTK_WIDGET (entry), colum, row, 1, 1);
			gtk_entry_set_text(GTK_ENTRY (entry), buf);
		}
		
		i=i+len;

		len=0; //reset

		// colum 4, partition size is last entry edit: not if corrupted!!
		if(colum==4) 
			row++;
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
	D printf("\ngpart_clicked end\n");
	}
	
			 /* build a gpart command and execute it*/
void on_gpart_submit_clicked(GtkButton *b) {
	
	
	D printf("gpart_submit()\n");
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
		
		D printf(" string:%s \n", part);
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
		D printf(" resizing2::%s , len:%i\n", part, len);
		i=len;

		while( (part[i] >= 0x30 ) &&  (part[i] <= 0x39 )  ) {
			i--;
		}
		
		strcat(cmd, &part[i+1]);
		part[i]='\0';
		
		//append attributes
		action = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (combo_s));
		if(action == NULL) {
			msg("choose an attribute.");
			goto end;
			}
			
		strcat(cmd, " -a ");
		strcat(cmd, action);
			
			
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
			len = strlen(action);
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
		
		else if(strcmp(action, "ufs1") == 0) {
			
			g_free((void *)action);
			strcpy(cmd, "newfs -U -O 1 ");
			action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo6) );
			if(action == NULL) {
				msg("choose a target.");
				goto end;
			}
			strcat(cmd, action);
			exe(cmd);
			g_free((void *)action);
		}
		
		else if(strcmp(action, "ufs2") == 0) {
			
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
		
		else if(strcmp(action, "FAT32") == 0) {
			
			g_free((void *)action);
			strcpy(cmd, "newfs_msdos -F 32 ");
			
			// append label		
			action = gtk_entry_get_text(GTK_ENTRY (entry7));
			len = strlen(action);
			if (len !=0 ) {
				strcat(cmd, " -L ");	
				strcat(cmd, action);
			}	
			
			// do we need disks/slices, or partitions..
			action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo6) );
			if(action == NULL) {
				msg("choose a target.");
				goto end;
			}
			strcat(cmd, " /dev/");
			strcat(cmd, action);
			exe(cmd);
			g_free((void *)action);
		}

		else if(strcmp(action, "ntfs") == 0) {
			
			g_free((void *)action);
			strcpy(cmd, "mkntfs -Q");
		
			// append label		
			action = gtk_entry_get_text(GTK_ENTRY (entry7));
			len = strlen(action);
			if (len !=0 ) {
				strcat(cmd, " -L ");	
				strcat(cmd, action);
			}	
			//todo: add sector start with "-p 40", e.g.
			//mkntfs -vIf -p 40 -H 16 -S 63 -L 'NTFS_slice' /dev/ada1p1
			
			action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo6) );
			if(action == NULL) {
				msg("choose a target.");
				goto end;
			}
			strcat(cmd, " /dev/");
			strcat(cmd, action);
			exe(cmd);
			g_free((void *)action);
		}

	
	}
	
end:
	on_gpart_refresh_clicked(GTK_BUTTON (b));
				
	}

