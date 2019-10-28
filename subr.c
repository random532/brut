#include "disk.h"

/* subroutines */


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
gtk_widget_hide(GTK_WIDGET (combo_s) );
gtk_widget_hide(GTK_WIDGET (entry9) );
}



	 /* execute gpart show
	  * put identifyers in front of each entry
	  * return a pointer to modified content 
	  * */
char * parse_gpart() {
	

	char line[250];	
	int linelen=0;
	
	int buflen=300;
	char * buf = malloc(buflen);
	if (buf == NULL) {
		D printf("malloc failed!\n");
		return NULL;
	}
	
	int pa=0; // counter of first buffer
	int pb=0; // counter of second buffer
	
	int cnt=0; // some counter

	int i=1;	// line counter, for debugging only
	//int ai=0;	// disk entry counter, for debugging only
	
	// execute gpart show
	
	FILE * fp = popen("/sbin/gpart show", "r");
	if (fp == NULL)
		printf("couldnt execute /sbin/gpart\n");



	while( fgets(line, sizeof line, fp)) {
	/* 
	/ first task:
	/ - remove double spaces
	/ - label the two numbers at 
	/ the beginning of each line, see gpart show
	/ - remove diskid entries 
	*/
 
	pa=0; //reset line
	D printf("line: %i\n%s", i, line);
	
	// is it an empty line?
	if(line[pa] == 0xA) 
		D printf("empty line\n");
	
	else {
	
	// resize buffer to fit our new line
	linelen = strlen(line);
	buflen = buflen + linelen;
	buf = realloc(buf, buflen);
	
	
	// find two numbers and write them to buf
	cnt = 0;
	while(cnt != 2) {
		if (( (line[pa] >= 0x30 ) &&  (line[pa] <= 0x39 )  )) {
			
			// we found a number, so increase cnt
			cnt++;
			
			// set an identifier
			if (cnt == 1)
				buf[pb] =  '!';
			if (cnt == 2)
				buf[pb] =  ':';
			
			pb++;
			
			//write number to the buffer
			
			while (line[pa] !=  ' ') {
				buf[pb] = line[pa];
				pa++;
				pb++; 
			}
			D printf("number - ");	
			

		}
		// else continue the search
		else
			pa++;
	}
		
	// skip space characters
	while(line[pa] == ' ')
		pa++;

	// diskid entry 
	if( (line[pa] == 'd' ) && (line[pa+1] == 'i') && (line[pa+2] == 's') && (line[pa+3] == 'k') && (line[pa+4] == 'i') && (line[pa+5] == 'd')) {
		
	D printf("diskid - ");
	buf[pb]='_';
	pb++;
	
	while(line[pa] != ' ') {
		pa++;
		}
	}
	
	else if( (line[pa] == 'g' ) && (line[pa+1] == 'p') && (line[pa+2] == 't') && (line[pa+3] == 'i') && (line[pa+4] == 'd')) {

		D printf("gptid - ");
		buf[pb]='_';
		pb++;
		
		while(line[pa] != ' ')
			pa++;
		}
	
	else if( (line[pa] == 'l' ) && (line[pa+1] == 'a') && (line[pa+2] == 'b') && (line[pa+3] == 'e') && (line[pa+4] == 'l')) {
		D printf("label - ");
		buf[pb]='_';
		pb++;
		
		while(line[pa] != ' ')
			pa++;
		}
			
	// disk			
	else if (( (line[pa] >=  'a') &&  (line[pa] <= 'z' )  )) {

		D printf("disk - ");
		// set identifier
		buf[pb] =  '$';
		pb++;
		// and copy
		while (line[pa] !=  ' ') {
				buf[pb] = line[pa];
				pa++;
				pb++; 
				}
			}

// now parse remaining entries

while (line[pa] != 0x0A) {

	// find the next entry
		while(line[pa] == ' ')
		pa++;
						
		// partition number
		if (( (line[pa] >= 0x30 ) &&  (line[pa] <= 0x39 )  )) {

			// set identifier
			buf[pb] =  '#';
			pb++;
				
			//and copy
			while (line[pa] !=  ' ') {
				buf[pb] = line[pa];
				pa++;
				pb++; 
				}
			D printf("partition - ");
			}

		// -free-
		else if (line[pa] ==  '-') {
			
			buf[pb] =  '=';
			buf[pb+1] =  'f';
			buf[pb+2] =  'r';
			buf[pb+3] =  'e';
			buf[pb+4] =  'e';
			pb= pb+5;
			pa = pa+7;
			
			D printf("free -");
			}

		// type		
		if (( (line[pa] >=  'a') &&  (line[pa] <= 'z' )  )) {

			// set identifier
			buf[pb] =  ';';
			pb++;
			// and copy
			while (line[pa] !=  ' ') {
					buf[pb] = line[pa];
					pa++;
					pb++; 
				}
			D printf("type -");
			}

		// schemes
		else if (( (line[pa] >=  'A') &&  (line[pa] <= 'Z' )  )) {
			
			// set identifier
			buf[pb] =  '%';
			pb++;

			// and copy
			while (line[pa] !=  ' ') {
					buf[pb] = line[pa];
					pa++;
					pb++; 
				}
			D printf("scheme - ");
			}
			
		// CORRUPT	
		else if( (line[pa] == '[') && (line[pa+1]== 'C'))	{
			D printf("Corrupt\n");
			
			// identifier
			buf[pb] = '*';
			pb++;
			pa++;
			
			// and copy
			while(line[pa] != ']') {

				buf[pb] = line[pa];
				pb++;
				pa++;
				
			}
			D printf("%c\n", line[pa]);

		}
			// attributes
		else if( line[pa] ==  '[')  {

			// and copy
			while (line[pa] !=  ']') {
					buf[pb] = line[pa];
					pa++;
					pb++; 
				}
			pa++; //needed??
			D printf("attrib - ");
			}

		//partition size
		else if ( line[pa] ==  '('  ) {

			// copy
			while (line[pa] !=  ')') {
					buf[pb] = line[pa];
					pa++;
					pb++; 
				}
		//	pa++;
		D printf("size - \n");
			}
			
	pa++;

}
	
	// We reached the end of a line
	// use '\n' instead of 0x0A
	D printf("end of line\n");
	buf[pb] = '\n';
	pb++;
	
	
	// debugging output
	i++;
//	D printf("\nline number: %i\n", i);

	} // empty lines are skipped
	} // gpart show ends here  


	// now zero terminate, and print the parsed string
	buf[pb-1] ='\0';
	D printf("end reached.\n-Start-\n%s\n-End-\n", buf);
	
	pclose(fp);
	
	// now sanitize it more
	buflen = strlen(buf);
	D printf("len: %i\n", buflen);
	char *ptr = malloc(buflen);
	pa= 0;
	pb = 0;
	
	while(1) {
		ptr[pa] = buf[pb];
		if(buf[pb]== '_') {
			
			// set pa
			while(ptr[pa] != '\n')
				pa--;
				
			// set pb 
			while((buf[pb] != '$') && (buf[pb] != '\0') ) {
				pb++;
				}
			
			if(buf[pb] == '$') {
				while(buf[pb] != '\n')
					pb--;
					
				}
			}
		if(buf[pb] == '\0') {
			break;
			}
	pa++;
	pb++;
	}
	ptr[pa] = '\0';
	
	D printf("end reached.\n\n-Start-\n%s\n-End-\n", ptr);
	
	free(buf);
	return(ptr);
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
		printf("camcontrol failed\n");
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
	int gtype = 0; // offset to label type
	int glabel = 0; // offset to label
	int gdisk = 0;	// offset to disk
	int error=0;
	
	FILE * fp = popen("glabel status", "r");
	if (fp == NULL) {
		printf("popen (glabel...) failed\n");
		return error;
		}

fgets(buf, sizeof buf, fp); // ignore first line

	while( fgets(buf, sizeof buf, fp)) {
		
		i=0;
		// skip spaces at the beginning of each line
		if(buf[i] == ' ') {
			while(buf[i] == ' ')
				i++;
}
	gtype = i;

	// find "/" and zero terminate it
		while(buf[i] != '/')
			i++;
	buf[i]='\0';
	
	i++;
	glabel = i;
		while(buf[i] != ' ')
			i++;

		buf[i]='\0';
		
		//and write both to textview 
		gtk_tree_store_append(treestore2 ,&iter2, NULL);
		gtk_tree_store_set(treestore2, &iter2, 0, &buf[gtype], -1);
		gtk_tree_store_set(treestore2, &iter2, 1, &buf[glabel], -1);
		
		i++;
		D printf("glabel entry: %s, %s\n", &buf[gtype], &buf[glabel]);
		// skip "status" entry in the glabel command
		while(buf[i] == ' ')
			i++;
		while(buf[i] != ' ')
			i++;
		while(buf[i] == ' ')
			i++;
		
		gdisk = i;
		
		// zero terminate instead of 0xA, which will break the treeview
		while(buf[i] != 0x0A)
			i++;
		buf[i]='\0';
		
		// write adaXpX to textview column 3
		gtk_tree_store_set(treestore2, &iter2, 2, &buf[gdisk], -1);
		D printf("glabel entry: %s\n", &buf[i]);

		}

		
	error = pclose(fp);

	D printf("glabel done\n");
	return 1;

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
		
		}
	msg(buf);
		int suc = pclose(fp)/256;
		D printf("%i == exit status of piped process\n\n", suc);
		
	return suc;
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
				D printf("disk: %s\n", p);
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
		gtk_widget_show(GTK_WIDGET(combo_s));
		}	
		
	else if(strcmp(string, "unset") == 0) {
		gtk_widget_show(GTK_WIDGET(combo6));
		gtk_widget_show(GTK_WIDGET(combo_s));
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
		gtk_widget_show(GTK_WIDGET(entry7));
	}
	
	g_free(string);
}

