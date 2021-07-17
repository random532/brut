/* 
 * Wireless tab:
 * This file handles the drawing of all the Options (top right).
 */

#include "disk.h"
#include "wireless.h"


GtkWidget *ComboModes() {

	wmodes = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wmodes), NULL, "default");	
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wmodes), NULL, "sta");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wmodes), NULL, "ahdemo");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wmodes), NULL, "adhoc"); //ibss
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wmodes), NULL, "ap"); // hostap
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wmodes), NULL, "mesh");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wmodes), NULL, "tdma");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wmodes), NULL, "wds");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wmodes), NULL, "monitor");
	gtk_combo_box_set_active( GTK_COMBO_BOX (wmodes), 0);
	return wmodes;
}

gboolean ComboAP() {

	/* Combo box with all the Access points. */
	if(GTK_IS_WIDGET(whosts))
		gtk_widget_destroy(whosts);
	whosts = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (whosts), NULL, "[Custom]");

	char *what;
	what = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (winterface));
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

	fgets(line, MAXLINE, fp); /* discard first line. */
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

	gtk_combo_box_set_active( GTK_COMBO_BOX (whosts), 0);		
	g_signal_connect (whosts, "changed", G_CALLBACK (AP_changed), NULL);	

	return TRUE;
}

GtkWidget *DrawHosts() {

	CleanOptions();

	GtkWidget *s = WScrolled(woptions);
	
	/* Grid */
	GtkWidget *hg	 = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(hg), FALSE);
//	gtk_grid_insert_column(GTK_GRID(gh), 7);
	gtk_grid_set_row_spacing(GTK_GRID(hg), 5);
	gtk_grid_set_column_spacing(GTK_GRID(hg), 0);
	gtk_container_add(GTK_CONTAINER (s), hg);

	return hg;
}

void ShowOptions(char *what) {

	CleanOptions();
	

	if(strcmp(what, "Create") == 0) {
		OptionsCreate();
		gtk_widget_show(wdev);
	}
	else if(strcmp(what, "Destroy") == 0) {
		gtk_widget_show(winterface);
	}
	else if(strcmp(what, "Scan") == 0) {
		/* No options */
		gtk_widget_show(winterface);
	}
	else if(strcmp(what, "Connect") == 0) {
		gtk_widget_show(winterface);
		OptionsConnect();
	}
	else if(strcmp(what, "Up") == 0) {
		/* No options */
		gtk_widget_show(winterface);
	}
	else if(strcmp(what, "Down") == 0) {
		/* No options */
		gtk_widget_show(winterface);
	}
	else if(strcmp(what, "Modify") == 0) {
		OptionsModify();
		gtk_widget_show(winterface);
	}
}

void CleanOptions() {

	if(GTK_IS_WIDGET (woptions))
		gtk_widget_destroy(woptions);
	
	woptions = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add (GTK_CONTAINER (topbox), woptions);
}

void OptionsCreate() {

	gtk_container_add(GTK_CONTAINER (woptions), gtk_label_new("Options:"));
	gtk_container_add(GTK_CONTAINER (woptions), gtk_label_new("Mode:"));

	/* Add Modes. */
	gtk_container_add(GTK_CONTAINER (woptions), ComboModes());

	gtk_widget_show_all(woptions);
}

