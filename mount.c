#include "disk.h"

int is_mounted(char *part) {
	
	/* execute mount */
	/* see if we hit our partition */
	char buf[100];
	memset(buf, 0, 100);
	if (part == NULL)
		return 2; /* should never happen */
	int len = strlen(part);
	FILE *fp = popen("mount", "r");
	if (fp == NULL) {
		msg("fopen failed");
		return 2;
	}
	while( fgets(buf, sizeof buf, fp)) {	
		if (strncmp(part, &buf[5], len) == 0) { /* skip "/dev/" */
			/* mounted */
			return 1;
		}
		memset(buf, 0, 100);
	}
	pclose(fp);
	return 0; /* no match, not mounted */
}

void mountfs(GtkMenuItem *gmenu, gpointer gp) {
	/* mount a partition */
		
	/* check permissions */
	if(geteuid() != 0) {
		if( nfs_usermount() != 1) {
			msg(l.no_root);
			return;
		}
	}
	
	/* setup */
	const gchar *label = gtk_menu_item_get_label(gmenu);
	char * part = selected_item(tree1, 1);	/* partition */
	int plen = strlen(part); /* is this really 0 terminated? */
	int mlen = 0;
	char * fs = selected_item(tree1, 4); 	/* file system type */
	char *path;
	char *cmd;
	int success = 0;
	
	if( (part == NULL) || (fs == NULL) || (label == NULL) )
		return;
	
	/* mountpoint */
	if(strncmp(label, "/mnt", 4) == 0) {
		path = malloc(10);
		mlen = 4;
		strncpy(path, "/mnt", 5);
	}
	else if(strncmp(label, "/media", 7) == 0) {
		path = malloc(10);
		mlen = 6;
		strncpy(path, "/media", 7);
	}
	else {
		/* other path */
		/* file chooser dialog */
		GtkWidget * dialog;
		GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
		dialog = gtk_file_chooser_dialog_new("Mointpoint", GTK_WINDOW (window), action, "Cancel", GTK_RESPONSE_CANCEL, "Mount", GTK_RESPONSE_ACCEPT, NULL);
		gint res = gtk_dialog_run(GTK_DIALOG (dialog));
		if(res == GTK_RESPONSE_ACCEPT) {
			GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
			path = gtk_file_chooser_get_filename(chooser);
			mlen = strlen(path);
			gtk_widget_destroy(dialog);
		}
		else {
			gtk_widget_destroy(dialog);
			return;
		}
	}
	
	/* file system type */
	if(strncmp(fs, "ufs", 3) == 0) {
		cmd = malloc(plen + mlen + 20);
		memset(cmd, 0, plen + mlen + 20);
		snprintf(cmd, plen+mlen+30, "mount /dev/%s %s", part, path);
	}
	else if(strncmp(fs, "msdos", 5) == 0) {
		cmd = malloc(plen + mlen + 30);
		memset(cmd, 0, plen + mlen + 30);
		snprintf(cmd, plen+mlen+30, "mount -t msdosfs /dev/%s %s", part, path);
	}
	else if(strncmp(fs, "ntfs", 5) == 0) {
		
		/* see if ntfs-3g is installed */
		if (!command_exist("/bin/ntfs-3g")) {
			msg("To mount ntfs file systems, please install this package: ntfs-3g. Also kldload fuse.");
			free(cmd);
			free(path);
			return;
		}
		cmd = malloc(plen + mlen + 30);
		memset(cmd, 0, plen + mlen + 30);
		snprintf(cmd, plen+mlen+30, "ntfs-3g /dev/%s %s", part, path);
	}
	else if(strncmp(fs, "n/a", 3) == 0) {
		/* file system is unknown to us */
		/* we have usermount */
		usermount(cmd, path);
		free(path);
		free(cmd);
		return;
	}
	
	if(confirm==1)
		ask(cmd);
	else {
		success = execute_cmd(cmd, 0);
		if(success == 0)
			msg(l.mdone);
		else
			msg(l.merror);
	}
	free(cmd);
	free(path);
}

void unmountfs() {
	/* unmount a partition */
	char *part = selected_item(tree1, 1); /* get selected partition */
	if(part != NULL) {
		int len = strlen(part);
		char *cmd = malloc (len + 20);
		memset(cmd, 0, len+20);
		snprintf(cmd, len+20, "umount /dev/%s", part);
		if(confirm==1)
			ask(cmd);
		else {
			int success = execute_cmd(cmd, 0);
			if(success == 0)
				msg(l.mdone);
			else
				msg(l.merror);
		}
		free(cmd);
	}
}

int nfs_usermount() {
	
	/* whether regular users are allowed to mount */
	int usermnt = 0;
	char buf[30];
	memset(buf, 0, 30);
	FILE * fp = popen("sysctl -n vfs.usermount", "r");
	if (fp == NULL) {
		msg("fopen failed");
		return 2;
	}
	fgets(buf, sizeof buf, fp);
	if (strncmp("1", buf, 1) == 0) 
		usermnt = 1;
	pclose(fp);
	return usermnt;
}

int usermount(char *cmd, char *path) {
	msg("Usermount not implemented yet.");
	return 1;
}
