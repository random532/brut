#include "disk.h"

GtkWidget *p;
GtkWidget *passwbox;

void update_view() {

	/* 
	 * Restore the GUI elements. 
	 */

	gint n = gtk_notebook_get_current_page(GTK_NOTEBOOK (tabs));
	const gchar *tab = gtk_notebook_get_tab_label_text(GTK_NOTEBOOK (tabs), gtk_notebook_get_nth_page(GTK_NOTEBOOK (tabs), n));
	
	if(strcmp(tab, l.tabdisks) == 0) {

		/* redraw_cb() can be called. */
		/* but this is nicer. */
		on_toplevel_changed();
		gtk_widget_destroy(thegrid);
		editor();
	}
		
	else if(strcmp(tab, l.tabgroup) == 0) {
		gtk_widget_destroy(groupbox);
		groups();
	}

	else if(strcmp(tab, l.tabuser) == 0) {
		gtk_widget_destroy(userbox);
		users();
	}

	else if(strcmp(tab, l.tabconfig) == 0) {
		gtk_widget_destroy(configbox);
		config();
	}
	else if(strcmp(tab, l.tabdevices) == 0) {
		gtk_widget_destroy(devbox);
		devices();
	}
	else if(strcmp(tab, l.tabwlan) == 0) {
		AfterRootCmd();
	}

}

void inform_user(int error, int sudo_failed, char *buf) {

	/* 
	 * Either print an extended error message, 
	 * or a short error message, 
	 * or success. 
	 */
	 
	if((todo == MOUNT) || (todo == FS)) {
		if(error == 0)
			msg(l.mdone);
		else {
			if(sudo_failed == 1)
				msg("sudo: Sorry, try again.");
			else
				msg(l.merror);
		}
	}
	else if((todo == GPART) || (todo == USR)) {
		if(sudo_failed == 1)
			msg("sudo: Sorry, try again.");
		else
			msg(buf);
	}

}

char *sudo( char *cmd, char *passw, int pw) {

	/* XXX: This one is deprecated. */

	/*
	 * Add "sudo -S" to a command.
	 */

	if((cmd == NULL) || (strlen(cmd) == 0))
		return NULL;
	if((passw == NULL) || (strlen(passw) == 0))
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

gboolean pw_needed() {

	int error;	
	FILE *fp = popen("sudo -nv 2>/dev/null", "r");
	if(fp == NULL)
		return TRUE;
	
		error = pclose(fp)/256;
		if(error != 0)
			return TRUE; /* yes, a password is needed */
		else
			return FALSE;
}

void c_cb(GtkMenuItem *item, gpointer cmd) {
	
	/* "Cancel" button */

	if(cmd != NULL)
		free(cmd);

	/* Restore GUI */
	gtk_widget_destroy(passwbox);
	gtk_widget_show(menubox);
	gtk_widget_show(tabs);
	gtk_widget_show(logwindow);
	update_view();
}

void o_cb(GtkMenuItem *item, gpointer cmd) {
		
	/* "Okay" clicked. */

	/* First draw something */
/*	gtk_widget_destroy(passwbox);
	passwbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add (GTK_CONTAINER (fixed), passwbox);
	gtk_container_add(GTK_CONTAINER(passwbox), gtk_label_new("Processing..."));
	gtk_widget_show_all(passwbox);
*/

	/* Execute the sudo command. */
	const gchar *pass;
	char *error;

	pass = gtk_entry_get_text(GTK_ENTRY (p));
	if((strlen(pass) > 0) && (strlen(pass) < 40)) {

		/* Try the command with password. */
		error = sudo_backend(cmd, (char *) pass);
		if(error != NULL) /* We don't need this string. */
			free(error);

	}
	else { /* No password was entered. */
		msg(l.no_root);
	}

	/* Restore GUI */
	gtk_widget_destroy(passwbox);
	gtk_widget_show(menubox);
	gtk_widget_show(tabs);
	gtk_widget_show(logwindow);
	update_view();

	return;
}

void window_pw(char *cmd) {

	/* this window asks for root password */
	gtk_widget_hide(tabs);
	gtk_widget_hide(menubox);
	gtk_widget_hide(logwindow);

	/* A top level container. */
	passwbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add (GTK_CONTAINER (fixed), passwbox);

	/* some labels */
	
	GtkWidget *label = gtk_label_new(l.mexplain);
	gtk_container_add(GTK_CONTAINER(passwbox), GTK_WIDGET(label));

	if(opt.confirm == TRUE) {
		GtkWidget *label1 = gtk_label_new(cmd);
		gtk_container_add(GTK_CONTAINER (passwbox), GTK_WIDGET(label1));	
	}

	GtkWidget *label2 = gtk_label_new(l.mpassw);
	gtk_container_add (GTK_CONTAINER(passwbox), GTK_WIDGET(label2));

	/* Text entry for password  */
	GtkWidget *ebox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
	gtk_container_add (GTK_CONTAINER (passwbox), ebox);

	p = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(p), FALSE);
	g_object_set(p, "input-purpose", GTK_INPUT_PURPOSE_PASSWORD, NULL);

	gtk_box_pack_start(GTK_BOX (ebox), GTK_WIDGET(p), TRUE, FALSE, 20);
	//gtk_widget_set_property(p, "fill", FALSE, "expand", FALSE, NULL);
	gtk_entry_set_max_length (GTK_ENTRY(p), 20);
	gtk_entry_set_width_chars(GTK_ENTRY(p), 30);
	g_signal_connect(p, "activate", G_CALLBACK(o_cb), cmd);

	/* Another box */
	ebox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
	gtk_container_add (GTK_CONTAINER (passwbox), ebox);

	/* A grid */
	GtkWidget *agrid = gtk_grid_new();
//	gtk_grid_insert_column(GTK_GRID(agrid), 3);
//	gtk_container_add(GTK_CONTAINER(passwbox), agrid);
//	gtk_grid_set_column_homogeneous(GTK_GRID(agrid), FALSE);
	gtk_grid_set_column_spacing(GTK_GRID(agrid), 20);

	gtk_box_pack_start(GTK_BOX (ebox), GTK_WIDGET(agrid), TRUE, FALSE, 5);

	/* two buttons */

	GtkWidget *o = gtk_button_new_with_mnemonic("_Ok");
	gtk_grid_attach(GTK_GRID (agrid), GTK_WIDGET (o), 1, 1, 1, 1);
	g_signal_connect (o, "clicked", G_CALLBACK (o_cb), cmd);

	GtkWidget *c = gtk_button_new_with_mnemonic("_Cancel");
	gtk_grid_attach(GTK_GRID (agrid), GTK_WIDGET (c), 2, 1, 1, 1);
	g_signal_connect (c, "clicked", G_CALLBACK (c_cb), cmd);

	/* and go! */
	gtk_widget_show_all(GTK_WIDGET(passwbox));
	gtk_widget_grab_focus(GTK_WIDGET(p));
}

