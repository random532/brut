/* language related info */
#include "disk.h"

lang en = {
	.overview="Overview - All Disks                                                  ", 

	/* menu bar items */
	.mapplication="_Application",
	.moptions="_Options",
	.mquit="_Quit",
	.mrefresh="_Refresh",
	.mlanguage="_Language",
	.mmsg="_Ask for Confirmation",
	.mshow="_Yes",
	.mhide="_No",
	.mfont="_Font size",
	.mfontinc="_Increase",
	.mfontdec="_Decrease",
	.medit="_Editor",

	/* hints */
	.no_root="not Root! Sorry.",
	.chose_disk="Choose a disk!",
	.chose_partition="Choose a partition!",
	.chose_scheme="Choose a scheme!",
	.chose_type="Choose a type!",
	.chose_size="How big? What size?",
	.chose_bootoptions="Choose an attribute",
	.chose_fs="Choose a file system!",
	.apply="_Apply!",
	.mdone="Done.",
	.merror="Command failed.",
	.mother="Other Location",
	.mrescan="Show Filesystems",
	.mpassw="Enter your sudo password!",
	.mexplain="This command needs higher privileges.",
	.mhello1="Hello! Please report bugs here:",
	.mhello="github.com/random532/xdisk/issues"
};

lang de = {
	.overview="Übersicht - Alle Disks                                        ", 

	/* menu bar items */
	.mapplication="_Programm",
	.moptions="_Optionen",
	.mquit="_Beenden",
	.mrefresh="_Aktualisieren",
	.mlanguage="_Sprache",
	.mmsg="_Immer nachfragen",
	.mshow="_Ja",
	.mhide="_Nein",
	.mfont="_Schriftgröße",
	.mfontinc="ver_größern",
	.mfontdec="ver_kleinern",
	.medit="_Editor",

	/* hints */
	.no_root="Du bist kein Root. Sorry.",
	.chose_disk="Welche Disk?",
	.chose_partition="Welche Partition?",
	.chose_scheme="Welches Schema?",
	.chose_type="Welcher Typ?",
	.chose_size="Wie groß?",
	.chose_bootoptions="Welches Attribut?",
	.chose_fs="Welches Dateisystem?",
	.apply="_Los jetzt!",
	.mdone="Fertig.",
	.merror="Befehl fehlgeschlagen.",
	.mother="Anderer Ort",
	.mrescan="Zeige Dateisysteme",
	.mpassw="Geben Sie Ihr Sudo Passwort ein!",
	.mexplain="Dieser Befehl braucht mehr Berechtigungen.",
	.mhello1="Hallo! Bitte melde Bugs hier:",
	.mhello="github.com/random532/xdisk/issues"
};

void en_lang() {

	l = en;	
	/* column header */
	strcpy(columns[0], "Disk");
	strcpy(columns[1], "Partition");
	strcpy(columns[2], "Type");
	strcpy(columns[3], "Size");
	strcpy(columns[4], "Label");
	strcpy(columns[5], "File System");
	strcpy(columns[6], "FSLabel");
	strcpy(columns[7], "Mountpoint");
	strcpy(columns[8], "Capacity");
	strcpy(columns[9], "Attribute");
	strcpy(columns[10], "State");
	strcpy(columns[11], "Start");
	strcpy(columns[12], "End");
	strcpy(columns[13], "Length");
	strcpy(columns[14], "Offset");
	strcpy(columns[15], "Stripesize");
	strcpy(columns[16], "Sectorsize");
	strcpy(columns[17], "Stripeoffset");
	strcpy(columns[18], "Efimedia");
	strcpy(columns[19], "Rawuuid");
	strcpy(columns[20], "Rawtype");
	strcpy(columns[21], "first");
	strcpy(columns[22], "Last");
	strcpy(columns[23], "Entries");
	strcpy(columns[24], "Modified");
	strcpy(columns[25], "Mode");
	strcpy(columns[26], "Index");
	
	strncpy(column[0], "Name", 10);
	strncpy(column[1], "Description", 15);
	strncpy(column[2], "Ident", 10);
	strncpy(column[3], "Mediasize", 15);
	strncpy(column[4], "Sectorsize", 15);
	strncpy(column[5], "Mode", 10);
	strncpy(column[6], "Rotationrate", 15);
	strncpy(column[7], "fwsectors", 10);
	strncpy(column[8], "fwheads", 10);
	strncpy(column[9], "Stripesize", 15);
	strncpy(column[10], "Stripeoffset", 15);
	/*  lunid lun ... */
}

void de_lang() {

	l=de;
	strcpy(columns[0], "Disk");
	strcpy(columns[1], "Partition");
	strcpy(columns[2], "Typ");
	strcpy(columns[3], "Größe");
	strcpy(columns[4], "Label");
	strcpy(columns[5], "DSLabel");
	strcpy(columns[6], "Dateisystem");
	strcpy(columns[7], "Mountpoint");
	strcpy(columns[8], "Kapazität");
	strcpy(columns[9], "Attribute");
	strcpy(columns[10], "Status");
	strcpy(columns[11], "Start");
	strcpy(columns[12], "Ende");
	strcpy(columns[13], "Länge");
	strcpy(columns[14], "Offset");
	strcpy(columns[15], "Stripegröße");
	strcpy(columns[16], "Sectorgröße");
	strcpy(columns[17], "Stripeoffset");
	strcpy(columns[18], "Efimedia");
	strcpy(columns[19], "Rawuuid");
	strcpy(columns[20], "Rawtype");
	strcpy(columns[21], "Erster");
	strcpy(columns[22], "Letzter");
	strcpy(columns[23], "Einträge");
	strcpy(columns[24], "Modifiziert");
	strcpy(columns[25], "Modus");
	strcpy(columns[26], "Index");

	strncpy(column[0], "Name", 10);
	strncpy(column[1], "Beschreibung", 15);
	strncpy(column[2], "Ident", 10);
	strncpy(column[3], "Größe", 15);
	strncpy(column[4], "Sectorgröße", 15);
	strncpy(column[5], "Modus", 10);
	strncpy(column[6], "Rotation", 15);
	strncpy(column[7], "fwsectors", 10);
	strncpy(column[8], "fwheads", 10);	
	strncpy(column[9], "Stripesize", 15);
	strncpy(column[10], "Stripeoffset", 15);
}

void update_column_lang(int lang) {

	/* first update arrays */
	if (lang == LANG_DE)
		de_lang();
	else if (lang == LANG_EN)
		en_lang();

	/* second update columns */
	int n =0;
	if(tree != NULL) {
		while(n < COL) {
			GtkTreeViewColumn   *col = gtk_tree_view_get_column( GTK_TREE_VIEW(tree), n);
			gtk_tree_view_column_set_title(col, column[n]);
			n++;	
		}
	}
	else if(tree1 != NULL) {
		while(n <COLUMNS) {
			GtkTreeViewColumn *col  = gtk_tree_view_get_column( GTK_TREE_VIEW(tree1), n);
			gtk_tree_view_column_set_title(col, columns[n]);
			n++;	
		}
	}
}

void update_menubar_lang(int lang) {
	gtk_widget_destroy(menu);
	add_menubar();
}
