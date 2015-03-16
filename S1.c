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

int main (int argc, char *argv[])
{
	int timer;
	gpoint data;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Swindow1");
	gtk_widget_set_usize(window, 200,200);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_widget_show(window);
	gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
	table = gtk_table_new(5, 11, TRUE);
	

}