/* Group tab */
#include "disk.h"

void execute_me(char *cmd) {
	
	if(!root() )  { /* try sudo */
		if(pw_needed() ) {
			window_pw(cmd);
			return;
		}
		else {
			/* no password needed */
			cmd = sudo(cmd, "empty", 0);
			if(cmd == NULL) {
				printf("restart recommended..\n");
				return;
			}
		}
	}
	submit(cmd, 0);
	free(cmd);
}

void button_pressed_cb (GtkButton *item, gpointer cmd) {

	if(strncmp(gtk_button_get_label(item), "Ok", 2) == 0 ) {
		execute_me(cmd);
		on_tabs_changed(NULL, NULL);
	}
	else {
		free(cmd);
		gtk_widget_destroy(groupconfirm);
		groupconfirm = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	}
}

void new_group_cb (GtkButton *item, gpointer e) {

	if(strncmp(gtk_button_get_label(item), "Ok", 2) == 0 ) {
		
		const gchar *newname = gtk_entry_get_text(GTK_ENTRY (e));
		int len = strlen(newname);
		char *cmd = malloc(len +20);
		sprintf(cmd, "pw groupadd %s", newname);
		execute_me(cmd);
	}

	gtk_widget_destroy(groupconfirm);
	groupconfirm = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
}

void del_group (GtkMenuItem *item, gpointer gtv) {
	
	char *groupname = selected_item(gtv, 0);
	int len = strlen(groupname);

	/* Build a shell command. */
	char *cmd = malloc(len + 15);
	if(cmd == NULL) {
		printf("Error in groups.c: malloc() returned NULL.\n");
		return;
	}
	sprintf(cmd, "pw groupdel %s", groupname);

	/* GUI elements. */
	gtk_widget_destroy(groupconfirm);
	groupconfirm = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

	GtkWidget *o = gtk_button_new_with_mnemonic("Ok");
	GtkWidget *c = gtk_button_new_with_mnemonic(l.mabort);
	
	gtk_container_add (GTK_CONTAINER (groupbox), groupconfirm);
	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(l.ginfodel));
	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(groupname));
	gtk_container_add(GTK_CONTAINER (groupconfirm), o);
	gtk_container_add(GTK_CONTAINER (groupconfirm), c);
	
	g_signal_connect(G_OBJECT (o), "clicked", G_CALLBACK (button_pressed_cb), cmd);
	g_signal_connect(G_OBJECT (c), "clicked", G_CALLBACK (button_pressed_cb), cmd);
	
	gtk_widget_show_all(groupconfirm);
}

void new_group (GtkMenuItem *item, gpointer user_data) {

	/* GUI elements. */
	gtk_widget_destroy(groupconfirm);
	groupconfirm = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

	gtk_container_add (GTK_CONTAINER (groupbox), groupconfirm);	
	
	GtkWidget *e = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(e), 50); // XXX: hardcoded?
	gtk_entry_set_placeholder_text (GTK_ENTRY(e), "Name");

	GtkWidget *o = gtk_button_new_with_mnemonic("Ok");
	GtkWidget *c = gtk_button_new_with_mnemonic(l.mabort);

	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(l.ginfocreate));
	gtk_container_add(GTK_CONTAINER (groupconfirm), o);
	gtk_container_add(GTK_CONTAINER (groupconfirm), c);
	gtk_container_add(GTK_CONTAINER (groupconfirm), e);

	g_signal_connect(G_OBJECT (o), "clicked", G_CALLBACK (new_group_cb), e);
	g_signal_connect(G_OBJECT (c), "clicked", G_CALLBACK (new_group_cb), NULL);
	
	gtk_widget_show_all(groupconfirm);
}

void adduser (GtkMenuItem *item, gpointer gtv) {
	
	const char *user = gtk_menu_item_get_label(item);
	char *groupname = selected_item(gtv, 0);


	/* Build a shell command. */
	int len = strlen(user) + strlen(groupname);
	char *cmd = malloc(len + 30);
	if(cmd == NULL) {
		printf("Error in groups.c: malloc() returned NULL.\n");
		return;
	}
	sprintf(cmd, "pw groupmod %s -m %s", groupname, user);
	
	/* GUI elements. */
	gtk_widget_destroy(groupconfirm);
	groupconfirm = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	
	GtkWidget *o = gtk_button_new_with_mnemonic("Ok");
	GtkWidget *c = gtk_button_new_with_mnemonic(l.mabort);
	
	gtk_container_add (GTK_CONTAINER (groupbox), groupconfirm);
	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(l.ginfoadduser1));
	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(user));	
	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(l.ginfoadduser2));
	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(groupname));
	gtk_container_add(GTK_CONTAINER (groupconfirm), o);
	gtk_container_add(GTK_CONTAINER (groupconfirm), c);
	
	g_signal_connect(G_OBJECT (c), "clicked", G_CALLBACK (button_pressed_cb), cmd);
	g_signal_connect(G_OBJECT (o), "clicked", G_CALLBACK (button_pressed_cb), cmd);
	gtk_widget_show_all(groupconfirm);
}

