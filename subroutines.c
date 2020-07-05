#include "disk.h"


/* return a buffer with disk names, space separated */
char *get_disks() {

/* buffer to read input stream */
char line[150];

/* buffer to hold our disk names */
int disk_buf_size = 30;
char* disk_buf = malloc(disk_buf_size);
	if ( disk_buf == NULL ) {
		return NULL;	
	}
	memset(disk_buf, 0, disk_buf_size);

FILE * fp = popen("geom disk status -s", "r");
if ( fp == NULL ) {
	printf("could not execute geom disk status\n");
	free(disk_buf);	
	return NULL;
	}

while( fgets(line, sizeof line, fp) ) {

		strtok(line, " ");
		strcat( disk_buf, line );
		strcat( disk_buf, " " );	
	
		disk_buf_size = disk_buf_size + 7;	
		disk_buf = realloc(disk_buf, disk_buf_size);
		if(disk_buf == NULL ) {
			printf("realloc(): failed\n");			
			return NULL;
			}
 
	 memset(line, 0, 150);
	}

pclose(fp);
return disk_buf;
}

/* XXX: */
int add_slices() {

/* buffer to read input stream */
char line[150];
int len=150;
int i=0;
int e=0;

FILE * fp = popen("geom part status -gs", "r");
if ( fp == NULL ) {
	printf("could not execute geom part status\n");
	return 0;
	}

while( fgets(line, sizeof line, fp) ) {

	while(strncmp(&line[i], " ", 1) == 0)
		i++;
	e = i + 1;
	while(strncmp(&line[e], " ", 1) != 0)
		e++;
	line[e] = (char) 0;
	/* do some heuristics */
	/* we only want slices */
	/* so we inspect the string */
	if ( (strncmp(&line[i], "diskid", 6) != 0)) {
		e--; /* last char - always a number */
		e--;
		while( (line[e] == '0') || (line[e] == '1') || (line[e] == '2') \
		  || (line[e] == '3') || (line[e] == '4') || (line[e] == '5') \
		  || (line[e] == '6') || (line[e] == '7') || (line[e] == '8') \
		  || (line[e] =='9') )
		  e--;
		 e--; /* this is either 'p' or 's' */
		 if( (line[e] == '0') || (line[e] == '1') || (line[e] == '2') \
		  || (line[e] == '3') || (line[e] == '4') || (line[e] == '5') \
		  || (line[e] == '6') || (line[e] == '7') || (line[e] == '8') \
		  || (line[e] =='9') )
			gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, &line[i]); 
	}
	/* prepare next round */
	memset(line, 0, 150);
	i=0;
	e=0;
	}
	
pclose(fp);
return 1;
}

int add_geoms() {
	
/* buffer to read input stream */
char line[150];
int len=150;
int i=0;
int e=0;

FILE * fp = popen("geom disk status -gs", "r");
if ( fp == NULL ) {
	printf("could not execute geom part status\n");
	return 0;
	}

while( fgets(line, sizeof line, fp) ) {

	while(strncmp(&line[i], " ", 1) == 0)
		i++;
	e = i + 1;
	while(strncmp(&line[e], " ", 1) != 0)
		e++;
	line[e] = (char) 0;
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, &line[i]); 

	/* prepare next round */
	memset(line, 0, 150);
	i=0;
	e=0;
	}
	
pclose(fp);
return 1;
}
/* add all partitions on the system */
/* to the partition combo box */
int add_partitions() {

gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combo_partitions));

/* buffer to read input stream */
char line[150];
int len=150;
int i=0;
int e=0;

FILE * fp = popen("geom part status -s", "r");
if ( fp == NULL ) {
	printf("could not execute geom part status\n");
	return 0;
	}

while( fgets(line, sizeof line, fp) ) {

	while(strncmp(&line[i], " ", 1) == 0)
		i++;
	e = i + 1;
	while(strncmp(&line[e], " ", 1) != 0)
		e++;
	line[e] = (char) 0;
	if ( (strncmp(&line[i], "diskid", 6) != 0)) 
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_partitions), NULL, &line[i]); 
	
	/* prepare next round */
	memset(line, 0, 150);
	i=0;
	e=0;
	}
	
pclose(fp);
return 1;
}

