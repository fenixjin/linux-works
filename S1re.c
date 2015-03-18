//This is a simple progressbar program

#include <gtk-2.0/gtk/gtk.h>
#include <string.h>

GtkWidget *window, *table, *button, *progress_bar;

int main(int argc, char **argv)
{
	int timer;
	gpointer data;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Window 1");
	gtk_widget_set_usize(window, 200, 200);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_widget_show(window);
	gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(gtk_main_quit), NULL);

	table = gtk_table_new(5, 11, TRUE);
	gtk_widget_show(table);
	gtk_container_add(GTK_CONTAINER(window), table);

	progress_bar = gtk_progress_bar_new();
	gtk_table_attach_defaults(GTK_TABLE(table), progress_bar, 0, 11, 1, 2);
	git_widget_show(progress_bar);

	timer = gtk_timeout_add(150, progress_timeout, data);

}

gint progress_timeout(gpointer data)
{
	gdouble value;
	char centraltext[20] = "0%";

	value = gtk_progressbar_get_fraction(GTK_PROGRESSBAR(progressbar)) + 0.01;
	if(value > 1.0)
		value = 0.0;
	strcpy(text, " ");
	sprintf(text, "%d", (int)(100 * value));
	strcat(text, "% ");
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), value);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), text);
	return TRUE;
}