
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
GtkWidget *wmodes;		/* modes */
GtkWidget *wpass;		/* WPA Passphrase */
GtkWidget *toggle_encrypted; /* WPA2 encryption */
GtkWidget *customAP;	/* access point */

/*Widgets for Modify */
GtkWidget *modsw;
GtkWidget *modgrid;

GtkWidget * wregdomain;
GtkWidget * wcountry;

#define W_POS_REGDOMAIN	0
#define W_POS_COUNTRY	1
#define W_POS_WOL		2


GtkTreeStore *wtree;

/* In case we issue a second root command. */
gboolean exec2; /* Execute another command. */
char *secondcmd;
char *wtmp; /* Tmpfile */

/* Functions */
void CleanWireless();
void CleanOptions();
void WTopbox();
GtkWidget *WScrolled(GtkWidget *);
GtkWidget *ComboModes();
GtkWidget *ComboCommands();
GtkWidget *ComboWlanDevices();
GtkWidget *ComboWlanInterfaces();
void WGridEntries();
char *GetBssid(char *);
char *GetSsid(char *);
void OptionsCreate();
void OptionsConnect();
void OptionsModify();
gboolean ComboAP();
GtkWidget *DrawHosts();
void ShowOptions(char *);
void command_changed( GtkWidget *, gpointer);
void winterface_changed( GtkWidget *, gpointer);
void WEditor();
void WBottomView();
GtkWidget *WTreeview(GtkWidget *);
void WFillTree(GtkWidget *);
void AfterRootCmd();
void wireless();
void AP_changed( GtkWidget *, gpointer);
void encrypted_changed( GtkWidget *, gpointer);


// Apply Clicked
void ApplyClicked( GtkWidget *, gpointer);
void ExecCreate();
void ExecDestroy();
void ExecConnect();
void ExecUp();
void ExecDown();
void ExecScan();
void ExecModify();
