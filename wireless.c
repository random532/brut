/* Wireless tab */
#include "disk.h"

/* Boxes */
GtkWidget *topbox;
GtkWidget *botbox;

GtkWidget *wedit;
GtkWidget *woptions;

/* Widgets */
GtkWidget *wcommands;
GtkWidget *wdevices; /* combo box */
GtkWidget *wdev; /* text entry */
GtkWidget *wname; /* text entry */
GtkWidget *whosts; /* combo box */
GtkWidget *wapply;
GtkWidget *wpass;  /* text entry */

GtkTreeStore *wtree;

/* In case we issue a second root command. */
gboolean exec2; /* Execute another command. */
char *secondcmd;
char *wtmp; /* Tmpfile */

/* Functions */
void CleanWireless();
void CleanOptions();
void WTopbox();
GtkWidget *WScrolled(GtkWidget *);
GtkWidget *ComboModes();
GtkWidget *ComboCommands();
GtkWidget *ComboDevices();
void WGridEntries();
void ExecCreate();
void ExecDestroy();
void ExecConnect();
char *GetBssid(char *);
void ExecDisconnect();
void ExecScan();
void ExecModify();
void ApplyClicked( GtkWidget *, gpointer);
void OptionsCreate();
void OptionsConnect();
gboolean ComboHosts();
GtkWidget *DrawHosts();
void DrawOptions(char *);
void command_changed( GtkWidget *, gpointer);
void devices_changed( GtkWidget *, gpointer);
void WEditor();
void WBottomView();
GtkWidget *WTreeview(GtkWidget *);
void WFillTree(GtkWidget *);
void AfterRootCmd();
void wireless();

void CleanWireless() {

	if(GTK_IS_WIDGET (wbox))
		gtk_widget_destroy(wbox);
}

void CleanOptions() {

	if(GTK_IS_WIDGET (woptions))
		gtk_widget_destroy(woptions);
	
	woptions = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add (GTK_CONTAINER (topbox), woptions);
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
	printf("bssid:%s\n", bssid);
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


GtkWidget *ComboModes() {
	GtkWidget *c = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "adhoc");

	return c;
}

GtkWidget *ComboCommands() {
	GtkWidget *c = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Create");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Destroy");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Scan");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Modify");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Connect");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, "Disconect");
	g_signal_connect (c, "changed", G_CALLBACK (command_changed), NULL);	

	gtk_grid_attach(GTK_GRID(wedit), c, 0, 0, 1, 1);
	return c;
}

GtkWidget *ComboDevices() {

	GtkWidget *c = gtk_combo_box_text_new();

	char line[MAXLINE];
	FILE *fp = popen("ifconfig -g wlan | sed 's/ /\\n/g'", "r");
	while(fgets(line, MAXLINE, fp)) {

		cosmetics(line);
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (c), NULL, line);
	}
	pclose(fp);
	
	g_signal_connect (c, "changed", G_CALLBACK (devices_changed), NULL);
	gtk_grid_attach(GTK_GRID(wedit), c, 0, 1, 1, 1);

	return c;
}

void WGridEntries() {

	wcommands = ComboCommands();
	wdevices = ComboDevices();

	wapply = gtk_button_new_with_mnemonic(l.apply);
	g_signal_connect(wapply, "clicked", G_CALLBACK(ApplyClicked), NULL);
	gtk_grid_attach(GTK_GRID(wedit), gtk_label_new("   "), 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(wedit), gtk_label_new("   "), 0, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(wedit), wapply, 0, 6, 1, 1);
}

void ExecCreate() {

	const gchar *dev = gtk_entry_get_text(GTK_ENTRY (wdev));
	if((dev == NULL) || (strlen(dev) == 0)) {
		msg("Device missing.");
		return;
	}

	const gchar *devname = gtk_entry_get_text(GTK_ENTRY (wname));
	if((devname == NULL) || (strlen(devname) == 0)) {
		msg("Name missing.");
		return;
	}

	char *cmd = malloc(CMDSIZE);
	if(cmd == NULL)
		return;
	memset(cmd, 0, CMDSIZE);
	sprintf(cmd, "ifconfig %s create wlandev %s", devname, dev);

	/* 2. Command: Mark it as "up", and do a preliminary scan? */
	secondcmd = malloc(CMDSIZE);
	if(secondcmd == NULL) {
		free(cmd);
		return;
	}
	memset(secondcmd, 0, CMDSIZE);
	sprintf(secondcmd, "ifconfig %s up list scan", devname);
	exec2 = TRUE;

	execute_me(cmd, USR);
}

