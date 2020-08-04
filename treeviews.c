#include "disk.h"

/* 
 * In the main window there are two distinct treeviews.
 * Only one at a time can exist.
 * - treeview refers to the (over-)view of all geoms.
 * - treeview1 refers to the view of one specific geom.
 */

GtkWidget *create_treeview() {
	
	/* create a treeview with columns, no rows */
	
	GtkWidget *disk_view = gtk_tree_view_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window), disk_view);	
	cellr = gtk_cell_renderer_text_new();

	g_object_set(cellr, "font", fontsize, NULL);
	g_object_set(cellr, "editable", TRUE, NULL);
	g_object_set(disk_view, "enable-grid-lines", GTK_TREE_VIEW_GRID_LINES_BOTH, NULL);

	/* add columns  */
	int cnt = 0;
	while( (cnt <= COL) && (strlen(column[cnt]) >0 ) ) {
	
		char *col_title = column[cnt];

		GtkTreeViewColumn *col = gtk_tree_view_column_new();
		gtk_tree_view_column_set_title(col, col_title);
		if(cnt == 1 ) /* ident string too long */
			gtk_tree_view_column_set_max_width(col, 220);
		gtk_tree_view_column_set_clickable(col, TRUE);
		gtk_tree_view_column_set_reorderable(col, TRUE);
		gtk_tree_view_column_set_resizable(col, TRUE);
  		gtk_tree_view_append_column(GTK_TREE_VIEW(disk_view), col);
		gtk_tree_view_column_pack_start(col, cellr, TRUE);
		gtk_tree_view_column_add_attribute(col, cellr, "text", (cnt));

		cnt++;
	}	
	/* treestore */
	treestore = gtk_tree_store_new(COL, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, \
									G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, \
									G_TYPE_STRING, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(disk_view), GTK_TREE_MODEL(treestore));
	g_object_unref(treestore); //destroy model automatically with view 
  	gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(disk_view)),
                             GTK_SELECTION_SINGLE);

return disk_view;	
}

GtkWidget *create_treeview1() {

	/* create a treeview with colums for a disk, no rows */
	
	GtkWidget *view = gtk_tree_view_new();
	
	gtk_container_add(GTK_CONTAINER(scrolled_window), view);	
	cell = gtk_cell_renderer_text_new();
	
	g_object_set(cell, "font", fontsize, NULL);
	//g_object_set(cell,"editable", TRUE, NULL);
	//gtk_tree_view_set_enable_search(view, TRUE);
	g_object_set(view, "enable-grid-lines", GTK_TREE_VIEW_GRID_LINES_BOTH, NULL);
	
	int cnt = 0;
	while( (cnt < COLUMNS) && (strlen(columns[cnt]) >0 ) ) {
	
		/* first column */
		char * col_title = columns[cnt];

		GtkTreeViewColumn   * col = gtk_tree_view_column_new();
		gtk_tree_view_column_set_title(col, col_title);
		gtk_tree_view_column_set_clickable(col, TRUE);
		gtk_tree_view_column_set_reorderable(col, TRUE);
		gtk_tree_view_column_set_resizable(col, TRUE);
  		gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

		gtk_tree_view_column_pack_start(col, cell, TRUE);
		gtk_tree_view_column_add_attribute(col, cell, "text", (cnt));

		cnt++;
		}

	/* we always use strings */
	treestore1 = gtk_tree_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 	G_TYPE_STRING, \
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, \
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, \
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 	G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, \
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(view), GTK_TREE_MODEL(treestore1));
	g_object_unref(treestore1); //destroy model automatically with view 
  	gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(view)),
                             GTK_SELECTION_SINGLE);

	g_signal_connect(G_OBJECT (view), "button-press-event", G_CALLBACK(right_clicked), NULL);
return view;
}

