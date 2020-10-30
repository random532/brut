#include "disk.h"

GtkWidget *p;

void update_view() {
	/* Update the view. */
	gint n = gtk_notebook_get_current_page(GTK_NOTEBOOK (tabs));
	const gchar *tab = gtk_notebook_get_tab_label_text(GTK_NOTEBOOK (tabs), gtk_notebook_get_nth_page(GTK_NOTEBOOK (tabs), n));
	
	if(strcmp(tab, "Disks") == 0) {
	
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

	else if(strcmp(tab, l.tababout) == 0) {
		gtk_widget_destroy(abox);
		about();
	}

	else if(strcmp(tab, l.tabuser) == 0) {
		gtk_widget_destroy(userbox);
		users();
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
			if(sudo_failed == 1 )
				msg("sudo: Sorry, try again.");
			else
				msg(l.merror);
		}
	}
	else if((todo == GPART) || (todo == USR)) {
		if(sudo_failed == 1 )
			msg("sudo: Sorry, try again.");
		else
			msg(buf);
	}

}

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
	gtk_widget_destroy(su);
	update_view();
}

void o_cb(GtkMenuItem *item, gpointer cmd) {
		
	/* "Okay" clicked. */

	const gchar *pass;
	char *error;
	
	pass = gtk_entry_get_text(GTK_ENTRY (p));
	if( (strlen(pass) > 0) && (strlen(pass) < 100 ) ) {

		/* test password */
		error = sudo_backend(cmd, (char *) pass);
		if( error != NULL)
			free(error);
	}
	else
		msg(l.no_root);

	gtk_widget_destroy(su);
	update_view();
	return;
}

void window_pw(char *cmd) {
	
	if((cmd == NULL) || (strlen(cmd) == 0) || (strlen(cmd) > 50))
		return;
	
	/* this window asks for root password */
	su = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	gtk_window_set_title (GTK_WINDOW (su), "sudo password");
	gtk_container_set_border_width (GTK_CONTAINER (su), 30);
	gtk_window_set_default_size(GTK_WINDOW (su), 250, 100);
	gtk_window_set_modal(GTK_WINDOW(su), TRUE);
	
	gtk_window_set_transient_for(GTK_WINDOW(su), GTK_WINDOW(window)); 

	/* This won't work in Wayland. */
	gint x = 0, y = 0, width, height;
	gtk_window_get_position (GTK_WINDOW(window), &x, &y);
	gtk_window_get_size(GTK_WINDOW (window), &width, &height);
	x = x +150;
	y = y + 50;
	gtk_window_move( GTK_WINDOW(su), x, y);

	/* a box */
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add (GTK_CONTAINER (su), box);

	/* grid for two buttons - ok - cancel*/
	GtkWidget *agrid = gtk_grid_new();
	gtk_grid_insert_column(GTK_GRID(agrid), 3);
	gtk_box_pack_end(GTK_BOX(box), agrid, TRUE, TRUE, 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(agrid), FALSE);
	gtk_grid_set_column_spacing(GTK_GRID(agrid), 85);
	
	/* type your password in here */
	p = gtk_entry_new();
	gtk_entry_set_max_length (GTK_ENTRY(p), 40);

	gtk_entry_set_visibility(GTK_ENTRY(p), FALSE);
	g_object_set(p, "input-purpose", GTK_INPUT_PURPOSE_PASSWORD, NULL);
	gtk_box_pack_end (GTK_BOX (box), GTK_WIDGET(p), TRUE, TRUE, 0);
	g_signal_connect(p, "activate", G_CALLBACK(o_cb), cmd);
	
	/* some labels */
	GtkWidget *label2 = gtk_label_new(l.mpassw);
	gtk_box_pack_end (GTK_BOX (box), GTK_WIDGET(label2), TRUE, TRUE, 0);
	
	if(opt.confirm == TRUE) {
		GtkWidget *label1 = gtk_label_new(cmd);
		gtk_box_pack_end (GTK_BOX (box), GTK_WIDGET(label1), TRUE, TRUE, 0);	
	}
	GtkWidget *label = gtk_label_new(l.mexplain);
	gtk_box_pack_end (GTK_BOX (box), GTK_WIDGET(label), TRUE, TRUE, 0);

	/* two buttons */
	GtkWidget *c = gtk_button_new_with_mnemonic("_Cancel");
	gtk_grid_attach(GTK_GRID (agrid), GTK_WIDGET (c), 1, 0, 1, 1);
	g_signal_connect (c, "clicked", G_CALLBACK (c_cb), cmd);

	GtkWidget *o = gtk_button_new_with_mnemonic("_Ok");
	gtk_grid_attach(GTK_GRID (agrid), GTK_WIDGET (o), 2, 0, 1, 1);
	g_signal_connect (o, "clicked", G_CALLBACK (o_cb), cmd);

	/* and go! */
	gtk_widget_show_all(GTK_WIDGET(su) );
	gtk_widget_grab_focus(GTK_WIDGET(p));
}

char *sudo_backend(char *rcmd, char * password) {
	
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
	if (mkfifo(pwfile, 0660) != 0) {
		printf("fifo error\n");
		return NULL;
	}

	/* run child process */
	cmdlen = strlen(rcmd) + strlen(pwfile) + 20;
	cmd = malloc(cmdlen);
	snprintf(cmd, cmdlen, "sudo -p- -S %s <%s 2>&1", rcmd, pwfile);
	child = popen(cmd, "r");

	/*write password to pipe and wait... */
	if((fd = open(pwfile, O_WRONLY)) < 0) {
		printf("open() O_WRONLY failed\n");
		return NULL;
	}
	written = write(fd, pw, strlen(password)+2 );
	if( written <= 0)
		printf("write() error\n");
	
	/* close pipe */
	close(fd);
	
	/* get stdout of child */
	buflen= 30; 
	buf = malloc(buflen);
	memset(line, 0, sizeof line);
	memset(buf, 0, buflen);
	
	sudo_failed = 0;
	
	while(fgets(line, sizeof line, child) ) {
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