void remuser (GtkMenuItem *item, gpointer gtv) {
	
	const char *user = gtk_menu_item_get_label(item);
	char *groupname = selected_item(gtv, 0);
	
	/* Build a shell command. */
	int len = strlen(user) + strlen(groupname);
	char *cmd = malloc(len + 30);
	if(cmd == NULL) {
		printf("Error in groups.c: malloc() returned NULL.\n");
		return;
	}
	sprintf(cmd, "pw groupmod %s -d %s", groupname, user);
	
	/* GUI elements. */
	gtk_widget_destroy(groupconfirm);
	groupconfirm = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

	GtkWidget *o = gtk_button_new_with_mnemonic("Ok");
	GtkWidget *c = gtk_button_new_with_mnemonic("No");

	gtk_container_add (GTK_CONTAINER (groupbox), groupconfirm);
	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(l.ginforemuser1));
	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(user));	
	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(l.ginforemuser2));
	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(groupname));
	gtk_container_add(GTK_CONTAINER (groupconfirm), o);
	gtk_container_add(GTK_CONTAINER (groupconfirm), c);

	g_signal_connect(G_OBJECT (c), "clicked", G_CALLBACK (button_pressed_cb), cmd);
	g_signal_connect(G_OBJECT (o), "clicked", G_CALLBACK (button_pressed_cb), cmd);
	gtk_widget_show_all(groupconfirm);
}

gboolean click(GtkWidget *gtv, GdkEventButton *event, gpointer userdata) {

	/* 
	 * A right click menu. 
	 */

	if( (event->type != GDK_BUTTON_PRESS) || (event->button != 3) ) 
		return FALSE;

	/* find and select the row that was clicked */

	GtkTreePath *path;
	GtkTreeViewColumn *column;
	if (!gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(gtv), event->x, event->y, &path, &column, NULL, NULL))
			return FALSE;
	GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(gtv));
	gtk_tree_selection_unselect_all(selection);
	gtk_tree_selection_select_path(selection, path);
	gtk_tree_path_free(path);

	char *groupname = selected_item(gtv, 0);
	if(groupname == NULL)
		return TRUE;

	/* Create the popup menu. */
	GtkWidget *pop_menu = gtk_menu_new();
	

	GtkWidget *newg = gtk_menu_item_new_with_label (l.gnew);
	GtkWidget *delg = gtk_menu_item_new_with_label(l.gdel);
	GtkWidget *addg = gtk_menu_item_new_with_label(l.gadd);
		
	gtk_menu_shell_append (GTK_MENU_SHELL (pop_menu), newg);
	gtk_menu_shell_append (GTK_MENU_SHELL (pop_menu), delg);
	gtk_menu_shell_append (GTK_MENU_SHELL (pop_menu), addg);

	g_signal_connect(delg, "activate", G_CALLBACK(del_group), gtv);
	g_signal_connect(newg, "activate", G_CALLBACK(new_group), NULL);


	/*
	 *  A submenu for 'Add user to group'.
	 */

	char *cmd = "pw user show -a | awk '{gsub(/\\:/, \" \"); print $1}'";
	char buf[50];
	
	FILE * fp = popen(cmd, "r");
	if ( fp != NULL ) {

		GtkWidget *addg_sub = gtk_menu_new();
		gtk_menu_item_set_submenu (GTK_MENU_ITEM (addg), addg_sub);
		

		while( fgets(buf, sizeof buf, fp) ) {
			
			int len = strlen(buf);
			buf[len-1] = '\0';
			
			GtkWidget *a = gtk_menu_item_new_with_label(buf);
			gtk_menu_shell_append(GTK_MENU_SHELL (addg_sub), a);
			g_signal_connect(a, "activate", G_CALLBACK(adduser), gtv);
			memset(buf, 0, sizeof buf);
		}
		pclose(fp);
	}
	
	/* 
	 * A potential submenu 'Remove user from group'. 
	 */

	char *users = selected_item(gtv, 3);
	
	if((users != NULL) && (strlen(users) > 1)) {
		GtkWidget *remg = gtk_menu_item_new_with_label(l.gremove);
		gtk_menu_shell_append (GTK_MENU_SHELL (pop_menu), remg);
		
		GtkWidget *remg_sub = gtk_menu_new();
		gtk_menu_item_set_submenu (GTK_MENU_ITEM (remg), remg_sub);
		
		/* For each user create a menu item. */
		char cmd2[200];
		sprintf(cmd2, "echo %s | awk '{gsub(/\\,/, \"\\n\"); printf}'", users);
		char buffer[100];
	
		FILE * f = popen(cmd2, "r");

		while( fgets(buffer, sizeof buffer, fp) ) {
			int l = strlen(buffer);
			if(buffer[l-1] == '\n')
				buffer[l-1] = '\0';
			GtkWidget *z = gtk_menu_item_new_with_label(buffer);
			gtk_menu_shell_append(GTK_MENU_SHELL (remg_sub), z);
			g_signal_connect(z, "activate", G_CALLBACK(remuser), gtv);
			memset(buffer, 0, sizeof buffer);
		}
		pclose(f);
		free(users);
	}

	gtk_widget_show_all(pop_menu);
	gtk_menu_popup_at_pointer( GTK_MENU (pop_menu), NULL);
	return TRUE; /* right click finished */
}

