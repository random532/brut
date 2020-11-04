/* Time tab related code */
#include "disk.h"

	/* 'Date and Time' Widgets */
	GtkWidget *gyear;
	GtkWidget *gmonth;
	GtkWidget *gday;
	GtkWidget *ghour;
	GtkWidget *gminute;
	GtkWidget *gsecond;

	GtkWidget *newyear;
	GtkWidget *newmonth;
	GtkWidget *newday;
	GtkWidget *newhour;
	GtkWidget *newminute;
	GtkWidget *newsecond;

	/* Timezone widgets */
	GtkWidget *gregion;
	GtkWidget *gcountry;

	gint timeup;

void write_time_to_widgets() {

	char *thetime;
	char *sep = ":";
	char *brk;
	char *snippet;

	thetime = command("date +%Y:%m:%d:%H:%M:%S");
	if(thetime == NULL)
		return;

	/* Year */
	snippet = strtok_r(thetime, sep, &brk);
	gtk_entry_set_text(GTK_ENTRY(gyear), snippet);
	
	/* Month */
	snippet = strtok_r(NULL, sep, &brk);
	gtk_entry_set_text(GTK_ENTRY(gmonth), snippet);

	/* Day */
	snippet = strtok_r(NULL, sep, &brk);
	gtk_entry_set_text(GTK_ENTRY(gday), snippet);

	/* Hour */
	snippet = strtok_r(NULL, sep, &brk);
	gtk_entry_set_text(GTK_ENTRY(ghour), snippet);

	/* Minute */
	snippet = strtok_r(NULL, sep, &brk);
	gtk_entry_set_text(GTK_ENTRY(gminute), snippet);

	/* Second */
	snippet = strtok_r(NULL, sep, &brk);
	gtk_entry_set_text(GTK_ENTRY(gsecond), snippet);

}

void sync_time(GtkMenuItem *item, gpointer userdata) {
	char *cmd = malloc(20);
	sprintf(cmd, "ntpd -gq");
	execute_me(cmd, MOUNT);
}

gint timeup_cb(gpointer data) {

	/* Is our tab still open? */
	gint n = gtk_notebook_get_current_page(GTK_NOTEBOOK (tabs));
	const gchar *tab = gtk_notebook_get_tab_label_text(GTK_NOTEBOOK (tabs), gtk_notebook_get_nth_page(GTK_NOTEBOOK (tabs), n));
	
	if(strcmp(tab, l.tabtime) != 0) {
		timeup = 0;
		return FALSE;
	}

	write_time_to_widgets();
	return TRUE;
}

char *get_timezone() {

	time_t currtime = time(NULL);
	struct tm *t = localtime(&currtime);
	
	if(t != NULL)
		return t->tm_zone;
	else
		return NULL;
}

void set_new_time(GtkMenuItem *item, gpointer userdata) {
	
	/* Be safe. */
	g_source_remove(timeup);
	
	const gchar *syear;
	const gchar *smonth;
	const gchar *sday;
	const gchar *shour;
	const gchar *sminute;
	const gchar *ssecond;

	/* 
	 * Read the new values.
	 * If empty, keep the current time insofar.
	 */

	syear = gtk_entry_get_text(GTK_ENTRY (newyear));
	if(strlen(syear) == 0)
		syear = gtk_entry_get_text(GTK_ENTRY (gyear));

	smonth = gtk_entry_get_text(GTK_ENTRY (newmonth));
	if(strlen(smonth) == 0)
		smonth = gtk_entry_get_text(GTK_ENTRY (gmonth));

	sday = gtk_entry_get_text(GTK_ENTRY (newday));
	if(strlen(sday) == 0)
		sday = gtk_entry_get_text(GTK_ENTRY (gday));

	shour = gtk_entry_get_text(GTK_ENTRY (newhour));
	if(strlen(shour) == 0)
		shour = gtk_entry_get_text(GTK_ENTRY (ghour));

	sminute = gtk_entry_get_text(GTK_ENTRY (newminute));
	if(strlen(sminute) == 0)
		sminute = gtk_entry_get_text(GTK_ENTRY (gminute));


	char *cmd = malloc(CMDSIZE);
	sprintf(cmd, "date %s%s%s%s%s", syear, smonth, sday, shour, sminute);
	execute_me(cmd, GPART);

	/* Restart the timeout. */
	timeup = g_timeout_add(6000, timeup_cb, NULL);
	
}

