#define GTK_ENABLE_BROKEN
#include <gtk/gtk.h>
#include <string.h>
GtkWidget *window;
GtkWidget *table;
GtkWidget *label;
GtkWidget *button;
GtkWidget *button1;
int i = 0;

gint hello(void)
{
	label = gtk_label_new("Hello World!");
	gtk_table_attach_defaults(GTK_TABLE(table), label, 3, 8, 0, 1);
	gtk_widget_show(label);
	return TRUE;
}

int main(int argc, char *argv[])
{
	GtkWidget *vscrollbar;
	int timer;
	gpointer data;

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Swindow2");
	gtk_widget_set_usize(window, 200, 200);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_MOUSE);
	gtk_widget_show(window);

	gtk_signal_connect(GTK_OBJECT(window), "destory", GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
	table = gtk_table_new(11, 10, true);
	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_widget_show(table);
	button = gtk_button_new_with_label("close");
	gtk_table_attach_defaults(GTK_TABLE(table), button, 3, 8, 6, 8);
	gtk_widget_show(button);
	gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FINC(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}