int populate_treeview() {
	char buf[30]= "geom disk list";		
	char line[150];
	int size=150;	
	int i = 0;
	
	FILE * fp = popen(buf, "r");
	if ( fp == NULL ) {
		printf("could not execute geom disk list\n");	
	return (0);
	}
	
	GtkTreeIter	parent;	/* geom */
	GtkTreeIter	child;	/* provider */
	
	/* get a line */
	while( fgets(line, sizeof line, fp) ) {
		
		/* remove leading space characters */
		i = 0;
		while(line[i] == ' ')
			i++;
			
		/* Evaluate the entries */
		if (strncmp(&line[i], "Geom name:", 10) == 0){
			i = vari(line, size);	/* where the variable starts */
			gtk_tree_store_append(treestore, &parent, NULL);
			gtk_tree_store_set(treestore, &parent, 0, &line[i], -1);
			child = parent; /* dirty, but usually there is only one provider */
		}
		else if (strncmp(&line[i], "Providers", 9) == 0) {
			/* skip */
		}
		else if (strncmp(&line[i], "Mediasize", 9) == 0) {
			/* only read whats inside the brackets */
			i = vari(line, size);
			while( (line[i] != '(') && (i < size ) )
				i++;
			if(i < size)
				format_string(&line[i]);
			gtk_tree_store_set(treestore, &child, 3, &line[i], -1);
		}
		else if(strncmp(&line[i], "Sectorsize", 10) == 0) {
			i = vari(line, size);
			gtk_tree_store_set(treestore, &child, 4, &line[i], -1);
		}
		else if(strncmp(&line[i], "descr", 5) == 0) {
			i = vari(line, size);
			gtk_tree_store_set(treestore, &child, 1, &line[i], -1);
		}
		else if(strncmp(&line[i], "ident", 5) == 0) {
			i = vari(line, size);
			gtk_tree_store_set(treestore, &child, 2, &line[i], -1);
		}
		else if(strncmp(&line[i], "rotationrate", 12) == 0) {
			i = vari(line, size);
			gtk_tree_store_set(treestore, &child, 6, &line[i], -1);
		}
		else if(strncmp(&line[i], "Mode", 4) == 0) {
			i = vari(line, size);
			gtk_tree_store_set(treestore, &child, 5, &line[i], -1);
		}
		else if(strncmp(&line[i], "fwheads", 7) == 0) {
			i = vari(line, size);
			gtk_tree_store_set(treestore, &child, 8, &line[i], -1);
		}
		else if(strncmp(&line[i], "fwsectors", 9) == 0) {
			i = vari(line, size);
			gtk_tree_store_set(treestore, &child, 7, &line[i], -1);
		}
		else if(strncmp(&line[i], "Stripesize", 10) == 0) {
			i = vari(line, size);
			gtk_tree_store_set(treestore, &child, 9, &line[i], -1);
		}
		else if(strncmp(&line[i], "Stripeoffset", 12) == 0) {
			i = vari(line, size);
			gtk_tree_store_set(treestore, &child, 10, &line[i], -1);
		}	
		else if(line[i] == '2') {
			/* additional providers get a new row */
			gtk_tree_store_append(treestore, &child, &parent);
			i = vari(line, size);
			gtk_tree_store_set(treestore, &child, 0, &line[i], -1);
		}
		memset(line, 0, size);
	}
	
	pclose(fp);
	/* be nice to Users */
	gtk_tree_view_expand_all(GTK_TREE_VIEW(tree));
	gtk_tree_view_set_enable_search (GTK_TREE_VIEW(tree), TRUE);	
	gtk_tree_view_set_enable_tree_lines (GTK_TREE_VIEW(tree), TRUE);
	gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(tree), GTK_TREE_VIEW_GRID_LINES_BOTH);
	
	return (1);
}

int populate_treeview1( char * one_disk) {

	/* 
	 * Add disk and slice information to the treeview.
	 */
	 
	clean_up_pointers();
	char *geom;

	geom = read_disk(one_disk);
	if(geom == NULL) {
		printf("read_disk() failed.\n");
		return (0);	
	}

	treeview_add_rows(geom, one_disk);
	free(geom);

	/* Treat slices as disks in this treeview. */
	char *slice;
	char *brk, *brk1;
	
	if(slices_on_a_disk) {
		slice = strtok_r ( slices_on_a_disk, " ", &brk1);
		while(slice) {

			geom = read_disk(slice);
			if (geom == NULL ) {
				printf("scanning a slice failed.\n");
				return (0);
			}
			
			treeview_add_rows(geom, slice);
			free(geom);

			/* next slice */
			slice = strtok_r( NULL, " ", &brk1);
		}	

		free(slices_on_a_disk);
		slices_on_a_disk= NULL;
	}

	/* be nice to Users */ //XXX: Move this to create treeview?
	gtk_tree_view_expand_all(GTK_TREE_VIEW(tree1));
	gtk_tree_view_set_enable_search (GTK_TREE_VIEW(tree1), TRUE);	
	gtk_tree_view_set_enable_tree_lines (GTK_TREE_VIEW(tree1), TRUE);
	gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(tree1), GTK_TREE_VIEW_GRID_LINES_BOTH);

	return (1);
}

