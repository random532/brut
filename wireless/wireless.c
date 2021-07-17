/* 
 * Wireless tab:
 * This file contains all the gtk/GUI elements.
 */

#include "disk.h"
#include "wireless.h"


void CleanWireless() {

	if(GTK_IS_WIDGET (wbox))
		gtk_widget_destroy(wbox);
}

char *GetSsid(char *string) {

	if((string == NULL) || (strlen(string) < 32))
		return NULL;	/* some error. */
	char *ssid = malloc(40);
	if(ssid == NULL)
		return NULL;
	
	strncpy(ssid, string, 32);
	
	/* Remove spaces at the end. Zero terminate. */
	int i = 31;
	while(strncmp(&ssid[i], " ", 1) == 0)
		i--;
	ssid[i+1] = '\0';
	printf("ssid: %s!!!\n", ssid);

	return ssid;
}

char *GetBssid(char *string) {
	
	int start = 33; /* Skip ssid. */
	char *bssid = malloc(20);
	if(bssid == NULL)
		return bssid;
	
	memset(bssid, 0, 20);
	while(strncmp(&string[start], " ", 1) == 0) //&& (start <= 40))
		start++;

	strncpy(bssid, &string[start], 18);
	return bssid;
}

void AfterRootCmd() {
	
	if(exec2 == TRUE) {
		exec2 = FALSE;
		if(secondcmd != NULL)
			execute_me(secondcmd, USR);
	}
	else {
		if(wtmp != NULL) { /* Clean up */
			unlink(wtmp);
			free(wtmp);
			wtmp = NULL;
		}
		wireless();
	}
}
 
void WTopbox() {

	/* A box at the upper half. */
	topbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_add (GTK_CONTAINER (wbox), topbox);
	gtk_widget_set_size_request(topbox, 300, 200); /* width, height */
}

GtkWidget *WScrolled(GtkWidget *box) {
	/* Scrolled window. */
	GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 
	gtk_box_pack_start(GTK_BOX(box), scrolled_window, FALSE, TRUE, 0);
	gtk_scrolled_window_set_propagate_natural_height (GTK_SCROLLED_WINDOW(scrolled_window), TRUE);
	gtk_scrolled_window_set_propagate_natural_width (GTK_SCROLLED_WINDOW(scrolled_window), TRUE);

	return scrolled_window;
}

GtkWidget *ComboCommands() {
	GtkWidget *c = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Create");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Destroy");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Scan");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Modify");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Connect");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Up");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Down");
	g_signal_connect (c, "changed", G_CALLBACK (command_changed), NULL);	

	gtk_grid_attach(GTK_GRID(wedit), c, 0, 0, 1, 1);
	return c;
}

GtkWidget *ComboWlanDevices() {

	/* Combo box with all wlan devices on the system. */

	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT (wdev));

	char line[MAXLINE];
	char *dev;
	char *brk;
	
	memset(line, 0, MAXLINE);
	FILE *fp = popen("sysctl -n net.wlan.devices", "r");
	while(fgets(line, MAXLINE, fp)) {
		
		cosmetics(line);
		dev = strtok_r(line, " ", &brk);
		while(dev) {

			gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wdev), NULL, dev);
			dev = strtok_r( NULL, " ", &brk);
		}
	}
	pclose(fp);

	return wdev;
}

GtkWidget *ComboWlanInterfaces() {

	/* Box with all currently configured wlan interfaces */

	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT (winterface));

	char line[MAXLINE];
	FILE *fp = popen("ifconfig -g wlan | sed 's/ /\\n/g'", "r");
	while(fgets(line, MAXLINE, fp)) {

		cosmetics(line);
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (winterface), NULL, line);
	}
	pclose(fp);

	return winterface;
}

void WGridEntries() {

	wcommands = ComboCommands();
	wdev = gtk_combo_box_text_new();
	winterface = gtk_combo_box_text_new();
	wapply = gtk_button_new_with_mnemonic(l.apply);


	g_signal_connect(wapply, "clicked", G_CALLBACK(ApplyClicked), NULL);
	g_signal_connect (winterface, "changed", G_CALLBACK (winterface_changed), NULL);

	gtk_grid_attach(GTK_GRID(wedit), gtk_label_new("   "), 0, 4, 1, 1);
//	gtk_grid_attach(GTK_GRID(wedit), gtk_label_new("   "), 0, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(wedit), wdev, 0, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(wedit), winterface, 0, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(wedit), wapply, 0, 8, 1, 1);
}

void command_changed( GtkWidget *w, gpointer p) {

	/* Update devices and interfaces. */
	wdev = ComboWlanDevices();
	winterface = ComboWlanInterfaces();

	gtk_widget_hide(GTK_WIDGET (wdev));
	gtk_widget_hide(GTK_WIDGET (winterface));
	gtk_widget_show(wapply);

	/* Show options to user. */
	char *cmd;
	cmd = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (wcommands));
	if(cmd == NULL)
		return;
	ShowOptions(cmd);
	free(cmd);
}

