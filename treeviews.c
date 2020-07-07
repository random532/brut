/* treeview functions */
#include "disk.h"

GtkWidget *disk_treeview() {
	
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

GtkWidget *make_treeview() {

	/* create a treeview with colums for a disk */
	
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
	treestore1 = gtk_tree_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 	G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 	G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(view), GTK_TREE_MODEL(treestore1));
	g_object_unref(treestore1); //destroy model automatically with view 
  	gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(view)),
                             GTK_SELECTION_SINGLE);

	g_signal_connect(G_OBJECT (view), "button-press-event", G_CALLBACK(view_clicked), NULL);
return view;
}

int fill_treeview() {
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

int fill_treeview1( char * one_disk) {

	/* clean up */
	clean_up_pointers();

	/*  */
	char *geom_info;
	char *geom_slice;

	/* call geom with diskname */
	geom_info = read_disk(one_disk);
	if (geom_info == NULL ) {
		printf("read_disk() failed.\n");
		return 0;	
	}
		
	/* fill in the tree	*/
	fill_tree(geom_info, one_disk);
	free(geom_info);
	
	/* we may have detected some slices */
	char *slice, *brk, *brk1;

	if(slices_on_a_disk != NULL) {
		slice = strtok_r ( slices_on_a_disk, " ", &brk1);
		while( slice != NULL ) {
	
			/* call geom with diskname */
			geom_slice = read_disk(slice);
			if (geom_slice == NULL ) {
				printf("no slice found\n");
				return 0;	
				}

			/* fill in the tree	*/
			fill_tree(geom_slice, slice);
			free(geom_slice);

			/* scan for next slice */
			slice = strtok_r( NULL, " ", &brk1);
		}			

		free(slices_on_a_disk);
		slices_on_a_disk= NULL;
	}

	/* be nice to Users */
	gtk_tree_view_expand_all(GTK_TREE_VIEW(tree1));
	gtk_tree_view_set_enable_search (GTK_TREE_VIEW(tree1), TRUE);	
	gtk_tree_view_set_enable_tree_lines (GTK_TREE_VIEW(tree1), TRUE);
	gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(tree1), GTK_TREE_VIEW_GRID_LINES_BOTH);

	return 1;
}

