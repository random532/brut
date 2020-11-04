#include "disk.h"

void redraw_menubar() {
	gtk_widget_destroy(menu);
	add_menubar();
}

void update_lang() {

	/* Update tabs. */
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab0, gtk_label_new(l.tabcontrol));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab1, gtk_label_new(l.tabdisks));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab2, gtk_label_new(l.tabgroup));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab3, gtk_label_new(l.tabuser));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab4, gtk_label_new(l.tabtime));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab5, gtk_label_new(l.tababout));	

	on_tabs_changed(NULL, NULL);
	redraw_menubar();
}

void change_lang_de (GtkMenuItem *item, gpointer la) {
	
	if(opt.language != LANG_DE) {
		opt.language = LANG_DE;
		de_lang();
		update_lang();
	}
}

void change_lang_en (GtkMenuItem *item, gpointer user_data) {

	if(opt.language != LANG_EN) {
		opt.language = LANG_EN;
		en_lang();
		update_lang();
	}
}

void font_inc (GtkMenuItem *item, gpointer user_data) {    
	change_fontsize(TRUE); /* increase */
}

void font_dec (GtkMenuItem *item, gpointer user_data) {    
	change_fontsize(FALSE); /* decrease */
}

void add_menubar() {
	
	GtkWidget * menuBar = gtk_menu_bar_new();	
	menu = menuBar;	/* it is global now */

	/* "Application" */
	GtkWidget *menu_app = gtk_menu_new();
	GtkWidget *menuItem1 = gtk_menu_item_new_with_mnemonic (l.mapplication);
   	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem1), menu_app);
    gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), menuItem1);
	
	/* App - Quit */
	GtkWidget *app_quit = gtk_menu_item_new_with_mnemonic (l.mquit);
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_app), app_quit);

	/* "Options" */
	GtkWidget *menu_options = gtk_menu_new();
	GtkWidget *menuItem2 = gtk_menu_item_new_with_mnemonic (l.moptions);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem2), menu_options);
	gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), menuItem2);

	/* language */
	GtkWidget *item_lang = gtk_menu_item_new_with_mnemonic (l.mlanguage);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_options), item_lang);

	/* language submenu */
	GtkWidget *menu_lang_sub = gtk_menu_new();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (item_lang), menu_lang_sub);

	/* language - de */
	GtkWidget *item_lang_de = gtk_menu_item_new_with_mnemonic ("_Deutsch");
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_lang_sub), item_lang_de);

	/* language - en */
	GtkWidget *item_lang_en = gtk_menu_item_new_with_mnemonic ("_English");
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_lang_sub), item_lang_en);

	/* Font size  */
	GtkWidget *item_font = gtk_menu_item_new_with_mnemonic (l.mfont);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_options), item_font);
	
	/* Font submenu */
	GtkWidget *menu_font_sub = gtk_menu_new();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (item_font), menu_font_sub);

	/* Font size  increase*/
	GtkWidget *item_fontinc = gtk_menu_item_new_with_mnemonic (l.mfontinc);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_font_sub), item_fontinc);

	/* Font size  increase*/
	GtkWidget *item_fontdec = gtk_menu_item_new_with_mnemonic (l.mfontdec);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_font_sub), item_fontdec);


	/*  callback functions */
	g_signal_connect_swapped (app_quit, "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect (item_lang_de, "activate", G_CALLBACK (change_lang_de), NULL);
	g_signal_connect (item_lang_en, "activate", G_CALLBACK (change_lang_en), NULL);
	g_signal_connect (item_fontinc, "activate", G_CALLBACK (font_inc), NULL);
	g_signal_connect (item_fontdec, "activate", G_CALLBACK (font_dec), NULL);


	gtk_box_pack_start(GTK_BOX(fixed), menuBar, FALSE, TRUE, 0);
	gtk_box_reorder_child(GTK_BOX(fixed), menuBar, 0);
	
	gtk_widget_show_all(menuBar);
}
