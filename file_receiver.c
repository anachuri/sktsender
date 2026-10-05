char recv_dir[256];

struct FileInfo {
    char file_name[256];
    int file_size;
};
void read_file_bytes(int client_socket, const char recv_dir[256], uintmax_t file_size) {
    FILE *fp = fopen(recv_dir, "wb");
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
}

void receive_file(int client_socket){
    struct FileInfo file_info;
    if (recv(client_socket, &file_info, sizeof(file_info), 0) < 0)
        error("cannot read file info");
    strcat(recv_dir, file_info.file_name);
    read_file_bytes(client_socket, recv_dir, file_info.file_size);
}

void init(){
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
}


