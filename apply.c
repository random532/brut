#include "disk.h"

void on_edit_clicked(GtkMenuItem *item, gpointer user_data) {

	char *cmd = malloc(150); /* the command we want to execute */
	if(cmd == NULL) {
		msg("malloc failed.");
		return;
	}
	memset(cmd, 0, 150);
	int inform = 1;
	int success = 0;
		
	/* what did our user choose? */
	const gchar *action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_geom) );
	/* big loop */
	if(action == NULL) {
		free(cmd);
		return;		
	}
	if(strncmp(action, "create", 6) == 0)
		cmd = gpart_create(cmd);	
	else if(strncmp(action, "destroy", 7) == 0)
		cmd = gpart_destroy(cmd);
	else if(strncmp(action, "add", 3) == 0)
		cmd = gpart_add(cmd);
	else if(strncmp(action, "delete", 6) == 0)
		cmd = gpart_delete(cmd);
	else if(strncmp(action, "modify", 6) == 0)
		cmd = gpart_modify(cmd);
	else if(strncmp(action, "resize", 7) == 0)
		cmd = gpart_resize(cmd);
	else if(strncmp(action, "set", 3) == 0)
		cmd = gpart_set(cmd);
	else if(strncmp(action, "unset", 5) == 0)
		cmd = gpart_set(cmd);
	else if(strncmp(action, "bootcode", 8) == 0)
		cmd = gpart_bootcode(cmd);
	else if(strncmp(action, "file system", 11) == 0) {
		cmd = gpart_filesystem(cmd);
		inform = 0;
	}
	 if(cmd != NULL) {
		 if(confirm==1)
			ask(cmd);
		else {
			success = execute_cmd(cmd, inform);
			if( (inform == 0) && (success != 0) )
				msg(merror);
			else if((inform == 0) && (success != 0))
				msg(mdone);
		}
		free(cmd);
		/* also redraw everything */
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

char *gpart_create( char *cmd) {

	/* "gpart create -s scheme gdisks" */
	strncat(cmd, "/sbin/gpart create -s ", 22);
	
	const gchar *gscheme = get_combo_box_scheme();
	if (gscheme == NULL) {
		free(cmd);
		return NULL;
	}
	
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
	if( gdisk == NULL) {
		free(cmd);
		return NULL;
	}
	strcat (cmd, gdisk);		/* gdisk */	
	return cmd;
}

char *gpart_destroy( char *cmd) {

	/* "gpart destroy gdisks */
	strncat(cmd, "/sbin/gpart destroy -F ", 23);

	const gchar *gdisk = get_combo_box_disk();
	if( gdisk == NULL) {
		free(cmd);
		return NULL;
	}
	strcat (cmd, gdisk);
	return cmd;
}

/* modify */
char *gpart_modify( char *cmd) {

	char *gpartition = get_combo_box_partition();
	if(gpartition == NULL) {
		free(cmd);
		return NULL;
	}

	const char *gtype = get_combo_box_type();
	if(gtype == NULL) {
		free(cmd);
		return NULL;
		}

	/* gpart modify -t gtype -l glabel - i index geom */
	strncat(cmd, "/sbin/gpart modify -t ", 22);
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
		if(i == 20) {
			free(cmd);
			return NULL;
		}
	}
	strncat(cmd, &gpartition[i+1], 2); /* index */
	strncat(cmd, " ", 1);
	strncat(cmd, gpartition, 20); /* geom */
	free(gpartition);
	return cmd;
}

	/* add */
char *gpart_add( char *cmd) {

	const char *gdisk = get_combo_box_disk();
	if(gdisk == NULL) {
		free(cmd);
		return NULL;
		}

	const char *gtype = get_combo_box_type();
	if(gtype == NULL) {
		free(cmd);
		return NULL;
		}

	/* "gpart add -t gtype -s gsize -a galignment -l glabel geom */
	strncat(cmd, "/sbin/gpart add -t ", 20);
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

	return cmd;
}

char *gpart_delete( char *cmd) {

	char *gpartition = get_combo_box_partition();
	if(gpartition == NULL) {
		free(cmd);
		return NULL;
		}

	/* "gpart delete -i index geom */
	strncat(cmd, "/sbin/gpart delete -i ", 22);
	
	int i=0;
	for(i=0; i<=20; i++) {
		if( gpartition[i] == (char) 0 )
			break;
		if(i == 20) {
			free(cmd);
			return NULL;
		}
	}
	strncat(cmd, &gpartition[i+1], 2); /* index */
	strncat(cmd, " ", 1);
	strncat(cmd, gpartition, 20);	/* geom */
	free(gpartition);
	return cmd;
}

	/* resize */
char *gpart_resize( char *cmd) {

	char *gpartition = get_combo_box_partition();
	if(gpartition == NULL) {
		free(cmd);
		return NULL;
		}
	const gchar *gsize = gtk_entry_get_text(GTK_ENTRY (text_size));
	if(strlen(gsize) == 0) {
		msg(chose_size);
		free(cmd);
		return NULL;
		}

	/* gpart resize -s gsize - i index geom */
	strncat(cmd, "/sbin/gpart resize ", 21);

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
		if(i == 20) {
			free(cmd);
			return NULL;
		}
	}
	strncat(cmd, &gpartition[i+1], 2); /* index */
	strncat(cmd, " ", 1);
	strncat(cmd, gpartition, 20);		/* geom */
	free(gpartition);
	return cmd;
}

