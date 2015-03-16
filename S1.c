#include <gtk/gtk.h>
#include <string.h>

GtkWidget *window;
GtkWidget *table;
GtkWidget *button;
GtkWidget *progress_bar;

gint progress_timeout(gpointer data)
{
	gdouble value;
	int v;
	char text[20] = "0%";

	value = gtk_progress_bar_get_fraction(GTK_PROGRESSBAR(progress_bar)) + 0.01;
	if(value > 1.0)
		value = 0.0;
	v = (int)(value * 100);
	strcpy(text, " ");
	sprintf(text, "%d", v);
	strcat(text, "% ");
	gtk_progress_bar_set_fraction(GTK+PROGRESS_BAR(progress_bar), value);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), text);
	return TRUE;
}