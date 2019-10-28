
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

 #define DEBUG

#ifdef DEBUG
	#define D
#else
	#define D for(;0;)
#endif

//D prrintf(...);

#define TT printf("test statement\n\n\n");

//dbus-uuidgen --ensure


	/* Global variables */

	/* main windows, containers */
GtkWidget	*window;
GtkWidget	*fixed1;
GtkWidget	*fixed2;
GtkWidget	*fixed3;
GtkWidget	*fixed4;

GtkWidget	*scrolled3;
 
	/* the grids */
GtkWidget	*grid1;	/* disk overview */
int row1;	 		/* number of rows*/
GtkWidget	*grid2;  /**/
GtkWidget	*grid3;  /**/


GtkTreeView *tree1;	 	/* vendor description */
GtkTreeStore *treestore1;
GtkTreeViewColumn *c1;
GtkTreeViewColumn *c2;

GtkCellRenderer	*cr1;
GtkCellRenderer	*cr2;

GtkTreeView *tree2;	 	/* disk labels */
GtkTreeStore *treestore2;
GtkTreeViewColumn *c3;
GtkTreeViewColumn *c4;
GtkTreeViewColumn *c5;

GtkCellRenderer	*cr3;
GtkCellRenderer	*cr4;
GtkCellRenderer	*cr5;

GtkTreeIter iter;
GtkTreeIter iter2;


	/* various combo boxes */
GtkWidget *combo1;
GtkWidget *combo4;
GtkWidget *combo5;
GtkWidget *combo6;
GtkWidget *combo7;

GtkWidget	*combo_disks;
GtkWidget	*combo_types;
GtkWidget	*combo_fs;
GtkWidget	*combo_s;

	 /* text entries */
GtkWidget *entry4;
GtkWidget *entry5;
GtkWidget *entry6;
GtkWidget *entry7;
GtkWidget *entry9;

	 /* file chooser */
GtkWidget	*file1;
GtkWidget	*file2;

GtkBuilder	*builder;


#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
// function prototypes
void combo_typ();
void combo_d();
void fchose_combo();
void disk_combo();
void fs_combo();
void combo_set_unset();

void on_button_quit_clicked(GtkButton *b);
void on_response(GtkDialog *dialog, gint response_id, gpointer user_data);
void on_buttonview1_clicked(GtkButton *b);
void on_fwrite1_clicked(GtkButton *b);
void on_gpart_refresh_clicked(GtkButton *b);
void on_gpart_submit_clicked(GtkButton *b);

void hide_all();
char * parse_gpart();
void msg(char * blah);
int camcontrol();
int glabel();
int exe(char * cmd);
void add_missing();
void on_gpart_combo_changed(GtkWidget *b);
#endif
