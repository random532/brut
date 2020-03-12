
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>


#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <sys/types.h>
#include <sys/sysctl.h>


	/* columns */
#define MAX_COLUMN  26
char myarray[MAX_COLUMN][25];


char fontsize[10];	/* font size */

char *list_of_disks;
char *list_of_slices;
char *list_of_partitions;
char *slices_on_a_disk;

	/* menu bar items */
char mapplication[20];
char moptions[20];
char mview[20];
char mquit[20];
char mrefresh[20];
char mlanguage[20];
char mall[20];
char mless[20];
char mfontinc[20];
char mfontdec[20];
char medit[25];


char chose_disk[30];
char chose_partition[30];
char chose_type[30];
char chose_size[30];
char chose_bootoptions[30];


	/* useful to have these global  */
GtkWidget	*window; 	/* main window */
GtkWidget	*fixed;
GtkWidget *scrolled_window;
GtkWidget	*tree;		/* disk information is displayed here */
GtkTreeStore	*treestore;	
GtkCellRenderer     *cell;
GtkWidget *menu;
GtkWidget *window_editor;
GtkWidget *thegrid;

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

	/* all functions */
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

/* subr.c */
char *get_disks();
char *read_disk(char *);
void change_fontsize(int);
char *add_to_list(char *, char *);
void clean_up_pointers();
char *what_file_system(char *);
int execute_cmd(char *);
void msg(char *);
void on_response(GtkDialog *, gint, gpointer);
char *check_free_space(char *, char *, char *);
int find_p(const char *);
void format_string(char *);

/* editorWindow.c */
void editor();
void hide_widgets();

/* menubar.c */
void add_menubar();

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
GtkWidget *make_treeview();
int fill_treeview();
void fill_tree(char *, char *);
void redraw_treeview();
void view_all();
void view_less();

/* ?? */
void show_message_cb(GtkMenuItem *item, gpointer);


#endif
