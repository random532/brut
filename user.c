/* User tab */
#include "disk.h"

struct {
	GtkWidget *uname;
	GtkWidget *ushell;
	GtkWidget *uhome;
	GtkWidget *uclass;
	GtkWidget *upassw;
	GtkWidget *ufullname;
} useradd_entries;

void redraw_user() {
		gtk_widget_destroy(userbox);
		users();
}

void add_cb(GtkButton *item, gpointer a) {
	
	if(strncmp(gtk_button_get_label(item), "Ok", 2) == 0) {

		/* Get the entries. */
		const gchar *gname = gtk_entry_get_text(GTK_ENTRY (useradd_entries.uname));
		const gchar *ghome = gtk_entry_get_text(GTK_ENTRY (useradd_entries.uhome));
		const gchar *gshell = gtk_entry_get_text(GTK_ENTRY (useradd_entries.ushell));
		const gchar *gclass = gtk_entry_get_text(GTK_ENTRY (useradd_entries.uclass));
		const gchar *gpass = gtk_entry_get_text(GTK_ENTRY (useradd_entries.upassw));
		
		if(strlen(gname) == 0) {
			redraw_user();
			return;
		}

		/* Build the command. */
		char *cmd = malloc(strlen(gshell) + strlen(gname) + strlen(ghome) + strlen(gclass) + strlen(gpass) + 60);
		if(cmd == NULL) {
			printf("add_cb: malloc() failed\n");
			redraw_user();
			return;
		}

		if(strlen(gpass) == 0) /* Password. */
			sprintf(cmd, "pw useradd -n %s", gname);
		else
			sprintf(cmd, "echo \"%s\" | sudo pw useradd -h 0 -n %s", gpass, gname);

		if(strlen(ghome) != 0) { /* Home directory. */
			strcat(cmd, " -d ");
			strcat(cmd, ghome);
		}
		if(strlen(gshell) != 0) { /* Shell. */
			strcat(cmd, " -s ");
			strcat(cmd, gshell);
		}
		if(strlen(gclass) != 0) {	/* Login class. */
			strcat(cmd, " -L ");
			strcat(cmd, gclass);
		}
		execute_me(cmd, USR);
	}
	redraw_user();
}

void edit_ok(GtkButton *item, gpointer user) {

	if(strncmp(gtk_button_get_label(item), "Ok", 2) == 0) {

		/* Get the entries. */
		const gchar *gname = gtk_entry_get_text(GTK_ENTRY (useradd_entries.uname));
		const gchar *ghome = gtk_entry_get_text(GTK_ENTRY (useradd_entries.uhome));
		const gchar *gshell = gtk_entry_get_text(GTK_ENTRY (useradd_entries.ushell));
		const gchar *gclass = gtk_entry_get_text(GTK_ENTRY (useradd_entries.uclass));

		/* Build the command. */
		char *cmd = malloc(strlen(gshell) + strlen(gname) + strlen(ghome) + strlen(gclass) + 60);
		if(cmd == NULL) {
			printf("edit_cb: malloc() failed\n");
			redraw_user();
			return;
		}

		sprintf(cmd, "pw usermod -n %s", (char *) user);

		if(strlen(gname) != 0) {	/* New user name. */
			strcat(cmd, " -l ");
			strcat(cmd, gname);
		}
		if(strlen(gclass) != 0) {	/* Login class. */
			strcat(cmd, " -L ");
			strcat(cmd, gclass);
		}
		if(strlen(ghome) != 0) { /* Home directory. */
			strcat(cmd, " -d ");
			strcat(cmd, ghome);
		}
		if(strlen(gshell) != 0) { /* Shell. */
			strcat(cmd, " -s ");
			strcat(cmd, gshell);
		}
		execute_me(cmd, USR);
	}
	else
		redraw_user();
}

void delete_ok(GtkButton *item, gpointer cmd) {

	if(strncmp(gtk_button_get_label(item), "Ok", 2) == 0 ) {
		execute_me(cmd, USR);
	}
	else
		redraw_user();
}

