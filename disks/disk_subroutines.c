#include "disk.h"
#include "../brut.h"

/* return a buffer with disk names, space separated */
char *get_disks() {

	int size = 40;
	char *buf = malloc(size);
		if(buf == NULL)
			return NULL;	

	memset(buf, 0, size);

	FILE *fp = popen("geom disk status -s | awk '{print $1}'", "r");
	if(fp == NULL) {
		printf("could not execute geom disk status\n");
		free(buf);	
		return NULL;
	}

	char line[40];
	int len;
	while(fgets(line, sizeof line, fp) ) {

		len = strlen(line);
		line[len-1] = (char) 0;
		size = size + len + 5;
		buf = realloc(buf, size);
		if( buf == NULL)
			goto finish;
		strncat(buf, line, len);
		strncat(buf, " ", 1);

		memset(line, 0, sizeof line);
	}

	len = strlen(buf);
	buf[len-1] = (char) 0;

	finish:
	pclose(fp);
	return buf;
}

int add_slices() {

/* buffer to read input stream */
char line[50];

FILE *fp = popen("geom part status -s | awk '{print $1}'", "r");
if (fp == NULL) {
	printf("could not execute geom part status\n");
	return 0;
}

while(fgets(line, sizeof line, fp)) {

	int len = strlen(line);
	line[len-1] = (char) 0;
	
	if((strncmp(line, "diskid", 6) != 0) && (strncmp( line, "gptid", 5) != 0) ){

		/* Is this partition type "freebsd"? */
		char *ptype = get_type(line);
		if(ptype == NULL)
			return 0;
		if( (strncmp(ptype, "freebsd", 7) == 0 ) && (strlen(ptype) == 7) )  
			gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, line);
		free(ptype); 
	}
	/* prepare next round */
	memset(line, 0, sizeof line);
}

pclose(fp);
return 1;
}


int add_geoms() {

/* add disks to the combo box */

//	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combo_disks)); SLICES!

	FILE *fp = popen("geom disk status -s | awk '{print $1}'", "r");
	if (fp == NULL) {
		printf("could not execute geom disk status\n");	
		return 0;
	}

	char line[40];
	int len;
	while(fgets(line, sizeof line, fp)) {

		len = strlen(line);
		line[len-1] = (char) 0;
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (combo_disks), NULL, line); 
		memset(line, 0, sizeof line);
	}
pclose(fp);
return 1;
}

/* add all partitions on the system */
/* to the partition combo box */
int add_partitions() {

gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combo_partitions));

FILE *fp = popen("geom part status -s | awk '{print $1}'", "r");
if (fp == NULL) {
	printf("could not execute geom part status\n");
	return 0;
}

char line[50];
while(fgets(line, sizeof line, fp)) {

	int len = strlen(line);
	line[len-1] = (char) 0;

	if(strncmp(line, "diskid", 5) != 0 )
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (combo_partitions), NULL, line); 

	memset(line, 0, sizeof line);
}
	
pclose(fp);
return 1;
}

/* do we have empty space on the disk? */
/* pstart = starting sector */
/* pend = ending sector */
/* psectorsize = sectorsize */
char *check_free_space(char *pstart, char *pend, char *psectorsize) {

if( (pstart == NULL) || (pend == NULL))
	return NULL;

long p_end = strtol(pend, NULL, 0);	/* convert to integer */
long p_start = strtol(pstart, NULL, 0);
long result = p_start - p_end;

if(result <=100) 
	return NULL;

int size = 20;
char* free_megabytes = malloc(size);

long sectorsize = strtol(psectorsize, NULL, 0);
result = result * sectorsize;
result = result / 1024;	/* kilobytes */
result = result / 1024;	/* megabytes */

if(result <= 1024) {
	snprintf(free_megabytes, size, " %ld", result);
	strncat(free_megabytes, "M", 1);
}
else {
	result = result / 1024; /* gigabytes */
	snprintf(free_megabytes, size, " %ld", result);
	strncat(free_megabytes, "G", 1);
}
return free_megabytes;
}


void clean_up_pointers() {
	if(all_disks != NULL) {
		free(all_disks);
		all_disks = NULL;
	}
	if(all_partitions != NULL) {
		free(all_partitions);
		all_partitions = NULL;
	}
	if(all_slices != NULL) {
		free(all_slices);
		all_slices = NULL;
	}
}

char *what_file_system(char *partition) {

	char *cmd;
	char *error;
	char *fs_type;
	int len;
	int size;
	int ac;

	if(partition == NULL)
		return NULL;
	
	size = 25;
	fs_type = malloc(size);
	memset(fs_type, 0, size);

	/* check read permissions */	
	len = strlen(partition);
	len = len +50;
	cmd = malloc(len);
	memset(cmd, 0, len);
	snprintf(cmd, len, "/dev/%s", partition);
	ac = access(cmd, R_OK);
	
	if(ac == 0)  /* read access on device */
		snprintf(cmd, len, "fstyp -u /dev/%s 2>/dev/null", partition);
	else if(!pw_needed()) /* try as sudo if no password is needed */
		snprintf(cmd, len, "sudo -S fstyp -u /dev/%s 2>/dev/null", partition);
	else {
		/* dont bother asking for sudo password */
		strncpy(fs_type, "n/a", 4);
		return fs_type;
	}
	
	FILE *fp = popen(cmd, "r");
	if (fp == NULL) {
		printf("could not execute popen() with %s\n", partition);	
		free(cmd);
		return NULL;
	}
	error = fgets(fs_type, size, fp);
	pclose(fp);

	if(error == NULL) {
		free(fs_type);
		return NULL;
	}
	else {
		len = strlen(fs_type);
		fs_type[len-1] = '\0'; /* replace 0x0A */
	}
		
	free(cmd);
	return fs_type;
}


