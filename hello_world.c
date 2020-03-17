#include <config.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>

#ifdef USE_BUTTON
static void print_hello (GtkWidget *widget, gpointer data)
{
  g_print ("Hello World\n");
}
#endif

static void
activate (GtkApplication *app, gpointer user_data)
{
  int i;
  char text[100];
  GtkWidget *window;

#ifdef USE_BUTTON
  GtkWidget *button;
  GtkWidget *button_box;
#endif

  GtkWidget *view;
  GtkTextBuffer *text_buffer;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
#ifdef USE_BUTTON
  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);
#endif
  view = gtk_text_view_new ();
  text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
  gtk_text_buffer_set_text (text_buffer, "Hello, this is some text", -1);
  gtk_container_add (GTK_CONTAINER (window), view);

  for (i = 0; i < 1000; i++) {
    g_sprintf(text, "Hello, this is some text %d\r\n", i);
    gtk_text_buffer_set_text (text_buffer, text, -1);
    g_usleep (200000);
  }
#ifdef USE_BUTTON
  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);
#endif

  gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
