#include "disk.h"


/* returns a buffer with disk names, space separated */

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
	
		disk_buf_size = disk_buf_size + 7;	
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


char *check_free_space( char *pstart, char *pend_old, char *psectorsize) {

if( (pstart == NULL) || (pend_old == NULL) )
	return NULL;


long p_end = strtol(pend_old, NULL, 0);
long p_start = strtol(pstart, NULL, 0);
long result = p_start - p_end;

if(result <=100 ) 
	return NULL;

char* free_megabytes = malloc(20);

long sectorsize = strtol(psectorsize, NULL, 0);
result = result * sectorsize;
result = result / 1024;
result = result / 1024;

if( result <= 1024 ) {
	sprintf(free_megabytes, " %ld", result);
	strcat(free_megabytes, "M");
}
else {
	result = result / 1024;
	sprintf(free_megabytes, " %ld", result);
	strcat(free_megabytes, "G");
}


return free_megabytes;
}


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

char *what_file_system(char *partition) {

	if (partition == NULL)
		return NULL;

	char cmd[30];
	strcpy(cmd, "fstyp /dev/");
	strcat(cmd, partition);
	strcat(cmd ," 2>&1"); // also capture stderr

	char *fs_type = malloc(30);

	FILE * fp = popen(cmd, "r");
	if ( fp == NULL ) {
		printf("could not execute fstyp %s\n", partition);	
	return NULL;
	}

	if ( fgets(fs_type, 25, fp) == NULL) {
		free(fs_type);
		return NULL;
		}
	else if (strncmp(fs_type,"fstyp:", 6) == 0 ) {
		/* that's either fs type not recognized, or permission denied */
		strcpy(fs_type, "n/a");
		return fs_type;
		}

	else {
	/* we actually have a file system */
		int len = strlen(fs_type);
		fs_type[len-1] = '\0'; /* replace 0x0A */
		return fs_type;
		}

}

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
		printf("%i == exit status of piped process\n\n", suc);
		
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

int find_p(const char *partition) {

int len = strlen(partition);
while( (partition[len] !='p') && (partition[len] != 's') )
	{
	len--;
	if (len == 0)
		break;
	}

return len;
}

