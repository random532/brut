/* language related info */
#include "disk.h"


void en_lang() {


	strcpy(myarray[0], "Disk");
	strcpy(myarray[1], "Index");
	strcpy(myarray[2], "Partition");
	strcpy(myarray[3], "Type");
	strcpy(myarray[4], "Size");
	strcpy(myarray[5], "State");
	strcpy(myarray[6], "File System");
	strcpy(myarray[7], "Label");
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

	strcpy(myarray[19], "fwheads");
	strcpy(myarray[20], "fwsectors");
	strcpy(myarray[21], "first");
	strcpy(myarray[22], "Last");
	strcpy(myarray[23], "Entries");
	strcpy(myarray[24], "Modified");
	strcpy(myarray[25], "Mode");




	strcpy(mapplication, "_Application");
	strcpy(moptions, "_Options");
	strcpy(mview, "_View");
	strcpy(mrefresh, "Refresh");
	strcpy(mquit, "Quit");
	strcpy(mlanguage, "Language");
	strcpy(mall, "View all");
	strcpy(mless, "View less");
	strcpy(mfontinc, "Increase font size");
	strcpy(mfontdec, "Decrease font size");
	strcpy(mmsg, "Gpart commands");
	strcpy(mshow, "show");
	strcpy(mhide, "hide");
	strcpy(medit, "Edit Disk");

	strcpy(chose_disk, "Choose a disk!");
	strcpy(chose_partition, "Choose a partition!");
	strcpy(chose_scheme, "Chose a scheme!");
	strcpy(chose_type, "Choose partition type!");
	strcpy(chose_size, "How big? Which size?");
	strcpy(chose_bootoptions, "Choose an attribute!");
}

void de_lang() {

	strcpy(myarray[0], "Disk");
	strcpy(myarray[1], "Index");
	strcpy(myarray[2], "Partition");
	strcpy(myarray[3], "Typ");
	strcpy(myarray[4], "Größe");
	strcpy(myarray[5], "Status");
	strcpy(myarray[6], "Dateisystem");
	strcpy(myarray[7], "Label");
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

	strcpy(myarray[19], "fwheads");
	strcpy(myarray[20], "fwsectors");
	strcpy(myarray[21], "Erster");
	strcpy(myarray[22], "Letzter");
	strcpy(myarray[23], "Einträge");
	strcpy(myarray[24], "Modifiziert");
	strcpy(myarray[25], "Modus");

	strcpy(mapplication, "_Datei");
	strcpy(moptions, "_Optionen");
	strcpy(mview, "_Ansicht");
	strcpy(mrefresh, "Ansicht aktualisieren");
	strcpy(mquit, "Beenden");
	strcpy(mlanguage, "Sprache");
	strcpy(mall, "Alle anzeigen");
	strcpy(mless, "Weniger anzeigen");
	strcpy(mfontinc, "Schrift vergrößern");
	strcpy(mfontdec, "Schrift verkleinern");
	strcpy(mmsg, "Gpart Befehl");
	strcpy(mshow, "anzeigen");
	strcpy(mhide, "verstecken");
	strcpy(medit, "Festplatte editieren");

	strcpy(chose_disk, "Welche Disk?");
	strcpy(chose_partition, "Welche Partition?");
	strcpy(chose_scheme, "Welches Schema? Im Zweifel GPT!");
	strcpy(chose_type, "Welcher Partitionstyp?");
	strcpy(chose_size, "Wie groß?");
	strcpy(chose_bootoptions, "Welches Attribut?");
}

void update_column_lang(int lang) {

	if (lang == 0)
		de_lang();
	else if (lang == 1)
		en_lang();

	int n =0;
	while(n <MAX_COLUMN) {
	GtkTreeViewColumn   *col = gtk_tree_view_get_column( GTK_TREE_VIEW(tree), n);
	gtk_tree_view_column_set_title(col, myarray[n]);
	n++;	
	}
}

void update_menubar_lang(int lang) {
	gtk_widget_destroy(menu);
	add_menubar();
}

