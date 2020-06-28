#include "disk.h"

void on_edit_clicked(GtkMenuItem *item, gpointer user_data) {

	int gpart_success=0; /* whether gpart command succeeded */

	/* what did our user choose? */
	const gchar *action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_geom) );
	
	/* big loop */
	if(action == NULL)
		return;		
	if(strncmp(action, "create", 6) == 0)
		gpart_success = gpart_create();	
	else if(strncmp(action, "destroy", 7) == 0)
		gpart_success = gpart_destroy();
	else if(strncmp(action, "add", 3) == 0)
		gpart_success = gpart_add();
	else if(strncmp(action, "delete", 6) == 0)
		gpart_success = gpart_delete();
	else if(strncmp(action, "modify", 6) == 0)
		gpart_success = gpart_modify();
	else if(strncmp(action, "resize", 7) == 0)
		gpart_success = gpart_resize();
	else if(strncmp(action, "set", 3) == 0)
		gpart_success = gpart_set();
	else if(strncmp(action, "unset", 5) == 0)
		gpart_success = gpart_set();
	else if(strncmp(action, "bootcode", 8) == 0)
		gpart_success = gpart_bootcode();
	else if(strncmp(action, "file system", 11) == 0)
		gpart_success = gpart_filesystem();

	 if(gpart_success == 1) {
		on_toplevel_changed();
		gtk_widget_destroy(window_editor);
		editor();
		}
}

const char *get_combo_box_disk() {
/* retrieve combo box entry */

	const gchar *gdisk = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_disks) );
		if(gdisk == NULL) {
			msg(chose_disk);
			return NULL;
			}
	if( (strlen(gdisk) == 0) || (strlen(gdisk) >= 20 ) )
		return NULL; /* this should never happen though */	
	return gdisk;
}

const char *get_combo_box_scheme() {
/* retrieve combo box entry */

	const gchar *gscheme = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_schemes) );
		if(gscheme == NULL) {
			msg(chose_scheme);
			return NULL;
			}
	if( (strlen(gscheme) == 0)  || (strlen(gscheme) >= 20 ) )
		return NULL; /* should never be that long */

	return gscheme;
}

char *get_combo_box_partition() {

/* while we are here: */
/* make it char instead of const char */
/* also format it!! */

	const gchar *gpartition = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_partitions) );
	if(gpartition == NULL) {
		msg(chose_partition);
		return NULL;
	}
	
	int len = strlen(gpartition);
	if( (len == 0) || (len > 20) ) {
		free((void *)gpartition);
		return NULL;
		}
		
	char * buffer = malloc(len+10);
	memset(buffer, 0, (len+10));
	strncpy(buffer, gpartition, len);
	free((void *)gpartition);
	int sep = find_p(buffer);
	return buffer;
}

const char *get_combo_box_type() {

	const gchar *gtype = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_types) );
	if(gtype == NULL) {
		msg(chose_type);
		return NULL;
		}

	int len = strlen(gtype);
	if( (len == 0) || (len > 20) ) {
		free((void *)gtype);
		return NULL;
		}
	return gtype;
}

int gpart_create() {

	/* "gpart create -s scheme gdisks" */
	char cmd[100];
	memset(cmd, 0, 100);
	strncat(cmd, "/sbin/gpart create -s ", 22);
	
	const gchar *gscheme = get_combo_box_scheme();
	if (gscheme == NULL)
		return 0;
	
	if( (strncmp(gscheme, "GPT", 3)) == 0 ) /* the entry is "GPT (recommended)", skip last part */
		strncat( cmd, "GPT ", 4);
	else {
		strcat (cmd, gscheme);	/* scheme */	
		strcat (cmd, " ");
		} 

	const gchar *gentry = gtk_entry_get_text(GTK_ENTRY (text_entries));	/* optional entries */
	int i=strlen(gentry);
	if( (i != 0) && (i <= 15)) { /* XXX: maybe tell user that he entered bogus */
		strncat(cmd, "-n ", 3);
		strncat(cmd, gentry, i); 
		strncat(cmd, " ", 1);
		}

	const gchar *gdisk = get_combo_box_disk();
	if( gdisk == NULL)
		return 0;
	strcat (cmd, gdisk);		/* gdisk */

	if(confirm_yn==1)
		confirm(cmd);
	else
		execute_cmd(cmd);	
	return 1;
}

