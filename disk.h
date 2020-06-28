/*TODO:
 * - increase code readability
 * - find bugs
 * */
 
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define LANG_EN 0
#define LANG_DE 1

	/* column header */
#define MAX_COLUMN  24
char myarray[MAX_COLUMN][23];
#define MAX_D 11
char tree_array[MAX_D][25];

	/* font size */
char fontsize[10];

	/* ask for confirmation 
	 * before issueing any gpart
	 * command */
int confirm_yn;

	/* keep track of disks and partitions */
char *all_disks;
char *list_of_slices;
char *all_partitions;
char *slices_on_a_disk;

	/* menu bar items */
char mapplication[20];
char moptions[20];
char mquit[20];
char mrefresh[20];
char mlanguage[20];
char mmsg[20];
char mshow[20];
char mhide[20];
char mfontinc[20];
char mfontdec[20];
char medit[25];

	/* toplevel */
char overview[80]; 

	/* editor hints */
char chose_disk[35];
char chose_partition[35];
char chose_scheme[35];
char chose_type[35];
char chose_size[35];
char chose_bootoptions[35];
char chose_fs[35];
char apply[15];	/* editor apply button */

	/* global gtk pointer  */
GtkWidget	*window; 	/* main window */
GtkWidget	*fixed;
GtkWidget *scrolled_window;
GtkWidget *combo_toplevel;
GtkWidget	*tree;		/* all disks are displayed here */
GtkWidget	*tree1;		/* only one disk is displayed here */
GtkTreeStore	*treestore;
GtkTreeStore	*treestore1;	
GtkCellRenderer     *cell;
GtkCellRenderer		*cellr;
GtkWidget *menu;
GtkWidget *window_editor;
GtkWidget *thegrid;
GtkWidget *grid;
GtkWidget * item_msg_hide;
GtkWidget * item_msg_show;
GtkWidget *b;

/* all items in the grid/editor window */
GtkWidget *combo_schemes;
GtkWidget *combo_types;
GtkWidget *combo_disks;
GtkWidget *combo_partitions;
GtkWidget *combo_filesystems;
GtkWidget *combo_bootoptions;
GtkWidget *edit_button;
GtkWidget *combo_geom;
GtkWidget *text_label;
GtkWidget *text_alignment;
GtkWidget *text_size;
GtkWidget *text_entries;

	/* (most) functions */
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/* lang.c */
void en_lang();
void de_lang();
void update_column_lang(int );
void update_menubar_lang(int);

/* gridEntries.c */
void create_combo_schemes();
void create_combo_types();
void create_combo_disks();
void create_combo_partitions();
void create_combo_filesystems();
void create_combo_bootoptions();
void create_combo_geom();
void create_text_label();
void create_text_entries();
void create_text_size();
void create_text_alignment();
void grid_attach_all();

/* on_combos_changed.c */
void on_geom_changed();
void on_toplevel_changed();
void toplevel_entries();

/* subr.c */
char *get_disks();
char *read_disk(char *);
int add_slices();
int add_geoms();
int add_partitions();
void change_fontsize(int);
char *add_to_list(char *, char *);
void clean_up_pointers();
char *what_file_system(char *);
int execute_cmd(char *);
char* command(char *);
void msg(char *);
void on_response(GtkDialog *, gint, gpointer);
void confirm( char *);
void confirm_cb(GtkDialog *, gint, gpointer);
char *check_free_space(char *, char *, char *);
int find_p(char *);
void format_string(char *);
int vari(char *, int);

/* editorWindow.c */
void editor();
void hide_widgets();

/* menubar.c */
void add_menubar();
void editor_cb (GtkMenuItem *, gpointer);
void redraw_cb (GtkMenuItem *, gpointer);

/* edit_clicked.c */
void on_edit_clicked (GtkMenuItem *, gpointer);
int gpart_destroy();
int gpart_create();
int gpart_modify();
int gpart_add();
int gpart_delete();
int gpart_resize();
int gpart_set();
int gpart_unset();
int gpart_filesystem();
int gpart_bootcode();

/* treeview.c */
GtkWidget *disk_treeview();
GtkWidget *make_treeview();
int fill_treeview();
int fill_treeview1(char *);
void fill_tree(char *, char *);

/* ?? */
void show_message_cb(GtkMenuItem *item, gpointer);

#endif
