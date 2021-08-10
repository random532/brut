/* Audio tab */
#include "brut.h"

GtkWidget *sndstat;
GtkWidget *mxgrid;

/* Functions */
//void mixer();
static gboolean is_default(char *);
static void cleanup_audio();
static void vol_changed(GtkWidget *item, GtkWidget *);
static void sndstat_changed(GtkButton *, gpointer);
static GtkWidget *CreateRadio (GtkWidget *, GSList **, char *);
static void audio_sources(GtkWidget *);
static void mixer();
static GtkWidget *audio_scrolled_window(GtkWidget *);

void audio();

gboolean is_default(char *line) {
	/* 
	 * Last character = ")" means not default.
	 * Last character = "t" means default audio device. 
	 */

	int len = strlen(line);

	if((len >0) && (line[len-1] == ')'))
		return FALSE;
	else
		return TRUE;
}

void cleanup_audio() {

	if(GTK_IS_WIDGET (audiobox))
		gtk_widget_destroy(audiobox);
}

void vol_changed(GtkWidget *item, GtkWidget *p) {

	gdouble volume = gtk_scale_button_get_value(GTK_SCALE_BUTTON (item));
	volume = volume * 100;
	const gchar *text = gtk_label_get_text(GTK_LABEL (p));

	char cmd[CMDSIZE];
	sprintf(cmd, "mixer %s %d", text, (int) volume);
	command(cmd);
}

void sndstat_changed(GtkButton *item, gpointer p) {

	/* We only care about sndstat changes later on. */
	if(GTK_IS_WIDGET (mxgrid) == FALSE)
		return;

	/* Get the audio device. */
	const gchar *text = gtk_button_get_label(item);
	if(is_default((char *) text))
		return;

	/* Extract the unit number. */
	int end = 0;
	while(text[end] != ':')
		end++;
	
	char cmd[MAXLINE + 100];
	char line[20];
	sprintf(cmd, "echo \"%s\" | awk '{print $1}'| awk -F'[^0-9]*' '{print $2}'", text);
	
	FILE *fp = popen(cmd, "r");
	memset(line, 0, 20);
	fgets(line, 20, fp);

	memset(cmd, 0, CMDSIZE);
	sprintf(cmd, "sysctl hw.snd.default_unit=%s", line);
	command(cmd);

	/* Just redraw everything. */
	audio();
}

GtkWidget *CreateRadio (GtkWidget *box, GSList **group, char *szLabel)
{
    GtkWidget *radio;

    radio = gtk_radio_button_new_with_label (*group, szLabel);
    *group = gtk_radio_button_get_group(GTK_RADIO_BUTTON (radio));
    gtk_box_pack_start (GTK_BOX (box), radio, FALSE, FALSE, 0);

    g_signal_connect(radio, "toggled", G_CALLBACK(sndstat_changed), radio);

    return (radio);
}

void audio_sources(GtkWidget *sw) {

	/* 
	 * Execute "cat /dev/sndstat"
	 * Each output line gets a checkbox.
	 * On_checkbox_changed() -> read the label
	 * Execute sysctl hw.snd.default_unit=x
	 */
	 
	/* A top level container. */
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add(GTK_CONTAINER (sw), box);

	/* Toggle buttons */
	char line[MAXLINE];
	memset(line, 0, MAXLINE);

	GtkWidget *button;
	GSList *g = NULL;

	FILE *fp = popen("cat /dev/sndstat", "r");

	/* Get a line */
	while(fgets(line, sizeof line, fp)) {
		if((strncmp(line, "Installed", 9) != 0) && (strncmp(line, "No devices", 10) != 0)) {
			cosmetics(line);
			button = CreateRadio(box, &g, line);
			if(is_default(line) == TRUE)
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (button), TRUE);
		}
		memset(line, 0, MAXLINE);
	}
	pclose(fp);
	
}

void mixer() {
	
	/* Grid. */
	mxgrid = gtk_grid_new();
	gtk_box_pack_start(GTK_BOX(audiobox), mxgrid, FALSE, TRUE, 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(mxgrid), FALSE);
	gtk_grid_set_column_spacing(GTK_GRID(mxgrid), 10);
	gtk_grid_set_row_spacing(GTK_GRID(mxgrid), 5);

	/* 
	 * widgets. with labels. in the grid.
	 * Execute "mixer".
	 * Set widgets 6x.
	 */
	
	char line[MAXLINE];
	int row = 0; /* Either 1 or 0 */
	int cl = 0; /* increases */
	GtkWidget *label;

//	FILE *fp = popen("mixer | awk '{print $2 \"\\n\" $7}'", "r");
//	FILE *fp = popen("mixer -s", "r");
	FILE *fp = popen("mixer -s | sed 's/ /\\n/g'", "r");
	while(fgets(line, MAXLINE, fp)) {


	if(row == 0) { /* The device */
		cosmetics(line);
		label = gtk_label_new(line);
		gtk_grid_attach(GTK_GRID (mxgrid), GTK_WIDGET (label), cl, row, 1, 1);
	}
	else  { /* A volume level, or recording device. */
		
		if(strncmp(gtk_label_get_text(GTK_LABEL (label)), "=", 1) == 0) /* Recording source */
			gtk_grid_attach(GTK_GRID (mxgrid), gtk_label_new(line), cl, row, 1, 1);		

		else { /* Volume level */
			GtkWidget *vol = gtk_volume_button_new();
			/*only care for left value atm.. */
			int i = 0;
			while((line[i] != ':') && (i < MAXLINE))
				i++;
			line[i] = '\0';
		
			double v = atof(line) / 100;
			gtk_scale_button_set_value(GTK_SCALE_BUTTON (vol), v);
			gtk_grid_attach(GTK_GRID (mxgrid), GTK_WIDGET (vol), cl, row, 1, 1);		
			g_signal_connect(vol, "value-changed", G_CALLBACK(vol_changed), label);
		}
	}

	/* Row is full, so go to next column. */
	if(row == 1)
		cl++;

	/* Always switch rows. */
	if(row == 1)
		row = 0;
	else
		row++;

	memset(line, 0, MAXLINE);
	}
	pclose(fp);
}

GtkWidget *audio_scrolled_window(GtkWidget *box) {
	/* Scrolled window in case we have many audio devices. */
	GtkWidget *w = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (w),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 
	gtk_box_pack_start(GTK_BOX(box), w, FALSE, TRUE, 0);

	/* fixed size? */
	gtk_widget_set_size_request (w, 500, 200); /* width, height */
//	gtk_scrolled_window_set_propagate_natural_height (GTK_SCROLLED_WINDOW(scrolled_window), TRUE);
//	gtk_scrolled_window_set_propagate_natural_width (GTK_SCROLLED_WINDOW(scrolled_window), TRUE);

	return w;
}

void audio() {

	cleanup_audio();

	/* A top level container. */
	audiobox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add(GTK_CONTAINER (tab11), audiobox);

	/* Checkboxes for audio output */
	GtkWidget *sw = audio_scrolled_window(audiobox);
	audio_sources(sw);

	/* Audio input? */
	
	/* Mixer settings */
	mixer();

	gtk_widget_show_all(audiobox);
}
