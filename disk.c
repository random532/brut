/* Disk tab */
#include "disk.h"

void add_grid() {
	
	grid = gtk_grid_new();
	gtk_grid_insert_column(GTK_GRID(grid), 3);
	gtk_box_pack_start(GTK_BOX(diskbox), grid, FALSE, TRUE, 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), FALSE);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 7);
	
	/*
	 * This grid has two entries.
	 * 1. a combo box that lets users chose whether to display
	 * an overview of all disks, or contents of a specific disk.
	 */
	main_combo();

	/* 2. A refresh button. */
	b = gtk_button_new_with_mnemonic(l.mrefresh);
	gtk_grid_attach(GTK_GRID (grid), GTK_WIDGET (b), 1, 0, 1, 1);
	g_signal_connect (b, "clicked", G_CALLBACK (redraw_cb), NULL);
}

void scrolled() {
	
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_ALWAYS, GTK_POLICY_AUTOMATIC); 
	gtk_box_pack_start(GTK_BOX(box), scrolled_window, FALSE, TRUE, 0);
	gtk_scrolled_window_set_propagate_natural_height (GTK_SCROLLED_WINDOW(scrolled_window), TRUE);
	gtk_scrolled_window_set_propagate_natural_width (GTK_SCROLLED_WINDOW(scrolled_window), TRUE);
}

void main_combo() {

	/* 
	 * A combo box with disk names.
	 */
	combo_toplevel = gtk_combo_box_text_new();

	gtk_widget_set_focus_on_click(combo_toplevel, TRUE);
	gtk_grid_attach(GTK_GRID (grid), GTK_WIDGET (combo_toplevel), 0, 0, 1, 1);
	g_signal_connect (combo_toplevel, "changed", G_CALLBACK (on_toplevel_changed), NULL);

	/* Add disk names */
	toplevel_entries();
}

void add_box() {

	/* 
	 * In this box we pack a scrolled window (for treeviews), 
	 * and the editor.
	 */
	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_container_add(GTK_CONTAINER (diskbox), box);
	
	/* A window with scrollbars. */
	scrolled();
	
	/* Separator */
	GtkWidget *s1 = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	gtk_container_add(GTK_CONTAINER (box), s1);	
}

void disk() {
		
	/* A top level container. */
	diskbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add (GTK_CONTAINER (tab1), diskbox);

	/* It has two boxes. */
	add_grid(); /* ... with a combo box and a refresh button. */
	add_box();	/* ... with a treeview and the editor. */

	/* Populate the scrolled window once. */
	gtk_combo_box_set_active( GTK_COMBO_BOX (combo_toplevel), 0);
	
	gtk_widget_show_all(diskbox);

	/* At last, add the editor. */
	editor();
}