/* return a buffer with all the geom information */
char *read_disk(char *diskname) {

	char buf[30]= "geom part list ";		
	char buffer[150];
	int size=150;	
	char* diskinfo = malloc(size);
	if ( diskinfo == NULL ) {
		return NULL;	
	}
	memset(diskinfo, 0, size);

	strcat(buf, diskname);
	strcat(buf ," 2>&1"); // also capture stderr
	FILE * fp = popen(buf, "r");
	if ( fp == NULL ) {
		printf("could not execute geom part list %s\n", diskname);	
	return NULL;
	}

	while( fgets(buffer, sizeof buffer, fp) ) {
		
		if(strncmp(buffer, "geom:", 5) == 0) {
			pclose(fp);
			return diskinfo;
			}
		size= size + strlen(buffer);
		diskinfo = realloc(diskinfo, size);
		if( diskinfo == NULL ) {
			printf("realloc(): failed\n");
			return NULL;
			}
		strcat(diskinfo, buffer);
		memset(buffer, 0, 150);
		}
	
	pclose(fp);
	return diskinfo;
}


/* remove brackets, i.e. () from a string */
void format_string(char* mystring) {

	int len = strlen(mystring);
	int i=0;

while(i < len) {
	if( (mystring[i] == '(') || (mystring[i] == ')') ){	
		mystring[i] = ' ';
		}
	i++;
	}
}

/* do we have empty space on the disk? */
/* pstart = starting sector */
/* pend = ending sector */
/* psectorsize = sectorsize */
char *check_free_space( char *pstart, char *pend, char *psectorsize) {

if( (pstart == NULL) || (pend == NULL) )
	return NULL;


long p_end = strtol(pend, NULL, 0);	/* convert to integer */
long p_start = strtol(pstart, NULL, 0);
long result = p_start - p_end;

if(result <=100 ) 
	return NULL;

char* free_megabytes = malloc(20);

long sectorsize = strtol(psectorsize, NULL, 0);
result = result * sectorsize;
result = result / 1024;	/* kilobytes */
result = result / 1024;	/* megabytes */

if( result <= 1024 ) {
	sprintf(free_megabytes, " %ld", result);
	strcat(free_megabytes, "M");
}
else {
	result = result / 1024; /* gigabytes */
	sprintf(free_megabytes, " %ld", result);
	strcat(free_megabytes, "G");
}
return free_megabytes;
}

/* increase or decrease fontsize */
void change_fontsize(int what) {

	long fsize = strtol(fontsize, NULL, 0);
   
	if( (what == 1) && (fsize < 15 ) )  	/* 1 increase, 0 decrease */ 
		fsize = fsize +1;
	if ((what == 0) && (fsize > 7) )
		fsize = fsize -1;

	sprintf(fontsize,"%ld", fsize);	
	on_toplevel_changed();
}

/* add a string to an existing string */
/* also adjust the buffer size */
char *add_to_list(char *pname, char *mylist) {

	int len, buflen;
	len = strlen(pname);

	if(mylist == NULL) {
		len = len + 5;
		mylist = malloc(len);
		if(mylist != NULL)
			strcpy(mylist, pname);
		}

	else {
		buflen = strlen(mylist);
		buflen = buflen + len + 2;
		mylist = realloc(mylist, buflen);
		strcat(mylist, " ");
		strcat(mylist, pname);
		}
return(mylist);
}

/* set back the list of disks, list of partitions, list of slices */
void clean_up_pointers() {
	if(all_disks != NULL) {
		free(all_disks);
		all_disks = NULL;
		}
	if(all_partitions != NULL) {
		free(all_partitions);
		all_partitions = NULL;
		}
	if(list_of_slices != NULL) {
		free(list_of_slices);
		list_of_slices = NULL;
		}
}

/* determine the file system on a partition */
/* uses fstyp(), which only suceeds as root */

char *what_file_system(char *partition) {

	if (partition == NULL)
		return NULL;

	char cmd[35];
	strcpy(cmd, "fstyp -u /dev/");
	strcat(cmd, partition);
	strcat(cmd ," 2>&1"); // also capture stderr

	int len= 40;
	char *fs_type = malloc(len);

	FILE * fp = popen(cmd, "r");
	if ( fp == NULL ) {
		printf("could not execute fstyp %s\n", partition);	
	return NULL;
	}

	if ( fgets(fs_type, len, fp) == NULL) {
		free(fs_type);
		return NULL;
		}
	else if (strncmp(fs_type,"fstyp:", 6) == 0 ) {
		/* that's either fs type not recognized, or permission denied */

		char *brk;
		strtok_r( &fs_type[8], ":", &brk);

		if(strncmp(brk, " Permission", 11) == 0) {
			strcpy(fs_type, "n/a");
			return fs_type;
			}
		free(fs_type);
		return NULL;
	}

	else {
	/* we actually have a file system */
		int len = strlen(fs_type);
		fs_type[len-1] = '\0'; /* replace 0x0A */

		gtk_window_set_title (GTK_WINDOW (window), "Xdisk - as root");
		return fs_type;
		}

}