void treeview_add_rows(char *geombuf, char *disk) {

	char *free_space;
	int entries;
	
	GtkTreeIter		parent; /* disk or slice */
	GtkTreeIter		child;	/* partition */
	GtkTreeIter		row_freespace;

	/* disk name */
	gtk_tree_store_append(treestore1, &parent, NULL);
	gtk_tree_store_set(treestore1, &parent, 0, disk, -1);

	if(geombuf[0] == '\0')	/* no geom information */
		return;

	/* replace newline with space characters */
	int len= strlen(geombuf);
	len = len - 1;
	while(len >= 0) {
		if (geombuf[len] == '\n') {	
			geombuf[len] = ' ';
		}
		len--;
	}
	
	g_zero();
	entries = buf_to_struct(geombuf);
	if(entries == 0) {
		printf("error populating tree\n");
		return;
	}

	/*
	* Now we have a structure with all entries.
	* We write them to the treeview.
	*/

	/* parent (disk) entries */
	gtk_tree_store_set(treestore1, &parent, 0, disk, 2, g.scheme, 10, g.state, 17, g.stripeoffset, -1);
	if( (g.first != NULL) && (g.last != NULL) )
		gtk_tree_store_set(treestore1, &parent, 21, g.first, 22, g.last, -1);
	if( g.entries != NULL)
		gtk_tree_store_set(treestore1, &parent, 23, g.entries, -1);
	if( g.modified != NULL)
		gtk_tree_store_set(treestore1, &parent, 24, g.modified, -1);
	if( g.stripesize != NULL)
		gtk_tree_store_set(treestore1, &parent, 15, g.stripesize, -1);

	/* free space before first partition */
	free_space = check_free_space(g.first, g.last, g.sectorsize);
	if (free_space) {
		gtk_tree_store_append(treestore1, &row_freespace, &parent);
		gtk_tree_store_set(treestore1, &row_freespace, 2, "-free-", 3, free_space, -1);
		free(free_space);
	}

	/*
	 *  loop through partitions.
	 */
	 
	while(1) {

		/* free space in between partitions */
		free_space = check_free_space(g.start, g.end_old, g.sectorsize);
		if (free_space != NULL) {
			gtk_tree_store_append(treestore1, &row_freespace, &parent);
			gtk_tree_store_set(treestore1, &row_freespace, 2, "-free-", 3, free_space, -1);
			free(free_space);
		}
		
		gtk_tree_store_append(treestore1, &child, &parent);

		gtk_tree_store_set(treestore1, &child, 1, g.name_capital, 2, g.type, \
				3, g.mediasize, 11, g.start, 12, g.end, 13, g.length, 14, g.offset, \
				15, g.stripesize, 16, g.sectorsize, 17, g.stripeoffset, \
				18, g.efimedia, 19, g.rawuuid, 20, g.rawtype, -1);

		if(g.index != NULL) /* be safe with these */
			gtk_tree_store_set(treestore1, &child, 26, g.index, -1);
		if(g.label != NULL)
			gtk_tree_store_set(treestore1, &child, 4, g.label, -1);
		if(g.attribute!= NULL)
			gtk_tree_store_set(treestore1, &child, 9, g.attribute, -1);
		g.attribute= NULL;
		if( g.mode != NULL)
			gtk_tree_store_set(treestore1, &child, 25, g.mode, -1);
	
		/* file system related entries */	
		if (g.filesystem != NULL) {
			gtk_tree_store_set(treestore1, &child, 5, g.filesystem, -1);
			free(g.filesystem);
		
			if(g.fslabel != NULL) {
				gtk_tree_store_set(treestore1, &child, 6, g.fslabel, -1);
				free(g.fslabel);
			}
			if(g.mountpoint != NULL) {
				gtk_tree_store_set(treestore1, &child, 7, g.mountpoint, -1);
				free(g.mountpoint);
				if(g.capacity != NULL) {
					gtk_tree_store_set(treestore1, &child, 8, g.capacity, -1);
					free(g.capacity);
				}
			}
		}
		
	/*
	 *  We wrote all entries.
	 * Get the next partition.
	 */
	entries = buf_to_struct(g.next_partition);
	if(entries == 0)
		break;
	}
	
	/* free space after last partition */
	free_space = check_free_space(g.last, g.end, g.sectorsize);
	if (free_space) {
		gtk_tree_store_append(treestore1, &row_freespace, &parent);
		gtk_tree_store_set(treestore1, &row_freespace, 2, "-free-", 3, free_space, -1);
		free(free_space);
	}
	/* Consumer information */
	gtk_tree_store_set(treestore1, &parent, 3, g.consumer_mediasize, \
				16, g.consumer_sectorsize, -1);
	if( g.consumer_mode != NULL)
		gtk_tree_store_set(treestore1, &parent, 25, g.consumer_mode, -1);
	// XXX: Sectorsize and stripesize belongs here

	/* empty row at the end for style points */
	gtk_tree_store_append(treestore1, &parent, NULL);
}

