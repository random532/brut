#include "disk.h"

	/* callback fuctions */
void change_lang_de (GtkMenuItem *item, gpointer user_data) {
	
	int lang=0;
	update_column_lang(lang);
	update_menubar_lang(lang);
}

void change_lang_en (GtkMenuItem *item, gpointer user_data) {
	
	int lang=1;
	update_column_lang(lang);
	update_menubar_lang(lang);
}

void redraw_cb (GtkMenuItem *item, gpointer user_data) {    
	redraw_treeview();
	if(window_editor != NULL) {
		gtk_widget_destroy(window_editor);
		editor();
		}
}

void font_inc (GtkMenuItem *item, gpointer user_data) {    
	int what = 1; /* 1 increase, 0 decrease */    	
	change_fontsize(what);
}

void font_dec (GtkMenuItem *item, gpointer user_data) {    
	int what = 0; /* 1 increase, 0 decrease */    	
	change_fontsize(what);
}

void edit_clicked (GtkMenuItem *item, gpointer user_data) {  
	/* are we open already? */
	if(window_editor == NULL )
		editor();
}
void add_menubar() {
	

	GtkWidget * menuBar;
	GtkWidget *menuItem1;
	GtkWidget *menuItem2;

	menuBar = gtk_menu_bar_new();	
	menu = menuBar;	/* it is global now */

	
	/* "Application" */
	GtkWidget * submenu1 = gtk_menu_new();
	menuItem1 = gtk_menu_item_new_with_mnemonic (mapplication);
    	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem1), submenu1);
    	gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), menuItem1);

	/* App - Refresh */
	GtkWidget * app_refresh = gtk_menu_item_new_with_label (mrefresh);
	gtk_menu_shell_append (GTK_MENU_SHELL (submenu1), app_refresh);

	/* App - Edit */
	GtkWidget * app_edit = gtk_menu_item_new_with_label (medit);
	gtk_menu_shell_append (GTK_MENU_SHELL (submenu1), app_edit);

	/* App - Quit */
	GtkWidget *app_quit = gtk_menu_item_new_with_label (mquit);
    	gtk_menu_shell_append (GTK_MENU_SHELL (submenu1), app_quit);

	/* "Options" */
	GtkWidget *menu_options = gtk_menu_new();
	menuItem2 = gtk_menu_item_new_with_mnemonic (moptions);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem2), menu_options);
	gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), menuItem2);

	/* language */
	GtkWidget * item_lang = gtk_menu_item_new_with_label (mlanguage);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_options), item_lang);

	/* language submenu */
	GtkWidget *menu_lang_sub = gtk_menu_new();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (item_lang), menu_lang_sub);

	/* language - de */
	GtkWidget * item_lang_de = gtk_menu_item_new_with_label ("Deutsch");
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_lang_sub), item_lang_de);

	/* language - en */
	GtkWidget * item_lang_en = gtk_menu_item_new_with_label ("English");
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_lang_sub), item_lang_en);

	/* Font size  increase*/
	GtkWidget * item_fontinc = gtk_menu_item_new_with_label (mfontinc);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_options), item_fontinc);

	/* Font size  increase*/
	GtkWidget * item_fontdec = gtk_menu_item_new_with_label (mfontdec);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_options), item_fontdec);

	/* "view" */
	GtkWidget *menu_view = gtk_menu_new();
	GtkWidget *menuItem3 = gtk_menu_item_new_with_mnemonic (mview);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem3), menu_view);
	gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), menuItem3);

	/* view - all */
	GtkWidget * item_view_all = gtk_menu_item_new_with_label (mall);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_view), item_view_all);	

	/* view - less */
	GtkWidget * item_view_less = gtk_menu_item_new_with_label (mless);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_view), item_view_less);

	/* if a menu item is clicked */
	g_signal_connect_swapped (app_quit, "activate", G_CALLBACK(gtk_main_quit), NULL);
    	g_signal_connect (app_refresh, "activate", G_CALLBACK (redraw_cb), NULL);
	g_signal_connect (item_lang_de, "activate", G_CALLBACK (change_lang_de), NULL);
	g_signal_connect (item_lang_en, "activate", G_CALLBACK (change_lang_en), NULL);
	g_signal_connect (item_view_all, "activate", G_CALLBACK (view_all), NULL);
	g_signal_connect (item_view_less, "activate", G_CALLBACK (view_less), NULL);
	g_signal_connect (item_fontinc, "activate", G_CALLBACK (font_inc), NULL);
	g_signal_connect (item_fontdec, "activate", G_CALLBACK (font_dec), NULL);
	g_signal_connect (app_edit, "activate", G_CALLBACK (edit_clicked), NULL);

	gtk_box_pack_start(GTK_BOX(fixed), menuBar, FALSE, TRUE, 0);

	gtk_widget_show (menuBar);
	gtk_widget_show_all(window);
}
