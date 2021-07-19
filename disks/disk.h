#pragma once

#include "../brut.h"

//#ifndef DISKS_INCL
//#define DISKS_INCL

/* column header for 2 disk treeviews */
#define COLUMNS  27
char columns[COLUMNS][26];
#define COL 11
char column[COL][25];


/* Treeview column positions */
#define POS_DISK	0
#define POS_PART	1
#define POS_TYPE	2
#define POS_SIZE	3
#define POS_LABEL	4
#define POS_FS		5
#define POS_FSLABEL	6
#define POS_MOUNTP	7
#define POS_CAPACITY 8
#define POS_ATTR	9
#define POS_STATE	10
#define POS_START	11
#define POS_END		12
#define POS_LEN		13
#define POS_OFFSET	14
#define POS_STRIPESIZE 15
#define POS_SECTORSIZE 16
#define POS_STRIPEOFFSET 17
#define POS_EFIMEDIA 18
#define POS_RAWUUID	19
#define POS_RAWTYPE 20
#define POS_FIRST	21
#define POS_LAST	22
#define POS_ENTRIES	23
#define POS_MODIFIED 24
#define POS_MODE	25
#define POS_INDEX	26


	/* keep track of disks and partitions */
char *all_disks;
char *all_slices;
char *all_partitions;
char *slices_on_a_disk;


GtkWidget *box; // XXX: Make this global?
GtkWidget *scrolled_window;
GtkWidget *combo_toplevel;
GtkWidget *tree;		/* all disks are displayed here */
GtkWidget *tree1;		/* only one disk is displayed here */
GtkTreeStore *treestore;
GtkTreeStore *treestore1;	
GtkCellRenderer *cell;
GtkCellRenderer *cellr;

GtkWidget *thegrid;
GtkWidget *grid;
GtkWidget *b;
GtkWidget *su;

/* all items in the grid/editor window */
GtkWidget *editor_sep;
GtkWidget *editor_label;
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
GtkWidget *toggle_ask;
GtkWidget *gfile;


typedef struct {

char *next_partition;

char *name;
char *name_capital;
char *mediasize;
char *sectorsize;
char *type;
char *start;
char *end;
char *end_old;
char *state;
char *entries;
char *scheme;
char *first;
char *last;
char *modified;
char *stripesize;
char *stripeoffset;
char *mode;
char *efimedia;
char *rawuuid;
char *rawtype;
char *length;
char *offset;
char *label;
char *index;
char *filesystem;
char *attribute;
char *mountpoint;
char *capacity;
char *fslabel;

char *consumer_mediasize;
char *consumer_mode;
char *consumer_sectorsize;

} geom_data;
geom_data g;

	/* (most) functions */

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
void create_toggle_buttons();
void grid_attach_all();
void add_types( char *);

/* on_combos_changed.c */
void on_geom_changed();
void on_toplevel_changed();
void on_fs_changed();
void toplevel_entries();
void on_bootcode_changed();
void on_disks_changed();
void on_partitions_changed();
void on_scheme_changed();

/* editorWindow.c */
void editor();
void hide_widgets();

/* applyButtonClicked.c */
void on_edit_clicked (GtkMenuItem *, gpointer);
const char *get_combo_box_disk(int);
const char *get_combo_box_scheme();
char *get_combo_box_partition(int);
const char *get_combo_box_type(int);
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
GtkWidget *create_treeview();
GtkWidget *create_treeview1();
int populate_treeview();
int populate_treeview1(char *);
void treeview_add_rows(char *, char *);
char *selected_item(GtkWidget *, int);
gboolean right_clicked(GtkWidget *, GdkEventButton *, gpointer); 
int buf_to_struct(char *);
void g_zero();
char *get_capacity(char *);
char *get_label(char *, char *);

//#endif