/*
void on_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
	// XXX: Obsolete?
	gtk_widget_destroy(GTK_WIDGET (dialog));	
}
*/

void ask_cb(GtkDialog *dialog, gint response_id, gpointer cmd) {
	/* YES -> execute, No -> skip */
	if((response_id == GTK_RESPONSE_YES) && (cmd != NULL) )
		submit(cmd, 0);
	free(cmd);
	gtk_widget_destroy(GTK_WIDGET (dialog));
	/* XXX: redraw? */
	on_toplevel_changed();
	gtk_widget_destroy(thegrid);
	editor();
}

/* ask for comfirmation */
void ask(char *cmd) {
	GtkWidget *message = gtk_message_dialog_new(GTK_WINDOW (window), GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, "%s", cmd);
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


int find_p(char *partition) {

/* return the partition index in a string like ada1p1 */
/* also remove any "s1" or p10" strings */

/* search backwards */
	int index=0;
	int slice;
	int len = strlen(partition);
	len--;
	
	if((partition[len] >= '0') && (partition[len] <= '9'))
		slice = 0;	/* slices are labeled with abcd.., not with numbers */

	else
		slice = 1;
		
	if(slice == 0) {
		while((partition[len] >= '0') && (partition[len] <= '9')) 
			len--;
		partition[len] = (char) 0;
		index = atoi(&partition[len+1]);	
	}
	else if(slice == 1) {
		
		/* can we do this more cleverly? */
		if(partition[len] == 'a')
			index=1;
		else if(partition[len] == 'b')
			index=2;
		else if(partition[len] == 'c')
			index=3;
		else if(partition[len] == 'd')
			index=4;
		else if(partition[len] == 'e')
			index=5;
		else if(partition[len] == 'f')
			index=6;
		else if(partition[len] == 'g')
			index=7;
		else if(partition[len] == 'h')
			index=8;
		else if(partition[len] == 'i')
			index=9;
		else if(partition[len] == 'j')
			index=10;
		else if(partition[len] == 'k')
			index=11;
		else if(partition[len] == 'l')
			index=12;
		else if(partition[len] == 'm')
			index=13;
		else if(partition[len] == 'n')
			index=14;
		else if(partition[len] == 'o')
			index=15;
		else if(partition[len] == 'p')
			index=16;
		else if(partition[len] == 'q')
			index=17;
		else if(partition[len] == 'r')
			index=18;				
		else if(partition[len] == 's')
			index=19;
		else if(partition[len] == 't')
			index=20;
		else if(partition[len] == 'u')
			index=21;
		else if(partition[len] == 'v')
			index=22;
		else if(partition[len] == 'w')
			index=23;
		else if(partition[len] == 'x')
			index=24;
		else if(partition[len] == 'y')
			index=25;
		else if(partition[len] == 'z')
			index=26;
		else  {/* unsupported */
			printf("xdisk: warning: I only support partitions up to 'z'!\n");
			index=0;
		}
		partition[len] = (char) 0;
	}		
	return index;
}

char *get_type( char *part) {
	
	if(part == NULL)
		return NULL;
	int len = strlen(part);
	
	/* extract the disk */
	char *disk = malloc(len+30);
	strncpy(disk, part, len+1);
	find_p(disk);
	
	char *cmd = malloc(CMDSIZE);
	snprintf(cmd, CMDSIZE, "geom part list %s | grep -A15 -E 'Name: %s' | awk '/ type: /{printf "" $2}'", disk, part);
	FILE *fp = popen(cmd, "r");
	char *type = disk;
	fgets(type, len+30, fp);
	pclose(fp);
	return type;
}

char *get_scheme(const gchar *gdisk) {
	
	char buf[CMDSIZE];
	memset(buf, 0, CMDSIZE);
	strncpy(buf, "gpart show ", 11);
	strcat(buf, gdisk);
	strncat(buf, " | awk 'NR==1{print $5}' ", 25); 
	
	FILE *fp = popen(buf, "r");
	if (fp == NULL) {
		msg("couldnt popen");
		return NULL;
	}
	char *scheme = malloc(40);
	fgets(scheme, 40, fp);
	int error = pclose(fp);
	if(error == 0)
		return scheme;
	else
		return NULL;
}


/* return a buffer with all the geom information */
char *read_disk(char *diskname) {

	int size = CMDSIZE;
	char buffer[CMDSIZE];
	snprintf(buffer, sizeof buffer, "geom part list %s 2>&1", diskname);

	char *diskinfo = malloc(size);
	if (diskinfo == NULL)
		return NULL;	

	memset(diskinfo, 0, size);

	FILE *fp = popen(buffer, "r");
	if (fp == NULL) {
		printf("could not execute geom part list %s\n", diskname);	
		return NULL;
	}
	memset(buffer, 0, sizeof buffer);
	
	while( fgets(buffer, sizeof buffer, fp) ) {
		
		if(strncmp(buffer, "geom:", 5) == 0) {
			pclose(fp);
			return diskinfo;
		}
		size= size + strlen(buffer);
		diskinfo = realloc(diskinfo, size +5);
		if(diskinfo == NULL) {
			printf("realloc(): failed\n");
			return NULL;
		}
		strcat(diskinfo, buffer);
		memset(buffer, 0, sizeof buffer);
	}
	
	pclose(fp);
	return diskinfo;
}

void fsscan() {
	
	todo = MOUNT;
	/* this is abit odd */
	char *cmd = malloc(10);
	strncpy(cmd, "whoami", 7); /* random command to start sudo timeout */
	window_pw(cmd);
}
