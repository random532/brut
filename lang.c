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
	strcpy(columns[POS_DISK], "Disk");
	strcpy(columns[POS_PART], "Partition");
	strcpy(columns[POS_TYPE], "Type");
	strcpy(columns[POS_SIZE], "Size");
	strcpy(columns[POS_LABEL], "Label");
	strcpy(columns[POS_FS], "File System");
	strcpy(columns[POS_FSLABEL], "FSLabel");
	strcpy(columns[POS_MOUNTP], "Mountpoint");
	strcpy(columns[POS_CAPACITY], "Capacity");
	strcpy(columns[POS_ATTR], "Attribute");
	strcpy(columns[POS_STATE], "State");
	strcpy(columns[POS_START], "Start");
	strcpy(columns[POS_END], "End");
	strcpy(columns[POS_LEN], "Length");
	strcpy(columns[POS_OFFSET], "Offset");
	strcpy(columns[POS_STRIPESIZE], "Stripesize");
	strcpy(columns[POS_SECTORSIZE], "Sectorsize");
	strcpy(columns[POS_STRIPEOFFSET], "Stripeoffset");
	strcpy(columns[POS_EFIMEDIA], "Efimedia");
	strcpy(columns[POS_RAWUUID], "Rawuuid");
	strcpy(columns[POS_RAWTYPE], "Rawtype");
	strcpy(columns[POS_FIRST], "first");
	strcpy(columns[POS_LAST], "Last");
	strcpy(columns[POS_ENTRIES], "Entries");
	strcpy(columns[POS_MODIFIED], "Modified");
	strcpy(columns[POS_MODE], "Mode");
	strcpy(columns[POS_INDEX], "Index");
	
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
	strcpy(columns[POS_DISK], "Disk");
	strcpy(columns[POS_PART], "Partition");
	strcpy(columns[POS_TYPE], "Typ");
	strcpy(columns[POS_SIZE], "Größe");
	strcpy(columns[POS_LABEL], "Label");
	strcpy(columns[POS_FSLABEL], "DSLabel");
	strcpy(columns[POS_FS], "Dateisystem");
	strcpy(columns[POS_MOUNTP], "Mountpoint");
	strcpy(columns[POS_CAPACITY], "Kapazität");
	strcpy(columns[POS_ATTR], "Attribute");
	strcpy(columns[POS_STATE], "Status");
	strcpy(columns[POS_START], "Start");
	strcpy(columns[POS_END], "Ende");
	strcpy(columns[POS_LEN], "Länge");
	strcpy(columns[POS_OFFSET], "Offset");
	strcpy(columns[POS_STRIPESIZE], "Stripegröße");
	strcpy(columns[POS_SECTORSIZE], "Sectorgröße");
	strcpy(columns[POS_STRIPEOFFSET], "Stripeoffset");
	strcpy(columns[POS_EFIMEDIA], "Efimedia");
	strcpy(columns[POS_RAWUUID], "Rawuuid");
	strcpy(columns[POS_RAWTYPE], "Rawtype");
	strcpy(columns[POS_FIRST], "Erster");
	strcpy(columns[POS_LAST], "Letzter");
	strcpy(columns[POS_ENTRIES], "Einträge");
	strcpy(columns[POS_MODIFIED], "Modifiziert");
	strcpy(columns[POS_MODE], "Modus");
	strcpy(columns[POS_INDEX], "Index");

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