void del_user (GtkMenuItem *item, gpointer userview) {

	char *user = selected_item(userview, 0);
	
	char *cmd = malloc(strlen(user) + 40);
	if(cmd == NULL)
		return;
	sprintf(cmd, "sudo rmuser -y %s", user);

	/* GUI elements */
	gtk_widget_destroy(userbox);
	userbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_box_pack_start(GTK_BOX (tab3), userbox, FALSE, FALSE, 0);
	
	GtkWidget *g = gtk_grid_new();
	gtk_grid_insert_column(GTK_GRID(g), 5);
	gtk_box_pack_start(GTK_BOX(userbox), g, FALSE, TRUE, 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(g), FALSE);
	gtk_grid_set_column_spacing(GTK_GRID(g), 20);


	gtk_grid_attach(GTK_GRID (g), gtk_label_new(l.uremove1), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID (g), gtk_label_new(user), 0, 1, 1, 1);

	GtkWidget *o = gtk_button_new_with_mnemonic("Ok");
	GtkWidget *c = gtk_button_new_with_mnemonic(l.mabort);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (o), 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (c), 2, 3, 1, 1);

	g_signal_connect(G_OBJECT (o), "clicked", G_CALLBACK (delete_ok), cmd);
	g_signal_connect(G_OBJECT (c), "clicked", G_CALLBACK (delete_ok), cmd);

	gtk_widget_show_all(userbox);
}

void add_user(GtkMenuItem *item, gpointer userview) {

	/* 
	 * GUI elements for adding a user.
	 */

	gtk_widget_destroy(userbox);
	userbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_box_pack_start(GTK_BOX (tab3), userbox, FALSE, FALSE, 0);
	
	GtkWidget *g = gtk_grid_new();
	gtk_grid_insert_column(GTK_GRID(g), 5);
	gtk_box_pack_start(GTK_BOX(userbox), g, FALSE, TRUE, 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(g), FALSE);
	gtk_grid_set_column_spacing(GTK_GRID(g), 20);

	
	GtkWidget *e = gtk_entry_new();
	gtk_entry_set_max_length (GTK_ENTRY(e), 50); // XXX: hardcode length?
	gtk_entry_set_placeholder_text (GTK_ENTRY(e), usercol[POS_UNAME]);

	GtkWidget *e1 = gtk_entry_new();
	gtk_entry_set_max_length (GTK_ENTRY(e1), 50); // XXX: hardcode length?
	gtk_entry_set_placeholder_text (GTK_ENTRY(e1), usercol[POS_UHOME]);
	
	GtkWidget *e2 = gtk_entry_new();
	gtk_entry_set_max_length (GTK_ENTRY(e2), 50); // XXX: hardcode length?
	gtk_entry_set_placeholder_text (GTK_ENTRY(e2), usercol[POS_USHELL]);

	GtkWidget *e3 = gtk_entry_new();
	gtk_entry_set_max_length (GTK_ENTRY(e3), 50); // XXX: hardcode length?
	gtk_entry_set_placeholder_text (GTK_ENTRY(e3), usercol[POS_UCLASS]);
	
	GtkWidget *e4 = gtk_entry_new();
	gtk_entry_set_max_length (GTK_ENTRY(e4), 50); // XXX: hardcode length?
	gtk_entry_set_placeholder_text (GTK_ENTRY(e4), "pw");

	GtkWidget *o = gtk_button_new_with_mnemonic("Ok");
	GtkWidget *c = gtk_button_new_with_mnemonic(l.mabort);


	gtk_grid_attach(GTK_GRID (g), gtk_label_new(l.uadd), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (e), 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (e1), 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (e2), 0, 3, 1, 1);	
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (e3), 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (e4), 0, 5, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (o), 1, 7, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (c), 2, 7, 1, 1);

	useradd_entries.uname = e;
	useradd_entries.uhome = e1;
	useradd_entries.ushell = e2;
	useradd_entries.uclass = e3;
	useradd_entries.upassw = e4;

	g_signal_connect(G_OBJECT (o), "clicked", G_CALLBACK (add_cb), NULL);
	g_signal_connect(G_OBJECT (c), "clicked", G_CALLBACK (add_cb), NULL);

	gtk_widget_show_all(userbox);
}

