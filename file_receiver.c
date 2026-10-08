char recv_dir[256];

struct FileInfo {
    char file_name[256];
    int file_size;
};
void read_file_bytes(int client_socket, const char *file_path, uintmax_t file_size) {
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
}

void receive_file(int client_socket){
    struct FileInfo file_info;
    if (recv(client_socket, &file_info, sizeof(file_info), 0) < 0)
        error("cannot read file info");
    char file_path[strlen(recv_dir)]; 
    //strcat(recv_dir, );
    read_file_bytes(client_socket, recv_dir, file_info.file_size);
}