int gpart_destroy() {

	/* "gpart destroy gdisks */
	char cmd[100];
	memset(cmd, 0, 100);
	strncat(cmd, "/sbin/gpart destroy -F ", 23);

	const gchar *gdisk = get_combo_box_disk();
	if( gdisk == NULL)
		return 0;
	strcat (cmd, gdisk);

	if(confirm_yn==1)
		confirm(cmd);
	else
		execute_cmd(cmd);
	return 1;
}

/* modify */
int gpart_modify() {

	char *gpartition = get_combo_box_partition();
	if(gpartition == NULL) {
		return 0;
		}

	const char *gtype = get_combo_box_type();
	if(gtype == NULL) {
		return 0;
		}

	/* gpart modify -t gtype -l glabel - i index geom */
	char cmd[150] ="/sbin/gpart modify -t ";
	strcat(cmd, gtype); /* gtype */

	const gchar *glabel = gtk_entry_get_text(GTK_ENTRY (text_label));
	if( (strlen(glabel) > 0) && (strlen(glabel) <= 20) ) { //XXX: maybe interact with user if >20
		strncat(cmd, " -l ", 4);
		strcat(cmd, glabel); /* label */
		strncat(cmd, " ", 1);
		}

	strncat(cmd, " -i ", 4);
	int i=0;
	for(i=0; i<=20; i++) {
		if( gpartition[i] == (char) 0 )
			break;
		if(i == 20)
			return 0;
		}
	strncat(cmd, &gpartition[i+1], 2); /* index */
	strncat(cmd, " ", 1);
	strncat(cmd, gpartition, 20); /* geom */
	free(gpartition);
	
	if(confirm_yn==1)
		confirm(cmd);
	else
		execute_cmd(cmd);
	return 1;
}

	/* add */
int gpart_add() {

	const char *gdisk = get_combo_box_disk();
	if(gdisk == NULL) {
		return 0;
		}

	const char *gtype = get_combo_box_type();
	if(gtype == NULL) {
		return 0;
		}

	/* "gpart add -t gtype -s gsize -a galignment -l glabel geom */
	char cmd[150] ="/sbin/gpart add -t ";
	strcat(cmd, gtype);
	strncat(cmd, " ", 1);	

	const gchar *gsize = gtk_entry_get_text(GTK_ENTRY (text_size));
	if (strlen(gsize) != 0)  {	
		strncat(cmd, " -s ", 4);
		strncat(cmd, gsize, 10);	
		strncat(cmd, " ", 1);
	}

	const gchar *galignment = gtk_entry_get_text(GTK_ENTRY (text_alignment)); /* alignment */
	if( (strlen(galignment) != 0) && (strlen(galignment) <= 20 ) ){
		strncat(cmd, " -a ", 4);
		strcat(cmd, galignment); 
		strncat(cmd, " ", 1);
		}

	const gchar *glabel = gtk_entry_get_text(GTK_ENTRY (text_label));	/* label */
	if( (strlen(glabel) != 0) && (strlen(glabel) <= 20 ) ) {
		strncat(cmd, " -l ", 4);
		strcat(cmd, glabel);
		strncat(cmd, " ", 1);
		}

	strcat(cmd, gdisk);
	free((void *)gdisk);
	free((void *)gtype);

	if(confirm_yn==1)
		confirm(cmd);
	else
		execute_cmd(cmd);
	return 1;
}

int gpart_delete() {

	char *gpartition = get_combo_box_partition();
	if(gpartition == NULL) {
		return 0;
		}

	/* "gpart delete -i index geom */
	
	char cmd[100] ="/sbin/gpart delete -i ";
	
	int i=0;
	for(i=0; i<=20; i++) {
		if( gpartition[i] == (char) 0 )
			break;
		if(i == 20)
			return 0;
		}
	strncat(cmd, &gpartition[i+1], 2); /* index */
	strncat(cmd, " ", 1);
	strncat(cmd, gpartition, 20);	/* geom */
	free(gpartition);
	if(confirm_yn==1)
		confirm(cmd);
	else
		execute_cmd(cmd);

	return 1;
}

	/* resize */