void fill_tree(char *geombuf, char *disk) {

char *ptr;

/* 26 pointer */
char *pname=	NULL;
char *pname_capital=NULL;
char *pmediasize=NULL;
char *psectorsize=NULL;
char *ptype=	NULL;
char *pstart=	NULL;
char *pend=	NULL;
char *pend_old= NULL;
char *pstate=	NULL;
char *pentries=	NULL;
char *pscheme=	NULL;
char *pfirst=	NULL;
char *plast=	NULL;
char *pmodified= NULL;
char *pstripesize=NULL;
char *pstripeoffset=NULL;
char *pmode=	NULL;
char *pefimedia=NULL;
char *prawuuid=	NULL;
char *prawtype=	NULL;
char *plength=	NULL;
char *poffset=	NULL;
char *plabel=	NULL;
char *pindex=	NULL;
char *pfilesystem=NULL;
char *pattribute=NULL;


int len = strlen(geombuf);
char *free_space;

	/* strtok cannot handle 0x0A */
int i=0;
	while(i < len) {
		if (geombuf[i] == '\n') {	
			geombuf[i] = ' ';
		}
		i++;
	}

	GtkTreeIter		parent; /* disk or slice */
	GtkTreeIter		child;	/* partition */
	GtkTreeIter		row_freespace;

	/* first column is disk name */
	gtk_tree_store_append(treestore1, &parent, NULL);
	gtk_tree_store_set(treestore1, &parent, 0, disk, -1);

	if(geombuf[0] == '\0')	/* no geom information available */
		return;

	/* parse the geom buffer */
	/* if we have a match */
	/* write it to matching char * variable */
	
char *sep = " !"; //XXX: why !
char *next = strtok_r(geombuf, sep, &ptr);

	next = strtok_r(NULL, sep, &ptr);
	while (next != NULL) {
		
		if ( (strcmp(next, "name:") )== 0) {
			pname = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "state:") )== 0) {
			pstate = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "fwheads:") )== 0) {
		/* skip */
			}
		else if ( (strcmp(next, "fwsectors:") )== 0) {
		/* skip */
		}
		else if ( (strcmp(next, "entries:") )== 0) {
			pentries = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "scheme:") )== 0) {
			pscheme = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "modified:") )== 0) {
			pmodified = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "Stripeoffset:") )== 0) {
			pstripeoffset = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "Stripesize:") )== 0) {
			pstripesize = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "Mode:") )== 0) {
			pmode = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "rawuuid:") )== 0) {
			prawuuid = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "rawtype:") )== 0) {
			prawtype = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "length:") )== 0) {
			plength = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "index:") )== 0) {
			pindex = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "first:") )== 0) {
			pfirst = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "last:") )== 0) {
			plast = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "offset:") )== 0) {
			poffset = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "label:") )== 0) {
			plabel = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "efimedia:") )== 0) {
			pefimedia = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "last:") )== 0) {
			plast = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "attrib:") )== 0) {
			pattribute = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "Name:") )== 0) {
			pname_capital = strtok_r(NULL, sep, &ptr); 
			}
		else if ( (strcmp(next, "Mediasize:") )== 0) {
			next = strtok_r(NULL, sep, &ptr);
			pmediasize = strtok_r(NULL, sep, &ptr);
			format_string(pmediasize);
			}
		else if ( (strcmp(next, "type:") )== 0) {
			ptype = strtok_r(NULL, sep, &ptr);
			if(strcmp(ptype, "freebsd") == 0) {
				list_of_slices = add_to_list(pname_capital, list_of_slices);
				slices_on_a_disk =add_to_list(pname_capital, slices_on_a_disk);
					/* a slice */
				}
			}
		else if ( (strcmp(next, "Sectorsize:") )== 0) {
			psectorsize = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "end:") )== 0) {
			next = strtok_r(NULL, sep, &ptr);
			pend_old = pend;
			pend = next;
			}
		else if ( (strcmp(next, "start:") )== 0) {
			pstart = strtok_r(NULL, sep, &ptr);

			/* start is the last entry of a provider(partition) */
			/* so it is a good place to do some work */

			/* tell user about free space in between partitions */
			free_space = check_free_space(pstart, pend_old, psectorsize);
			if (free_space != NULL) {
				gtk_tree_store_append(treestore1, &row_freespace, &parent);
				gtk_tree_store_set(treestore1, &row_freespace, 3, "-free-", 4, free_space, -1);
				free(free_space);
				}
			
			/* XXX: do we still need this?*/
			/* add partition to all_partitions */
			all_partitions = add_to_list(pname_capital, all_partitions);
			gtk_tree_store_append(treestore1, &child, &parent);
	
			/* what file system? */
			pfilesystem = what_file_system(pname_capital);
			if (pfilesystem != NULL) {
				gtk_tree_store_set(treestore1, &child, 4, pfilesystem, -1);
				free(pfilesystem);
			}
			
			/* put the p.. variables in the tree */
			gtk_tree_store_set(treestore1, &child, 1, pname_capital, 2, ptype, \
								3, pmediasize, 9, pstart, 10, pend, 11, plength, \
								12, poffset, 13, pstripesize, 14, psectorsize, \
								15, pstripeoffset, 16, pefimedia, 17, prawuuid, \
								18, prawtype, -1);


			if(pindex != NULL) /* be safe with these */
				gtk_tree_store_set(treestore1, &child, 8, pindex, -1);
			if(plabel != NULL)
				gtk_tree_store_set(treestore1, &child, 5, plabel, -1);
			if(pattribute!= NULL)
				gtk_tree_store_set(treestore1, &child, 6, pattribute, -1);
			pattribute= NULL;
			if( pmode != NULL)
				gtk_tree_store_set(treestore1, &child, 23, pmode, -1);
		}

		next = strtok_r(NULL, sep, &ptr);
	}

	/* inform user about free space after last partition */
	free_space = check_free_space(plast, pend, psectorsize);
		if (free_space != NULL) {
			gtk_tree_store_append(treestore1, &row_freespace, &parent);
			gtk_tree_store_set(treestore1, &row_freespace, 2, "-free-", 3, free_space, -1);
			free(free_space);
			}

	/* parent or disk entries */
	gtk_tree_store_set(treestore1, &parent, 0, disk, 2, pscheme, 3, pmediasize, 7, pstate, \
						14, psectorsize, 15, pstripeoffset, -1);
	if( (pfirst != NULL) && (plast != NULL) )
		gtk_tree_store_set(treestore1, &parent, 19, pfirst, 20, plast, -1);
	if( pentries != NULL)
		gtk_tree_store_set(treestore1, &parent, 21, pentries, -1);
	if( pmodified != NULL)
		gtk_tree_store_set(treestore1, &parent, 22, pmodified, -1);
	if( pmode != NULL)
		gtk_tree_store_set(treestore1, &parent, 23, pmode, -1);
	if( pstripesize != NULL)
		gtk_tree_store_set(treestore1, &parent, 13, pstripesize, -1);
}

