#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pwd.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}


static int bind_socket (){
    int server_socket;
    struct sockaddr_in serv_addr, cli_addr;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
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
    return server_socket;
}

static void bind_socket_thread_cb (GTask         *task,gpointer       source_object,
                                  gpointer       task_data,
                                  GCancellable  *cancellable){
  //SomeBlockingFunctionData *data = task_data;
  int retval;

  /* Handle cancellation. */
  if (g_task_return_error_if_cancelled (task))
    {
      return;
    }

  /* Run the blocking function. */
  retval = bind_socket ();
  g_task_return_int (task, retval);
}

static void bind_socket_data_free (gpointer *data){
 // free_param (data->param1);
  //free_param (data->param2);

  //g_free (data);
}

void bind_socket_async ( GCancellable         *cancellable,
                              GAsyncReadyCallback   callback,
                              gpointer              user_data){
  GTask *task = NULL;  /* owned */
  //SomeBlockingFunctionData *data = NULL;  /* owned */
  gpointer *data = NULL;

  g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

  task = g_task_new (NULL, cancellable, callback, user_data);
  g_task_set_source_tag (task, bind_socket_async);

  /* Cancellation should be handled manually using mechanisms specific to
   * some_blocking_function(). */
  g_task_set_return_on_cancel (task, FALSE);

  //g_task_set_task_data (task, data, join_multicast_data_free); //investigar porque da error al compilar

  /* Run the task in a worker thread and return immediately while that continues
   * in the background. When it’s done it will call @callback in the current
   * thread default main context. */
  g_task_run_in_thread (task, bind_socket_thread_cb);

  g_object_unref (task);
}

int bind_socket_finish (GAsyncResult  *result,
                               GError       **error){
  g_return_val_if_fail (g_task_is_valid (result,
                                         bind_socket_async), -1);
  g_return_val_if_fail (error == NULL || *error == NULL, -1);

  return g_task_propagate_int (G_TASK (result), error);
}