char *selected_item(GtkWidget *tview, int column) {
	
	/* get contents of the selected row in a treeview*/
	char *data = NULL;
	if(tview != NULL) {
		GtkTreeSelection *selected = gtk_tree_view_get_selection(GTK_TREE_VIEW (tview));
		if (selected == NULL) {
			printf("please select a row!\n");
			return NULL;
		}
		GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW (tview));
		if (model == NULL) {
			printf("gtk_tree_view_get_model() failed\n");
			return NULL;
		}
		GtkTreeIter iter;
		if (gtk_tree_selection_get_selected(selected, &model, &iter) ) {
			gtk_tree_model_get(model, &iter, column, &data, -1);
			if(data != NULL) 
				return data;
		}
	}
	return NULL;
}

gboolean right_clicked(GtkWidget *btn, GdkEventButton *event, gpointer userdata) {

	/* 
	 * If the user right-clicks on a row,
	 * we may open a popup menu with mount options. 
	 */
	
	char *part;
	char *fs;
	char *mountpoint;
	
	GtkWidget *mount;
	GtkWidget *unmount;
	GtkWidget *rescan;
	
	if( (event->type != GDK_BUTTON_PRESS) || (event->button != 3) ) 
		return FALSE;

	/* Where did he click? */
	GtkTreePath *path;
	GtkTreeViewColumn *column;
	if (!gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(tree1), event->x, event->y, &path, &column, NULL, NULL))
			return FALSE;

	/* find and select the row that was clicked */
	GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree1));
	gtk_tree_selection_unselect_all(selection);
	gtk_tree_selection_select_path(selection, path);
	gtk_tree_path_free(path);

	/* Mount or unmount? */
	fs = selected_item(tree1, 5); /* 5 = file system type */
	part = selected_item(tree1, 1); /* 1 = partition */
	if(fs == NULL)
		return TRUE;
	if(part == NULL)
		return TRUE;
			
	todo = MOUNT;
	GtkWidget *pop_menu = gtk_menu_new();

	if(strncmp(fs, "ntfs", 4) == 0 || strncmp(fs, "exfat", 5) == 0)
		mountpoint = is_mounted_fuse(part);
	else
		mountpoint = is_mounted(part);

	if (mountpoint != NULL) { /* "unmount" */
				
		free(mountpoint);
		unmount = gtk_menu_item_new_with_label ("unmount");
		gtk_menu_shell_append (GTK_MENU_SHELL (pop_menu), unmount);
		g_signal_connect(unmount, "activate", G_CALLBACK(unmountfs), NULL);
	}

	else if (mountpoint == NULL) {
		
		/* XXX: NULL could be an error too! */
		
		if(strncmp(fs, "n/a", 3) == 0) {
		/* "show file system" */		
			rescan = gtk_menu_item_new_with_label(l.mrescan);
			gtk_menu_shell_append (GTK_MENU_SHELL (pop_menu), rescan);
			g_signal_connect(rescan, "activate", G_CALLBACK(fsscan), NULL);
		}
		else {
			/* "mount" "mointpoints" */
			mount = gtk_menu_item_new_with_label("mount");
			gtk_menu_shell_append (GTK_MENU_SHELL (pop_menu), mount);
		
			GtkWidget *mount_sub = gtk_menu_new();
			gtk_menu_item_set_submenu (GTK_MENU_ITEM (mount), mount_sub);

			/* /mnt */
			GtkWidget * mount_mnt = gtk_menu_item_new_with_label ("/mnt");
			gtk_menu_shell_append (GTK_MENU_SHELL (mount_sub), mount_mnt);

			/* /media */
			GtkWidget * mount_media = gtk_menu_item_new_with_label ("/media");
			gtk_menu_shell_append (GTK_MENU_SHELL (mount_sub), mount_media);

			/* other */
			GtkWidget * mount_other = gtk_menu_item_new_with_label (l.mother);
			gtk_menu_shell_append (GTK_MENU_SHELL (mount_sub), mount_other);
			
			g_signal_connect(mount_mnt, "activate", G_CALLBACK(mountfs), NULL);
			g_signal_connect(mount_media, "activate", G_CALLBACK(mountfs), NULL);
			g_signal_connect(mount_other, "activate", G_CALLBACK(mountfs), NULL);
		}
	}

	free(part);
	free(fs);
	gtk_widget_show_all(pop_menu);
	gtk_menu_popup_at_pointer( GTK_MENU (pop_menu), NULL);
	return TRUE; /* right click finished */
}