char *selected_item(GtkWidget *tview, int column) {
	char *user_data = NULL;

	if(tview != NULL) {
		GtkTreeSelection *selected = gtk_tree_view_get_selection(GTK_TREE_VIEW (tview));
		if (selected == NULL) {
			printf("gtk_tree_view_get_selection() failed \n");
			return NULL;
		}
		GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW (tview));
		if (model == NULL) {
			printf("gtk_tree_view_get_model() failed\n");
			return NULL;
		}
		GtkTreeIter iter;
		if (gtk_tree_selection_get_selected(selected, &model, &iter) ) {
			gtk_tree_model_get(model, &iter, column, &user_data, -1);
			if(user_data != NULL) 
				return user_data;
		}
		else /* obsolete */
			msg("select a row!");
	}
	return NULL;
}

gboolean view_clicked(GtkWidget *btn, GdkEventButton *event, gpointer userdata) {
	if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
		GtkTreePath *path;
		GtkTreeViewColumn *column;

		GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree1));
		if (!gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(tree1), event->x, event->y, &path, &column, NULL, NULL))
			return FALSE;

/*		if (column != gtk_tree_view_get_column(GTK_TREE_VIEW(tree1), 0)) {	
			// wrong column, don't bother
			gtk_tree_path_free(path);
			return FALSE;
		}
*/
		gtk_tree_selection_unselect_all(selection);
		gtk_tree_selection_select_path(selection, path);
		gtk_tree_path_free(path);

		/* a potential popup menu for mount options */
		char * my = selected_item(tree1, 4); /* file system type */
		char *part = selected_item(tree1, 1); /* partition */
		if((my != NULL) && (part != NULL) ) {
			GtkWidget *pop_menu = gtk_menu_new();
			
			int mnt = is_mounted(part);
			if (mnt == 1) {
				GtkWidget *unmount = gtk_menu_item_new_with_label ("unmount");
				gtk_menu_shell_append (GTK_MENU_SHELL (pop_menu), unmount);
				g_signal_connect(unmount, "activate", G_CALLBACK(unmountfs), NULL);
			}
			else if (mnt == 0) {
				GtkWidget *mount = gtk_menu_item_new_with_label("mount");
				gtk_menu_shell_append (GTK_MENU_SHELL (pop_menu), mount);
				
				GtkWidget *mount_sub = gtk_menu_new();
				gtk_menu_item_set_submenu (GTK_MENU_ITEM (mount), mount_sub);

				/* /mnt */
				GtkWidget * mount_mnt = gtk_menu_item_new_with_label ("/mnt");
				gtk_menu_shell_append (GTK_MENU_SHELL (mount_sub), mount_mnt);

				/* /media */
				GtkWidget * mount_media = gtk_menu_item_new_with_label ("/media");
				gtk_menu_shell_append (GTK_MENU_SHELL (mount_sub), mount_media);

				/* /media */
				GtkWidget * mount_other = gtk_menu_item_new_with_label (l.mother);
				gtk_menu_shell_append (GTK_MENU_SHELL (mount_sub), mount_other);
				
				g_signal_connect(mount_mnt, "activate", G_CALLBACK(mountfs), NULL);
				g_signal_connect(mount_media, "activate", G_CALLBACK(mountfs), NULL);
				g_signal_connect(mount_other, "activate", G_CALLBACK(mountfs), NULL);

			}
			else if (mnt == 2)
				msg("error in mount routines!");

			gtk_widget_show_all(pop_menu);
			gtk_menu_popup_at_pointer( GTK_MENU (pop_menu), NULL);
		}
		return TRUE;
	}
	else
		return FALSE;
	}