void ExecDestroy() {

	char *what;
	what = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (wdevices));
	if((what == NULL) || (strlen(what) == 0)) {
		printf("no device!\n");
		return;
	}
	char *cmd = malloc(CMDSIZE);
	if(cmd == NULL)
		return;
	memset(cmd, 0, CMDSIZE);
	sprintf(cmd, "ifconfig %s destroy", what);

	exec2 = FALSE;
	execute_me(cmd, USR);
}

void ExecScan() {

	char *what;
	what = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (wdevices));
	if(what == NULL) {
		return;
	}
	char line[MAXLINE];
	char cmd[CMDSIZE];
	int row = 0;

	memset(line, 0, MAXLINE);
	memset(cmd, 0, CMDSIZE);

	GtkWidget *g = DrawHosts();

	sprintf(cmd, "ifconfig %s list scan", what);
	FILE *fp = popen(cmd, "r");
	if(fp == NULL)
		return;
	while(fgets(line, MAXLINE, fp)) {
		cosmetics(line);
		gtk_grid_attach(GTK_GRID (g), gtk_label_new(line), 0, row, 1, 1);
		row++;
		memset(line, 0, MAXLINE);
	}
	pclose(fp);
	
	if(row == 0)
		gtk_grid_attach(GTK_GRID (g), gtk_label_new("No results!"), 0, row, 1, 1);

	/* Show everything. */
	gtk_grid_attach(GTK_GRID (g), gtk_label_new("   "), 0, (row+1), 1, 1);
	gtk_widget_show_all(woptions);
}

void ExecModify() {
}

void ExecDisconnect() {

	char *what;
	what = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (wdevices));
	if(what == NULL) {
		return;
	}
	char *cmd = malloc(CMDSIZE);
	if(cmd == NULL)
		return;
	memset(cmd, 0, CMDSIZE);
	sprintf(cmd, "ifconfig %s down", what);
	free(what);
	exec2 = FALSE;
	execute_me(cmd, USR);
	}

void ExecConnect() {

	/* Network interface. */
	char *dev;
	dev = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (wdevices));
	if(dev == NULL) {
		return;
	}

	/* Access point. */
	char *h;
	h = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (whosts));
	if(h == NULL) {
		return;
	}
	/* Only care for bssid. */
	char *bssid = GetBssid(h);

	/* Passphrase. */
	const gchar *gpass = gtk_entry_get_text(GTK_ENTRY (wpass));
	if(!gtk_widget_is_visible(GTK_WIDGET (wpass)) || (gpass == NULL) || (strlen(gpass) == 0)) {
		return;
	}

	/*
	 * echo > /tmp
	 * pkill wpa_supplicant
	 * wpa_supplicant -i -B -c
	 */
	char *tmpfile = random_filename();
	char *cmd = malloc(MAXLINE); /* Make it big. */
	memset(cmd, 0, MAXLINE);
	snprintf(cmd, MAXLINE, "echo 'ctrl_interface=/var/run/wpa_supplicant\nnetwork={\nbssid=%s\npsk=\"%s\"\n}\n' > %s", bssid, gpass, tmpfile);
	FILE *fp = popen(cmd, "r");
	pclose(fp);

	printf("%s\n", cmd);

	/* pkill wpa_supplicant */
	memset(cmd, 0, MAXLINE);
	sprintf(cmd, "pkill wpa_supplicant");

	/* Second command: wpa_supplicant -i -B -c */
	secondcmd = malloc(MAXLINE); /* Make it big. */
	memset(secondcmd, 0, MAXLINE);
	snprintf(secondcmd, MAXLINE, "wpa_supplicant -i %s -B -c %s", dev, tmpfile);
	exec2 = TRUE;
	wtmp = tmpfile;
	printf("%s\n", secondcmd);

	free(bssid);
	free(dev);
	free(h);
//	unlink(tmpfile);
	execute_me(cmd, USR);
}

void ApplyClicked( GtkWidget *w, gpointer p) {

	/* Default is to only execute one root command. */
	exec2 = FALSE;
	secondcmd = NULL;
	wtmp = NULL;

	char *what;
	what = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (wcommands));
	if(what == NULL) {
		return;
	}
	if(strcmp(what, "Create") == 0) {
		free(what);
		ExecCreate();
		wireless();
	}
	if(strcmp(what, "Destroy") == 0) {
		free(what);
		ExecDestroy();
		wireless();
	}
	if(strcmp(what, "Scan") == 0) {
		free(what);
		ExecScan();
	}
	if(strcmp(what, "Modify") == 0) {
		free(what);
		ExecModify();
	}
	if(strcmp(what, "Connect") == 0) {
		free(what);
		ExecConnect();
		wireless();
	}
	if(strcmp(what, "Disconnect") == 0) {
		free(what);
		ExecDisconnect();
	}
}