void set_timezone(GtkMenuItem *item, gpointer userdata) {

	char *string;
	string = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (gregion));
	if(string == NULL)
		return;

	char *string1;
	string1 = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (gcountry));
	
	char *cmd;
	if(string1 == NULL) {
		cmd = malloc(strlen(string) + 50);
		sprintf(cmd, "cp /usr/share/zoneinfo/%s /etc/localtime", string);
	}
	else {
		cmd = malloc(strlen(string) + strlen(string1) + 50);
		sprintf(cmd, "cp /usr/share/zoneinfo/%s/%s /etc/localtime", string, string1);
	}
	
	execute_me(cmd, MOUNT);
}

void region_changed() {

	/* Cleanup */
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT (gcountry));

	char *string;
	string = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT (gregion));
	if(string == NULL)
		return;

	char *cmd = malloc(strlen(string) + 40);
	if(cmd == NULL)
		return;
	sprintf(cmd, "ls /usr/share/zoneinfo/%s", string);

	FILE *fp = popen(cmd, "r");
	if (fp == NULL) {
		msg("couldnt popen");
		return;
	}
	char info[200];
	memset(info, 0, 200);

	while( fgets(info, sizeof info, fp)) {
		int len = strlen(info);
		if((len > 0) && (info[0] != '/')) {
			info[len-1]='\0';
			gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (gcountry), NULL, info);
		}
	}

	pclose(fp);
	free(cmd);
	gtk_widget_show(gcountry);
}

void fill_region() {

	FILE *fp = popen("ls /usr/share/zoneinfo", "r");
	if (fp == NULL) {
		msg("couldnt popen");
		return;
	}
	char info[200];
	memset(info, 0, 200);

	while( fgets(info, sizeof info, fp)) {
		int len = strlen(info);
		if(len > 0) {
			info[len-1]='\0';
			gtk_combo_box_text_append( GTK_COMBO_BOX_TEXT (gregion), NULL, info);
		}
	}
	pclose(fp);
}

void add_time() {

	gtk_container_add(GTK_CONTAINER (timebox), gtk_label_new(l.ctime1));
	gtk_container_add(GTK_CONTAINER (timebox), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));
	
	/* Grid */
	GtkWidget *gtime = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(gtime), FALSE);
	gtk_grid_insert_column(GTK_GRID(gtime), 7);
	gtk_grid_set_row_spacing(GTK_GRID(gtime), 5);
	gtk_grid_set_column_spacing(GTK_GRID(gtime), 5);
	gtk_box_pack_start(GTK_BOX(timebox), gtime, FALSE, FALSE, 0);

	/* Grid entries */

	/* First row */
	gtk_grid_attach(GTK_GRID (gtime), gtk_label_new(l.tyear), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), gtk_label_new(l.tmonth), 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), gtk_label_new(l.tday), 2, 0, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), gtk_label_new("--"), 3, 0, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), gtk_label_new(l.thour), 4, 0, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), gtk_label_new(l.tminute), 5, 0, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), gtk_label_new(l.tsecond), 6, 0, 1, 1);

	/* Second row */
	gyear = gtk_entry_new();
	gmonth = gtk_entry_new();
	gday = gtk_entry_new();
	ghour = gtk_entry_new();
	gminute = gtk_entry_new();
	gsecond = gtk_entry_new();

	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (gyear)), 4);
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (gmonth)), 2);
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (gday)), 2);
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (ghour)), 2);
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (gminute)), 2);
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (gsecond)), 2);

	gtk_entry_set_width_chars(GTK_ENTRY(gyear), 4);
	gtk_entry_set_width_chars(GTK_ENTRY(gmonth), 2);
	gtk_entry_set_width_chars(GTK_ENTRY(gday), 2);
	gtk_entry_set_width_chars(GTK_ENTRY(ghour), 2);
	gtk_entry_set_width_chars(GTK_ENTRY(gminute), 2);
	gtk_entry_set_width_chars(GTK_ENTRY(gsecond), 2);

	g_object_set(gyear, "editable", FALSE, "can_focus", FALSE, NULL);
	g_object_set(gmonth, "editable", FALSE, "can_focus", FALSE, NULL);
	g_object_set(gday, "editable", FALSE, "can_focus", FALSE, NULL);
	g_object_set(ghour, "editable", FALSE, "can_focus", FALSE, NULL);
	g_object_set(gminute, "editable", FALSE, "can_focus", FALSE, NULL);
	g_object_set(gsecond, "editable", FALSE, "can_focus", FALSE, NULL);

	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (gyear), 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (gmonth), 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (gday), 2, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (ghour), 4, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (gminute), 5, 1, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (gsecond), 6, 1, 1, 1);

	/* Third row */
	newyear = gtk_entry_new();
	newmonth = gtk_entry_new();
	newday = gtk_entry_new();
	newhour = gtk_entry_new();
	newminute = gtk_entry_new();
	newsecond = gtk_entry_new();

	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (newyear)), 4);
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (newmonth)), 2);
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (newday)), 2);
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (newhour)), 2);
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (newminute)), 2);
	gtk_entry_buffer_set_max_length (gtk_entry_get_buffer(GTK_ENTRY (newsecond)), 2);

	gtk_entry_set_width_chars(GTK_ENTRY(newyear), 4);
	gtk_entry_set_width_chars(GTK_ENTRY(newmonth), 2);
	gtk_entry_set_width_chars(GTK_ENTRY(newday), 2);
	gtk_entry_set_width_chars(GTK_ENTRY(newhour), 2);
	gtk_entry_set_width_chars(GTK_ENTRY(newminute), 2);
	gtk_entry_set_width_chars(GTK_ENTRY(newsecond), 2);

	g_object_set(newsecond, "editable", FALSE, "can_focus", FALSE, NULL);

	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (newyear), 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (newmonth), 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (newday), 2, 2, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (newhour), 4, 2, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (newminute), 5, 2, 1, 1);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (newsecond), 6, 2, 1, 1);

	GtkWidget *b = gtk_button_new_with_label(l.tsettime);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (b), 7, 2, 1, 1);
	g_signal_connect(b, "clicked", G_CALLBACK(set_new_time), NULL);


	/* Synchronize with network time GUI */
	gtk_container_add(GTK_CONTAINER (timebox), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));
	
	gtime = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(gtime), FALSE);
	gtk_grid_set_row_spacing(GTK_GRID(gtime), 5);
	gtk_grid_set_column_spacing(GTK_GRID(gtime), 20);
	gtk_box_pack_start(GTK_BOX(timebox), gtime, FALSE, FALSE, 0);

	gtk_grid_attach(GTK_GRID (gtime), gtk_label_new(l.tsync), 0, 0, 1, 1);
	
	b = gtk_button_new_with_label("Ok");
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (b), 1, 0, 1, 1);
	g_signal_connect(b, "clicked", G_CALLBACK(sync_time), NULL);

}

