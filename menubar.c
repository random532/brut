#include "disk.h"

	/* callback fuctions */

void redraw_cb (GtkMenuItem *item, gpointer user_data) {  
	toplevel_entries();
	gtk_combo_box_set_active( GTK_COMBO_BOX (combo_toplevel), 0);
	gtk_widget_destroy(thegrid);
	editor();
	gtk_text_buffer_set_text(logs, "          ", 10);
}

void update_lang() {

	update_column_lang(opt.language);
	update_menubar_lang(opt.language);	
	redraw_cb(NULL, NULL);
	gtk_button_set_label(GTK_BUTTON (b) ,l.mrefresh);
	
	/* Update tabs. */
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab2, gtk_label_new(l.tabgroup));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab3, gtk_label_new(l.tabuser));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab5, gtk_label_new(l.tababout));
	on_tabs_changed(NULL, NULL);
}

void change_lang_de (GtkMenuItem *item, gpointer la) {
	
	opt.language=LANG_DE;
	update_lang();
}

void change_lang_en (GtkMenuItem *item, gpointer user_data) {

	opt.language=LANG_EN;
	update_lang();
}

void font_inc (GtkMenuItem *item, gpointer user_data) {    
	int what = 1; /* 1 increase, 0 decrease */    	
	change_fontsize(1);
}

void font_dec (GtkMenuItem *item, gpointer user_data) {    
	int what = 0; /* 1 increase, 0 decrease */    	
	change_fontsize(what);
}

void add_menubar() {
	
	GtkWidget * menuBar = gtk_menu_bar_new();	
	menu = menuBar;	/* it is global now */

	/* "Application" */
	GtkWidget * menu_app = gtk_menu_new();
	GtkWidget *menuItem1 = gtk_menu_item_new_with_mnemonic (l.mapplication);
   	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem1), menu_app);
    gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), menuItem1);

	/* App - Refresh */
//	GtkWidget * app_refresh = gtk_menu_item_new_with_mnemonic (l.mrefresh);
//	gtk_menu_shell_append (GTK_MENU_SHELL (menu_app), app_refresh);

//	GtkWidget *sep = gtk_separator_menu_item_new();
//	gtk_menu_shell_append (GTK_MENU_SHELL (menu_app), sep);
	
	/* App - Quit */
	GtkWidget *app_quit = gtk_menu_item_new_with_mnemonic (l.mquit);
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_app), app_quit);

	/* "Options" */
	GtkWidget *menu_options = gtk_menu_new();
	GtkWidget *menuItem2 = gtk_menu_item_new_with_mnemonic (l.moptions);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem2), menu_options);
	gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), menuItem2);

	/* language */
	GtkWidget * item_lang = gtk_menu_item_new_with_mnemonic (l.mlanguage);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_options), item_lang);

	/* language submenu */
	GtkWidget *menu_lang_sub = gtk_menu_new();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (item_lang), menu_lang_sub);

	/* language - de */
	GtkWidget * item_lang_de = gtk_menu_item_new_with_mnemonic ("_Deutsch");
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_lang_sub), item_lang_de);

	/* language - en */
	GtkWidget * item_lang_en = gtk_menu_item_new_with_mnemonic ("_English");
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_lang_sub), item_lang_en);

	/* Font size  */
	GtkWidget * item_font = gtk_menu_item_new_with_mnemonic (l.mfont);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_options), item_font);
	
	/* Font submenu */
	GtkWidget *menu_font_sub = gtk_menu_new();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (item_font), menu_font_sub);

	/* Font size  increase*/
	GtkWidget * item_fontinc = gtk_menu_item_new_with_mnemonic (l.mfontinc);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_font_sub), item_fontinc);

	/* Font size  increase*/
	GtkWidget * item_fontdec = gtk_menu_item_new_with_mnemonic (l.mfontdec);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_font_sub), item_fontdec);


	/*  callback functions */
	g_signal_connect_swapped (app_quit, "activate", G_CALLBACK(gtk_main_quit), NULL);
//   	g_signal_connect (app_refresh, "activate", G_CALLBACK (redraw_cb), NULL);
	g_signal_connect (item_lang_de, "activate", G_CALLBACK (change_lang_de), NULL);
	g_signal_connect (item_lang_en, "activate", G_CALLBACK (change_lang_en), NULL);
	g_signal_connect (item_fontinc, "activate", G_CALLBACK (font_inc), NULL);
	g_signal_connect (item_fontdec, "activate", G_CALLBACK (font_dec), NULL);


	gtk_box_pack_start(GTK_BOX(fixed), menuBar, FALSE, TRUE, 0);
	gtk_box_reorder_child(GTK_BOX(fixed), menuBar, 0);
	
	gtk_widget_show (menuBar);
	gtk_widget_show_all(window);
}
