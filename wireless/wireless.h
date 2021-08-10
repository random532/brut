
#pragma once

/* Boxes */
GtkWidget *topbox;
GtkWidget *botbox;
GtkWidget *wedit;
GtkWidget *woptions;

/* Widgets */
GtkWidget *wcommands;
GtkWidget *winterface;	/* interfaces */
GtkWidget *wdev;		/* devices */
GtkWidget *wapply;


GtkWidget *whosts;		/* access points */
GtkWidget *wpass;		/* WPA Passphrase */
GtkWidget *toggle_encrypted; /* WPA2 encryption */
GtkWidget *customAP;	/* access point */

/*Widgets for Modify */
GtkWidget *modsw;
GtkWidget *modgrid;
GtkWidget *wregdomain;
GtkWidget *wcountry;
GtkWidget *winet;
GtkWidget *wmodes;		/* modes */
GtkWidget *w11g;
GtkWidget *wdebug;
GtkWidget *wpower;

#define W_POS_REGDOMAIN	0
#define W_POS_COUNTRY	1
#define W_POS_INET		2
#define W_POS_11G		3
#define W_POS_POWER		0
#define W_POS_DEBUG		1

GtkTreeStore *wtree;

/* In case we issue a second root command. */
gboolean exec2; /* Execute another command. */
char *secondcmd;
char *wtmp; /* Tmpfile */

/* Functions */
void CleanWireless();
GtkWidget *WScrolled(GtkWidget *);
GtkWidget *ComboWlanDevices();
GtkWidget *ComboWlanInterfaces();
GtkWidget *DrawHosts();
void ShowOptions(char *);
void command_changed( GtkWidget *, gpointer);
void winterface_changed( GtkWidget *, gpointer);
//void AfterRootCmd();
void wireless();
//void AP_changed( GtkWidget *, gpointer);
//void encrypted_changed( GtkWidget *, gpointer);


// Apply Clicked
void ApplyClicked( GtkWidget *, gpointer);
