#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

int main() {
    int srcFile, destFile;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    srcFile = open("lab2_ex3_origem.txt", O_RDONLY);
    if (srcFile == -1) {
        perror("Erro ao abrir o arquivo de origem");
        exit(EXIT_FAILURE);
    }

    destFile = open("lab2_ex3_destino.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFile == -1) {
        perror("Erro ao abrir/criar o arquivo de destino");
        close(srcFile);
        exit(EXIT_FAILURE);
    }

    while ((bytesRead = read(srcFile, buffer, BUFFER_SIZE)) > 0) {
        char *bufferPtr = buffer;  // Ponteiro para rastrear posição no buffer

        while (bytesRead > 0) {
            bytesWritten = write(destFile, bufferPtr, bytesRead);
            if (bytesWritten == -1) {
                perror("Erro ao escrever no arquivo de destino");
                close(srcFile);
                close(destFile);
                exit(EXIT_FAILURE);
            }
            bytesRead -= bytesWritten;
            bufferPtr += bytesWritten;
        }
    }

    if (bytesRead == -1) {
        perror("Erro ao ler o arquivo de origem");
    }

    if (close(srcFile) == -1 || close(destFile) == -1) {
        perror("Erro ao fechar os arquivos");
        exit(EXIT_FAILURE);
    }

    return 0;
}
