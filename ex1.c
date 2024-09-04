#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    char buffer[128];
    ssize_t bytesLidos;

    fd = open("lab2_ex1.txt", O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    bytesLidos = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesLidos == -1) {
        perror("Erro ao ler o arquivo");
        close(fd);
        return 1;
    }

    buffer[bytesLidos] = '\0';
    printf("Conteúdo do arquivo:\n%s", buffer);

    close(fd);
    return 0;
}
