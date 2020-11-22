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
	.mmsg="ask for confirmation",
	.mshow="_Yes",
	.mhide="_No",
	.mfont="_Font size",
	.mfontinc="_Increase",
	.mfontdec="_Decrease",
	.medit="_Editor",
	.mabort="Cancel",
	.mback="Back",

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

	/* Control Panel */
	.ctitle="<b>Control Panel</b>",
	.chardware="Hardware",
	.cdisks="<a href=\" \"> Disks</a>",
	.cdevices="<a href=\" \"> Devices</a>",
	.caccount="Accounts",
	.cuser="<a href=\" \"> User</a>",
	.cgroups="<a href=\" \"> Groups</a>",
	.ctime1="Date, Time, Jobs",
	.ctime2="<a href=\" \"> Date/Time</a>",
	.ctime3="Date, Time, Timezone",
	.ctasks="<a href=\" \"> cron</a>",
	.csystem="System",
	.cconfigfiles="<a href=\" \"> Config files</a>",
	.cabout="<a href=\" \"> About</a>",
	.cnetwork="Network",
	.cwlan="<a href=\" \"> Wireless</a>",
	.clan="<a href=\" \"> Ethernet</a>",
	.caudio="<a href=\" \"> Sound</a>",


	/* groups */
	.gname="Name",
	.gpassword="Password",
	.gmember="Members",
	.gid="ID",
	
	.gnew="New group",
	.gdel="Delete group",
	.gadd="Add user",
	.gremove="Remove user",

	.ginfodel="Delete this group?",
	.ginfocreate="Create new group?",
	.ginfoadduser1="Add user:",
	.ginfoadduser2="To this group?",
	.ginforemuser1="Remove user:",
	.ginforemuser2="From this group?",
	.ginfoclick="Right click on a group!",
	
	/* User tab menu */
	.uadd="Add",
	.uedit="Modify",
	.uremove="Remove",
	.uremove1="Delete this user, including home directory?",

	/* Time */
	.tsettime="Set time",
	.tsetzone="Set timezone",
	.tyear="year",
	.tmonth="month",
	.tday="day",
	.thour="hour",
	.tminute="minute",
	.tsecond="second",
	.ttimezone="Timezone",
	.ttitle="Clock, Date, Timezone",
	.tsync="Synchronize with network time, once:",
	.ttooltip="Takes effect after next logout/login",

	/* Config */
	.csave="Save",
	.cfchose="Choose a file",

	/* About */
	.about="Hello.\n\nThis program makes use of GTK (GIMP Toolkit). See: www.gtk.org\n\
For bugs, questions, feedback, open an issue here: github.com/random532/brut/issues\n\
Have fun,\nBrut.\n",

	/* Tabs */
	.tabcontrol="Control",
	.tabdisks="Disks",
	.tababout="About",
	.tabgroup="Groups",
	.tabuser="User",
	.tabtime="Time",
	.tabtasks="Tasks",
	.tabconfig="Config",
	.tabdevices="Devices",
	.tabwlan="Wireless",
	.tablan="Ethernet",
	.tabaudio="Sound"

};