/* execute a shell command */
/* return with a message box */

int execute_cmd(char * cmd, int inform) {

	char buf[200];
	
	strcpy(buf, cmd);
	strcat(buf ," 2>&1"); // also capture stderr
	
	FILE * fp = popen(buf, "r");
	if (fp == NULL)
		msg("couldnt popen");
	
	while( fgets(buf, sizeof buf, fp)) {
		
		}
	if(inform == 1)
		msg(buf);
	int suc = pclose(fp)/256;
		
	return suc;
}

	/* popup a message box */
void msg(char * blah) {
	GtkWidget * message = gtk_message_dialog_new(GTK_WINDOW (window_editor), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", blah);
	gtk_widget_show(message);
	g_signal_connect(message, "response", G_CALLBACK(on_response), NULL);
	}

	/* destroy message box if ok is clicked */
void on_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
	gtk_widget_destroy(GTK_WIDGET (dialog));	
}

	/* ask for comfirmation */
void ask(char * cmd) {
	GtkWidget *message = gtk_message_dialog_new(GTK_WINDOW (window_editor), GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, "%s", cmd);
	//gtk_dialog_set_default_response (GTK_DIALOG (message), GTK_RESPONSE_YES);
	
	int len = strlen(cmd);
	char *c = malloc(len+5);
	if(c != NULL) {
		memset(c, 0, len+5);
		strncpy(c, cmd, len);
	}
	gtk_widget_show(message);
	g_signal_connect(message, "response", G_CALLBACK(ask_cb), c);
}

void ask_cb(GtkDialog *dialog, gint response_id, gpointer c) {
	/* YES -> execute, No -> skip */
	if((response_id == GTK_RESPONSE_YES) && (c != NULL) ) {
		int success = execute_cmd(c, 1);
		if(success == 0)
			msg(mdone);
		else
			msg(merror);
	}
	free(c);
	gtk_widget_destroy(GTK_WIDGET (dialog));
}
/* execute a command */
/* return the result in a buffer */
char* command(char *cmd) {
	
	if(cmd == NULL)
		return NULL;
	int sz=150;
	char buf[150];
	char *ret = malloc(sz+2);
	if(ret == NULL)
		return NULL;

	FILE * fp = popen(cmd, "r");
	if (fp == NULL) {
		msg("fopen failed");
		return NULL;
	}
	while( fgets(buf, sizeof buf, fp)) {
		strncat(ret, buf, sz);
		sz = sz +150;
		ret = realloc(ret, sz);
		if(ret == NULL)
			return NULL;
		memset(buf, 0, 150);
	}
	pclose(fp);
	return ret;
}

/* find the partition index in a string like ada1p1 */
/* modify it to look like "ada1 1" */

int find_p(char *partition) {

/* search backwards */
int len = strlen(partition);
while( (partition[len] !='p') && (partition[len] != 's') )
	{
	/* handle slices */
	if( (partition[len] == 'a') || (partition[len] == 'b')  || (partition[len] == 'c')  || (partition[len] == 'd')  || (partition[len] == 'e')  || (partition[len] == 'f')  || (partition[len] == 'g') ) {
	/* an index should be a number, not a char */
		if(partition[len] == 'a')
			partition[len+1] = '1';
		else if(partition[len] == 'b')
			partition[len+1] = '2';
		else if(partition[len] == 'c')
			partition[len+1] = '3';
		else if(partition[len] == 'd')
			partition[len+1] = '4';
		else if(partition[len] == 'e')
			partition[len+1] = '5';
		else if(partition[len] == 'f')
			partition[len+1] = '6';
		else if(partition[len] == 'g')
			partition[len+1] = '7';
		partition[len+2] = (char) 0;
		break;
		}
	len--;
	if (len == 0)
		break;
	}

	partition[len] = (char) 0;
	return len;
}

int vari(char *line, int max) {
	int i = 0;
	while( (strncmp(&line[i], ":", 1) != 0) && (i < max) )
				i++;
	i++;
	
	/*XXX: is this good? */
	/* zero terminate instead of 0xA */
	int z = strlen(&line[i]);
	z = z + i;
	z--;
	line[z] = (char) 0;
	
	return i;
	}

