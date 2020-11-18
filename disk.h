/*
 * TODO:
 * -Doublecheck all buffers that handle user input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <inttypes.h>

#include <gtk/gtk.h>
#include <glib.h>

#define LANG_EN 0
#define LANG_DE 1

#define CMDSIZE 150
#define MAXLINE	250
#define ENTRY_MAX 8

	/* column header for 2 treeviews */
#define COLUMNS  27
char columns[COLUMNS][26];
#define COL 11
char column[COL][25];

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

	/* do we mount or gpart? Or something else? */
#define MOUNT	0
#define GPART	1
#define FS		3
#define USR 	4

int todo;

/* User tab treeview column header */
#define UCOL 16
char usercol[UCOL][25];

#define POS_UNAME		0
#define POS_UPASSWORD	1
#define POS_UGROUPID	2
#define POS_USERID		3
#define POS_UCLASS		4
#define POS_UNKNOWN2	5
#define POS_UNKNOWN3	6
#define POS_UDESC		7
#define POS_UHOME		8
#define POS_USHELL		9


/* Options */
struct {

	char fontsize[10];	/* font size */
	int language;		/* language */
	gboolean confirm;	/* ask for confirmation */
		
} opt;

	/* keep track of disks and partitions */
char *all_disks;
char *all_slices;
char *all_partitions;
char *slices_on_a_disk;

	/* Global GUI elements  */
GtkWidget *window; 	/* main window */
GtkWidget *fixed;

/* More toplevel widgets */
GtkWidget *menu;
GtkWidget *logwindow;

/* All tabs */
GtkWidget *tabs;
GtkWidget *tab0;
GtkWidget *tab1;
GtkWidget *tab2;
GtkWidget *tab3;
GtkWidget *tab4;
GtkWidget *tab5;
GtkWidget *tab6;
GtkWidget *tab7;

/* Each tab has one box that serves as a reference point. */
/* Global in case we redraw the tab. */
GtkWidget *controlbox;	/* Control */
GtkWidget *diskbox; 	/* Disks */
GtkWidget *abox;		/* About */
GtkWidget *userbox;		/* User */
GtkWidget *groupbox;	/* Groups */
GtkWidget *timebox;		/* Time */
GtkWidget *taskbox;		/* Tasks */
GtkWidget *configbox;	/* Config files */

/* More disk related widgets */

/* We generally try to avoid global pointers to Widgets
 * that only belong to one particular tab. */
GtkWidget *box;
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

/* Strings for different languages. */
typedef struct {
	
	char overview[85]; 

	/* menu bar items */
	char mapplication[20];
	char moptions[20];
	char mquit[20];
	char mrefresh[20];
	char mlanguage[20];
	char mmsg[25];
	char mshow[20]; //XXX: Obsolete?
	char mhide[20];
	char mfont[20];
	char mfontinc[25];
	char mfontdec[25];
	char medit[25];
	char mabort[15];

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

	/* Control panel */
	char ctitle[30];
	char chardware[20];
	char cdisks[30];
	char caccount[30];
	char cuser[30];
	char cgroups[30];
	char ctime1[40];
	char ctime2[30];
	char ctime3[40];
	char ctasks[30];
	char csystem[10];
	char cconfigfiles[40];
	char cabout[30];
	
	/* Group options */
	char gname[10];
	char gid[10];
	char gmember[15];
	char gpassword[20];
	
	char gnew[20];
	char gdel[20];
	char gadd[20];
	char gremove[20];
	
	char ginfodel[35];
	char ginfocreate[35];
	char ginfoadduser1[25];
	char ginfoadduser2[25];
	char ginforemuser1[25];
	char ginforemuser2[25];
	char ginfoclick[50];

	/* User tab menu options */
	char uadd[20];
	char uedit[20];
	char uremove[20];
	char uremove1[60];

	/* Time tab */
	char tsettime[20];
	char tsetzone[30];
	char tyear[10];
	char tmonth[10];
	char tday[10];
	char thour[10];
	char tminute[10];
	char tsecond[10];
	char ttimezone[20];
	char ttitle[30];
	char tsync[50];
	char ttooltip[40];

	/* config tab */
	char csave[15];
	char cfchose[30];

	/* About */
	char about[250];

	/* Tab names. */
	char tabcontrol[10];
	char tabdisks[10];
	char tabgroup[10];
	char tababout[10];
	char tabuser[10];
	char tabtime[10];
	char tabtasks[10];
	char tabconfig[10];
} lang;
lang l;

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
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/* lang.c */
void en_lang();
void de_lang();

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

/* subroutines.c */
char *get_disks();
char *read_disk(char *);
int add_slices();
int add_geoms();
int add_partitions();
void change_fontsize(gboolean);
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
char *get_partition_type(char *);
char *get_type(char *);
char *get_scheme(const gchar *);
char *random_filename();

/* root.c */
char *sudo(char *, char *, int);
int test_pw(char *);
void window_pw(char *);
int pw_needed();
char *sudo_backend(char *, char *);
void update_view();

/* editorWindow.c */
void editor();
void hide_widgets();

/* menubar.c */
void add_menubar();
void redraw_menubar();


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

/* mount.c */
char *is_mounted(char *);
char *is_mounted_fuse(char *);
void mountfs(GtkMenuItem *, gpointer);
void unmountfs();
int vfs_usermount();
void usermount(char *, char *);
int volume_cmp(char *, char *);

/* mainWindow.c */
/* int main() */
void top_window();
void on_tabs_changed(GtkMenuItem *item, gpointer user_data);

/* about.c */
void about();

/* groups.c */
void groups();
void execute_me(char *, int);

/* user.c */
void users();

/* tasks */
void tasks();

/* config files */
void config();

/* disk.c */
void redraw_cb (GtkMenuItem *, gpointer);
void scrolled();
void main_combo();
void disk();

void control();		/* control.c */
void timetab();		/* time.c */

lang en;
lang de;
#endif
