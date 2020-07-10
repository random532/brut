#include "disk.h"

int is_mounted(char *part) {
	
	if (part == NULL)
		return 2; /* should never happen */
	
	/* execute mount w/o arguments */
	char buf[100];
	memset(buf, 0, 100);
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
		path = malloc(20);
		memset(path, 0, 10);
		mlen = 4;
		strncpy(path, "/mnt", mlen);
	}
	else if(strncmp(label, "/media", 7) == 0) {
		path = malloc(20);
		memset(path, 0, 10);
		mlen = 6;
		strncpy(path, "/media", mlen);
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
		int x = 50;
		cmd = malloc(plen + mlen + x + 1);
		memset(cmd, 0, plen + mlen + x + 1);
	
	/* file system type */
	int error = 0;
	if(strncmp(fs, "ufs", 3) == 0) 
		snprintf(cmd, plen+mlen+x, "mount /dev/%s %s", part, path);
	else if(strncmp(fs, "msdosfs", 7) == 0) 
		snprintf(cmd, plen+mlen+x, "mount -t msdosfs /dev/%s %s", part, path);
	else if(strncmp(fs, "ntfs", 5) == 0) {
		
		/* see if ntfs-3g is installed */
		if (!command_exist("/bin/ntfs-3g")) {
			msg("To mount ntfs file systems, please install this package: ntfs-3g. Also kldload fuse.");
			error = 1;
		}
		snprintf(cmd, plen+mlen+x, "ntfs-3g /dev/%s %s", part, path);
	}
	else if(strncmp(fs, "cd9660", 6) == 0)
		snprintf(cmd, plen+mlen+x, "mount_cd9660 /dev/%s %s", part, path);
	else if(strncmp(fs, "ext2fs", 5) == 0) {
		if (!command_exist("/bin/fuse-ext2")) {
			msg("To mount ext2 file systems, please install this package: fusefs-ext2. Also kldload fuse.");
			error = 1;
		}
		snprintf(cmd, plen+mlen+x, "fuse-ext2 /dev/%s %s", part, path);
	}
	else if(strncmp(fs, "exfat", 5) == 0) {
		if (!command_exist("/sbin/mount.exfat")) {
			msg("To mount exfat file systems, please build this package via ports: sysutils/fusefs-exfat. Also kldload fuse(?).");
			error = 1;
		}
		snprintf(cmd, plen+mlen+x, "mount.exfat /dev/%s %s", part, path);
	}
	else if(strncmp(fs, "geli", 4) == 0)
		snprintf(cmd, plen+mlen+x, "mount /dev/%s %s", part, path);

	else if(strncmp(fs, "zfs", 3) == 0)
		snprintf(cmd, plen+mlen+x, "mount -t zfs /dev/%s %s", part, path);

	else if(strncmp(fs, "n/a", 3) == 0) {
		/* no read write permission on partition */
		msg("no read-write permission on partition.");
		error = 1;
	}
	else { /* undocumented file system */
		msg("undocumented file system.");
		error = 1;
	}
	free(path);
	
	if(!error) {
		if(!root() )  {
			if(vfs_usermount() == 1) {
				if (execute_cmd(cmd, 0) == 0) {
					free(cmd);
					msg(l.mdone);
					return;
				}
			}
			/* try sudo */
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
}

void unmountfs() {
	/* unmount */
	int success=0;
	char *part = selected_item(tree1, 1); /* partition */
	if(part == NULL)
		return;
		
	int len = strlen(part);
	char *cmd = malloc (len + 20);
	memset(cmd, 0, len+20);
	snprintf(cmd, len+20, "umount /dev/%s", part);
	if(!root()) {
		if( (vfs_usermount() == 0) ) { 
			if( execute_cmd(cmd, 0) == 0) {
				msg(l.mdone);
				free(cmd);
				return;
			}
		}
		/* try sudo */
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

int vfs_usermount() {
	
	/* checks wether regular users are allowed to mount */
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