void mountfs(GtkMenuItem *gmenu, gpointer gp) {
		/* mount a partition */
		
		const gchar *label = gtk_menu_item_get_label(gmenu);
		char * part = selected_item(tree1, 1);	/* partition */
		int plen = 	strlen(part); /* is this really 0 terminated? */
		int mlen = 0;
		char * fs = selected_item(tree1, 4); 	/* file system type */
		char *path;
		char *cmd;
		int success = 0;
		
		if( (part == NULL) || (fs == NULL) || (label == NULL) )
			return;
		
		/* mountpoint */
		if(strncmp(label, "/mnt", 4) == 0) {
			path = malloc(10);
			mlen = 4;
			strncpy(path, "/mnt", 5);
		}
		else if(strncmp(label, "/media", 7) == 0) {
			path = malloc(10);
			mlen = 6;
			strncpy(path, "/media", 7);
		}
		else {
			/* other path */
			/* file chooser dialog */
			GtkWidget * dialog;
			GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
			dialog = gtk_file_chooser_dialog_new("Mointpoint", GTK_WINDOW (window), action, "Cancel", GTK_RESPONSE_CANCEL, "Mount", GTK_RESPONSE_ACCEPT, NULL);
			gint res = gtk_dialog_run(GTK_DIALOG (dialog));
			if(res == GTK_RESPONSE_ACCEPT) {
				GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
				path = gtk_file_chooser_get_filename(chooser);
				mlen = strlen(path);
				gtk_widget_destroy(dialog);
			}
			else {
				gtk_widget_destroy(dialog);
				return;
			}
		}
		
		/* file system type */
		if(strncmp(fs, "ufs", 3) == 0) {
			cmd = malloc(plen + mlen + 20);
			memset(cmd, 0, plen + mlen + 20);
			strncpy(cmd, "mount /dev/", 12);
			strncat(cmd, part, plen);
			strncat(cmd, " ", 2);
			strncat(cmd, path, mlen);
		}
		else if(strncmp(fs, "msdos", 5) == 0) {
			cmd = malloc(plen + mlen + 30);
			memset(cmd, 0, plen + mlen + 30);
			strncpy(cmd, "mount -t msdosfs /dev/", 23);
			strncat(cmd, part, plen);
			strncat(cmd, " ", 2);
			strncat(cmd, path, mlen);
		}
		else if(strncmp(fs, "ntfs", 5) == 0) {
			cmd = malloc(plen + mlen + 30);
			memset(cmd, 0, plen + mlen + 30);
			strncpy(cmd, "ntfs-3g /dev/", 13);
			strncat(cmd, part, plen);
			strncat(cmd, " ", 2);
			strncat(cmd, path, mlen);
		}
		printf("%s\n", cmd);
		if(confirm==1)
			ask(cmd);
		else
			success = execute_cmd(cmd, 0);
			if(success == 0)
				msg(mdone);
			else
				msg(merror);
		free(cmd);
		free(path);
}

void unmountfs() {
	/* unmount a partition */
	char * part = selected_item(tree1, 1); /* get selected partition */
	if(part != NULL) {
		int len = strlen(part);
		char *cmd = malloc (len + 20);
		memset(cmd, 0, len+20);
		strncpy(cmd, "umount /dev/", 14);
		strncat(cmd, part, len);
		if(confirm==1)
			ask(cmd);
		else {
			int success = execute_cmd(cmd, 0);
			if(success == 0)
				msg(mdone);
			else
				msg(merror);
		}
		free(cmd);
	}
}
int is_mounted(char *part) {
	
	/* execute mount */
	/* see if we hit our partition */
	char buf[100];
	memset(buf, 0, 100);
	if (part == NULL)
		return 2; /* should never happen */
	int len = strlen(part);
	FILE * fp = popen("mount", "r");
	if (fp == NULL) {
		msg("fopen failed");
		return 2;
	}
	while( fgets(buf, sizeof buf, fp)) {
		
		if (strncmp(part, &buf[5], len) == 0) {
			/* mounted */
			return 1;
	}
		memset(buf, 0, 100);
	}
	pclose(fp);
	return 0; /* no match, not mounted*/
}

int root() {
	/* are we root? */
	uid_t perm = geteuid();
	if (perm != 0 ) {
		msg(no_root);
		return 0; /* no */
	}
	else
		return 1; /* yes */
}
