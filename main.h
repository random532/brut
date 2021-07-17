/*
 * TODO:
 * -Bugs?
 */
#pragma once

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


/* pci devices column header */
#define PCICOL 10 /* lol.. DEVCLASS */
char pcicol[PCICOL][20];

/* usb devices column header */
#define USBCOL 10
char usbcol[USBCOL][20];


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


	/* Global GUI elements  */
GtkWidget *window; 	/* main window */
GtkWidget *fixed;

/* More toplevel widgets */
GtkWidget *menubox;
GtkWidget *bback;
GtkWidget *logwindow;

/* All tabs */
GtkWidget *tabs;	/* GtkNotebook */
GtkWidget *tab0;	/* Control panel */
GtkWidget *tab1;	/* Disks */
GtkWidget *tab2;	/* Groups */
GtkWidget *tab3;	/* User */
GtkWidget *tab4;	/* Time */
GtkWidget *tab5;	/* About */
GtkWidget *tab6;	/* Tasks */
GtkWidget *tab7;	/* Config files */
GtkWidget *tab8;	/* Devices */
GtkWidget *tab9;	/* Wireless */
GtkWidget *tab10;	/* Ethernet */
GtkWidget *tab11;	/* Audio */

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
GtkWidget *devbox;		/* Devices */
GtkWidget *wbox;		/* Wireless */
GtkWidget *audiobox;	/* Audio */
GtkWidget *lanbox;		/* Ethernet */


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
	char mback[10];

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
	char cdevices[30];
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
	char cnetwork[20];
	char cwlan[30];
	char clan[35];
	char caudio[30];

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
	char tabdevices[20];
	char tabwlan[20];
	char tablan[10];
	char tabaudio[10];

} lang;
lang l;

	/* (most) functions */
//#ifndef FUNCTIONS_H_INCLUDED
//#define FUNCTIONS_H_INCLUDED

/* lang.c */
void en_lang();
void de_lang();

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

/* menubar.c */
void add_menubar();
void redraw_menubar();

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
void add_menubox();
void on_tabs_changed(GtkMenuItem *item, gpointer user_data);


/* groups.c */
void groups();
void execute_me(char *, int);

void about();	/* about.c */
void users();	/* user.c */
void tasks();	/* tasks.c */
void config();	/* config.c */
void devices();	/* devices.c */
void lan();		/* Ethernet */
void wireless();	/* wireless.c */
void AfterRootCmd();

void audio();	/* audio.c */
void cosmetics(char *); 

void control();		/* control.c */
void timetab();		/* time.c */

lang en;
lang de;
//#endif
