#include <gtk/gtk.h>
#include "resources.c"
#include <string.h>
#include <pwd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <pwd.h>
#include "join_multicast.c"
#include "navigation.c"
#include "bind_socket.c"
#include "accept_connection.c"
#include "file_receiver.c"

static void load_grid(const char* path);

GtkStack *stack;
GtkBuilder *builder;
GtkGridView *grid;
char *home_dir;
Stack backward_stack;
Stack forward_stack;
char *current_path = "";
GtkListBox *transfer_list;

static void send_file (GtkGestureClick* self,gint n_press,gdouble x,gdouble y,char *file_name){
  GtkWidget *pbar = gtk_progress_bar_new ();
  gtk_progress_bar_set_text (GTK_PROGRESS_BAR(pbar),file_name);
  gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR(pbar),true);
  gtk_list_box_append (transfer_list,pbar);
  gtk_stack_set_visible_child_name (stack,"2");
  //select a device
}

static void pressed_cb (GtkGestureClick *gesture,int n_press,double x, double y,GtkListItem *list_item){  
  GtkWidget *box = gtk_list_item_get_child (list_item);
  GFileInfo *file_info = gtk_list_item_get_item (list_item);
  if(g_file_info_get_file_type (file_info) == G_FILE_TYPE_DIRECTORY)
      return;
  GtkWidget *popover_menu = gtk_popover_new();//gtk_popover_menu_new_from_model (G_MENU_MODEL(menu));
  GtkWidget *label = gtk_label_new("transfer");
  GtkGesture *gesture_click = gtk_gesture_click_new ();
  gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (gesture_click), GDK_BUTTON_PRIMARY);
  gtk_widget_add_controller (label, GTK_EVENT_CONTROLLER (gesture_click));
  g_signal_connect (gesture_click, "pressed", G_CALLBACK (send_file), (char *) g_file_info_get_name(file_info));
  gtk_popover_set_child (GTK_POPOVER(popover_menu),label);
  gtk_widget_set_parent(popover_menu,GTK_WIDGET(box));
  gtk_popover_set_pointing_to(GTK_POPOVER(popover_menu), &(const GdkRectangle){x,y,1,1});;
  gtk_popover_popup(GTK_POPOVER (popover_menu));
}

static void setup_listitem_cb (GtkListItemFactory *factory,GtkListItem *list_item){
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
  GtkWidget *image = gtk_image_new ();
  GtkWidget *label = gtk_label_new(NULL);
  gtk_image_set_icon_size (GTK_IMAGE (image), GTK_ICON_SIZE_NORMAL);
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
  char *path = g_file_get_path(G_FILE(g_file_info_get_attribute_object (file_info,"standard::file")));      
  if (strcmp(current_path,"")!=0)
      push(&backward_stack,current_path);
  current_path = path;
  load_grid(current_path); 
}

static void load_grid(const char* path){
  GFile *file = g_file_new_for_path (path);
  GtkDirectoryList *dl = gtk_directory_list_new ("standard::*", file);
  g_object_unref (file);
  GtkNoSelection *model = gtk_no_selection_new (G_LIST_MODEL(dl));
  GtkListItemFactory *factory = gtk_signal_list_item_factory_new ();
  g_signal_connect (factory, "setup", G_CALLBACK (setup_listitem_cb), NULL);
  g_signal_connect (factory, "bind", G_CALLBACK (bind_listitem_cb), NULL);
  grid = GTK_GRID_VIEW(gtk_builder_get_object (builder, "grid"));
  gtk_grid_view_set_factory (grid, factory);
  gtk_grid_view_set_model (grid, GTK_SELECTION_MODEL (model));
  g_object_ref (grid);
}

static void home_clicked (GtkButton* self,gpointer user_data){
  load_grid(home_dir);
}

static void forward (GtkButton* self,gpointer user_data){
    if (is_empty(&forward_stack) || strcmp(current_path,peek(&forward_stack))==0) {
        printf("Not Available\n");
        return;
    } else {
        push(&backward_stack,current_path);
        current_path = peek(&forward_stack);
        pop(&forward_stack);
        load_grid(current_path);
    }
}

static void backward (GtkButton* self,gpointer user_data){
    if (is_empty(&backward_stack) || strcmp(current_path,peek(&backward_stack))==0) {
        printf("Not Available\n");
        return;
    } else {
        push(&forward_stack,current_path);
        current_path = peek(&backward_stack);
        pop(&backward_stack);
        load_grid(current_path);
    }
}

void send_file_button_cb (GtkButton *source, gpointer user_data){
  gtk_stack_set_visible_child_name (stack,"1");
  load_grid(home_dir);
}

void clipboard_cb (GtkButton *source, gpointer user_data){
  
}

static void app_activate (GApplication *app, gpointer *user_data) {
  //stack = malloc(sizeof(Stack));
  initialize(&backward_stack);
  initialize(&forward_stack);
  home_dir = getpwuid(getuid())->pw_dir;
  current_path = home_dir;
  strcpy(recv_dir, home_dir);
  strcat(recv_dir, "/Downloads");
  builder = gtk_builder_new_from_resource("/com/github/anachuri/sktsender/ui/sktsender.ui");
  grid = GTK_GRID_VIEW(gtk_builder_get_object (builder, "grid"));
  stack = GTK_STACK(gtk_builder_get_object (builder, "stack"));
  transfer_list = GTK_LIST_BOX(gtk_builder_get_object (builder, "transfer_list"));
//  load_grid(home_dir);
  GtkWidget *win = GTK_WIDGET (gtk_builder_get_object (builder, "win"));
  gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
  g_signal_connect (GTK_GRID_VIEW (grid), "activate", G_CALLBACK (grid_activate), NULL);

  //g_signal_connect (GTK_WINDOW (win), "activate-focus", G_CALLBACK (activate_focus), NULL);
  g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);
    
  GObject *home_button = gtk_builder_get_object (builder, "home");
  g_signal_connect (GTK_BUTTON (home_button), "clicked", G_CALLBACK (home_clicked), NULL);
  
  GObject *backward_button = gtk_builder_get_object (builder, "backward");
  g_signal_connect (GTK_BUTTON (backward_button), "clicked", G_CALLBACK (backward), NULL);
  
  GObject *forward_button = gtk_builder_get_object (builder, "forward");
  g_signal_connect (GTK_BUTTON (forward_button), "clicked", G_CALLBACK (forward), NULL);

  GtkIconTheme *theme = gtk_icon_theme_get_for_display (gdk_display_get_default());
  gtk_icon_theme_add_resource_path (theme, "/com/github/anachuri/sktsender/48x48/actions");
  gtk_window_set_default_icon_name ("skt-sender"); 
  gtk_window_set_icon_name(GTK_WINDOW (win),"skt-sender");
  gtk_window_present (GTK_WINDOW (win));
  
  //join_multicast_async(NULL,NULL,NULL);
  //accept_connection_async(NULL,NULL,NULL);
  //read_file_bytes_async(NULL,NULL,NULL);
}

int main (int argc, char **argv) {
  GtkApplication *app = gtk_application_new ("com.github.anachuri.sktsender", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
  int stat = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  return stat;
}
