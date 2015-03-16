#include <string.h>
GtkWidget *window;
GtkWidget *table;
GtkWidget *label;
GtkWidget *text;
int i = 0;

gint text_timeout(gpointer data)
{
	char buf[20], temp[10];

	sprintf(temp, "%d", i);
	strcpy(buf, "text ");
	strcat(buf , temp);
	strcat(buf, "\n");
	gtk_text_insert(GTK_TEXT(text), NULL, NULL, NULL, buf, -1);
	i++;
	return TRUE;
}

int main (int argc, char *argv[])
{
	GtkWidget *vscrollbar;
	int timer;
	gpointer data;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_Set_title(GTK_WINDOW(window), "Swindow3");
	gtk_widget_set_usize(window, 200, 400);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_widget_show(window);

	gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
	table = gtk_table_bew(11, 10, TRUE);
	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_widget_show(table);

	label = gtk_label_new("Text")
	gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 10, 0, 1);
	gtk_widget_show(label);
	text = gtk_text_new(NULL, NULL);
	gtk_widget_show(text);
	gtk_table_attach_defaults(GTK_TABLE(table), text, 0, 9, 1, 11);
	vscrollbar = gtk_vscrollbar_new(GTK_TEXT(text)->vadj);
	gtk_widget_show(vscrollbar);
	gtk_table_attach_defaults(GTK_TABLE(table), vscrollbar, 9, 10, 1, 11);
	timer = gtk_timeout_add(1000,text_timeout, data);
	gtk_main();
	return 0;
}