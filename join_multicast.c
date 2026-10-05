static int join_multicast (){
    struct sockaddr_in local_sock;
    struct ip_mreq group;
    // Create a datagram socket on which to receive.
    int udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_fd < 0) {
        perror("opening datagram socket");
        exit(1);
    }
    /*Enable SO_REUSEADDR to allow multiple instances of this application
    to receive copies of the multicast datagrams.*/
    {
        int reuse = 1;

        if (setsockopt(udp_fd, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof(reuse)) < 0) {
            perror("setting SO_REUSEADDR");
            close(udp_fd);
            exit(1);
        }
    }
    // Bind to the proper port number with the IP address specified as INADDR_ANY.
    memset((char *) &local_sock, 0, sizeof(local_sock));
    local_sock.sin_family = AF_INET;
    local_sock.sin_port = htons(3000);
    local_sock.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(udp_fd, (struct sockaddr *) &local_sock, sizeof(local_sock))) {
        perror("binding datagram socket");
        close(udp_fd);
        exit(1);
    }
    /* Join the multicast group 225.1.1.1 on the local 9.5.1.1
   * interface.  Note that this IP_ADD_MEMBERSHIP option must be
   * called for each local interface over which the multicast
   * datagrams are to be received.   */
    group.imr_multiaddr.s_addr = inet_addr("225.1.1.1");
    group.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(udp_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &group, sizeof(group)) < 0) {
        perror("adding multicast group");
        close(udp_fd);
        exit(1);
    }
}

static void join_multicast_thread_cb (GTask         *task,gpointer       source_object,
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
  retval = join_multicast ();
  g_task_return_int (task, retval);
}

static void join_multicast_data_free (gpointer *data){
 // free_param (data->param1);
  //free_param (data->param2);

  //g_free (data);
}

void join_multicast_async ( GCancellable         *cancellable,
                              GAsyncReadyCallback   callback,
                              gpointer              user_data){
  GTask *task = NULL;  /* owned */
  //SomeBlockingFunctionData *data = NULL;  /* owned */
  gpointer *data = NULL;

  g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

  task = g_task_new (NULL, cancellable, callback, user_data);
  g_task_set_source_tag (task, join_multicast_async);

  /* Cancellation should be handled manually using mechanisms specific to
   * some_blocking_function(). */
  g_task_set_return_on_cancel (task, FALSE);

  //g_task_set_task_data (task, data, join_multicast_data_free); //investigar porque da error al compilar

  /* Run the task in a worker thread and return immediately while that continues
   * in the background. When it’s done it will call @callback in the current
   * thread default main context. */
  g_task_run_in_thread (task, join_multicast_thread_cb);

  g_object_unref (task);
}

int join_multicast_finish (GAsyncResult  *result,
                               GError       **error){
  g_return_val_if_fail (g_task_is_valid (result,
                                         join_multicast_async), -1);
  g_return_val_if_fail (error == NULL || *error == NULL, -1);

  return g_task_propagate_int (G_TASK (result), error);
}