void edit_user(GtkMenuItem *item, gpointer userview) {

	/* Assemble user data. */
	char *user = selected_item(userview, POS_UNAME);
	char *home = selected_item(userview, POS_UHOME);
	char *shell = selected_item(userview, POS_USHELL);
	char *class = selected_item(userview, POS_UCLASS);

	/* GUI elements */

	/* A grid */
	GtkWidget *g = gtk_grid_new();
	gtk_grid_insert_column(GTK_GRID(g), 5);
	gtk_grid_set_column_homogeneous(GTK_GRID(g), FALSE);
	gtk_grid_set_column_spacing(GTK_GRID(g), 20);

	/* User name. */
	GtkWidget *e = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(e), 50); // XXX: hardcoded?
	gtk_entry_set_placeholder_text (GTK_ENTRY(e), usercol[POS_UNAME]);

	/* Shell. */
	GtkWidget *e1 = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(e1), 50); // XXX: hardcoded?
	gtk_entry_set_placeholder_text (GTK_ENTRY(e1), usercol[POS_USHELL]);

	/* Class. */
	GtkWidget *e2 = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(e2), 50); // XXX: hardcoded?
	gtk_entry_set_placeholder_text (GTK_ENTRY(e2), usercol[POS_UCLASS]);

	/* Home directory. */
	GtkWidget *e3 = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(e3), 50); // XXX: hardcoded?
	gtk_entry_set_placeholder_text (GTK_ENTRY(e3), usercol[POS_UHOME]);

	/* Be visible to callback functions. */
	useradd_entries.uname = e;
	useradd_entries.ushell = e1;
	useradd_entries.uclass = e2;
	useradd_entries.uhome = e3;

	/* Two buttons. */
	GtkWidget *o = gtk_button_new_with_mnemonic("Ok");
	GtkWidget *c = gtk_button_new_with_mnemonic(l.mabort);
	g_signal_connect(G_OBJECT (o), "clicked", G_CALLBACK (edit_ok), user);
	g_signal_connect(G_OBJECT (c), "clicked", G_CALLBACK (edit_ok), user);

	/* Attach everything. */
	gtk_grid_attach(GTK_GRID (g), gtk_label_new(l.uedit), 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID (g), gtk_label_new(user), 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (g), gtk_label_new(shell), 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID (g), gtk_label_new(class), 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID (g), gtk_label_new(home), 0, 5, 1, 1);
	
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (e), 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (e1), 1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (e2), 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (e3), 1, 5, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (o), 2, 6, 1, 1);
	gtk_grid_attach(GTK_GRID (g), GTK_WIDGET (c), 3, 6, 1, 1);

	/* Destroy the treeview, and show our new stuff. */
	gtk_widget_destroy(userbox);
	userbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_box_pack_start(GTK_BOX (tab3), userbox, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(userbox), g, FALSE, TRUE, 0);
	gtk_widget_show_all(userbox);
}

gboolean uclick(GtkWidget *gtv, GdkEventButton *event, gpointer userdata) {

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

	//char *username = selected_item(gtv, 0);
	//if(username == NULL)
	//	return TRUE;

	/* Create the popup menu. */
	GtkWidget *pop_menu = gtk_menu_new();

	GtkWidget *newu = gtk_menu_item_new_with_label (l.uadd);
	GtkWidget *delu = gtk_menu_item_new_with_label(l.uremove);
	GtkWidget *editu = gtk_menu_item_new_with_label(l.uedit);
	
	gtk_menu_shell_append (GTK_MENU_SHELL (pop_menu), newu);
	gtk_menu_shell_append (GTK_MENU_SHELL (pop_menu), delu);
	gtk_menu_shell_append(GTK_MENU_SHELL (pop_menu), editu);
	
	g_signal_connect(newu, "activate", G_CALLBACK(add_user), gtv);
	g_signal_connect(delu, "activate", G_CALLBACK(del_user), gtv);
	g_signal_connect(editu, "activate", G_CALLBACK(edit_user), gtv);

	gtk_widget_show_all(pop_menu);
	gtk_menu_popup_at_pointer( GTK_MENU (pop_menu), NULL);
	return TRUE; /* right click finished */
}

