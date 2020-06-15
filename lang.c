/* language related info */
#include "disk.h"


void en_lang() {

	strncpy(overview, "Overview - All Disks                                                  ", 65);
	strcpy(myarray[0], "Disk");
	strcpy(myarray[1], "Partition");
	strcpy(myarray[2], "Type");
	strcpy(myarray[3], "Size");
	strcpy(myarray[4], "File System");
	strcpy(myarray[5], "Label");
	strcpy(myarray[6], "Index");
	strcpy(myarray[7], "State");
	strcpy(myarray[8], "Attribute");
	strcpy(myarray[9], "Start");
	strcpy(myarray[10], "End");
	strcpy(myarray[11], "Length");
	strcpy(myarray[12], "Offset");
	strcpy(myarray[13], "Stripesize");
	strcpy(myarray[14], "Sectorsize");
	strcpy(myarray[15], "Stripeoffset");
	strcpy(myarray[16], "Efimedia");
	strcpy(myarray[17], "Rawuuid");
	strcpy(myarray[18], "Rawtype");
	strcpy(myarray[19], "first");
	strcpy(myarray[20], "Last");
	strcpy(myarray[21], "Entries");
	strcpy(myarray[22], "Modified");
	strcpy(myarray[23], "Mode");

	strncpy(tree_array[0], "Name", 10);
	strncpy(tree_array[1], "Description", 15);
	strncpy(tree_array[2], "Ident", 10);
	strncpy(tree_array[3], "Mediasize", 15);
	strncpy(tree_array[4], "Sectorsize", 15);
	strncpy(tree_array[5], "Mode", 10);
	strncpy(tree_array[6], "Rotationrate", 15);
	strncpy(tree_array[7], "fwsectors", 10);
	strncpy(tree_array[8], "fwheads", 10);
	
	/* optional fields */
	strncpy(tree_array[9], "Stripesize", 15);
	strncpy(tree_array[10], "Stripeoffset", 15);
	/*  lunid lun ... */

	strncpy(apply, "Apply!", 10);
	
	strcpy(mapplication, "_Application");
	strcpy(moptions, "_Options");
	strcpy(mrefresh, "Refresh");
	strcpy(mquit, "Quit");
	strcpy(mlanguage, "Language");
	strcpy(mfontinc, "Increase font size");
	strcpy(mfontdec, "Decrease font size");
	strcpy(mmsg, "Ask for Confirmation");
	strcpy(mshow, "yes");
	strcpy(mhide, "no");
	strcpy(medit, "Edit Disk");

	strcpy(chose_disk, "Choose a disk!");
	strcpy(chose_partition, "Choose a partition!");
	strcpy(chose_scheme, "Chose a scheme!");
	strcpy(chose_type, "Choose partition type!");
	strcpy(chose_size, "How big? Which size?");
	strcpy(chose_bootoptions, "Choose an attribute!");
}

void de_lang() {

	strncpy(overview, "Übersicht - Alle Disks                                        ", 65);
	
	strcpy(myarray[0], "Disk");
	strcpy(myarray[1], "Partition");
	strcpy(myarray[2], "Typ");
	strcpy(myarray[3], "Größe");
	strcpy(myarray[4], "Dateisystem");
	strcpy(myarray[5], "Label");
	strcpy(myarray[6], "Index");
	strcpy(myarray[7], "Status");
	strcpy(myarray[8], "Attribut");
	strcpy(myarray[9], "Start");
	strcpy(myarray[10], "Ende");
	strcpy(myarray[11], "Länge");
	strcpy(myarray[12], "Offset");
	strcpy(myarray[13], "Stripegröße");
	strcpy(myarray[14], "Sectorgröße");
	strcpy(myarray[15], "Stripeoffset");
	strcpy(myarray[16], "Efimedia");
	strcpy(myarray[17], "Rawuuid");
	strcpy(myarray[18], "Rawtype");
	strcpy(myarray[19], "Erster");
	strcpy(myarray[20], "Letzter");
	strcpy(myarray[21], "Einträge");
	strcpy(myarray[22], "Modifiziert");
	strcpy(myarray[23], "Modus");

	strncpy(tree_array[0], "Name", 10);
	strncpy(tree_array[1], "Beschreibung", 15);
	strncpy(tree_array[2], "Ident", 10);
	strncpy(tree_array[3], "Größe", 15);
	strncpy(tree_array[4], "Sectorgröße", 15);
	strncpy(tree_array[5], "Modus", 10);
	strncpy(tree_array[6], "Rotation", 15);
	strncpy(tree_array[7], "fwsectors", 10);
	strncpy(tree_array[8], "fwheads", 10);
	
	/* optional fields */
	strncpy(tree_array[9], "Plattengröße", 15);
	strncpy(tree_array[10], "Stripeoffset", 15);
	/*  lunid lun ... */
	
	strncpy(apply, "Los jetzt!", 10);
	
	strcpy(mapplication, "_Datei");
	strcpy(moptions, "_Optionen");
	strcpy(mrefresh, "Aktualisieren");
	strcpy(mquit, "Beenden");
	strcpy(mlanguage, "Sprache");
	strcpy(mfontinc, "Schrift vergrößern");
	strcpy(mfontdec, "Schrift verkleinern");
	strcpy(mmsg, "Bestätigung");
	strcpy(mshow, "ja");
	strcpy(mhide, "nein");
	strcpy(medit, "Editieren");

	strcpy(chose_disk, "Welche Disk?");
	strcpy(chose_partition, "Welche Partition?");
	strcpy(chose_scheme, "Welches Schema? Im Zweifel GPT!");
	strcpy(chose_type, "Welcher Partitionstyp?");
	strcpy(chose_size, "Wie groß?");
	strcpy(chose_bootoptions, "Welches Attribut?");
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
		while(n < MAX_D) {
			GtkTreeViewColumn   *col = gtk_tree_view_get_column( GTK_TREE_VIEW(tree), n);
			gtk_tree_view_column_set_title(col, tree_array[n]);
			n++;	
		}
	}
	else if(tree1 != NULL) {
		while(n <MAX_COLUMN) {
				GtkTreeViewColumn *col  = gtk_tree_view_get_column( GTK_TREE_VIEW(tree1), n);
				gtk_tree_view_column_set_title(col, myarray[n]);
				n++;	
		}
	}
}

void update_menubar_lang(int lang) {
	gtk_widget_destroy(menu);
	add_menubar();
}

