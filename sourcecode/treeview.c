/* treeview functions */
#include "disk.h"

GtkWidget *make_treeview() {
	
	GtkWidget *view = gtk_tree_view_new();
	
	gtk_container_add(GTK_CONTAINER(scrolled_window), view);	
	cell = gtk_cell_renderer_text_new();
	if(fontsize[0] == '\0')
		strcpy(fontsize, "11");
	
	g_object_set(cell, "font", fontsize, NULL);
	//g_object_set(cell,"editable", TRUE, NULL);
	//g_object_set(cell, "background", "gray", "background-set", TRUE, NULL);

	//g_object_set(cell, "mode", GTK_SELECTION_BROWSE, NULL);
	//gtk_tree_view_set_enable_search(view, TRUE);
	g_object_set(view, "enable-grid-lines", GTK_TREE_VIEW_GRID_LINES_BOTH, NULL);


	
	int cnt = 0;
	while( (cnt <= MAX_COLUMN) && (strlen(myarray[cnt]) >0 ) ) {
	
		/* first column */
		char * col_title = myarray[cnt];

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

	/* the treestore holds the rows */
	treestore = gtk_tree_store_new(MAX_COLUMN, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 	G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 	G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(view), GTK_TREE_MODEL(treestore));
	g_object_unref(treestore); //destroy model automatically with view 
  	gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(view)),
                             GTK_SELECTION_SINGLE);

return view;
}

int fill_treeview() {
	
	/* clean up */
	clean_up_pointers();

	/* gather all disks */
	list_of_disks = get_disks();
	if( list_of_disks == NULL )	{
		printf("get_disks(): failed! No disks were found.\n");
		return 0;
		}

	/* extract one disk from the string of disks */
	char *one_disk, *one_slice, *brk, *brk1;
	char *buffer_geom_disk;
	char *buffer_geom_slice;

	
	one_disk = strtok_r( list_of_disks, " ", &brk);

	while( one_disk != NULL ) {

		/* call geom with diskname */
		buffer_geom_disk = read_disk(one_disk);
		if (buffer_geom_disk == NULL ) {
			printf("read_disk() failed. This is critical.\n");
			return 0;	
			}
		
		/* fill in the tree	*/
		fill_tree(buffer_geom_disk, one_disk);
	
		/* we may have detected some slices */
		if(slices_on_a_disk != NULL) {
			one_slice = strtok_r ( slices_on_a_disk, " ", &brk1);
			while( one_slice != NULL ) {
	
				/* call geom with diskname */
				buffer_geom_slice = read_disk(one_slice);
				if (buffer_geom_slice == NULL ) {
					printf("no slice found\n");
					return 0;	
					}
		
				/* fill in the tree	*/
				fill_tree(buffer_geom_slice, one_slice);
				free(buffer_geom_slice);

				/* scan for next slice */
				one_slice = strtok_r( NULL, " ", &brk1);
			}			
	
		free(slices_on_a_disk);
		slices_on_a_disk= NULL;
		}


		/* disk/slice done, so.. */
		free(buffer_geom_disk);

		/* scan for next disk */
		one_disk = strtok_r( NULL, " ", &brk);	
		}

	/* be nice to Users */
	gtk_tree_view_expand_all(GTK_TREE_VIEW(tree));
	gtk_tree_view_set_enable_search (GTK_TREE_VIEW(tree), TRUE);	
	gtk_tree_view_set_enable_tree_lines (GTK_TREE_VIEW(tree), TRUE);
	gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(tree), GTK_TREE_VIEW_GRID_LINES_BOTH);
	

	return 1;
}