GtkWidget *user_treeview() {

	/* A scrolled window. */
	GtkWidget *scrollw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollw),
                                    GTK_POLICY_ALWAYS, GTK_POLICY_AUTOMATIC); 
	gtk_box_pack_start(GTK_BOX(userbox), scrollw, FALSE, TRUE, 0);
	gtk_scrolled_window_set_propagate_natural_height (GTK_SCROLLED_WINDOW(scrollw), TRUE);
	gtk_scrolled_window_set_propagate_natural_width (GTK_SCROLLED_WINDOW(scrollw), TRUE);

	/* 
	 * Create a treeview with columns for the
	 * user overview.
	 * Rows will be added later.
	 */
	
	GtkWidget *userview = gtk_tree_view_new();
	gtk_container_add(GTK_CONTAINER(scrollw), userview);	
	GtkCellRenderer *c = gtk_cell_renderer_text_new();

	g_object_set(c, "font", opt.fontsize, NULL);
	g_object_set(userview, "enable-grid-lines", GTK_TREE_VIEW_GRID_LINES_BOTH, NULL);


	/* A right-click menu. */
	g_signal_connect(G_OBJECT (userview), "button-press-event", G_CALLBACK(uclick), userview);

	/* Add columns  */
	int cnt = 0;
	while((cnt <= UCOL) && (strlen(usercol[cnt]) >0)) {
	
		char *col_title = usercol[cnt];

		GtkTreeViewColumn *col = gtk_tree_view_column_new();
		gtk_tree_view_column_set_title(col, col_title);

		gtk_tree_view_column_set_clickable(col, TRUE);
		gtk_tree_view_column_set_reorderable(col, TRUE);
		gtk_tree_view_column_set_resizable(col, TRUE);
  		gtk_tree_view_append_column(GTK_TREE_VIEW(userview), col);
		gtk_tree_view_column_pack_start(col, c, TRUE);
		gtk_tree_view_column_add_attribute(col, c, "text", (cnt));

		cnt++;
	}

	/* Treestore */
	GtkTreeStore *t= gtk_tree_store_new(UCOL, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, \
									G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, \
									G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(userview), GTK_TREE_MODEL(t));
	g_object_unref(t); /* Destroy model automatically with view. */ 
  	gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(userview)),
                             GTK_SELECTION_SINGLE);


	/* Now add rows. */
	char *buf= "pw usershow -a | awk '{gsub(/:/, \"\\n\"); print}'";		
	char line[150];
	int size=150;	
	int i = 0; /* Some char counter in a line */
	int n = 0;
	cnt = 0;

	FILE *fp = popen(buf, "r");
	if ( fp == NULL ) {
		printf("could not execute pw usershow -a\n");	
		return NULL;
	}

	GtkTreeIter	iter;
	gtk_tree_store_append(t, &iter, NULL);

	/* Get a line */
	while( fgets(line, sizeof line, fp) ) {

		/* Cosmetics. */
		if(line[0] != '\0') {	
			int len = strlen(line);
			line[len-1] = '\0';
		}
		
		gtk_tree_store_set(t, &iter, cnt, line, -1);

		if(cnt == 9) {
			gtk_tree_store_append(t, &iter, NULL);
			cnt = 0;
		}
		else
			cnt++;
	}

	pclose(fp);
	return userview;
}

void users() {
	
	if(GTK_IS_WIDGET (userbox))
		gtk_widget_destroy(userbox);

	/* A top level container. */
	userbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
	gtk_container_add (GTK_CONTAINER (tab3), userbox);

	/* A treeview that contains all users. */
	user_treeview();

	gtk_widget_show_all(userbox);
}
