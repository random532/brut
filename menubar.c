#include "brut.h"

void redraw_menubar() {

	gtk_widget_destroy(menubox);
	add_menubox();

	/* Show or hide the "back" button. */
	gint n = gtk_notebook_get_current_page(GTK_NOTEBOOK (tabs));
	const gchar *tab = gtk_notebook_get_tab_label_text(GTK_NOTEBOOK (tabs), gtk_notebook_get_nth_page(GTK_NOTEBOOK (tabs), n));
	
	if(tab == NULL)
		return;
	if(strcmp(tab, l.tabcontrol) == 0)
		gtk_widget_hide(bback);
	else
		gtk_widget_show(bback);
}

void update_lang() {

	/* Update tabs. */
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab0, gtk_label_new(l.tabcontrol));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab1, gtk_label_new(l.tabdisks));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab2, gtk_label_new(l.tabgroup));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab3, gtk_label_new(l.tabuser));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab4, gtk_label_new(l.tabtime));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab5, gtk_label_new(l.tababout));	
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab6, gtk_label_new(l.tabtasks));	
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab7, gtk_label_new(l.tabconfig));	
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab7, gtk_label_new(l.tabconfig));	
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab8, gtk_label_new(l.tabdevices));	
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab9, gtk_label_new(l.tabwlan));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab10, gtk_label_new(l.tablan));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab11, gtk_label_new(l.tabaudio));
	gtk_notebook_set_tab_label(GTK_NOTEBOOK (tabs), tab12, gtk_label_new(l.tabdmesg));
	on_tabs_changed(NULL, NULL);

	redraw_menubar();
	gtk_button_set_label(GTK_BUTTON(bback), l.mback);
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

void back_cb (GtkMenuItem *item, gpointer user_data) {    
		gtk_notebook_set_current_page(GTK_NOTEBOOK(tabs), 0);
}

void add_menubar() {
	
	GtkWidget * menuBar = gtk_menu_bar_new();	
//	menu = menuBar;	/* it is global now */

	/* "Application" */
	GtkWidget *menu_app = gtk_menu_new();
	GtkWidget *menuItem1 = gtk_menu_item_new_with_mnemonic (l.mapplication);
   	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem1), menu_app);
    gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), menuItem1);
	
	/* App - Back */
	GtkWidget *app_back = gtk_menu_item_new_with_mnemonic (l.mback);
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_app), app_back);

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
	g_signal_connect (app_back, "activate", G_CALLBACK (back_cb), NULL);
	g_signal_connect (item_lang_de, "activate", G_CALLBACK (change_lang_de), NULL);
	g_signal_connect (item_lang_en, "activate", G_CALLBACK (change_lang_en), NULL);
	g_signal_connect (item_fontinc, "activate", G_CALLBACK (font_inc), NULL);
	g_signal_connect (item_fontdec, "activate", G_CALLBACK (font_dec), NULL);

	/* Add to container. */
	gtk_container_add (GTK_CONTAINER (menubox), menuBar);

//	gtk_widget_show_all(bbox);
//	gtk_box_pack_start(GTK_BOX(fixed), menuBar, FALSE, TRUE, 0);
//	gtk_box_reorder_child(GTK_BOX(fixed), menuBar, 0);
	
//	gtk_widget_show_all(menuBar);
}
