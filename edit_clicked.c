#include "disk.h"

void on_edit_clicked(GtkMenuItem *item, gpointer user_data) {

	int gpart_success=0;
	/* what did our user choose? */
	const gchar *action = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_geom) );


if(action == NULL)
		return;
	
	/* big loop  */		
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
		gpart_success = gpart_unset();
	else if(strncmp(action, "bootcode", 8) == 0)
		gpart_success = gpart_bootcode();
	else if(strncmp(action, "file system", 11) == 0)
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
			msg(chose_disk);
			return 0;
			}

	const gchar *scheme = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_schemes) );
		if(scheme == NULL) {
			msg("Chose a scheme!\n");
			return 0;
			}


	/* "gpart create -s scheme gdisks" */
	char cmd[100] ="/sbin/gpart create -s ";
	int max = 20;
	
	if( (strncmp(scheme, "GPT", 3)) == 0 )
		strncat( cmd, "GPT ", 4);
	else {
		strncat (cmd, scheme, max);	
		strncat (cmd, " ", 1);
		}

	max = strlen(gdisk);
	if( (max != 0) && (max <= 20) ) 
		strncat (cmd, gdisk, max);

	execute_cmd(cmd);
	return 1;
}

int gpart_destroy() {

	const gchar *gdisk = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_disks) );
	if(gdisk == NULL) {
		msg(chose_disk);
		return 0;
		}

	/* "gpart destroy gdisks */
	char cmd[100] ="/sbin/gpart destroy -F ";
	int max =strlen(gdisk);
	if( (max != 0) && (max <= 20 ) )
		strncat (cmd, gdisk, max);
	execute_cmd(cmd);

	return 1;
}

/* modify */
int gpart_modify() {

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

	/* gpart modify -t gtype -l glabel - i index geom */
	char cmd[100] ="/sbin/gpart modify -t ";
	int max=20;
	char buffer[max+2];
	strncpy(buffer, gpartition, max);
	int sep = find_p(buffer);

	if(strlen(gtype) <= max ) /* type */
		strncat(cmd, gtype, max);

	const gchar *glabel = gtk_entry_get_text(GTK_ENTRY (text_label));
	if( (strlen(glabel) != 0) && (strlen(glabel) <= max) ) {
	strncat(cmd, " -l ", 4);
	strncat(cmd, glabel, max); /* label */
	strncat(cmd, " ", 1);
		}

	strncat(cmd, " -i ", 4);
	strncat(cmd, &buffer[sep+1], 2); /* index */
	strncat(cmd, " ", 1);
	strncat(cmd, buffer, max); /* geom */

	execute_cmd(cmd);
	return 1;
}


/* add */
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
	int max=20;

	if (strlen(gtype) <= max )	/* type */
		strncat(cmd, gtype, max); 
	strncat(cmd, " -s ", 4);
	if ( strlen(gsize) <= max)	/* size */
		strncat(cmd, gsize, max);	
	strncat(cmd, " ", 1);

	const gchar *galignment = gtk_entry_get_text(GTK_ENTRY (text_alignment)); /* alignment */
	if( (strlen(galignment) != 0) && (strlen(galignment) <= max ) ){
		strncat(cmd, " -a ", 4);
		strncat(cmd, galignment, max); 
		strncat(cmd, " ", 1);
		}

	const gchar *glabel = gtk_entry_get_text(GTK_ENTRY (text_label));	/* label */
	if( (strlen(glabel) != 0) && (strlen(glabel) <= max ) ) {
		strncat(cmd, " -l ", 4);
		strncat(cmd, glabel, max);
		strncat(cmd, " ", 1);
		}

	if(strlen(gdisk) <= max )	/* geom */
		strncat(cmd, gdisk, max);

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

	char cmd[100] ="/sbin/gpart delete -i ";
	int max =20;
	char buffer[max+2];
	strncpy(buffer, gpartition, max);
	int sep = find_p(buffer);


	strncat(cmd, &buffer[sep+1] , max);	/* index */
	strncat(cmd, " ", 1);
	strncat(cmd, buffer, max);	/* geom */

	execute_cmd(cmd);

	return 1;
}


	/* resize */
int gpart_resize() {

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

	/* gpart resize -s gsize - i index geom */

	char cmd[100] ="/sbin/gpart resize ";
	int max= 20;
	char buffer[max+2];
	strncpy(buffer, gpartition, max);
	int sep = find_p(buffer);

	const gchar *galignment = gtk_entry_get_text(GTK_ENTRY (text_alignment));	/* alignment */
	if( (strlen(galignment) != 0) && (strlen(galignment) <= max ) ) {
		strncat(cmd, "-a ", 3);
		strncat(cmd, galignment, max);
		}

	strncat(cmd," -s ", 4);		/* size */
	if( (strlen(gsize) != 0) && (strlen(gsize) <= max ) )
		strncat(cmd, gsize, max);
	strncat(cmd, " -i ", 4);
	strncat(cmd, &buffer[sep+1] , max);	/* index */
	strncat(cmd, " ", 1);
	strncat(cmd, buffer, max);		/* geom */

	execute_cmd(cmd);
	return 1;
}

int gpart_set() {

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

	char cmd[100] ="/sbin/gpart set -a ";
	int max=20;
	char buffer[max+2];
	strncpy(buffer, gpartition, max);
	int sep = find_p(buffer);
	
	strncat(cmd, gbootoptions, max); /* attribute */
	strncat(cmd, " -i ", 4);	
	strncat(cmd, &buffer[sep+1], max );	/* index */
	strncat(cmd, " ", 1);
	strncat(cmd, buffer, max);		/* geom */

	execute_cmd(cmd);

	return 1;
}
int gpart_unset() {


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

	char cmd[100] ="/sbin/gpart unset -a ";
	
	int max = 20;	
	char buffer[max+2];
	strncpy(buffer, gpartition, max);
	int sep = find_p(buffer);
	
	strncat(cmd, gbootoptions, max);	/* attribute */
	strncat(cmd, " -i ", 4);		/* index */
	strncat(cmd, &buffer[sep+1], max );
	strncat(cmd, " ", 1);			/* geom */
	strncat(cmd, buffer, max);

	execute_cmd(cmd);

	return 1;
}
int gpart_filesystem() {
return 0;
}
int gpart_bootcode() {
return 0;
}



