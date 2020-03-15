/* includes and definitions */
#include "disk.h"

int main(int argc, char *argv[]) {
	
	en_lang();

	gtk_init(&argc, &argv);

	/* main window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Xdisk");
	gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	

	fixed = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add (GTK_CONTAINER (window), fixed);

	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	 gtk_widget_set_size_request (scrolled_window, 570, 350); /* width, height */

	gtk_box_pack_end(GTK_BOX(fixed), scrolled_window, TRUE, TRUE, 0);

	add_menubar();

	/* create tree view with columns */
	tree = make_treeview();
	if (tree == NULL )
		return 0;

	/* fill rows */
	int tree_test = fill_treeview();
	if(tree_test == 0)
		printf("error filling tree");

	
	/*  let the user see everything */
	gtk_widget_show_all(window);
	view_less();

	/* and go! */
	gtk_main();


	return EXIT_SUCCESS;
}
