static void cb(){
  if (FILE *fp = fopen(filePath, "rb")) {
        size_t readBytes;
        char buffer[8192];
        int s = 0;
        while ((readBytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
            if (send(clientSocket, buffer, readBytes, 0) != readBytes) {
                perror("");
                //handleErrors();
                break;
            }
            s+=readBytes;
        }
}
