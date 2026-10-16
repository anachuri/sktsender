

char recv_dir[256];

struct FileInfo {
    char file_name[256];
    int file_size;
};

gboolean set_progress_bar_fraction(gpointer fraction){
 // printf("%f\n",*((double *)fraction));
  printf("fraction\n");
}

int read_file(int *client_socket) {
    double fraction = 0;
    struct FileInfo file_info;
    if (recv(*client_socket, &file_info, sizeof(file_info), 0) < 0)
        error("cannot read file info");
    char file_path[256];//[strlen(recv_dir)+strlen(file_info.file_name)+1]; 
    strcpy(file_path,recv_dir);
    strcat(file_path,file_info.file_name);
    FILE *fp = fopen(file_path, "wb");
    if (fp != NULL) {
        size_t read_bytes;
        char buffer[8192];
        while ((read_bytes = recv(*client_socket, buffer, sizeof(buffer), 0)) > 0) {
            if (fwrite(buffer, 1, read_bytes, fp) != read_bytes) {
                printf("error al escribir\n");
                break;
            }
            fraction += (double) read_bytes / file_info.file_size;
            printf("%f\n",fraction);
            //g_main_context_invoke (g_main_context_default(),set_progress_bar_fraction,&fraction);
        }
        fclose(fp);
    }
  return 0;
}


static void read_file_thread_cb (GTask *task,gpointer source_object,gpointer client_socket,GCancellable *cancellable){
  //SomeBlockingFunctionData *data = task_data;
  int retval;
  /* Handle cancellation. */
  
  if (g_task_return_error_if_cancelled (task))
      return;
  /* Run the blocking function. */
 
  retval = read_file ((int *)client_socket);
  g_task_return_int (task, retval);
}

static void read_file_data_free (gpointer *data){
 // free_param (data->param1);
  //free_param (data->param2);

  //g_free (data);
}

static void read_file_async (GCancellable *cancellable, GAsyncReadyCallback callback,gpointer client_socket){
  GTask *task = NULL;  /* owned */
  //SomeBlockingFunctionData *data = NULL;  /* owned */
  gpointer *data = client_socket;
  g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));
  task = g_task_new (NULL, cancellable, callback, client_socket);
  g_task_set_source_tag (task, read_file_async);
  /* Cancellation should be handled manually using mechanisms specific to
   * some_blocking_function(). */
  //g_task_set_return_on_cancel (task, TRUE);
  g_task_set_task_data (task, data, (GDestroyNotify) read_file_data_free);
  
  /* Run the task in a worker thread and return immediately while that continues
   * in the background. When it’s done it will call @callback in the current
   * thread default main context. */
  g_task_run_in_thread (task, read_file_thread_cb);
  g_object_unref (task);
}

int read_file_finish (GAsyncResult  *result,GError  **error){
  g_return_val_if_fail (g_task_is_valid (result,read_file_async), -1);
  g_return_val_if_fail (error == NULL || *error == NULL, -1);
  return g_task_propagate_int (G_TASK (result), error);
}


