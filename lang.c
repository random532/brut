/* language related info */
#include "disk.h"

lang en = {
	.overview="Overview - All Disks                                                  ", 

	/* menu bar items */
	.mapplication="_Application",
	.moptions="_Options",
	.mquit="_Quit",
	.mrefresh="Refresh",
	.mlanguage="_Language",
	.mmsg="_Ask for Confirmation",
	.mshow="_Yes",
	.mhide="_No",
	.mfontinc="_Increase font size",
	.mfontdec="_Decrease font size",
	.medit="Editor",

	/* hints */
	.no_root="no Root! Sorry.",
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
	.mother="Other Location"
};

lang de = {
	.overview="Übersicht - Alle Disks                                        ", 

	/* menu bar items */
	.mapplication="_Programm",
	.moptions="_Optionen",
	.mquit="_Beenden",
	.mrefresh="Aktualisieren",
	.mlanguage="_Sprache",
	.mmsg="_Immer nachfragen",
	.mshow="_Ja",
	.mhide="_Nein",
	.mfontinc="Schrift ver_größern",
	.mfontdec="Schrift ver_kleinern",
	.medit="Editor",

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
	.mother="Anderer Ort"
};


void en_lang() {

	l = en;
	/* column header */
	strcpy(columns[0], "Disk");
	strcpy(columns[1], "Partition");
	strcpy(columns[2], "Type");
	strcpy(columns[3], "Size");
	strcpy(columns[4], "File System");
	strcpy(columns[5], "Label");
	strcpy(columns[6], "Attribute");
	strcpy(columns[7], "State");
	strcpy(columns[8], "Index");
	strcpy(columns[9], "Start");
	strcpy(columns[10], "End");
	strcpy(columns[11], "Length");
	strcpy(columns[12], "Offset");
	strcpy(columns[13], "Stripesize");
	strcpy(columns[14], "Sectorsize");
	strcpy(columns[15], "Stripeoffset");
	strcpy(columns[16], "Efimedia");
	strcpy(columns[17], "Rawuuid");
	strcpy(columns[18], "Rawtype");
	strcpy(columns[19], "first");
	strcpy(columns[20], "Last");
	strcpy(columns[21], "Entries");
	strcpy(columns[22], "Modified");
	strcpy(columns[23], "Mode");

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
	strcpy(columns[4], "Dateisystem");
	strcpy(columns[5], "Label");
	strcpy(columns[6], "Attribut");
	strcpy(columns[7], "Status");
	strcpy(columns[8], "Index");
	strcpy(columns[9], "Start");
	strcpy(columns[10], "Ende");
	strcpy(columns[11], "Länge");
	strcpy(columns[12], "Offset");
	strcpy(columns[13], "Stripegröße");
	strcpy(columns[14], "Sectorgröße");
	strcpy(columns[15], "Stripeoffset");
	strcpy(columns[16], "Efimedia");
	strcpy(columns[17], "Rawuuid");
	strcpy(columns[18], "Rawtype");
	strcpy(columns[19], "Erster");
	strcpy(columns[20], "Letzter");
	strcpy(columns[21], "Einträge");
	strcpy(columns[22], "Modifiziert");
	strcpy(columns[23], "Modus");

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