void add_timezone() {

	gtk_container_add(GTK_CONTAINER (timebox), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));
	gtk_container_add(GTK_CONTAINER (timebox), gtk_label_new(l.ttimezone));

	/* A grid. */
	GtkWidget *gtime = gtk_grid_new();	
	gtk_grid_set_column_homogeneous(GTK_GRID(gtime), FALSE);
	gtk_grid_set_row_spacing(GTK_GRID(gtime), 5);
	gtk_grid_set_column_spacing(GTK_GRID(gtime), 5);
	gtk_box_pack_start(GTK_BOX(timebox), gtime, TRUE, FALSE, 0);

	/* Grid elements */
	
	/*Current timezone */
	char *mytimezone = get_timezone();
	if(mytimezone != NULL)
		gtk_grid_attach(GTK_GRID (gtime), gtk_label_new(mytimezone), 0, 0, 1, 1);

	/* Region combo box */
	gregion = gtk_combo_box_text_new();
	gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(gregion), 3);
	fill_region();
	g_signal_connect(gregion, "changed", G_CALLBACK (region_changed), NULL);
	gtk_grid_attach(GTK_GRID (gtime), gregion, 1, 0, 1, 1);

	/* Country combo box */
	gcountry = gtk_combo_box_text_new();
	gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(gcountry), 3);
	gtk_grid_attach(GTK_GRID (gtime), gcountry, 2, 0, 1, 1);

	/* Button */
	GtkWidget *b = gtk_button_new_with_label(l.tsetzone);
	g_signal_connect(b, "clicked", G_CALLBACK(set_timezone), NULL);
	gtk_widget_set_tooltip_text(b, l.ttooltip);
	gtk_grid_attach(GTK_GRID (gtime), GTK_WIDGET (b), 3, 0, 1, 1);
}

void timetab() {
		
	if(GTK_IS_WIDGET(timebox))
		gtk_widget_destroy(timebox);

	/* A top level container. */
	timebox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add (GTK_CONTAINER (tab4), timebox);
	
	/* Raw GUI elements */
	add_time();
	add_timezone();
	
	/* Write time once, then update regularly. */
	write_time_to_widgets();
	if(timeup)
		g_source_remove(timeup);
	timeup = g_timeout_add(4000, timeup_cb, NULL);

	gtk_widget_show_all(timebox);
}