char *sudo_backend(char *rcmd, char *password) {

	/*
	 * The sudo backend.
	 * 
	 * We create a subprocess ("sudo xxx")
	 * and feed it the password via a named pipe.
	 * 
	 * That's the only way to communicate a password to sudo,
	 * as sudo has no command line option for the password.
	 * Sudo fails to find anonymous pipes, and we don't want
	 * sth like "echo password | sudo cmd".
	 */
	
	char *pw;		/* Password */
	char *pwfile;	/* Named pipe */
	char *cmd;		/* The sudo command to execute */
	char *buf;		/* Stdout of sudo command */
	FILE *child;	/* The sudo command we execute */
	char line[100]; /* a line for fgets() */
	int cmdlen;		/**/
	int buflen;		/**/
	int len;		/* Bytes read */
	int error;		/**/
	int fd;			/* File descriptior of pipe */
	int sudo_failed;	/* Whether sudo failed */
	ssize_t written;	/* Bytes written to pipe */
	
	/* sudo password */
	pw = malloc (strlen(password) +5);
	sprintf(pw, "%s\n%d", password, EOF); /* newline and EOF? */
	
	/* create named pipe */
	pwfile = random_filename();

	if(mkfifo(pwfile, 0660) != 0) {
		printf("root.c: mkfifo() failed\n");
		return NULL;
	}

	/* run child process */
	cmdlen = strlen(rcmd) + strlen(pwfile) + 40;
	cmd = malloc(cmdlen);
	memset(cmd, 0, cmdlen);
	snprintf(cmd, cmdlen, "sudo -p- -S %s <%s 2>&1", rcmd, pwfile);
	child = popen(cmd, "r");

	/*write password to pipe and wait... */
	if((fd = open(pwfile, O_WRONLY)) < 0) {
		printf("open() O_WRONLY failed\n");
		return NULL;
	}

	written = write(fd, pw, strlen(password)+2 );
	if(written <= 0)
		printf("write() error\n");

	/* close pipe */
	close(fd);
	
	/* get stdout of child */
	buflen = 30; 
	buf = malloc(buflen);
	memset(line, 0, sizeof line);
	memset(buf, 0, buflen);
	
	sudo_failed = 0;
	
	while(fgets(line, sizeof line, child)) {
		len = strlen(line);
		if(len > 0) {
			
			buflen = len + buflen + 1; /* increase buffer */
			buf = realloc(buf, buflen);
			if(buf != NULL)
				strncat(buf, line, len);
			if(strncmp(line, "sudo:", 5) == 0) {
				sudo_failed = 1; 
				break;
			}
		}
	}

	/* end child process */	
	error = pclose(child);
	
	/* destroy pipe */
	if (unlink(pwfile) != 0)
		printf("unlink() failed\n");
		
	free(pw);
	free(cmd);

	/* inform user */
	inform_user(error, sudo_failed, buf);

	return buf;
}
