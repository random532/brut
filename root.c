#include "disk.h"

char *sudo( char *cmd, char *passw, int pw) {

	if( (cmd == NULL) || (strlen(cmd) == 0) )
		return NULL;
	if( (passw == NULL) || (strlen(passw) == 0) )
		return NULL;
		
	int len = strlen(cmd);
	int len1 = strlen(passw);
	int len2 = len + len1 + 30;
	char *rcmd = malloc(len2);
	if( rcmd == NULL )
		return NULL;

	if(pw == 1)
		snprintf(rcmd, len2, "echo \"%s\" | sudo -S %s", passw, cmd);
	else
		snprintf(rcmd, len2, "sudo -S %s", cmd); /* XXX: add -n ? */
	free(cmd);
	return rcmd;
}

int test_pw(char *passw) {
	
	char buf[200];
	memset(buf, 0, 200);
	if( (passw == NULL) || (strlen(passw) > 100) )
		return 0;

	snprintf(buf, 200, "echo \"%s\" | sudo -S whoami 2>/dev/null", passw);
	FILE * fp = popen(buf, "r");
	if (fp == NULL)
		return 0;
	
	fgets(buf, sizeof buf, fp);
	if(strncmp(buf, "root", 4) == 0) {
		pclose(fp);
		return 1;
	}
	else {
		pclose(fp);
		msg(l.no_root);
		return 0;
	}
}

int pw_needed() {

	int error;	
	FILE * fp = popen("sudo -nv 2>/dev/null", "r");
	if (fp == NULL)
		return 1;
	
		error = pclose(fp)/256;
		if(error != 0)
			return 1; /* yes, a password is needed */
		else
			return 0;
}

void c_cb(GtkMenuItem *item, gpointer cmd) {
	
	/* "Cancel" button */
	if(cmd != NULL)
		free(cmd);
	char *hash = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	gtk_entry_set_text(GTK_ENTRY (passbuf),  hash);
	gtk_widget_destroy(su);
	on_toplevel_changed();
	if( (window_editor != NULL) && (todo != MOUNT )) {
		gtk_widget_destroy(window_editor);
		editor();
	}
}

void o_cb(GtkMenuItem *item, gpointer cmd) {
		
	/* "Okay" button */
	const gchar *pass = gtk_entry_get_text(GTK_ENTRY (passbuf));
	int len = strlen(pass);
	if( (len == 0) || (len > 100 ) ) {
		msg(l.no_root);
		goto bad;
	}
	
	/* dont depend on gtk_entry text */
	char *passw = malloc(len+10);
	strncpy(passw, pass, len+1);
	
	/* test password */
	if( (test_pw( passw) == 0) || (cmd == NULL) )
		goto bad;

	cmd = sudo(cmd, passw, 1);
	free(passw);
	
	submit(cmd, confirm);
	if(confirm == 0)
		free(cmd);
	gtk_widget_destroy(su);
	on_toplevel_changed();
	if(window_editor != NULL) {
		gtk_widget_destroy(window_editor);
		editor();
	}
	return;

bad:	
	if(cmd != NULL)
		free(cmd);
	gtk_widget_destroy(su);
	on_toplevel_changed();
	if( (window_editor != NULL) && (todo != MOUNT) ){
		gtk_widget_destroy(window_editor);
		editor();
	}
}

void window_pw(char *cmd) {
	
	/* this window asks for root password */
	su = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (su), "sudo password");
	gtk_container_set_border_width (GTK_CONTAINER (su), 30);
	gtk_window_set_default_size(GTK_WINDOW (su), 250, 100);
	gtk_window_set_modal(GTK_WINDOW(su), TRUE);
	gtk_window_set_transient_for(GTK_WINDOW(su), GTK_WINDOW(window)); 
	
	gint x = 0, y = 0, width, height;
	gtk_window_get_position (GTK_WINDOW(window), &x, &y);
	gtk_window_get_size(GTK_WINDOW (window), &width, &height);
	x = x +150;
	y = y + 50;
	gtk_window_move( GTK_WINDOW(su), x, y);
	
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add (GTK_CONTAINER (su), box);

	GtkWidget *agrid = gtk_grid_new();
	gtk_grid_insert_column(GTK_GRID(agrid), 3);
	gtk_box_pack_end(GTK_BOX(box), agrid, TRUE, TRUE, 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(agrid), FALSE);
	gtk_grid_set_column_spacing(GTK_GRID(agrid), 85);
	
	GtkEntryBuffer *pass = gtk_entry_buffer_new (NULL, 0);
	gtk_entry_buffer_set_max_length (pass, 40);
	passbuf = gtk_entry_new_with_buffer (pass);

	gtk_entry_set_visibility(GTK_ENTRY(passbuf), FALSE);
	//gtk_entry_set_invisible_char(GTK_ENTRY(passbuf), 9679);
	g_object_set(passbuf, "input-purpose", GTK_INPUT_PURPOSE_PASSWORD, NULL);
	gtk_box_pack_end (GTK_BOX (box), GTK_WIDGET(passbuf), TRUE, TRUE, 0);
	
	GtkWidget *label1 = gtk_label_new(l.mpassw);
	gtk_box_pack_end (GTK_BOX (box), GTK_WIDGET(label1), TRUE, TRUE, 0);	
	GtkWidget *label = gtk_label_new(l.mexplain);
	gtk_box_pack_end (GTK_BOX (box), GTK_WIDGET(label), TRUE, TRUE, 0);

	GtkWidget *c = gtk_button_new_with_mnemonic("_Cancel");
	gtk_grid_attach(GTK_GRID (agrid), GTK_WIDGET (c), 1, 0, 1, 1);
	g_signal_connect (c, "clicked", G_CALLBACK (c_cb), cmd);

	GtkWidget *o = gtk_button_new_with_mnemonic("_Ok");
	gtk_grid_attach(GTK_GRID (agrid), GTK_WIDGET (o), 2, 0, 1, 1);
	g_signal_connect (o, "clicked", G_CALLBACK (o_cb), cmd);

	//g_signal_connect() enter pressed

	gtk_widget_show_all(GTK_WIDGET(su) );
	gtk_widget_grab_focus(GTK_WIDGET(passbuf));
}
