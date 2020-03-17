#include "disk.h"

void on_edit_clicked(GtkMenuItem *item, gpointer user_data) {

	int gpart_success=0;
	/* what did our user choose? */
	const gchar *action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_geom) );


if(action == NULL)
		return;
	
	/* big loop  */		
	if(strcmp(action, "create") == 0)
		gpart_success = gpart_create();	
	else if(strcmp(action, "destroy") == 0)
		gpart_success = gpart_destroy();
	else if(strcmp(action, "add") == 0)
		gpart_success = gpart_add();
	else if(strcmp(action, "delete") == 0)
		gpart_success = gpart_delete();
	else if(strcmp(action, "modify") == 0)
		gpart_success = gpart_modify();
	else if(strcmp(action, "resize") == 0)
		gpart_success = gpart_resize();
	else if(strcmp(action, "set") == 0)
		gpart_success = gpart_set();
	else if(strcmp(action, "unset") == 0)
		gpart_success = gpart_unset();
	else if(strcmp(action, "bootcode") == 0)
		gpart_success = gpart_bootcode();
	else if(strcmp(action, "file system") == 0)
		gpart_success = gpart_filesystem();

	 if(gpart_success == 1) {
		redraw_treeview();
		gtk_widget_destroy(window_editor);
		editor();
		}
}

int gpart_create() {

const gchar *gdisk = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_disks) );
	if(gdisk == NULL) {
		msg("chose a disk!\n");
		return 0;
		}

const gchar *scheme = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_schemes) );
	if(scheme == NULL) {
		msg("chose a scheme!\n");
		return 0;
		}


/* "gpart create -s scheme gdisks" */
char cmd[100] ="/sbin/gpart create -s ";

if( (strncmp(scheme, "GPT", 3)) == 0 )
	strcat( cmd, "GPT ");
else {
	strcat (cmd, scheme);
	strcat (cmd, " ");
	}

strcat (cmd, gdisk);
execute_cmd(cmd);
return 1;
}

int gpart_destroy() {

const gchar *gdisk = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_disks) );
	if(gdisk == NULL) {
		msg("chose a disk!\n");
		return 0;
		}

/* "gpart destroy gdisks */
char cmd[100] ="/sbin/gpart destroy -F ";
strcat (cmd, gdisk);
execute_cmd(cmd);
return 1;
}

int gpart_modify() {

char buffer[20];

const gchar *gpartition = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_partitions) );
	if(gpartition == NULL) {
		msg(chose_partition);
		return 0;
		}

const gchar *gtype = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_types) );
	if(gtype == NULL) {
		msg(chose_type);
		return 0;
		}

/* gpart modify -t gtype - i index geom */
int sep = find_p(gpartition);
char cmd[100] ="/sbin/gpart modify -t ";

strcat(cmd, gtype);
strcat(cmd, " -i ");

strcpy(buffer, gpartition);
buffer[sep] = (char) 0;
strcat(cmd, &buffer[sep+1] );
strcat(cmd, " ");
strcat(cmd, buffer);

execute_cmd(cmd);

return 1;
}

int gpart_add() {
const gchar *gdisk = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_disks) );
	if(gdisk == NULL) {
		msg(chose_disk);
		return 0;
		}

const gchar *gtype = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_types) );
	if(gtype == NULL) {
		msg(chose_type);
		return 0;
		}

const gchar *gsize = gtk_entry_get_text(GTK_ENTRY (text_size));
	if (strlen(gsize) == 0) {
		msg(chose_size);
		return 0;
		}

/* "gpart add -t gtype -s gsize -a galignment -l glabel geom */
char cmd[130] ="/sbin/gpart add -t ";

strcat(cmd, gtype);
strcat(cmd, " -s ");
strcat(cmd, gsize);
strcat(cmd, " ");

const gchar *galignment = gtk_entry_get_text(GTK_ENTRY (text_alignment));
	if(strlen(galignment) != 0) {
	strcat(cmd, " -a ");
	strcat(cmd, galignment);
	strcat(cmd, " ");
		}

const gchar *glabel = gtk_entry_get_text(GTK_ENTRY (text_label));
	if(strlen(glabel) != 0) {
	strcat(cmd, " -l ");
	strcat(cmd, glabel);
	strcat(cmd, " ");
		}

strcat(cmd, gdisk);

execute_cmd(cmd);
return 1;
}


int gpart_delete() {

const gchar *gpartition = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_partitions) );
	if(gpartition == NULL) {
		msg(chose_partition);
		return 0;
		}

/* "gpart delete -i index geom */
char buffer[20];
int sep = find_p(gpartition);
char cmd[100] ="/sbin/gpart delete -i ";

strcpy(buffer, gpartition);
buffer[sep] = (char) 0;
strcat(cmd, &buffer[sep+1] );
strcat(cmd, " ");
strcat(cmd, buffer);

execute_cmd(cmd);
return 1;
}

int gpart_resize() {
char buffer[20];

const gchar *gpartition = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_partitions) );
	if(gpartition == NULL) {
		msg(chose_partition);
		return 0;
		}
const gchar *gsize = gtk_entry_get_text(GTK_ENTRY (text_size));
	if(strlen(gsize) == 0) {
		msg(chose_size);
		return 0;
		}

/* gpart modify -t gtype - i index geom */
int sep = find_p(gpartition);
char cmd[100] ="/sbin/gpart resize ";

const gchar *galignment = gtk_entry_get_text(GTK_ENTRY (text_alignment));
	if(strlen(galignment) != 0) {
	strcat(cmd, "-a ");
	strcat(cmd, galignment);
		}

strcat(cmd," -t ");
strcat(cmd, gsize);
strcat(cmd, " -i ");

strcpy(buffer, gpartition);
buffer[sep] = (char) 0;
strcat(cmd, &buffer[sep+1] );
strcat(cmd, " ");
strcat(cmd, buffer);

execute_cmd(cmd);

return 1;
}

int gpart_set() {

char buffer[20];

const gchar *gpartition = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_partitions) );
	if(gpartition == NULL) {
		msg(chose_partition);
		return 0;
		}

const gchar *gbootoptions = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_bootoptions) );
	if(gbootoptions == NULL) {
		msg(chose_bootoptions);
		return 0;
		}

/* "gpart set -a attribute - i index geom" */
int sep = find_p(gpartition);
char cmd[100] ="/sbin/gpart set -a ";

strcat(cmd, gbootoptions);
strcat(cmd, " -i ");

strcpy(buffer, gpartition);
buffer[sep] = (char) 0;
strcat(cmd, &buffer[sep+1] );
strcat(cmd, " ");
strcat(cmd, buffer);

execute_cmd(cmd);

return 1;
}
int gpart_unset() {
char buffer[20];

const gchar *gpartition = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_partitions) );
	if(gpartition == NULL) {
		msg(chose_partition);
		return 0;
		}

const gchar *gbootoptions = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_bootoptions) );
	if(gbootoptions == NULL) {
		msg(chose_bootoptions);
		return 0;
		}

/* "gpart set -a attribute - i index geom" */
int sep = find_p(gpartition);
char cmd[100] ="/sbin/gpart unset -a ";

strcat(cmd, gbootoptions);
strcat(cmd, " -i ");

strcpy(buffer, gpartition);
buffer[sep] = (char) 0;
strcat(cmd, &buffer[sep+1] );
strcat(cmd, " ");
strcat(cmd, buffer);

execute_cmd(cmd);

return 1;
}
int gpart_filesystem() {
return 0;
}
int gpart_bootcode() {
return 0;
}



