#include "disk.h"

char *is_mounted(char *part) {
	/* execute mount w/o arguments */
	/* return Mountpoint or NULL */
		
	if (part == NULL)
		return NULL;

	char buf[100];
	memset(buf, 0, 100);
	
	int len = strlen(part);
	sprintf(buf, "mount | awk '/");
	strcat( buf, part);
	strcat( buf, "/{printf $3}'");
	
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
 * This is surely not how things should
 * be done.
 */
	
	char buf[150];
	int bufsize = 150;
	char cmd[]= "mount | awk '/fuse/{print $3}'";
	int len=0;
	int result = 0;
	char *mountpoint = NULL;

	if (partition == NULL)
		return NULL;

	if(!root() && pw_needed() == 1) {
		printf("Note: fuse mountpoints unknown. Need higher privileges for that.\n");
		char *empty = malloc(10);
		strcpy(empty, "--");
		return empty;
	}

	memset(buf, 0, bufsize);

	/* iterate through all mounted fuse file systems */
	
	FILE *fp = popen(cmd, "r");
	if (fp == NULL) {
		msg("fopen failed");
		return NULL;
	}
	while( fgets(buf, sizeof buf, fp)) {

		len = strlen(buf);
		if(len == 0)
			break;
		buf[len-1] = '\0';
		
		/* compare the volume information with device */
		result = volume_cmp(partition, buf);
			
			if(result == 0) {
				mountpoint = malloc(len +1);
				strncpy(mountpoint, buf, len);
			}
			else if(result == -1) {
				/* abort */
				mountpoint = malloc(10);
				strcpy(mountpoint, "--");
				break;
			}
	}
	
	pclose(fp);
	return mountpoint;
}

void mountfs(GtkMenuItem *gmenu, gpointer gp) {
	
	/*
	 * Mount a partition.
	 */
		
	char *part;	/* Partition */
	char *fs;	/* File system */
	char *path;	/* Mount path */
	char *cmd;	/* Mount command */
	const gchar *label; /* Users choice of mountpoint */
	int success = 0;
	int plen;	/* Partition length */
	int mlen = 0;	/* Mount path length (?) */
	
	label = gtk_menu_item_get_label(gmenu);
	part = selected_item(tree1, POS_PART);
	plen = strlen(part);
	fs = selected_item(tree1, POS_FS);
	
	if( (part == NULL) || (fs == NULL) || (label == NULL) )
		return;
	
	/* mountpoint */
	path = malloc(10);
	memset(path, 0, 10);
	if( strncmp(label, "/mnt", 4) == 0) 
		strncpy(path, label, 4);
	else if( strncmp(label, "/media", 6) == 0)  
		strncpy(path, label, 6);
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
		
		/* see if ntfs-3g is installed */
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

int volume_cmp(char *partition, char *mpoint) {
	
	/* 
	 * Compare Volume information of the mountpoint
	 * with the information of the device.
	 * If they match, they are identical.
	 */
	
	char *filename;
	char *tmpfile1 = "/tmp/file1";
	char *tmpfile2 = "/tmp/file2";
	char cmd1[CMDSIZE];
	char cmd2[CMDSIZE];
	char buf1[CMDSIZE];
	char buf2[CMDSIZE];
	
	int mlen;
	int match=1;

	if(mpoint == NULL || partition == NULL)
		return -1;

	memset(buf1, 0, CMDSIZE);
	memset(buf2, 0, CMDSIZE);
	
	/* first read the info from mountpoint */
	mlen = strlen(mpoint);
	filename = malloc(50+mlen);
	if(filename == NULL)
		return -1;

	sprintf(filename, "%s/System Volume Information/IndexerVolumeGuid", mpoint);
/*	if(access(filename, R_OK) != 0) {
		printf("%s: %s\n", filename,  strerror(errno));
		free(filename);
		return 1;
	}
*/

	snprintf(cmd1, CMDSIZE, "sudo -S cat %s/System\\ Volume\\ Information/IndexerVolumeGuid >%s", mpoint, tmpfile1);
	if(execute_cmd(cmd1, 0) != 0) {
		printf("No System Volume Information on: %s -- Aborting.\n", mpoint);
		free(filename);
		return -1;
	}

	/* second read device */
	snprintf(cmd2, CMDSIZE, "sudo -S ntfscat -fq /dev/%s System\\ Volume\\ Information/IndexerVolumeGuid | tail -n 1 >%s ", partition, tmpfile2);
	if(execute_cmd(cmd2, 0) != 0) {
		printf("No System Volume Information on device: /dev/%s -- Aborting.\n", partition);
		free(filename);
		return -1;
	}

	if(execute_cmd("diff /tmp/file1 /tmp/file2", 0) == 0)
		match = 0;
	//else
	//	printf("/dev/%s is not mounted on: %s\n", partition, mpoint);

	free(filename);
	execute_cmd("sudo -S rm /tmp/file1 /tmp/file2", 0);
	
	return match;
}