lang de = {
	.overview="Übersicht - Alle Disks                                        ", 

	/* menu bar items */
	.mapplication="_Programm",
	.moptions="_Optionen",
	.mquit="_Beenden",
	.mrefresh="_Aktualisieren",
	.mlanguage="_Sprache",
	.mmsg="Nachfragen",
	.mshow="_Ja",
	.mhide="_Nein",
	.mfont="_Schriftgröße",
	.mfontinc="ver_größern",
	.mfontdec="ver_kleinern",
	.medit="_Editor",
	.mabort="Abbrechen",
	.mback="Zurück",

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

	/* Control Panel */
	.ctitle="<b>Systemsteuerung</b>",
	.chardware="Hardware",
	.cdisks="<a href=\" \"> Disks</a>",
	.cdevices="<a href=\" \"> Geräte</a>",
	.caccount="Accounts",
	.cuser="<a href=\" \"> Benutzer</a>",
	.cgroups="<a href=\" \"> Gruppen</a>",
	.ctime1="Uhrzeit, Datum, Jobs",
	.ctime2="<a href=\" \"> Zeit</a>",
	.ctime3="Uhrzeit, Datum, Zeitzone",
	.ctasks="<a href=\" \"> Cron</a>",
	.csystem="System",
	.cconfigfiles="<a href=\" \"> Konfigurations Dateien</a>",
	.cabout="<a href=\" \"> Über</a>",
	.cnetwork="Netzwerk",
	.cwlan="<a href=\" \"> WLAN</a>",
	.clan="<a href=\" \"> LAN</a>",
	.caudio="<a href=\" \"> Sound</a>",

	/* groups */
	.gname="Name",
	.gpassword="Passwort",
	.gmember="Teilnehmer",
	.gid="ID",

	.gnew="Neue Gruppe",
	.gdel="Lösche Gruppe",
	.gadd="User dazu",
	.gremove="User rausnehmen",
	
	.ginfodel="Diese Gruppe löschen?",
	.ginfocreate="Neue Gruppe erstellen?",
	.ginfoadduser1="Adde den Benutzer:",
	.ginfoadduser2="Zur dieser Gruppe?",
	.ginforemuser1="Entferne den Benutzer:",
	.ginforemuser2="Von dieser Gruppe?",
	.ginfoclick="Rechtsclick auf eine Gruppe!",

	/* User tab */
	.uadd="Neu",
	.uedit="Ändern",
	.uremove="Entfernen",
	.uremove1="Benutzer entfernen (inklusive Heimatverzeichnis)?",

	/* Time */
	.tsettime="Uhrzeit einstellen",
	.tsetzone="Zeitzone festlegen",
	.tyear="Jahr",
	.tmonth="Monat",
	.tday="Tag",
	.thour="Stunde",
	.tminute="Minute",
	.tsecond="Sekunde",
	.ttimezone="Zeitzone",
	.ttitle="Uhrzeit, Datum, Zeitzone",
	.tsync="Zeit aus dem Netzwerk beziehen, einmalig",
	.ttooltip="Erfordert logout/login",

	/* Config */
	.csave="Speichern",
	.cfchose="Wähle eine Datei",

	/* About tab */
	.about="Hallo.\n\nDieses Programm benutzt GTK (GIMP Toolkit). Siehe: www.gtk.org\n\
Bei Bugs, Fragen, Problemen, öffne ein Problemreport: github.com/random532/brut/issues\n\
Viel Spass,\nBrut.\n",

	/* Tabs */
	.tabcontrol="System",
	.tabdisks="Disks",
	.tababout="Über",
	.tabgroup="Gruppen",
	.tabuser="Benutzer",
	.tabtime="Uhrzeit",
	.tabtasks="Aufgaben",
	.tabconfig="Konfig",
	.tabdevices="Hardware",
	.tabwlan="Wlan",
	.tablan="LAN",
	.tabaudio="Sound"
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
	
	/* User tab treeview. */
	strcpy(usercol[POS_UNAME], "Name");
	strcpy(usercol[POS_UPASSWORD],"PW");
	strcpy(usercol[POS_UCLASS], "Class");
	strcpy(usercol[POS_UGROUPID], "GroupID");
	strcpy(usercol[POS_USERID], "UserID");
	strcpy(usercol[POS_UNKNOWN2], "--");
	strcpy(usercol[POS_UNKNOWN3], "--");
	strcpy(usercol[POS_UDESC], "Full Name");
	strcpy(usercol[POS_UHOME], "Home directory");
	strcpy(usercol[POS_USHELL], "Login Shell");


	/* Pci devices columns */
	strcpy(pcicol[0], "Name");
	strcpy(pcicol[1], "Description");
	strcpy(pcicol[2], "Vendor");
	strcpy(pcicol[3], "Card");
	strcpy(pcicol[4], "Chip");
	strcpy(pcicol[5], "Slot");
	strcpy(pcicol[6], "Class");
	strcpy(pcicol[7], "Class");
	strcpy(pcicol[8], "Sublass");
	strcpy(pcicol[9], "--");
	
	/* Usb device columns */
	strcpy(usbcol[0], "Name");
	strcpy(usbcol[1], "Description");
	strcpy(usbcol[2], "Bus");
	strcpy(usbcol[3], "cfg");
	strcpy(usbcol[4], "Mode");
	strcpy(usbcol[5], "Speed");
	strcpy(usbcol[6], "Power");
	strcpy(usbcol[7], "Power2");
	strcpy(usbcol[8], "empty");
	strcpy(usbcol[9], "empty");

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
	
	/* User tab treeview. */
	strcpy(usercol[POS_UNAME], "Name");
	strcpy(usercol[POS_UPASSWORD],"PW");
	strcpy(usercol[POS_UCLASS], "Login-Klasse");
	strcpy(usercol[POS_UGROUPID], "GruppenID");
	strcpy(usercol[POS_USERID], "UserID");
	strcpy(usercol[POS_UNKNOWN2], "--");
	strcpy(usercol[POS_UNKNOWN3], "--");
	strcpy(usercol[POS_UDESC], "Ganzer Name");
	strcpy(usercol[POS_UHOME], "Heimatverzeichnis");
	strcpy(usercol[POS_USHELL], "Shell");

	/* pci devices columns */
	strcpy(pcicol[0], "Name");
	strcpy(pcicol[1], "Beschreibung");
	strcpy(pcicol[2], "Hersteller");
	strcpy(pcicol[3], "Karte");
	strcpy(pcicol[4], "Chip");
	strcpy(pcicol[5], "Steckplatz");
	strcpy(pcicol[6], "Typ");
	strcpy(pcicol[7], "Typ");
	strcpy(pcicol[8], "Subtyp");
	strcpy(pcicol[9], "--");

	/* Usb device columns */
	strcpy(usbcol[0], "Name");
	strcpy(usbcol[1], "Beschreibung");
	strcpy(usbcol[2], "Bus");
	strcpy(usbcol[3], "cfg");
	strcpy(usbcol[4], "Modus");
	strcpy(usbcol[5], "Geschwindigkeit");
	strcpy(usbcol[6], "Power");
	strcpy(usbcol[7], "Strom");
	strcpy(usbcol[8], "--");
	strcpy(usbcol[9], "--");

}