GtkWidget *group_treeview() {
	
	GtkWidget *scrollw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollw),
                                    GTK_POLICY_ALWAYS, GTK_POLICY_AUTOMATIC); 
	gtk_box_pack_start(GTK_BOX(groupbox), scrollw, FALSE, TRUE, 0);
	gtk_scrolled_window_set_propagate_natural_height (GTK_SCROLLED_WINDOW(scrollw), TRUE);
	gtk_scrolled_window_set_propagate_natural_width (GTK_SCROLLED_WINDOW(scrollw), TRUE);

	/* A treeview. */
	GtkWidget *gtv = gtk_tree_view_new();
	gtk_container_add(GTK_CONTAINER(scrollw), gtv);	
	GtkCellRenderer *c = gtk_cell_renderer_text_new();

	g_object_set(c, "font", opt.fontsize, NULL);
	g_object_set(c, "editable", FALSE, NULL);
	g_object_set(gtv, "enable-grid-lines", GTK_TREE_VIEW_GRID_LINES_BOTH, NULL);
	
	/* A right-click menu. */
	g_signal_connect(G_OBJECT (gtv), "button-press-event", G_CALLBACK(click), NULL);
	
	/* Insert 4 columns. */
	GtkTreeViewColumn   *col;
	
	col = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(col, l.gname);
  	gtk_tree_view_append_column(GTK_TREE_VIEW(gtv), col);
	gtk_tree_view_column_pack_start(col, c, TRUE);
	gtk_tree_view_column_add_attribute(col, c, "text", 0);

	col = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(col, l.gid);
  	gtk_tree_view_append_column(GTK_TREE_VIEW(gtv), col);
	gtk_tree_view_column_pack_start(col, c, TRUE);
	gtk_tree_view_column_add_attribute(col, c, "text", 1);

	col = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(col, l.gpassword);
  	gtk_tree_view_append_column(GTK_TREE_VIEW(gtv), col);
	gtk_tree_view_column_pack_start(col, c, TRUE);
	gtk_tree_view_column_add_attribute(col, c, "text", 2);

	col = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(col, l.gmember);
  	gtk_tree_view_append_column(GTK_TREE_VIEW(gtv), col);
	gtk_tree_view_column_pack_start(col, c, TRUE);
	gtk_tree_view_column_add_attribute(col, c, "text", 3);


	char *buf= "pw groupshow -aq";		
	char line[150];
	int size=150;	
	int i = 0; /* Some char counter in a line */
	int n = 0;
	
	/* A Treestore. */
	GtkTreeStore *t = gtk_tree_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	

	gtk_tree_view_set_model(GTK_TREE_VIEW(gtv), GTK_TREE_MODEL(t));
	g_object_unref(t); /* Destroy model automatically with view. */ 
  	gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(gtv)),
                             GTK_SELECTION_SINGLE);
         
	FILE * fp = popen(buf, "r");
	if ( fp == NULL ) {
		printf("could not execute pw gruopshow -aq\n");	
		return NULL;
	}
	
	GtkTreeIter	parent;

	/* Get a line */
	while( fgets(line, sizeof line, fp) ) {
		if(&line[0] != '\0') {
			
		int len = strlen(line);
		line[len-1] = '\0';
		 
		char *name;
		char *id;
		char *pw;
		char *memb;

		/* Locate the group name. */
		name = line;
		
		i = 0;
		while(line[i] != ':')
			i++;
		line[i] = '\0';
		id = &line[i+1];
		
		while(line[i] != ':')
			i++;
		line[i] = '\0';
		pw = &line[i+1];
		
		while(line[i] != ':')
			i++;
		line[i] = '\0';
		memb = &line[i+1];
		
	
		gtk_tree_store_append(t, &parent, NULL);
		gtk_tree_store_set(t, &parent, 0, name, 1, pw, 2, id, -1);
		if(&line[i+1] != '\0')
			gtk_tree_store_set(t, &parent, 3, memb, -1);
	}
		memset(line, 0, size);
	}
	
	pclose(fp);
	
	/* Empty row at the end for style points. */
	gtk_tree_store_append(t, &parent, NULL);

	/* scrollbars? */

	return gtv;
}

void groups() {
	
	/* A top level container. */
	groupbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
	gtk_container_add (GTK_CONTAINER (tab2), groupbox);
	
	/* A treeview that contains all groups. */
	GtkWidget *gtree = group_treeview();
	
	groupconfirm = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_container_add (GTK_CONTAINER (groupbox), groupconfirm);
	gtk_container_add(GTK_CONTAINER (groupconfirm), gtk_label_new(l.ginfoclick));
	gtk_widget_show_all(groupbox);
}
