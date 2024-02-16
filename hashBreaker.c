#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "hashBruteForce.h"

#define REQUEST_HASH "demande de hash"
#define QUIT_MESSAGE "quit"
#define MODE_HASHBREAKER "demande de hash"
#define MAX 32
#define MAX_BUFFER_SIZE 1024

int requestCondensat = 0;
int gil_design();

void signalErrors() {
    perror("\033[1;31mSignalErrors detect something wrong and stop it.\033[0m\n");
    exit(EXIT_FAILURE);
}

void sendData(const char *msg, int sockfd) {
    if (send(sockfd, msg, strlen(msg), 0) == -1) {
        signalErrors();
    }
}

ssize_t receiveData(int sockfd, char *buffer, size_t buffer_size) {
    ssize_t recv_len = recv(sockfd, buffer, buffer_size - 1, 0);
    if (recv_len == -1) {
        signalErrors();
    }
    buffer[recv_len] = '\0';
    return recv_len;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Use: %s <server_ip> <server_port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    gil_design();
    // Initialisation du socket TCP
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        fprintf(stderr, "\033[1;31m[-] Init of the Socket Failed\033[0m\n");
        signalErrors();
    }
    printf("\033[32m[+] Init of the Socket Done\033[0m\n");
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("\033[1;31m[-] Connexion to Server Failed\033[0m\n");
        signalErrors();
    }
    printf("\033[32m[+]Connected to the server\033[0m\n");
    printf("\n");
    printf("\n");
    printf("Welcome sur le Cmd Client. Entrez  'demande de hash' ou 'quit' pour exit\n");
    printf("\n");
    printf("\n");
    while (1) {
        char input[MAX * 2 + 1];
        printf(" Client > ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, QUIT_MESSAGE) == 0) {
            sendData(input, sockfd);
            printf(" Client > 'quit'. Exiting...\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        } else if (strcmp(input, MODE_HASHBREAKER) == 0) {
            printf("\033[32m hashBreaker  >  HashBreaker Enable\033[0m\n");
                // Demande de Condensat
            sendData(input, sockfd);
            while (!requestCondensat) {
                char hash[MAX * 2 + 1];
                memset(hash, 0, sizeof(hash));
                receiveData(sockfd, hash, sizeof(hash));

                if (strlen(hash) == 0) {
                    printf(" hashBreaker > Waiting for Server request......\n");
                } else {
                    printf(" hashBreaker > Client  Received hash: %s\n", hash);
                    printf(" hashBreaker > Initialisation de l'attaque par Force Brute sur String... \n");
                    sleep(9);
                    start_bruteforce(hash, sockfd);
                    requestCondensat = 0;
                    memset(hash, 0, sizeof(hash));
                }
            }
        } else {
            printf("Entrée invalide. Veuillez saisir 'quit' ou 'mode hashbreaker'.\n");
        }
    }
    close(sockfd);

    return 0;
}

