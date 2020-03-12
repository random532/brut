#include "disk.h"

void on_geom_changed() {

	char *string;
	string = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (combo_geom));
	if(string == NULL)
		return;
		
	hide_widgets();
		
	if(strcmp(string, "create") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_disks));
		gtk_widget_show(GTK_WIDGET (combo_schemes));
		gtk_widget_show(GTK_WIDGET (text_entries));
		}

	else if(strcmp(string, "destroy") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_disks));
		}
	else if(strcmp(string, "add") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_disks));
		gtk_widget_show(GTK_WIDGET (combo_types));
		gtk_widget_show(GTK_WIDGET (text_size));
		gtk_widget_show(GTK_WIDGET (text_label));
		gtk_widget_show(GTK_WIDGET (text_alignment));
		}
	else if(strcmp(string, "delete") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		}
	else if(strcmp(string, "modify") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		gtk_widget_show(GTK_WIDGET (combo_types));
		gtk_widget_show(GTK_WIDGET (text_label));
		}
	else if(strcmp(string, "set") == 0) { 
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		gtk_widget_show(GTK_WIDGET (combo_bootoptions));
		}
	else if(strcmp(string, "unset") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		gtk_widget_show(GTK_WIDGET (combo_bootoptions));
		}
	else if(strcmp(string, "resize") == 0) { 
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		gtk_widget_show(GTK_WIDGET (text_size));
		gtk_widget_show(GTK_WIDGET (text_alignment));
		}
	else if(strcmp(string, "bootcode") == 0) { //??
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		}
	else if(strcmp(string, "file system") == 0) {
		gtk_widget_show(GTK_WIDGET (combo_partitions));
		gtk_widget_show(GTK_WIDGET (combo_filesystems));
		gtk_widget_show(GTK_WIDGET (text_label));
		}
}