int buf_to_struct(char *buf) {

/*
 * Recieve a buffer with geom information.
 * Read it and set the pointers of struct geom_info.
 * Basically information for one row (partition).
 */
	
	if(buf == NULL)
		return(0);
	
	/* initialize most entries to zero */
g.name = NULL;
g.name_capital = NULL;
g.mediasize = NULL;
g.type = NULL;
g.start = NULL;
if(g.end != NULL)
	g.end_old = g.end;
else
	g.end_old = NULL;
/* let these survive as they belong to the parent(the disk) */
//g->end = NULL; 
//g->sectorsize = NULL;
//g.first = NULL;
//g->last = NULL;
g.state = NULL;
g.entries = NULL;
g.scheme = NULL;
g.modified = NULL;
g.stripesize = NULL;
g.stripeoffset = NULL;
g.mode = NULL;
g.efimedia = NULL;
g.rawuuid = NULL;
g.rawtype = NULL;
g.length = NULL;
g.offset = NULL;
g.label = NULL;
g.index = NULL;
g.filesystem = NULL;
g.attribute = NULL;
g.mountpoint = NULL;
g.capacity = NULL;
g.fslabel = NULL;

	/* parse buffer information */
	char *ptr;
	char *sep;
	char *next;	
	int entries;
	
	entries=0;
	sep = " ";
	next = strtok_r(buf, sep, &ptr);
	next = strtok_r(NULL, sep, &ptr);
	
	while(next != NULL) {
		
		entries++;
		if ( (strcmp(next, "name:") )== 0) {
			g.name = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "state:") )== 0) {
			g.state = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "fwheads:") )== 0) {
		/* skip */
		}
		else if ( (strcmp(next, "fwsectors:") )== 0) {
		/* skip */
		}
		else if ( (strcmp(next, "entries:") )== 0) {
			g.entries = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "scheme:") )== 0) {
			g.scheme = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "modified:") )== 0) {
			g.modified = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "Stripeoffset:") )== 0) {
			g.stripeoffset = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "Stripesize:") )== 0) {
			g.stripesize = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "Mode:") )== 0) {
			g.mode = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "rawuuid:") )== 0) {
			g.rawuuid = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "rawtype:") )== 0) {
			g.rawtype = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "length:") )== 0) {
			g.length = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "index:") )== 0) {
			g.index = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "first:") )== 0) {
			g.first = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "last:") )== 0) {
			g.last = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "offset:") )== 0) {
			g.offset = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "label:") )== 0) {
			g.label = strtok_r(NULL, sep, &ptr);
			if(strncmp(g.label, "(null)", 6) == 0)
				g.label = NULL;
		}
		else if ( (strcmp(next, "efimedia:") )== 0) {
			g.efimedia = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "last:") )== 0) {
			g.last = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "attrib:") )== 0) {
			g.attribute = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "Name:") )== 0) {
			g.name_capital = strtok_r(NULL, sep, &ptr); 
		}
		else if ( (strcmp(next, "Mediasize:") )== 0) {
			next = strtok_r(NULL, sep, &ptr);
			g.mediasize = strtok_r(NULL, sep, &ptr);
			format_string(g.mediasize);
		}
		else if ( (strcmp(next, "type:") )== 0) {
			g.type = strtok_r(NULL, sep, &ptr);
			if(strcmp(g.type, "freebsd") == 0) {
				all_slices = add_to_list(g.name_capital, all_slices);
				slices_on_a_disk =add_to_list(g.name_capital, slices_on_a_disk);
			}
		}
		else if ( (strcmp(next, "Sectorsize:") )== 0) {
			g.sectorsize = strtok_r(NULL, sep, &ptr);
		}
		else if ( (strcmp(next, "end:") )== 0) {
			g.end = strtok_r(NULL, sep, &ptr);
		}
		else if(strncmp(next, "start:", 6) == 0) {
			g.start = strtok_r(NULL, sep, &ptr);
			/* 
			 * start is the last entry of a provider(partition).
			 * We read Consumer information and return.
			 */
			 
			g.next_partition = g.start + strlen(g.start) +1 ;
			if(strncmp(g.next_partition, "Consumer", 8) == 0) {
				next = strtok_r(NULL, sep, &ptr);
				while(next != NULL) {
					if(strncmp(next, "Consumers:", 9) == 0) {
						/* skip */
					}
					else if(strncmp(next, "Name:", 6) == 0) {
						/* skip */
					}
					else if ( (strncmp(next, "Mediasize:", 10) )== 0) {
						next = strtok_r(NULL, sep, &ptr);
						g.consumer_mediasize = strtok_r(NULL, sep, &ptr);
						format_string(g.consumer_mediasize);
					}
					else if(strncmp(next, "Sectorsize:", 11) == 0)
						g.consumer_sectorsize = strtok_r(NULL, sep, &ptr);
					else if(strncmp(next, "Mode:", 5) == 0)
						g.consumer_mode = strtok_r(NULL, sep, &ptr);
					next = strtok_r(NULL, sep, &ptr);
				}
				g.next_partition = NULL; /* end of buffer */
			}

			break;
		}
		next = strtok_r(NULL, sep, &ptr);
	}
	
	if(entries == 0)
		return(0);

	/* 
	 * check file system related entries
	 */
	g.filesystem = what_file_system(g.name_capital);
	if(g.filesystem == NULL || strncmp(g.filesystem, "n/a", 3) == 0)
		return(entries);
	
	/* file system label */
	if(strncmp(g.type, "ntfs", 4) == 0 || strncmp(g.type, "exfat", 5) == 0) {
		/*fuse label */
	}
	else
		g.fslabel = get_label(g.name_capital, g.filesystem);

	/* mountpoint */
	if(strncmp(g.type, "ntfs", 4) == 0 || strncmp(g.type, "exfat", 5) == 0)
		g.mountpoint = is_mounted_fuse(g.name_capital);
	else
		g.mountpoint = is_mounted(g.name_capital);

	/* capacity */
	if(g.mountpoint != NULL && strncmp(g.mountpoint, "--", 2) != 0)
			g.capacity = get_capacity(g.mountpoint);

	return(entries);
}

