#include "disk.h"

char *is_mounted(char *part) {

	/*
	 * Execute mount w/o arguments.
	 * Return Mountpoint or NULL.
	 */
		
	if (part == NULL)
		return NULL;

	char buf[100];
	memset(buf, 0, 100);
	
	int len = strlen(part);
	sprintf(buf, "mount | awk '/\\/");
	strcat(buf, part);
	strcat(buf, "/{printf $3}'");
	
	FILE *fp = popen(buf, "r");
	if (fp == NULL) {
		msg("fopen failed");
		return NULL;
	}
	fgets(buf, sizeof buf, fp);
	pclose(fp);
		if( strncmp(buf, "/", 1) == 0 ) {
			len= strlen(buf);
			char *mountpoint = malloc(len+5);
			if( mountpoint != NULL)
				strncpy(mountpoint, buf, len+1);
			return mountpoint;
		}
		else
			return NULL;
}

char *is_mounted_fuse(char *partition) {

	/*
	 * Just check whether there is at least one fuse mount.
	 * If so, return "--", else return NULL.
	 */

	char buf[150];
	char *empty;
	char cmd[]= "mount | awk '/fuse/{print $3}'";
	char *mountpoint;
	int len;
	
	if (partition == NULL)
		return NULL;

	memset(buf, 0, sizeof buf);
	mountpoint = NULL;
	len = 0;

	FILE *fp = popen(cmd, "r");
	if (fp == NULL) {
		msg("fopen failed");
		return NULL;
	}
	
	fgets(buf, sizeof buf, fp);
	pclose(fp);

	if(strncmp(buf, "/", 1) == 0) {
			mountpoint = malloc(10);
			strcpy(mountpoint, "--");
			return mountpoint;
	}
	else
		return NULL;
}

char *do_mountpoint(char *mp) {


	const gchar *label = gtk_menu_item_get_label(gmenu); //XXX: free(label) ??

	/* mountpoint */
	if(strncmp(label, "/mnt", 4) == 0) {
		mp = malloc(10);
		strncpy(mp, "/mnt", 4);
		return mp;
	}
	else if(strncmp(label, "/media", 6) == 0) {
		mp = malloc(10);
		strncpy(mp, "/media", 6);
		return mp;
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
			mp = gtk_file_chooser_get_filename(chooser);
			gtk_widget_destroy(dialog);
			return mp;
		}
		else {
			gtk_widget_destroy(dialog);
			return NULL;
		}
	}
}

void mountfs(GtkMenuItem *gmenu, gpointer gp) {
	
	/*
	 * Mount a partition.
	 */
		
	char *part;	/* Partition */
	char *fs;	/* File system */
	char *path;	/* Mount path */
	char *cmd;	/* Mount command */
	int success = 0;
	int plen;	/* Partition length */
	int mlen = 0;	/* Mount path length (?) */

	part = selected_item(tree1, POS_PART);
	plen = strlen(part);
	fs = selected_item(tree1, POS_FS);
	
	if((part == NULL) || (fs == NULL))
		return;

	path = do_mountpoint(path);
	if(path == NULL) {
		msg("No mount point selected.");
		return;
	}
	mlen = strlen(path);

	/* 
	 * We have all we need.
	 * So build the mount command.
	 */
	 
	int x = 50;
	cmd = malloc(plen + mlen + x + 1);
	memset(cmd, 0, plen + mlen + x + 1);

	int error = 0;
	if(strncmp(fs, "ufs", 3) == 0) 
		snprintf(cmd, plen+mlen+x, "mount /dev/%s %s", part, path);
	else if(strncmp(fs, "msdosfs", 7) == 0) 
		snprintf(cmd, plen+mlen+x, "mount -t msdosfs /dev/%s %s", part, path);
	else if(strncmp(fs, "ntfs", 4) == 0) {
		
		/* see if ntfs-3g is installed. XXX: Never reached. */
		if (!command_exist("/bin/ntfs-3g")) {
			msg("To mount ntfs file systems, please install this package: fusefs-ntfs. Also kldload fuse.");
			error = 1;
		}
		snprintf(cmd, plen+mlen+x, "ntfs-3g /dev/%s %s", part, path);
	}
	else if(strncmp(fs, "cd9660", 6) == 0)
		snprintf(cmd, plen+mlen+x, "mount_cd9660 /dev/%s %s", part, path);
	else if(strncmp(fs, "ext2fs", 6) == 0) {
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

	if(error) {
		free(path);
		free(cmd);
		return;
	}

	/*
	 *  Execute the mount command.
	 */
	 
	if(root()) {
		submit(cmd, 1);
		free(path);
		free(cmd);
	}
	else if(vfs_usermount() == 1 && access(path, W_OK) == 0 && execute_cmd(cmd, 0) == 0) {
		free(path);
		free(cmd);
		msg(l.mdone);
	}
	else if(pw_needed()) {
		window_pw(cmd);
		free(path);
	}
	else {
		/* no password needed */
		cmd = sudo(cmd, "empty", 0);
		if(cmd == NULL) {
			printf("restart recommended..\n");
			return;
		}
		submit(cmd, 1);
		free(path);
	}

	on_toplevel_changed(); 		/* redraw everything */
}

void unmountfs() {
	
	char *m;	 /* mountpoint */
	char *cmd;
	int len;
	int success=0;

	m = selected_item(tree1, POS_MOUNTP);
	if(m == NULL)
		return;
	
	/* Build the unmount command. */	
	len = strlen(m);
	cmd = malloc (len + 20);
	memset(cmd, 0, len+20);
	snprintf(cmd, len+20, "umount %s", m);
	free(m);

	/* Execute the unmount command. */
	
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
	on_toplevel_changed(); 		/* redraw everything */
}

int vfs_usermount() {
	
	/* 
	 * Checks wether regular users are allowed to mount.
	 * There is no need to include /sys/sysctl.h
	 */

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