void OptionsCreate() {

	/* Two text entries. */
	wdev = gtk_entry_new();
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (wdev)), 10);
	gtk_entry_set_width_chars(GTK_ENTRY(wdev), 20);
	gtk_entry_set_placeholder_text (GTK_ENTRY(wdev), "e.g. ath0, iwn0");

	wname = gtk_entry_new();
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (wname)), 10);
	gtk_entry_set_width_chars(GTK_ENTRY(wname), 20);
	gtk_entry_set_placeholder_text (GTK_ENTRY(wname), "e.g. wlan0, wlan1");
	
	gtk_container_add(GTK_CONTAINER (woptions), gtk_label_new("Options:"));
	gtk_container_add(GTK_CONTAINER (woptions), wdev);
	gtk_container_add(GTK_CONTAINER (woptions), wname);

// XXX: todo: Add Modes.
//	gtk_container_add(GTK_CONTAINER (woptions), ComboModes());

	gtk_widget_show_all(woptions);
}

void OptionsConnect() {

	/* Did he choose an interface yet? */
	char *dev;
	dev = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (wdevices));
	if((dev == NULL) || (strlen(dev) == 0)) {
		msg("Choose an interface!");
		return;
	}

	wpass = gtk_entry_new();
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (wpass)), 30);
	gtk_entry_set_width_chars(GTK_ENTRY(wpass), 20);
	gtk_entry_set_placeholder_text (GTK_ENTRY(wpass), "Passphrase");


	gtk_container_add(GTK_CONTAINER (woptions), gtk_label_new("Options:"));
	if(ComboHosts() == TRUE)
		gtk_container_add(GTK_CONTAINER (woptions), whosts);
	else
		gtk_container_add(GTK_CONTAINER (woptions), gtk_label_new("I scanned, but no Access Points were found!"));
	gtk_container_add(GTK_CONTAINER (woptions), wpass);

	gtk_widget_show_all(woptions);
}

gboolean ComboHosts() {

	if(GTK_IS_WIDGET(whosts))
		gtk_widget_destroy(whosts);
	whosts = gtk_combo_box_text_new();

	char *what;
	what = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (wdevices));
	if(what == NULL) {
		msg("Choose a wlan interface!");
		return FALSE;
	}
	char line[MAXLINE];
	char cmd[CMDSIZE];
	int items = 0;
		
	memset(line, 0, MAXLINE);
	memset(cmd, 0, CMDSIZE);

	sprintf(cmd, "ifconfig %s list scan", what);
	FILE *fp = popen(cmd, "r");
	if(fp == NULL)
		return FALSE;
	while(fgets(line, MAXLINE, fp)) {
		/* Only show ssid and bssid */
		line[56] = '\0';
		gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (whosts), NULL, line);
		memset(line, 0, MAXLINE);
		items++;
	}
	pclose(fp);

	if(items == 0)
		return FALSE;
	return TRUE;
}

GtkWidget *DrawHosts() {

	CleanOptions();

	GtkWidget *s = WScrolled(woptions);
	
	/* Grid */
	GtkWidget *hg = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(hg), FALSE);
//	gtk_grid_insert_column(GTK_GRID(gh), 7);
	gtk_grid_set_row_spacing(GTK_GRID(hg), 5);
	gtk_grid_set_column_spacing(GTK_GRID(hg), 0);
	gtk_container_add(GTK_CONTAINER (s), hg);

	return hg;
}

void DrawOptions(char *what) {

	CleanOptions();

	if(strcmp(what, "Create") == 0) {
		OptionsCreate();
	}
	else if(strcmp(what, "Destroy") == 0) {
		/* No options */
		gtk_widget_show(wdevices);
	}
	else if(strcmp(what, "Scan") == 0) {
		/* No options */
		gtk_widget_show(wdevices);
	}
	else if(strcmp(what, "Disconnect") == 0) {
		/* No options */
		gtk_widget_show(wdevices);
	}
	else if(strcmp(what, "Connect") == 0) {
		gtk_widget_show(wdevices);
		OptionsConnect();
	}
	else if(strcmp(what, "Modify") == 0) {
		/* empty for now */
	}
}

void command_changed( GtkWidget *w, gpointer p) {

	gtk_widget_show(wapply);

	char *cmd;
	cmd = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (wcommands));
	if(cmd == NULL) {
		return;
	}
	
	DrawOptions(cmd);
	free(cmd);
}

void devices_changed( GtkWidget *w, gpointer p) {
	
	char *cmd;
	cmd = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (wcommands));
	if((cmd == NULL) || (strlen(cmd) == 0)) {
		return;
	}
	if(strcmp(cmd, "Connect") == 0) {
		DrawOptions(cmd);
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

	devlist = command("ifconfig -g wlan");
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
	
	/* Update treeview nicely. */
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
	gtk_widget_hide(wdevices);
}

