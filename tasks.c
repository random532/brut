#include "brut.h"

/* keep a reference to those boxes: */
GtkWidget *task_tabs;
GtkWidget *ttab0;
GtkWidget *ttab1;

GtkWidget *user_crontab;
GtkWidget *system_crontab;


void cleanup() {

	/* Somehow we need this: */

	if(GTK_IS_WIDGET (taskbox))
		gtk_widget_destroy(taskbox);

	if(GTK_IS_WIDGET (task_tabs))
		gtk_widget_destroy(task_tabs);

	if(GTK_IS_WIDGET (ttab0))
		gtk_widget_destroy(ttab0);

	if(GTK_IS_WIDGET (ttab1))
		gtk_widget_destroy(ttab1);

	if(GTK_IS_WIDGET (system_crontab))
		gtk_widget_destroy(system_crontab);

	if(GTK_IS_WIDGET (user_crontab))
		gtk_widget_destroy(user_crontab);

	task_tabs = NULL;
	ttab0 = NULL;
	ttab1 = NULL;
	user_crontab = NULL;
	system_crontab = NULL;

}

gboolean crontab_clicked(GtkWidget *gtv, GdkEventButton *event, gpointer userdata) {

/* A right click menu */

return TRUE;
}

gboolean ucrontab_clicked(GtkWidget *gtv, GdkEventButton *event, gpointer userdata) {

/* A right click menu */

return TRUE;
}

void fill_cronview(GtkWidget *tv, GtkTreeStore *ts, char *cmd) {

	/* Add rows */
	char line[MAXLINE];
	int size = MAXLINE;	

	memset(line, 0, MAXLINE);

	FILE *fp = popen(cmd, "r");
	if(fp == NULL) {
		printf("could not execute crontab -l\n");	
		return;
	}

	GtkTreeIter	iter;

	/* Get a line */
	while( fgets(line, sizeof line, fp) ) {
		if((line[0] != '#') && (line[0] != '\0') && (line[0] != '\n')) {	/* ignore comments */
		
			/* Cosmetics. */
			if(line[0] != '\0') {	
				int len = strlen(line);
				line[len-1] = '\0';
			}
			gtk_tree_store_append(ts, &iter, NULL);
			gtk_tree_store_set(ts, &iter, 0, line, -1);

		}
		memset(line, 0, MAXLINE);
	}
	pclose(fp);
}

void crontab_treeview(gboolean is_user) {

	/* Scrolled Window */
	GtkWidget *scrollw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollw),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 
	if(is_user == TRUE)
		gtk_box_pack_start(GTK_BOX(user_crontab), scrollw, FALSE, TRUE, 0);
	else
		gtk_box_pack_start(GTK_BOX(system_crontab), scrollw, FALSE, TRUE, 0);

	gtk_scrolled_window_set_propagate_natural_height (GTK_SCROLLED_WINDOW(scrollw), TRUE);
	gtk_scrolled_window_set_propagate_natural_width (GTK_SCROLLED_WINDOW(scrollw), TRUE);

	/* Treeview */
	GtkWidget *crontabview = gtk_tree_view_new();
	gtk_container_add(GTK_CONTAINER(scrollw), crontabview);	
	GtkCellRenderer *c = gtk_cell_renderer_text_new();
	
		gtk_widget_set_tooltip_text(crontabview, "Read only");

	g_object_set(c, "font", opt.fontsize, NULL);
	g_object_set(crontabview, "enable-grid-lines", GTK_TREE_VIEW_GRID_LINES_BOTH, NULL);

	GtkTreeViewColumn *col = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(col, "Job");

	gtk_tree_view_column_set_clickable(col, TRUE);
	gtk_tree_view_column_set_resizable(col, TRUE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(crontabview), col);
	gtk_tree_view_column_pack_start(col, c, TRUE);
	gtk_tree_view_column_add_attribute(col, c, "text", 0);

	/* Treestore */
	GtkTreeStore *t= gtk_tree_store_new(1, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(crontabview), GTK_TREE_MODEL(t));
	g_object_unref(t); /* Destroy model automatically with view. */ 
  	gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(crontabview)),
                             GTK_SELECTION_SINGLE);
	
	/* A right-click menu. */
	if(is_user == TRUE) {
		fill_cronview(crontabview, t, "crontab -l");
		g_signal_connect(G_OBJECT (crontabview), "button-press-event", G_CALLBACK(ucrontab_clicked), crontabview);
	}
	else {
		fill_cronview(crontabview, t, "cat /etc/crontab");
		g_signal_connect(G_OBJECT (crontabview), "button-press-event", G_CALLBACK(crontab_clicked), crontabview);
	}

}

void on_tasks_changed(GtkMenuItem *item, gpointer p) {
	

	if(item == NULL) {
		printf("on_tasks_changed(): error. NULL ptr.\n");
		return;
	}

	/* Redraw current tab. */
	GtkWidget *current_tab;
	const gchar *tab;

	current_tab = gtk_notebook_get_nth_page(GTK_NOTEBOOK (item), gtk_notebook_get_current_page(GTK_NOTEBOOK (item)));
	tab = gtk_notebook_get_tab_label_text(GTK_NOTEBOOK (item), current_tab);

	if(tab == NULL) {
		printf("on_tasks_changed(): error: empty tab!\n");
		return;
	}

	else if(strcmp(tab, "User crontab") == 0) {

		if(GTK_IS_WIDGET (user_crontab))
			gtk_widget_destroy(user_crontab);

		user_crontab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
		gtk_container_add (GTK_CONTAINER (ttab0), user_crontab);

		crontab_treeview(TRUE);
	}

	else if(strcmp(tab, "System crontab") == 0) {

		if(GTK_IS_WIDGET (system_crontab))
			gtk_widget_destroy(system_crontab);

		system_crontab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
		gtk_container_add (GTK_CONTAINER (ttab1), system_crontab);

		crontab_treeview(FALSE);
	}

		gtk_widget_show_all(taskbox);

}

void tasks_add_tabs() {

	/* Gtk notebook. */

	task_tabs = gtk_notebook_new();
//	gtk_notebook_set_tab_pos(task_tabs, GTK_POS_LEFT);
	gtk_notebook_set_show_border(GTK_NOTEBOOK (task_tabs), FALSE);
	gtk_container_add (GTK_CONTAINER (taskbox), task_tabs);

	/* Two tabs. */
	
	ttab0 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	ttab1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

	gtk_notebook_append_page(GTK_NOTEBOOK (task_tabs), ttab0, gtk_label_new("User crontab"));
	gtk_notebook_append_page(GTK_NOTEBOOK (task_tabs), ttab1, gtk_label_new("System crontab"));

	g_signal_connect_after(G_OBJECT (task_tabs), "switch-page", G_CALLBACK(on_tasks_changed), task_tabs);

}

void tasks() {

	/* Cleanup */
	cleanup();

	/* A top level container. */
	taskbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add (GTK_CONTAINER (tab6), taskbox);


	/* Add tabs. */
	tasks_add_tabs();

	gtk_widget_show_all(taskbox);

}
