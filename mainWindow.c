#include "disk.h"



	 /* create the main window and update the pointers */
int main(int argc, char *argv[]) {


	gtk_init(&argc, &argv);
	
	
	builder = gtk_builder_new_from_resource("/glade2.glade");
	
	if(builder==NULL)
		exit(1);
		
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_builder_connect_signals(builder, NULL);
	
	 
	/* fill our pointers */
	fixed1 = 	GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	fixed2 = 	GTK_WIDGET(gtk_builder_get_object(builder, "fixed2"));
	fixed3 = 	GTK_WIDGET(gtk_builder_get_object(builder, "fixed3"));	

	grid1 =	GTK_WIDGET(gtk_builder_get_object(builder, "grid1"));
	grid2 =	GTK_WIDGET(gtk_builder_get_object(builder, "grid2"));
	grid3 =	GTK_WIDGET(gtk_builder_get_object(builder, "grid3"));
	
	tree1 =	GTK_TREE_VIEW(gtk_builder_get_object(builder, "tree1"));
	treestore1 = GTK_TREE_STORE(gtk_builder_get_object(builder, "treestore1"));
	c1 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "c1"));
	c2 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "c2"));
	cr1 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr1"));
	cr2 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr2"));
	
	gtk_tree_view_column_add_attribute(c1, cr1, "text", 0);
	gtk_tree_view_column_add_attribute(c2, cr2, "text", 1);
	
	tree2 =	GTK_TREE_VIEW(gtk_builder_get_object(builder, "tree2"));
	treestore2 = GTK_TREE_STORE(gtk_builder_get_object(builder, "treestore2"));
	c3 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "c3"));
	c4 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "c4"));
	c5 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "c5"));
	cr3 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr3"));
	cr4 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr4"));
	cr5 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "cr5"));	
	
	gtk_tree_view_column_add_attribute(c3, cr3, "text", 0);
	gtk_tree_view_column_add_attribute(c4, cr4, "text", 1);	
	gtk_tree_view_column_add_attribute(c5, cr5, "text", 2);

	combo1 =	GTK_WIDGET(gtk_builder_get_object(builder, "combo5"));
	entry4 =	GTK_WIDGET(gtk_builder_get_object(builder, "entry4"));
	entry5 =	GTK_WIDGET(gtk_builder_get_object(builder, "entry5"));
	entry6 =	GTK_WIDGET(gtk_builder_get_object(builder, "entry6"));
	entry7 =	GTK_WIDGET(gtk_builder_get_object(builder, "entry7"));
	entry9 =	GTK_WIDGET(gtk_builder_get_object(builder, "entry9"));
	scrolled3 = GTK_WIDGET(gtk_builder_get_object(builder, "scrolled3"));
	
	file1 =	GTK_WIDGET(gtk_builder_get_object(builder, "fchose1"));
	file2 =	GTK_WIDGET(gtk_builder_get_object(builder, "fchose2"));
	

	combo_d();
	combo_typ();
	camcontrol();
	glabel();
	fs_combo();
	combo_set_unset();
	
	gtk_widget_show(window);
	
	gtk_widget_hide(GTK_WIDGET (combo_disks));
	gtk_widget_hide(GTK_WIDGET (combo_types));
	gtk_widget_hide(GTK_WIDGET (combo_fs));
	gtk_widget_hide(GTK_WIDGET (entry4));
	gtk_widget_hide(GTK_WIDGET (entry5));
	gtk_widget_hide(GTK_WIDGET (entry6));


	on_gpart_refresh_clicked(GTK_BUTTON (combo5));

	fchose_combo();
	

	gtk_main();
	 
	
	return EXIT_SUCCESS;
}