void OptionsConnect() {

	/* Did he choose an interface yet? */
	char *dev;
	dev = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (winterface));
	if((dev == NULL) || (strlen(dev) == 0)) {
		msg("Choose an interface!");
		return;
	}

	/* Create widgets. */
	wpass = gtk_entry_new();
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (wpass)), 30);
	gtk_entry_set_width_chars(GTK_ENTRY(wpass), 20);
	gtk_entry_set_placeholder_text (GTK_ENTRY(wpass), "Passphrase");
	
	toggle_encrypted = gtk_check_button_new_with_label("WPA2 encrypted network");
	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (toggle_encrypted), TRUE);
	g_signal_connect (toggle_encrypted, "clicked", G_CALLBACK (encrypted_changed), NULL);

	customAP = gtk_entry_new();
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (customAP)), 40);
	gtk_entry_set_width_chars(GTK_ENTRY(customAP), 40);
	gtk_entry_set_placeholder_text (GTK_ENTRY(customAP), "Access Point");


	/* Add them. */
	gtk_container_add(GTK_CONTAINER (woptions), gtk_label_new("Options:"));
	if(ComboAP() == TRUE)
		gtk_container_add(GTK_CONTAINER (woptions), whosts);
	else
		gtk_container_add(GTK_CONTAINER (woptions), gtk_label_new("Try again, put interface 'Up', or use custom AP!"));

	gtk_container_add(GTK_CONTAINER (woptions), GTK_WIDGET (toggle_encrypted));
	gtk_container_add(GTK_CONTAINER (woptions), wpass);
	gtk_container_add(GTK_CONTAINER (woptions), GTK_WIDGET (customAP));

	gtk_widget_show_all(woptions);
//	gtk_widget_hide(customAP);
}


void add_regdomain() {

	wregdomain = gtk_combo_box_text_new();
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "default");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "ETSI");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "ETSI2");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "FCC");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "FCC3");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "FCC4");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "JAPAN");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "ETSI3");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "APAC");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "APAC2");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "APAC3");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "KOREA");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "ROW");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "NONE");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "SR9");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "XR9");
	gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (wregdomain), NULL, "XC900M");
	gtk_grid_attach(GTK_GRID(modgrid), wregdomain, 1, W_POS_REGDOMAIN, 1, 1);
}

void add_country() {

	GtkEntryBuffer *cbuf = gtk_entry_buffer_new (NULL, 0);
	gtk_entry_buffer_set_max_length (cbuf, 3);
	wcountry = gtk_entry_new_with_buffer (cbuf);
	gtk_entry_set_placeholder_text (GTK_ENTRY(wcountry), "US");
	gtk_grid_attach(GTK_GRID(modgrid), wcountry, 1, W_POS_COUNTRY, 1, 1);
}

void OptionsGridItems() {
	
	gtk_grid_attach(GTK_GRID(modgrid), gtk_label_new("Regdomain:"), 0, W_POS_REGDOMAIN, 1, 1);
	gtk_grid_attach(GTK_GRID(modgrid), gtk_label_new("Country:"), 0, W_POS_COUNTRY, 1, 1);
	gtk_grid_attach(GTK_GRID(modgrid), gtk_label_new("WOL:"), 0, W_POS_WOL, 1, 1);
	gtk_grid_attach(GTK_GRID(modgrid), gtk_label_new("What else?:"), 0, 4, 1, 1);
	
	add_regdomain();
	add_country();
	// add_wol();

}

void OptionsModify() {
	
	/* 
	 * Layout:
	 * A scrolled window containing a grid.
	 */

	modsw = WScrolled(woptions);
	
	/* Grid */
	modgrid = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(modgrid), FALSE);
//	gtk_grid_insert_column(GTK_GRID(modgrid), 7);
	gtk_grid_set_row_spacing(GTK_GRID(modgrid), 5);
	gtk_grid_set_column_spacing(GTK_GRID(modgrid), 5);
	gtk_container_add(GTK_CONTAINER(modsw), modgrid);

	OptionsGridItems();
	gtk_widget_show_all(woptions);
}

void AP_changed( GtkWidget *w, gpointer p) {
	char *what;
	what = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (whosts));
	if(what == NULL)
		return;
	if((strncmp(what, "[Custom]", 8) == 0))
		gtk_widget_show(GTK_WIDGET (customAP));
	else
		gtk_widget_hide(GTK_WIDGET (customAP));

	free(what);
}

void encrypted_changed( GtkWidget *w, gpointer p) {

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_encrypted)) == TRUE)
		gtk_widget_show(GTK_WIDGET (wpass));
	else
		gtk_widget_hide(GTK_WIDGET (wpass));
}


