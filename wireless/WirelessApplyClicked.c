/* wireless tab:
 * This file contains functions in case "Apply" was clicked.
 */
 
#include "disk.h"
#include "wireless.h"

void ApplyClicked( GtkWidget *, gpointer);
void ExecCreate();
void ExecDestroy();
void ExecConnect();
void ExecUp();
void ExecDown();
void ExecScan();
void ExecModify();

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
	else if(strcmp(what, "Destroy") == 0) {
		free(what);
		ExecDestroy();
		wireless();
	}
	else if(strcmp(what, "Scan") == 0) {
		free(what);
		ExecScan();
	}
	else if(strcmp(what, "Modify") == 0) {
		free(what);
		ExecModify();
		wireless();
	}
	else if(strcmp(what, "Connect") == 0) {
		free(what);
		ExecConnect();
		wireless();
	}
	else if(strcmp(what, "Up") == 0) {
		free(what);
		ExecUp();
		//wireless(); XXX: ???
	}
	else if(strcmp(what, "Down") == 0) {
		free(what);
		ExecDown();
		//wireless(); XXX: ???
	}
	
	printf("ApplyClicked finished.\n");
}

void ExecCreate() {

	const gchar *dev =  gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (GTK_COMBO_BOX_TEXT (wdev)));
	if((dev == NULL) || (strlen(dev) == 0)) {
		msg("No wlan devices chosen. Driver issues?");
		return;
	}

	/* Gather the options. */
	const gchar *mode =  gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (GTK_COMBO_BOX_TEXT (wmodes)));
	if((mode == NULL) || (strlen(mode) == 0)) {
		msg("No wireless mode chosen.");
		return;
	}

	/* Build the command. */
	char *cmd = malloc(CMDSIZE);
	if(cmd == NULL)
		return;

	memset(cmd, 0, CMDSIZE);
	if(strncmp(mode, "default", 7) == 0)
		sprintf(cmd, "ifconfig wlan create wlandev %s", dev);
	else
		sprintf(cmd, "ifconfig wlan create wlandev %s wlanmode %s", dev, mode);

	/* Execute the command. */
	exec2 = FALSE;
	execute_me(cmd, USR);
}

void ExecDestroy() {

	char *what;
	what = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (winterface));
	if((what == NULL) || (strlen(what) == 0)) {
		msg("no device!");
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
	what = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (winterface));
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
		/* XXX: This might look better in a treeview. */
		gtk_grid_attach(GTK_GRID (g), gtk_label_new(line), 0, row, 1, 1);
		gtk_grid_attach(GTK_GRID (g), gtk_label_new("-- "), 1, row, 1, 1);

		row++;
		memset(line, 0, MAXLINE);
	}
	pclose(fp);
	
	if(row == 0)
		gtk_grid_attach(GTK_GRID (g), gtk_label_new("No results!"), 0, row, 1, 1);


	gtk_grid_attach(GTK_GRID (g), gtk_label_new("   "), 0, (row+1), 1, 1);
	gtk_widget_show_all(woptions);
}

char *build_modify_command(char *iface, char *domain, const char *country) {

	char *cmd = malloc(MAXLINE);
	if(cmd == NULL)
		return cmd;
	memset(cmd, 0, MAXLINE);
	snprintf(cmd, MAXLINE, "ifconfig %s ", iface);
	
	if((domain != NULL) && (strncmp(domain, "default", 7) != 0)) {
		strncat(cmd, "regdomain ",10); 
		strcat(cmd, domain);
	}

	if((country != NULL) && (strlen(country) > 0))
		strncat(cmd, " country ",9); 
		strcat(cmd, country);
	
	return cmd;	
}

void ExecModify() {
	
	char *iface;
	char *domain;
	const char *country;
	
	/* 1. Retrieve options. */
	
	iface = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (winterface));
	if(iface == NULL) {
		msg("Chose an interface!");
		return;
	}

	domain = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (wregdomain));

	country = gtk_entry_get_text(GTK_ENTRY (wcountry));
	if(!gtk_widget_is_visible(GTK_WIDGET (wcountry)) || (wcountry == NULL)) {
		msg("error reading country");
		return;
	}

	/* 2. Build the command. */

	char *cmd = build_modify_command(iface, domain, country);
	exec2 = FALSE;

	/* 3. Clean up. */
	free(iface);
	if(domain != NULL)
		free(domain);


	/* 4. Execute. */
	if(cmd != NULL) {
		printf("executing: %s\n", cmd);
		execute_me(cmd, USR);
	}
	printf("execution finished.\n");
}

