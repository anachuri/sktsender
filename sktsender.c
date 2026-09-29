#include <gtk/gtk.h>
#include "resources.c"

GtkStack *stack;

static void transfer_activated(GSimpleAction* self,gpointer user_data){
  gtk_stack_set_visible_child_name (stack,"2");
}

static void pressed_cb (GtkGestureClick *gesture,int n_press,double x, double y,GtkListItem *list_item){  
  GtkWidget *box = gtk_list_item_get_child (list_item);
  GFileInfo *file_info = gtk_list_item_get_item (list_item);
  GFile *file = G_FILE (g_file_info_get_attribute_object (file_info,"standard::file"));
  if(g_file_info_get_file_type (file_info) == G_FILE_TYPE_DIRECTORY)
      return;
  /*
  GSimpleAction *act_transfer = g_simple_action_new ("transfer", NULL);
  g_signal_connect (act_transfer, "activate", G_CALLBACK (transfer_activated),G_APPLICATION(app));
  g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (act_transfer));
  g_object_unref (act_transfer);
  */
  GtkWidget *popover_menu = gtk_popover_new();//gtk_popover_menu_new_from_model (G_MENU_MODEL(menu));
  GtkWidget *label = gtk_label_new("transfer");
  GtkGesture *gesture_click = gtk_gesture_click_new ();
  gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (gesture_click), GDK_BUTTON_PRIMARY);
  gtk_widget_add_controller (label, GTK_EVENT_CONTROLLER (gesture_click));
  g_signal_connect (gesture_click, "pressed", G_CALLBACK (transfer_activated), NULL);
  gtk_popover_set_child (GTK_POPOVER(popover_menu),label);
  gtk_widget_set_parent(popover_menu,GTK_WIDGET(box));
  //gtk_popover_set_has_arrow (GTK_POPOVER(popover_menu),false);
  gtk_popover_set_pointing_to(GTK_POPOVER(popover_menu), &(const GdkRectangle){x,y,1,1});;
  gtk_popover_popup(GTK_POPOVER (popover_menu));
}

static void setup_listitem_cb (GtkListItemFactory *factory,GtkListItem *list_item){
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);
  GtkWidget *image;
  GtkWidget *label = gtk_label_new(NULL);
  image = gtk_image_new ();
  gtk_image_set_icon_size (GTK_IMAGE (image), GTK_ICON_SIZE_LARGE);
  gtk_box_append (GTK_BOX (box), image);
  gtk_box_append (GTK_BOX (box), label);
  gtk_list_item_set_child (list_item, box);
}

static void bind_listitem_cb (GtkListItemFactory *factory, GtkListItem *list_item){
  GtkWidget *box = gtk_list_item_get_child (list_item);
  GFileInfo *file_info = gtk_list_item_get_item (list_item);
  GtkImage *image = GTK_IMAGE (gtk_widget_get_first_child(box));
  GtkLabel *label = GTK_LABEL (gtk_widget_get_last_child(box));
  gtk_image_set_from_gicon (GTK_IMAGE (image),g_file_info_get_icon(file_info));
  gtk_label_set_label (GTK_LABEL (label), g_file_info_get_name(file_info));
  GtkGesture *gesture = gtk_gesture_click_new ();
  gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (gesture), GDK_BUTTON_SECONDARY);
  gtk_widget_add_controller (box, GTK_EVENT_CONTROLLER (gesture));
  g_signal_connect (gesture, "pressed", G_CALLBACK (pressed_cb), list_item);
}

static void grid_activate (GtkGridView *grid, int position, gpointer user_data) {
  GFileInfo *file_info = G_FILE_INFO (g_list_model_get_item (G_LIST_MODEL (gtk_grid_view_get_model (grid)), position));
  if(g_file_info_get_file_type (file_info) != G_FILE_TYPE_DIRECTORY)
      return;
}

static void activate_focus (GtkWindow* self,  gpointer user_data){
  printf("activated\n");
}

static void app_activate (GApplication *app, gpointer *user_data) {
  //GtkBuilder *builder = gtk_builder_new_from_file ("sktsender.ui");
  GtkBuilder *builder = gtk_builder_new_from_resource("/com/github/anachuri/sktsender/ui/sktsender.ui");
  GtkWidget *win = GTK_WIDGET (gtk_builder_get_object (builder, "win"));
  GtkWidget *nb = GTK_WIDGET (gtk_builder_get_object (builder, "nb"));
  gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));

  GFile *file = g_file_new_for_path ("/home/anachuri");
  GtkDirectoryList *dl = gtk_directory_list_new ("standard::*", file);
  g_object_unref (file);
  //GtkSingleSelection *model = gtk_single_selection_new (G_LIST_MODEL (dl));
  GtkNoSelection *model = gtk_no_selection_new (G_LIST_MODEL(dl));
  GtkListItemFactory *factory = gtk_signal_list_item_factory_new ();
  g_signal_connect (factory, "setup", G_CALLBACK (setup_listitem_cb), NULL);
  g_signal_connect (factory, "bind", G_CALLBACK (bind_listitem_cb), NULL);
  GtkGridView *grid = GTK_GRID_VIEW(gtk_builder_get_object (builder, "grid"));
  
  stack = GTK_STACK(gtk_builder_get_object (builder, "stack"));
  
  gtk_grid_view_set_factory (grid, factory);
  gtk_grid_view_set_model (grid, GTK_SELECTION_MODEL (model));
  g_object_ref (grid);
  g_signal_connect (GTK_GRID_VIEW (grid), "activate", G_CALLBACK (grid_activate), NULL);
  g_signal_connect (GTK_WINDOW (win), "activate-focus", G_CALLBACK (activate_focus), NULL);
  g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);
 
 //GtkCssProvider *provider = gtk_css_provider_new ();
//  gtk_css_provider_load_from_string (provider, "popover {background-color: red; padding:0px;}");
  //gtk_css_provider_load_from_data (provider,"popover.menu context-menu {padding: 0;margin:0;background-color: blue;} ",-1);
  /* Add CSS to the default GdkDisplay. */
  //gtk_style_context_add_provider_for_display (gdk_display_get_default (), GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  GtkIconTheme *theme = gtk_icon_theme_get_for_display (gdk_display_get_default());
  gtk_icon_theme_add_resource_path (theme, "/com/github/anachuri/sktsender/48x48/actions");
  gtk_window_set_default_icon_name ("skt-sender"); 
  gtk_window_set_icon_name(GTK_WINDOW (win),"skt-sender");
  gtk_window_present (GTK_WINDOW (win));
}

int main (int argc, char **argv) {
  GtkApplication *app = gtk_application_new ("com.github.anachuri.sktsender", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
  int stat = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  return stat;
}