void g_zero() {
	
/* initialize all entries to zero */
g.name = NULL;
g.name_capital = NULL;
g.mediasize = NULL;
g.sectorsize = NULL;
g.type = NULL;
g.start = NULL;
g.end = NULL;
g.end_old = NULL;
g.state = NULL;
g.entries = NULL;
g.scheme = NULL;
g.first = NULL;
g.last = NULL;
g.modified = NULL;
g.stripesize = NULL;
g.stripeoffset = NULL;
g.mode = NULL;
g.efimedia = NULL;
g.rawuuid = NULL;
g.rawtype = NULL;
g.length = NULL;
g.offset = NULL;
g.label = NULL;
g.index = NULL;
g.filesystem = NULL;
g.attribute = NULL;
g.mountpoint = NULL;	
g.capacity = NULL;
g.fslabel = NULL;
g.next_partition = NULL;
g.consumer_mediasize = NULL;
g.consumer_mode = NULL;
g.consumer_sectorsize = NULL;

}

char *get_capacity(char *mountpoint) {
	
	if(mountpoint == NULL)
		return NULL;

	char cmd[CMDSIZE];
	snprintf(cmd, CMDSIZE, "df %s | awk '{print $5}' | tail -n 1", mountpoint);
	return (command(cmd));
}

char *get_label(char *partition, char *filesystem) {
		
	if(partition == NULL)
		return NULL;

	char cmd[CMDSIZE];
	char *label;
	int len;

	snprintf(cmd, CMDSIZE, "glabel status | grep %s | awk '/%s/{print $1}'", partition, filesystem);
	label = command(cmd);
	if(label == NULL || label[0] == '\n' || label[0] == '\0')
		return NULL;
	
	/* format output */
	len = strlen(filesystem);
	if(strncmp(&label[len], "id", 2) == 0 ) {
		free(label);
		return NULL;
	}
	
	int i=0;
	int max = strlen(label);
	
	while( ((len+i) < max) && label[len+i] != '/')
		i++;
	return (&label[len+i+1]);
	
	printf("label:%s\n", label);
	return label;
		
		
}