char *gpart_set( char *cmd ) {

	const gchar *gcmd = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_geom) );
	if (gcmd == NULL) {	/* is never true */
		msg("Error.Don't know if set or unset.\n");
		free(cmd);
		return NULL;
		}
	if(strncmp(gcmd, "set", 3) == 0)
		strcpy(cmd, "/sbin/gpart set -a ");
	else if((strncmp(gcmd, "unset", 5)) == 0 )
		strcpy(cmd, "/sbin/gpart unset -a ");

	char *gpartition = get_combo_box_partition();
	if(gpartition == NULL) {
		free(cmd);
		return NULL;
		}

	const gchar *gbootoptions = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_bootoptions) );
	if(gbootoptions == NULL) {
		msg(chose_bootoptions);
		free(cmd);
		return NULL;
		}

	/* "gpart set -a attribute - i index geom" */
	
	if( (strlen(gbootoptions) > 0) && (strlen(gbootoptions) <= 20) )
		strcat(cmd, gbootoptions); /* attribute */
	strncat(cmd, " -i ", 4);	
	int i=0;
	for(i=0; i<=20; i++) {
		if( gpartition[i] == (char) 0 )
			break;
		if(i == 20) {
			free(cmd);
			return NULL;
		}
	}
	strncat(cmd, &gpartition[i+1], 2); /* index */
	strncat(cmd, " ", 1);
	strncat(cmd, gpartition, 20);		/* geom */

	free(gpartition);
	return cmd;
}

char *gpart_filesystem( char *cmd) {

	/* double check this */
	const gchar *gf = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_filesystems) );
		if(gf == NULL) {
			msg(chose_fs);
			free(cmd);
			return NULL; 
		}
	const gchar *gpartition = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (combo_partitions));
	if( gpartition == NULL) {
		msg(chose_partition);
		free(cmd);
		return NULL;
	}

	/* what did user chose? */

	if(strncmp(gf, "ufs2", 4) == 0) {
		strncat(cmd, "newfs ", 7);
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_journal)) == TRUE)
			strncat(cmd, "-J ", 4);
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_soft)) == TRUE)
			strncat(cmd, "-U ", 4);
		const gchar *glabel = gtk_entry_get_text(GTK_ENTRY (text_label));	/* label */
		if( (strlen(glabel) != 0) && (strlen(glabel) <= 20 ) ) {
			strncat(cmd, " -l ", 4);
			strcat(cmd, glabel);
		strncat(cmd, " ", 1);
		}
		strncat(cmd, "/dev/", 6);
		strcat(cmd, gpartition);
	}
	else if(strncmp(gf, "FAT32", 5) == 0) {
		strncat(cmd, "newfs_msdos ", 13);
		const gchar *glabel = gtk_entry_get_text(GTK_ENTRY (text_label));	/* label */
		if( (strlen(glabel) != 0) && (strlen(glabel) <= 20 ) ) {
			strncat(cmd, " -l ", 4);
			strcat(cmd, glabel);
			strncat(cmd, " ", 1);
		}
		strncat(cmd, "/dev/", 6);
		strcat(cmd, gpartition);
	}
	else if(strncmp(gf, "ntfs", 4) == 0) {
		strncat(cmd, "mkntfs ", 8);
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (toggle_fast)) == TRUE)
			strncat(cmd, "-f ", 4);
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (toggle_comp)) == TRUE)
			strncat(cmd, "-C ", 4);		
		const gchar *glabel = gtk_entry_get_text(GTK_ENTRY (text_label));	/* label */
		if( (strlen(glabel) != 0) && (strlen(glabel) <= 20 ) ) {
			strncat(cmd, " -l ", 4);
			strcat(cmd, glabel);
		strncat(cmd, " ", 1);
		}
		strncat(cmd, "/dev/", 6);
		strcat(cmd, gpartition);
	}
	
	free((void *) gpartition);
	free((void *) gf); //XXX: ???
	return cmd;
}

char *gpart_bootcode( char *cmd ) {
	
	int i=0;
	const char *gdisk;
	char *gpartition;
	
	const gchar *gf = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_bootcode) );
	if(gf == NULL) {
		msg("Partition? Disk?");
		free(cmd);
		return NULL; 
	}
	if(strncmp(gf, "Partition", 9) == 0) {
		gpartition = get_combo_box_partition();
		if( gpartition == NULL) {
			msg(chose_partition);
			free(cmd);
			return NULL;
		}
	}
	else if(strncmp(gf, "Disk", 4) == 0) {
		i=1; 
		gdisk = get_combo_box_disk();
		if( gdisk == NULL) {
			msg(chose_disk);
			free(cmd);
			return NULL;
		}
	}
	
	const char *fname = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(gfile));
	if (fname  == NULL) {
		msg("No File!");
		free(cmd);
		return NULL;
	}
	int len =strlen(fname);
	if(len >= 100 ) {
		msg("File name too long, sorry..");
		free(cmd);
		return NULL;
	}
	cmd = realloc(cmd, len+100);
	if( cmd == NULL) {
		msg("realloc() failed.");
		return NULL;
	}
	memset(cmd, 0, len+100);
	strncat(cmd, "/sbin/gpart bootcode ", 22);
	if(i == 1) {
		strncat(cmd, "-b ", 4);
		strncat(cmd, fname, len);
		strncat(cmd, " ", 2);
		strncat(cmd, "/dev/", 6);
		strncat(cmd, gdisk, 20);
		free( (void *) gdisk);
	}
	else {
		strncat(cmd, "-p ", 4);
		strncat(cmd, fname, len);
		strncat(cmd, " -i ", 5);
		int c=0;
	for(c=0; c<=20; c++) {
		if( gpartition[c] == (char) 0 )
			break;
		if(c == 20) {
			free(cmd);
			return NULL;
		}
	}
	strncat(cmd, &gpartition[c+1], 2); /* index */
	strncat(cmd, " ", 1);
	strncat(cmd, gpartition, 20); /* geom */
	free(gpartition);
	}

	free((void *) gf);
	return cmd;
}