void fill_tree(char *buffer, char * one_disk) {

char *ptr;

/* 28 pointer */
char *pname=	NULL;
char *pname_capital=NULL;
char *pmediasize=NULL;
char *psectorsize=NULL;
char *ptype=	NULL;
char *pstart=	NULL;
char *pend=	NULL;
char *pend_old= NULL;
char *pstate=	NULL;
char *pfwheads=	NULL;
char *pfwsectors=NULL;
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


int len = strlen(buffer);
char *free_space;

	/* strtok cannot handle 0x0A */
int i=0;

	while(i < len) {
		if (buffer[i] == '\n') {	
			buffer[i] = ' ';
			}
		i++;
		}

 	/* parent - disks and slices */
	/* child - partitions		*/
	GtkTreeIter    parent, child, row_freespace;

	gtk_tree_store_append(treestore, &parent, NULL);
	gtk_tree_store_set(treestore, &parent, 0, one_disk, -1);

	if(buffer[0] == '\0')	/* no geom information available */
		return;

	/* parse the geom buffer */
char *sep = " !";
char *next = strtok_r(buffer, sep, &ptr);

	next = strtok_r(NULL, sep, &ptr);
	while (next != NULL) {
		
		if ( (strcmp(next, "name:") )== 0) {
			pname = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "state:") )== 0) {
			pstate = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "fwheads:") )== 0) {
			pfwheads = strtok_r(NULL, sep, &ptr);
			}
		else if ( (strcmp(next, "fwsectors:") )== 0) {
			pfwsectors = strtok_r(NULL, sep, &ptr);
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
				gtk_tree_store_append(treestore, &row_freespace, &parent);
				gtk_tree_store_set(treestore, &row_freespace, 3, "-free-", 4, free_space, -1);
				free(free_space);
				}
				

			/* add partition to list_of_partitions */
			list_of_partitions = add_to_list(pname_capital, list_of_partitions);
			gtk_tree_store_append(treestore, &child, &parent);
	
			/* what file system? */
			 pfilesystem = what_file_system(pname_capital);
			if (pfilesystem != NULL) {
				gtk_tree_store_set(treestore, &child, 6, pfilesystem, -1);
				free(pfilesystem);
			}
			
	/* basic info */
	gtk_tree_store_set(treestore, &child, 2, pname_capital, 3, ptype, 4, pmediasize, 9, pstart, 10, pend, 11, plength, -1);

	if(pindex != NULL) /* be safe */
		gtk_tree_store_set(treestore, &child, 1, pindex, -1);
	if(plabel != NULL) /* be safe */
		gtk_tree_store_set(treestore, &child, 7, plabel, -1);
	if(pattribute!= NULL)
		gtk_tree_store_set(treestore, &child, 8, pattribute, -1);
	pattribute= NULL;

		gtk_tree_store_set(treestore, &child, 12, poffset, 13, pstripesize, 14, psectorsize, 15, pstripeoffset, 16, pefimedia, 17, prawuuid, 18, prawtype, -1);

		if( pmode != NULL)
		gtk_tree_store_set(treestore, &child, 25, pmode, -1);

			}

		next = strtok_r(NULL, sep, &ptr);
	}

	/* inform user about free space after last partition */
	free_space = check_free_space(plast, pend, psectorsize);
		if (free_space != NULL) {
			gtk_tree_store_append(treestore, &row_freespace, &parent);
			gtk_tree_store_set(treestore, &row_freespace, 3, "-free-", 4, free_space, -1);
			free(free_space);
			}

	/* parent entries */
	gtk_tree_store_set(treestore, &parent, 0, one_disk, 3, pscheme, 4, pmediasize, 5, pstate, 14, psectorsize, 15, pstripeoffset, 19, pfwheads, 20, pfwsectors, -1);
	if( (pfirst != NULL) && (plast != NULL) )
		gtk_tree_store_set(treestore, &parent, 21, pfirst, 22, plast, -1);
	if( pentries != NULL)
		gtk_tree_store_set(treestore, &parent, 23, pentries, -1);
	if( pmodified != NULL)
		gtk_tree_store_set(treestore, &parent, 24, pmodified, -1);
	if( pmode != NULL)
		gtk_tree_store_set(treestore, &parent, 25, pmode, -1);
	if( pstripesize != NULL)
		gtk_tree_store_set(treestore, &parent, 13, pstripesize, -1);
		

}

void redraw_treeview() {

	gtk_tree_store_clear(treestore);

	 int tree_test = fill_treeview();
	if(tree_test == 0)
		printf("error filling tree\n");
	
	gtk_widget_show(tree);
}

void view_all() {

	int n =0;
	while(n <MAX_COLUMN) {
	GtkTreeViewColumn   * col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree), n);
	gtk_tree_view_column_set_visible (col, TRUE);
	n++;	
	}

}
void view_less() {

	int n =0;
	while(n <MAX_COLUMN) {
	GtkTreeViewColumn   * col = gtk_tree_view_get_column(GTK_TREE_VIEW(tree), n);
	if( n >=7 )
		gtk_tree_view_column_set_visible (col, FALSE);
	n++;	
	}
}

