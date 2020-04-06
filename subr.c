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

FILE * fp = popen("geom disk status", "r");
if ( fp == NULL ) {
	printf("could not execute geom disk status\n");
	free(disk_buf);	
	return NULL;
	}

while( fgets(line, sizeof line, fp) ) {

	if (strncmp (line, "Name", 4) != 0 )
		{
		strtok(line, " ");
		strcat( disk_buf, line );
		strcat( disk_buf, " " );	
	
		disk_buf_size = disk_buf_size + 10;	
		disk_buf = realloc(disk_buf, disk_buf_size);
		if(disk_buf == NULL ) {
			printf("realloc(): failed\n");			
			return NULL;
			}
		} 
	 memset(line, 0, 150);
	}
pclose(fp);
return disk_buf;
}

/* return a buffer with all the geom information */
char *read_disk(char *diskname) {

	char buf[35]= "geom part list "; /* ... "ada1p3" */
	int size=150;	/* geom returns info in lines, size is max line length */	
	char buffer[size+2];
	
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
	if(result <=100 ) 		/* too little to bother */
		return NULL;

	long sectorsize = strtol(psectorsize, NULL, 0);
	result = result * sectorsize;
	result = result / 1024;	/* kilobytes */
	result = result / 1024;	/* megabytes */

	char* free_megabytes = malloc(30);
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
	g_object_set(cell, "font", fontsize, NULL);
	redraw_treeview();
}

/* add a string to an existing string */
/* also adjust the buffer size */
char * add_to_list(char *pname, char *mylist) {

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
	if(list_of_disks != NULL) {
		free(list_of_disks);
		list_of_disks = NULL;
		}
	if(list_of_partitions != NULL) {
		free(list_of_partitions);
		list_of_partitions = NULL;
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
			gtk_window_set_title (GTK_WINDOW (window), "Xdisk - no root!");
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

int execute_cmd(char * cmd) {

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