void winterface_changed( GtkWidget *w, gpointer p) {
	
	/* Special case: User chose "Connect" but no interface yet. XXX: Necessary? */
	char *cmd;
	cmd = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (wcommands));
	if((cmd == NULL) || (strlen(cmd) == 0)) {
		return;
	}
	if(strcmp(cmd, "Connect") == 0) {
		ShowOptions(cmd);
	}
}

void WEditor() {

	WTopbox();

	/* Grid */
	wedit = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(wedit), FALSE);
	gtk_grid_insert_column(GTK_GRID(wedit), 7);
	gtk_grid_set_row_spacing(GTK_GRID(wedit), 5);
	gtk_grid_set_column_spacing(GTK_GRID(wedit), 5);
	gtk_box_pack_start(GTK_BOX(topbox), wedit, FALSE, FALSE, 10);

	WGridEntries();

	/* Options */
	woptions = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_add (GTK_CONTAINER (topbox), woptions);
}

GtkWidget *WTreeview(GtkWidget *box) {

	GtkWidget *view = gtk_tree_view_new();
	
	gtk_container_add(GTK_CONTAINER(box), view);	
	GtkCellRenderer *cell = gtk_cell_renderer_text_new();

	g_object_set(cell, "font", opt.fontsize, NULL);
	//g_object_set(cell,"editable", TRUE, NULL);
	//gtk_tree_view_set_enable_search(view, TRUE);
	g_object_set(view, "enable-grid-lines", GTK_TREE_VIEW_GRID_LINES_BOTH, NULL);
	

	char *col_title = "Name";
	GtkTreeViewColumn *col = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(col, col_title);
	gtk_tree_view_column_set_clickable(col, TRUE);
	gtk_tree_view_column_set_reorderable(col, TRUE);
	gtk_tree_view_column_set_resizable(col, TRUE);
  	gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

	gtk_tree_view_column_pack_start(col, cell, TRUE);
	gtk_tree_view_column_add_attribute(col, cell, "text", 0);

	wtree = gtk_tree_store_new(1, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(view), GTK_TREE_MODEL(wtree));
	g_object_unref(wtree); /* destroy model automatically with view. */
  	gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(view)),
                             GTK_SELECTION_SINGLE);

	return view;
}

void WFillTree(GtkWidget *tv) {
	
	/* Execute "ifconfig -g inet*/
	char cmd[CMDSIZE];
	char *devlist;
	char *devinfo;
	char *dev;
	char *brk;
	
	GtkTreeIter child;
	GtkTreeIter parent;


	devlist = command("ifconfig -g wlan | tr \"\n\" \" \"");
	if((devlist == NULL) || (strlen(devlist) == 0))
		return;


	dev = strtok_r(devlist, " ", &brk);
	while(dev) {

		gtk_tree_store_append(wtree, &parent, NULL);
		gtk_tree_store_set(wtree, &parent, 0, dev, -1);

		sprintf(cmd, "ifconfig %s", dev);
		devinfo = command(cmd);
		if(devinfo != NULL) {
			gtk_tree_store_append(wtree, &child, &parent);
			gtk_tree_store_set(wtree, &child, 0, devinfo, -1);
			free(devinfo);
		}
		/* next device */
		dev = strtok_r( NULL, " ", &brk);
	}
	
	free(devlist);
	
	gtk_tree_view_expand_all(GTK_TREE_VIEW(tv));
	gtk_tree_view_set_enable_search (GTK_TREE_VIEW(tv), TRUE);	
	gtk_tree_view_set_enable_tree_lines (GTK_TREE_VIEW(tv), TRUE);
	gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(tv), GTK_TREE_VIEW_GRID_LINES_BOTH);

}

void WBottomView() {

	/* A top level container. */
	botbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add (GTK_CONTAINER (wbox), botbox);
	
	/* A scrolled window. */
	GtkWidget *sw = WScrolled(botbox);

	/* A treeview */
	GtkWidget *tv = WTreeview(sw);
	
	/* Fill the treestore. */
	WFillTree(tv);

	/* Update treeview nicely. XXX: Still problems displaying this! */
	gtk_widget_hide(sw);
	gtk_widget_show(sw);
}

void wireless() {

	CleanWireless();
	
	/* A top level container. */
	wbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add (GTK_CONTAINER (tab9), wbox);

	/* Editor */
	WEditor();

	/* Display current wireless interfaces. */
	WBottomView();
	
	gtk_widget_show_all(wbox);
	gtk_widget_hide(wapply);
	gtk_widget_hide(winterface);
	gtk_widget_hide(wdev);
}

