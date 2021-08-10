#include "brut.h"

char *add_to_list(char *pname, char *mylist) {

	/* Add a string to an existing string. */
	/* Adjust the buffer size. */


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

void cosmetics(char *line) {
	/* Zero terminate. */
	int i = 0;
	while((line[i] != '\n') && (i < MAXLINE))
		i++;
	line[i] = '\0';
}

/* remove brackets, i.e. () from a string */
void format_string(char *mystring) {

	int len = strlen(mystring);
	int i=0;

	while(i < len) {
		if((mystring[i] == '(') || (mystring[i] == ')')) {	
			mystring[i] = ' ';
		}
	i++;
	}
}

void change_fontsize(gboolean increase) {

	long fsize = strtol(opt.fontsize, NULL, 0);
   
	if( (increase == TRUE) && (fsize < 15 ) )
		fsize = fsize +1;
	if ((increase == FALSE) && (fsize > 7) ) /* decrease */
		fsize = fsize -1;

	sprintf(opt.fontsize,"%ld", fsize);
	on_tabs_changed(NULL, NULL);
}

int execute_cmd(char *cmd, int inform) {

	/* 
	 * Execute a shell command. 
	 * Stdout goes to the debug window.
	 * Return either 1 or 0 (success).
	 */

	if(cmd == NULL)
		return 1;
	int len = strlen(cmd);
	char *buf = malloc(len +20);
	memset(buf, 0, len+20);
	
	snprintf(buf, len+20, "%s 2>&1", cmd);
	FILE *fp = popen(buf, "r");
	if (fp == NULL)
		msg("couldnt popen");

	char info[MAXLINE];
	memset(info, 0, MAXLINE);

	while(fgets(info, sizeof info, fp)) { /* pointless? */

		}
	if((inform == 1) && (strlen(info) != 0))
		msg(info);
	int suc = pclose(fp); /* /256 */;

	return suc;
}

void msg(char *blah) {

	/* Send a string to log window. */
	if(blah == NULL)
		return;
	int len = strlen(blah);
	if(len > 0)
		gtk_text_buffer_set_text(GTK_TEXT_BUFFER (gtk_text_view_get_buffer(GTK_TEXT_VIEW(logwindow))), blah, len);
}

char *command(char *cmd) {

	/* 
	 * Execute a shell command.
	 * Return stdout in a buffer.
	 * We only read MAXLINE chars per line, which is 250.
	 */


	if(cmd == NULL)
		return NULL;

	char line[MAXLINE];
	int len;	/* Characters read. */
	char *buf;
	int buflen;	/* The buffer might grow in size. */

	buflen = MAXLINE + 2;
	buf = malloc(buflen);
	if(buf == NULL)
		return NULL;

	memset(line, 0, MAXLINE);
	memset(buf, 0, buflen);

	FILE *fp = popen(cmd, "r");
	if (fp == NULL) {
		msg("fopen failed");
		return NULL;
	}
	while(fgets(line, MAXLINE, fp)) {
		
		/* Add contents to our buffer. */
		len = strlen(line);
		strncat(buf, line, len);
		
		/* Adjust buffer size. */
		buflen = buflen + len;
		buf = realloc(buf, buflen);
		if(buf == NULL)
			return NULL;
		memset(line, 0, MAXLINE);
	}
	pclose(fp);
	
	/* zero terminate */
	buflen = strlen(buf);
	buf[buflen-1] = '\0';
	return buf;
}

int vari(char *line, int max) {
	
	/* in a string like " name: variable" find the variable */
	int i = 0;
	while((strncmp(&line[i], ":", 1) != 0) && (i < max))
		i++;
	i++;
	
	/* zero terminate instead of 0xA */
	int z = strlen(&line[i]);
	z = z + i;
	z--;
	line[z] = (char) 0;
	
	return i; /* XXX: has potential space charackter at the beginning */
}

int root() {
	/* are we root? */
	uid_t perm = geteuid();
	if (perm != 0 ) {
		return 0; /* no */
	}
	else
		return 1; /* yes */
}

int command_exist(char *cmd) {

	char *localbase = PATH;
	int a = strlen(localbase);
	int b = strlen(cmd);
	char *exist = malloc(a+b+5);
	snprintf(exist, a+b+1, "%s%s", localbase, cmd);

	if (access(exist, X_OK) == 0) /* or check for file exists? */
		return 1;
	else
		return 0;
}

int submit(char *cmd, int conf) {

	int error = 0;
	
	if((todo == MOUNT) || (todo == USR)) {
		error = execute_cmd(cmd, 0);
		if(error == 0)
			msg(l.mdone);
		else
			msg(l.merror);
	}
	
	else if(todo == GPART) {
		if(conf == 1)
			ask(cmd);
		else
			error = execute_cmd(cmd, 1);
	}

	else if(todo == FS) {
		if( conf == 1)
			ask(cmd);
		else {
			error = execute_cmd(cmd, 0);
			if(error == 0)
				msg(l.mdone);
			else
				msg(l.merror);
		}
	}
	return error;
}

void destroyme(GtkMenuItem *item, gpointer user_data) {
	// XXX: Obsolete?
	gtk_widget_destroy(user_data);
}

char *random_filename() {
	
	char *fname;
	uint32_t number;
	int len;

	number = arc4random();
	len = 50;
	fname = malloc(len);
	if(fname == NULL)
		return NULL;
	memset(fname, 0, len);
	
	sprintf(fname,"/tmp/1%i", number);
	return fname;
}

char *selected_item(GtkWidget *tview, int column) {
	
	/* 
	 * Get the contents of the selected row/column.
	 */
	char *data = NULL;
	if(tview != NULL) {
		GtkTreeSelection *selected = gtk_tree_view_get_selection(GTK_TREE_VIEW (tview));
		if (selected == NULL) {
			printf("please select a row!\n");
			return NULL;
		}
		GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW (tview));
		if (model == NULL) {
			printf("gtk_tree_view_get_model() failed\n");
			return NULL;
		}
		GtkTreeIter iter;
		if (gtk_tree_selection_get_selected(selected, &model, &iter) ) {
			gtk_tree_model_get(model, &iter, column, &data, -1);
			if(data != NULL) 
				return data;
		}
	}
	return NULL;
}
