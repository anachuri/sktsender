char recv_dir[256];

struct FileInfo {
    char file_name[256];
    int file_size;
};

int read_file_bytes(int client_socket, uintmax_t file_size) {
    struct FileInfo file_info;
    if (recv(client_socket, &file_info, sizeof(file_info), 0) < 0)
        error("cannot read file info");
    char file_path[strlen(recv_dir)+strlen(file_info.file_name)+1]; 
    strcat(file_path,file_info.file_name);
  
    FILE *fp = fopen(file_path, "wb");
    if (fp != NULL) {
        size_t read_bytes;
        char buffer[8192];
        printf("file_size: %d\n",file_size);
        int s = 0;
        while ((read_bytes = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
            if (fwrite(buffer, 1, read_bytes, fp) != read_bytes) {
                printf("error al escribir\n");
                break;
            }
            s += read_bytes;
            file_size -= read_bytes;
            //std::cout << "Received " << readBytes << " bytes" << std::endl;
            //std::cout << "file size subtracted " << fileSize << std::endl;
        }
        fclose(fp);
        //std::cout << "bytes recibdos " << s << std::endl;
    }
    if (file_size > 0) {
        //std::cout << "error al recibir el archivo,archivo incompleto" << std::endl;
    } else{}
        //std::cout << "File transfer complete." << std::endl;
  return 0;
}


static void read_file_bytes_thread_cb (GTask *task,gpointer source_object,gpointer task_data,GCancellable  *cancellable){
  //SomeBlockingFunctionData *data = task_data;
  int retval;
  /* Handle cancellation. */
  if (g_task_return_error_if_cancelled (task))
      return;
  /* Run the blocking function. */
  retval = read_file_bytes (1,3); // PARAMETROS INVALIDOS, CAMBIAR
  g_task_return_int (task, retval);
}

static void read_file_bytes_data_free (gpointer *data){
 // free_param (data->param1);
  //free_param (data->param2);

  //g_free (data);
}

void read_file_bytes_async ( GCancellable *cancellable, GAsyncReadyCallback callback,int *client_socket){
  GTask *task = NULL;  /* owned */
  //SomeBlockingFunctionData *data = NULL;  /* owned */
  gpointer *data = NULL;
  g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));
  task = g_task_new (NULL, cancellable, callback, client_socket);
  g_task_set_source_tag (task, read_file_bytes_async);
  /* Cancellation should be handled manually using mechanisms specific to
   * some_blocking_function(). */
  g_task_set_return_on_cancel (task, FALSE);
  //g_task_set_task_data (task, data, join_multicast_data_free); //investigar porque da error al compilar
  
  /* Run the task in a worker thread and return immediately while that continues
   * in the background. When it’s done it will call @callback in the current
   * thread default main context. */
  g_task_run_in_thread (task, read_file_bytes_thread_cb);
  g_object_unref (task);
}

int read_file_bytes_finish (GAsyncResult  *result,GError  **error){
  g_return_val_if_fail (g_task_is_valid (result,read_file_bytes_async), -1);
  g_return_val_if_fail (error == NULL || *error == NULL, -1);
  return g_task_propagate_int (G_TASK (result), error);
}


