/*TODO:
 * - test everything
 * - get feedback
 * */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <inttypes.h>
#include <gtk/gtk.h>

#define LANG_EN 0
#define LANG_DE 1

#define CMDSIZE 150
#define ENTRY_MAX 8

	/* column header for 2 treeviews */
#define COLUMNS  25
char columns[COLUMNS][26];
#define COL 11
char column[COL][25];

	/* font size */
char fontsize[10];

	/* ask for confirmation 
	 * before issueing a command */
int confirm;

	/* do we mount or gpart? Or something else? */
#define MOUNT	0
#define GPART	1
#define FS 		3
int todo;

	/* keep track of disks and partitions */
char *all_disks;
char *all_slices;
char *all_partitions;
char *slices_on_a_disk;

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
GtkWidget *su;
GtkWidget *passbuf;

/* all items in the grid/editor window */
GtkWidget *combo_schemes;
GtkWidget *combo_types;
GtkWidget *combo_disks;
GtkWidget *combo_partitions;
GtkWidget *combo_filesystems;
GtkWidget *combo_bootoptions;
GtkWidget *edit_button;
GtkWidget *combo_geom;
GtkWidget *combo_bootcode;
GtkWidget *text_label;
GtkWidget *text_alignment;
GtkWidget *text_size;
GtkWidget *text_entries;
GtkWidget *toggle_soft;
GtkWidget *toggle_journal;
GtkWidget *toggle_fast;
GtkWidget *toggle_comp;
GtkWidget *gfile;

/* strings */
typedef struct {
	
	char overview[85]; 

	/* menu bar items */
	char mapplication[20];
	char moptions[20];
	char mquit[20];
	char mrefresh[20];
	char mlanguage[20];
	char mmsg[25];
	char mshow[20];
	char mhide[20];
	char mfont[20];
	char mfontinc[25];
	char mfontdec[25];
	char medit[25];

	/* hints */
	char no_root[35];
	char chose_disk[35];
	char chose_partition[35];
	char chose_scheme[35];
	char chose_type[35];
	char chose_size[35];
	char chose_bootoptions[35];
	char chose_fs[35];
	char apply[15];
	char mdone[20];
	char merror[25];
	char mother[30];
	char mrescan[30];
	char mpassw[50];
	char mexplain[60];
	char mhello[60];
	char mhello1[60];
} lang;

lang l;

	/* (most) functions */
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/* lang.c */
void en_lang();
void de_lang();
void update_column_lang(int );
void update_menubar_lang(int);

/* EditorGridEntries.c */
void create_combo_geom();
void create_combo_schemes();
void create_combo_types();
void create_combo_disks();
void create_combo_partitions();
void create_combo_filesystems();
void create_combo_bootoptions();
void create_combo_bootcode(); 
void create_text_label();
void create_text_entries();
void create_text_size();
void create_text_alignment();
void grid_attach_all();

/* on_combos_changed.c */
void on_geom_changed();
void on_toplevel_changed();
void on_fs_changed();
void toplevel_entries();
void on_bootcode_changed();

/* subroutines.c */
char *get_disks();
char *read_disk(char *);
int add_slices();
int add_geoms();
int add_partitions();
void change_fontsize(int);
char *add_to_list(char *, char *);
void clean_up_pointers();
char *what_file_system(char *);
int execute_cmd(char *, int);
char* command(char *);
void msg(char *);
void on_response(GtkDialog *, gint, gpointer);
void ask( char *);
void ask_cb(GtkDialog *, gint, gpointer);
char *check_free_space(char *, char *, char *);
int find_p(char *);
void format_string(char *);
int vari(char *, int);
int root();
int command_exist(char *);
int submit(char *, int);
void fsscan();
void info_cb(GtkMenuItem *, gpointer);
char *get_partition_type(char *);
char *get_type(char *);

/* root.c */
char *sudo(char *, char *, int);
int test_pw(char *);
void window_pw(char *);
int pw_needed();
char *sudo_backend(char *, char *);

/* editorWindow.c */
void editor();
void hide_widgets();

/* menubar.c */
void add_menubar();
void editor_cb (GtkMenuItem *, gpointer);
void redraw_cb (GtkMenuItem *, gpointer);

/* applyButtonClicked.c */
void on_edit_clicked (GtkMenuItem *, gpointer);
char *gpart_destroy(char *);
char *gpart_create(char *);
char *gpart_modify(char *);
char *gpart_add(char *);
char *gpart_delete(char *);
char *gpart_resize(char *);
char *gpart_set(char *);
char *gpart_unset(char *);
char *gpart_filesystem(char *);
char *gpart_bootcode(char *);

/* treeviews.c */
GtkWidget *disk_treeview();
GtkWidget *make_treeview();
int fill_treeview();
int fill_treeview1(char *);
void fill_tree(char *, char *);
char *selected_item(GtkWidget *, int);
gboolean right_clicked(GtkWidget *, GdkEventButton *, gpointer); 

/* mount.c */
char *is_mounted(char *);
void mountfs(GtkMenuItem *, gpointer);
void unmountfs();
int vfs_usermount();
void usermount(char *, char *);

/* mainWindow.c */
/* int main() */
void top_window();
void scrolled();
void main_combo();

lang en;
lang de;
#endif