int gpart_resize() {

	char *gpartition = get_combo_box_partition();
	if(gpartition == NULL) {
		return 0;
		}
	const gchar *gsize = gtk_entry_get_text(GTK_ENTRY (text_size));
	if(strlen(gsize) == 0) {
		msg(chose_size);
		return 0;
		}

	/* gpart resize -s gsize - i index geom */

	char cmd[100] ="/sbin/gpart resize ";

	const gchar *galignment = gtk_entry_get_text(GTK_ENTRY (text_alignment));	/* alignment */
	if( (strlen(galignment) != 0) && (strlen(galignment) <= 20 ) ) {
		strncat(cmd, "-a ", 3);
		strcat(cmd, galignment);
		}

	strncat(cmd," -s ", 4);		/* size */
	if( (strlen(gsize) != 0) && (strlen(gsize) <= 20 ) )
		strcat(cmd, gsize);
	strncat(cmd, " -i ", 4);

	int i=0;
	for(i=0; i<=20; i++) {
		if( gpartition[i] == (char) 0 )
			break;
		if(i == 20)
			return 0;
		}
	strncat(cmd, &gpartition[i+1], 2); /* index */
	strncat(cmd, " ", 1);
	strncat(cmd, gpartition, 20);		/* geom */
	free(gpartition);
	if(confirm_yn==1)
		confirm(cmd);
	else
		execute_cmd(cmd);
	return 1;
}

int gpart_set() {

	char cmd[100];
	const gchar *gcmd = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_geom) );
	if (gcmd == NULL) {	/* is never true */
		msg("Error.Don't know if set or unset.\n");
		return 0;
		}
	if(strncmp(gcmd, "set", 3) == 0)
		strcpy(cmd, "/sbin/gpart set -a ");
	else if((strncmp(gcmd, "unset", 5)) == 0 )
		strcpy(cmd, "/sbin/gpart unset -a ");

	char *gpartition = get_combo_box_partition();
	if(gpartition == NULL) {
		return 0;
		}

	const gchar *gbootoptions = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_bootoptions) );
	if(gbootoptions == NULL) {
		msg(chose_bootoptions);
		return 0;
		}

	/* "gpart set -a attribute - i index geom" */

	if( (strlen(gbootoptions) > 0) && (strlen(gbootoptions) <= 20) )
		strcat(cmd, gbootoptions); /* attribute */
	strncat(cmd, " -i ", 4);	
	int i=0;
	for(i=0; i<=20; i++) {
		if( gpartition[i] == (char) 0 )
			break;
		if(i == 20)
			return 0;
		}
	strncat(cmd, &gpartition[i+1], 2); /* index */
	strncat(cmd, " ", 1);
	strncat(cmd, gpartition, 20);		/* geom */

	free(gpartition);
	if(confirm_yn==1)
		confirm(cmd);
	else
		execute_cmd(cmd);
	return 1;
}

int gpart_filesystem() {

	/* double check this */
	const gchar *gf = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_filesystems) );
		if(gf == NULL) {
			msg(chose_fs);
			return 0; 
		}
	const gchar *gpartition = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (combo_partitions));
	if( gpartition == NULL) {
		msg(chose_partition);
		return 0;
	}

	/* what did user chose? */
	char cmd[100];
	memset(cmd, 0, 100);
	/*
	if(strncmp(gf, "ufs1", 4) == 0) {
		strncat(cmd, "newfs", 6);
		strcat(cmd, gpartition); //naaah
	}
	*/
	if(strncmp(gf, "ufs2", 4) == 0) {
		strncat(cmd, "newfs -JU /dev/", 14);
		strcat(cmd, gpartition);
	}
	else if(strncmp(gf, "FAT32", 5) == 0) {
		strncat(cmd, "newfs_msdos /dev/", 18);
		strcat(cmd, gpartition);
	}
	else if(strncmp(gf, "ntfs", 4) == 0) {
		strncat(cmd, "mkntfs -fC /dev/", 17);
		strcat(cmd, gpartition);
	}
	
	free((void *) gpartition);
	free((void *) gf); //XXX: ???
	if(confirm_yn==1)
		confirm(cmd);
	else
		execute_cmd(cmd);	
	return 1;
}
int gpart_bootcode() {
return 0;
}
