static struct FileInfo *accept_connection (){
    struct sockaddr_in serv_addr, cli_addr;
    struct FileInfo *file_info;
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
        error("ERROR opening socket");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(3000);
    if (bind(server_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    if (listen(server_socket, 5) < 0)
        error("Cannot listen on socket!");
    socklen_t clilen = sizeof(cli_addr);
    int client_socket = accept(server_socket, (struct sockaddr *) &cli_addr, &clilen);
    if (client_socket < 0)
        error("ERROR on accept");
    file_info = malloc(sizeof(struct FileInfo));
    if(file_info == NULL) 
      error("ERROR on allocate memory");
    if (recv(client_socket,file_info, sizeof(struct FileInfo), 0) < 0)
        error("cannot read file info");
    file_info->socket = client_socket;
    printf("file size : %d\n",file_info->filesize);
    return file_info;
}

static void accept_connection_thread_cb (GTask *task,gpointer source_object,gpointer client_socket,GCancellable  *cancellable){
  //SomeBlockingFunctionData *data = task_data;
  struct FileInfo *retval;
  /* Handle cancellation. */
  if (g_task_return_error_if_cancelled (task))
      return;
  /* Run the blocking function. */
  retval = accept_connection (client_socket);
  g_task_return_pointer (task, retval,NULL);
}

static void accept_connection_data_free (gpointer *data){
 // free_param (data->param1);
  //free_param (data->param2);
  //g_free (data);
}

void accept_connection_async (GCancellable *cancellable,GAsyncReadyCallback callback,gpointer user_data){
  GTask *task = NULL;  /* owned */
  //SomeBlockingFunctionData *data = NULL;  /* owned */
  gpointer *data = NULL;
  g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));
  task = g_task_new (NULL, cancellable, callback, user_data);
  g_task_set_source_tag (task, accept_connection_async);
  /* Cancellation should be handled manually using mechanisms specific to
   * some_blocking_function(). */
  g_task_set_return_on_cancel (task, FALSE);
  g_task_set_task_data (task, data, (GDestroyNotify) join_multicast_data_free);
  /* Run the task in a worker thread and return immediately while that continues
   * in the background. When it’s done it will call @callback in the current
   * thread default main context. */
  g_task_run_in_thread (task, accept_connection_thread_cb);

  g_object_unref (task);
}

gpointer accept_connection_finish (GAsyncResult *result, GError **error){
  //g_return_val_if_fail (g_task_is_valid (result,accept_connection_async), -1);
  //g_return_val_if_fail (error == NULL || *error == NULL, -1);
  return g_task_propagate_pointer (G_TASK (result), error);
}
