#include "disk.h"

	/* callback fuctions */
void editor_cb (GtkMenuItem *item, gpointer user_data) { 
	if( window_editor == NULL)
		editor();
	else
		gtk_widget_destroy(window_editor);
}
void redraw_cb (GtkMenuItem *item, gpointer user_data) {  
	toplevel_entries();
	gtk_combo_box_set_active( GTK_COMBO_BOX (combo_toplevel), 0);
	if(window_editor != NULL) {
		gtk_widget_destroy(window_editor);
		editor();
		}
}

void change_lang_de (GtkMenuItem *item, gpointer user_data) {

	int lang=LANG_DE;
	update_column_lang(lang);
	update_menubar_lang(lang);
	redraw_cb(item, user_data);
	gtk_button_set_label(b ,mrefresh);
}

void change_lang_en (GtkMenuItem *item, gpointer user_data) {

	int lang=LANG_EN;	
	update_column_lang(lang);
	update_menubar_lang(lang);
	redraw_cb(item, user_data);
	gtk_button_set_label(b ,mrefresh);
}

void font_inc (GtkMenuItem *item, gpointer user_data) {    
	int what = 1; /* 1 increase, 0 decrease */    	
	change_fontsize(what);
}

void font_dec (GtkMenuItem *item, gpointer user_data) {    
	int what = 0; /* 1 increase, 0 decrease */    	
	change_fontsize(what);
}

void msg_show (GtkMenuItem *item, gpointer user_data) {    

	confirm_yn = 1;
	char buf[35];
	strcpy(buf, mshow);
	strcat(buf, "  (x)");
	gtk_menu_item_set_label(GTK_MENU_ITEM(item_msg_show), buf);
	gtk_menu_item_set_label(GTK_MENU_ITEM(item_msg_hide), mhide);
}

void msg_hide (GtkMenuItem *item, gpointer user_data) {    

	confirm_yn = 0;
	char buf[35];
	strcpy(buf, mhide);
	strcat(buf, "  (x)");
	gtk_menu_item_set_label(GTK_MENU_ITEM(item_msg_hide), buf);
	gtk_menu_item_set_label(GTK_MENU_ITEM(item_msg_show), mshow);
}

void edit_clicked (GtkMenuItem *item, gpointer user_data) {  
	/* are we open already? */
	if(window_editor == NULL )
		editor();
}

void add_menubar() {
	
	GtkWidget * menuBar = gtk_menu_bar_new();	
	menu = menuBar;	/* it is global now */

	/* "Application" */
	GtkWidget * menu_app = gtk_menu_new();
	GtkWidget *menuItem1 = gtk_menu_item_new_with_mnemonic (mapplication);
   	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuItem1), menu_app);
    gtk_menu_shell_append (GTK_MENU_SHELL (menuBar), menuItem1);

	/* App - Refresh */
	GtkWidget * app_refresh = gtk_menu_item_new_with_label (mrefresh);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_app), app_refresh);

	/* App - Edit */
	GtkWidget * app_edit = gtk_menu_item_new_with_label (medit);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_app), app_edit);

	/* App - Quit */
	GtkWidget *app_quit = gtk_menu_item_new_with_label (mquit);
    	gtk_menu_shell_append (GTK_MENU_SHELL (menu_app), app_quit);

	/* "Options" */
	GtkWidget *menu_options = gtk_menu_new();
	GtkWidget *menuItem2 = gtk_menu_item_new_with_mnemonic (moptions);
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

	/* show messages */
	GtkWidget * item_msg = gtk_menu_item_new_with_label (mmsg);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_options), item_msg);


	/* message submenu */
	GtkWidget *menu_msg_sub = gtk_menu_new();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (item_msg), menu_msg_sub);

	/* message -show */
	item_msg_show = gtk_menu_item_new_with_label (mshow);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_msg_sub), item_msg_show);

	/* message - hide */
	item_msg_hide = gtk_menu_item_new_with_label (mhide);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu_msg_sub), item_msg_hide);


	if(confirm_yn == 1)
		msg_show (GTK_MENU_ITEM(item_msg_show), NULL);
	else
		msg_hide (GTK_MENU_ITEM(item_msg_hide), NULL);

	/* if a menu item is clicked */
	g_signal_connect_swapped (app_quit, "activate", G_CALLBACK(gtk_main_quit), NULL);
   	g_signal_connect (app_refresh, "activate", G_CALLBACK (redraw_cb), NULL);
	g_signal_connect (item_lang_de, "activate", G_CALLBACK (change_lang_de), NULL);
	g_signal_connect (item_lang_en, "activate", G_CALLBACK (change_lang_en), NULL);
	g_signal_connect (item_fontinc, "activate", G_CALLBACK (font_inc), NULL);
	g_signal_connect (item_fontdec, "activate", G_CALLBACK (font_dec), NULL);
	g_signal_connect (app_edit, "activate", G_CALLBACK (edit_clicked), NULL);
	g_signal_connect (item_msg_show, "activate", G_CALLBACK (msg_show), NULL);
	g_signal_connect (item_msg_hide, "activate", G_CALLBACK (msg_hide), NULL);

	gtk_box_pack_start(GTK_BOX(fixed), menuBar, FALSE, TRUE, 0);

	gtk_widget_show (menuBar);
	gtk_widget_show_all(window);
}