void ExecDown() {

	char *what;
	what = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (winterface));
	if(what == NULL)
		return;
	char *cmd = malloc(CMDSIZE);
	if(cmd == NULL)
		return;
	memset(cmd, 0, CMDSIZE);
	sprintf(cmd, "ifconfig %s down", what);
	free(what);
	exec2 = FALSE;
	execute_me(cmd, USR);
	}

void ExecUp() {

	char *what;
	what = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (winterface));
	if(what == NULL)
		return;
	char *cmd = malloc(CMDSIZE);
	if(cmd == NULL)
		return;
	memset(cmd, 0, CMDSIZE);
	sprintf(cmd, "ifconfig %s up", what);
	free(what);
	exec2 = FALSE;
	execute_me(cmd, USR);
	}

char *get_interface() {
	/* Network interface. */
	return gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (winterface));
}

char *get_ap() {

	char *ap;
	char *ssid;
	
	ap = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (whosts));

	if( (ap == NULL) || (strncmp(ap, "[Custom]", 8) == 0)) {
		/* we have custom Access Point */

		if(!ap)
			free(ap);
	
		if(!gtk_widget_is_visible(GTK_WIDGET (customAP))) {
			msg("Error choosing custom access point");
			return NULL;
		}

		const char *custom = gtk_entry_get_text(GTK_ENTRY (customAP));
		if((custom == NULL) || (strlen(custom) == 0)) {
			msg("Which Access point?");
			return NULL;
		}

		/* make it a buffer. */
		int len = strlen(custom);
		printf("custom ssid chosen: %s, len=%d\n", custom, len);
		ssid = malloc(len+5);
		memset(ssid, 0, len+5);
		strncpy(ssid, custom, len);
	}

	else {
		if(!ap)
			free(ap);
		/* Get ssid. */
		ssid = GetSsid(ap);
	}
	
	return ssid;
}

int do_unencrypted(char *interface, char *ssid) {
	
	if((interface == NULL) || ssid == NULL)
		return 0;

	char *cmd = malloc(MAXLINE); /* Make it big. */
	if(cmd == NULL) {
		printf("error: WirelessApplyClicked: malloc() failed. Are you out of memory?\n");
		return 0;
	}
	memset(cmd, 0, MAXLINE);
	snprintf(cmd, MAXLINE, "ifconfig %s ssid \"%s\"", interface, ssid);
	printf("%s\n", cmd);
	free(ssid);
	free(interface);
	exec2 = FALSE;
	execute_me(cmd, USR);
	return 1;
}

int do_encrypted(char *interface, char* ssid) {

	/* Retrieve Passphrase. */
	const gchar *gpass = gtk_entry_get_text(GTK_ENTRY (wpass));
	if(!gtk_widget_is_visible(GTK_WIDGET (wpass)) || (gpass == NULL) || (strlen(gpass) == 0)) {
		return 0;
	}

	/*
	 * XXX: This is certainly a dirty way to connect.
	 * echo > /tmp
	 * pkill wpa_supplicant
	 * wpa_supplicant -i -B -c
	 */
	char *tmpfile = random_filename();
	char *cmd = malloc(MAXLINE); /* Make it big. */
	memset(cmd, 0, MAXLINE);
	snprintf(cmd, MAXLINE, "echo 'ctrl_interface=/var/run/wpa_supplicant\nnetwork={\nssid=\"%s\"\npsk=\"%s\"\n}\n' > %s", ssid, gpass, tmpfile);
	printf("%s\n", cmd);
	FILE *fp = popen(cmd, "r");
	pclose(fp);

	/* pkill wpa_supplicant */
	memset(cmd, 0, MAXLINE);
	sprintf(cmd, "pkill wpa_supplicant");

	/* Second command: wpa_supplicant -i -B -c */
	secondcmd = malloc(MAXLINE); /* Make it big. */
	memset(secondcmd, 0, MAXLINE);
	snprintf(secondcmd, MAXLINE, "wpa_supplicant -i %s -B -c %s", interface, tmpfile);
	exec2 = TRUE;
	wtmp = tmpfile;

	free(ssid);
	free(interface);
//	unlink(tmpfile);
	execute_me(cmd, USR);
	return 1;
}

void ExecConnect() {

	char *interface;
	char *ssid;

	interface = get_interface();
	ssid = get_ap();

	if((interface == NULL) || (ssid == NULL)) {
		msg("error: ExecConnect()");
		return;
	}

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_encrypted)) == FALSE)
		do_unencrypted(interface, ssid);		
	else
		do_encrypted(interface, ssid);
	return;	
}

