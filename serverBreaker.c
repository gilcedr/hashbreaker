#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024
#define QUIT  "quit"
#define MODE_HASHBREAKER "mode hashbreaker"
#define MAX 32
#define MAX_RETRY 20

int sockid;
int isCondensat = 0;
int design_gilS();

struct sockaddr_in server_addr;

void signalErrors() {
    perror("\033[1;31mServer_Root detect something wrong and stop it.\033[0m\n");
    exit(EXIT_FAILURE);
}

void sendData(const char *msg, int client_sockid) {
    if (send(client_sockid, msg, strlen(msg), 0) == -1) {
        signalErrors();
    }
}

ssize_t receiveData(int client_sockid, char *buffer, size_t buffer_size) {
    ssize_t recv_len = recv(client_sockid, buffer, buffer_size - 1, 0);
    if (recv_len == -1) {
        signalErrors();
    }
    buffer[recv_len] = '\0';
    return recv_len;
}

void hashbreakFile(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        // Tentative d'ouverture en mode écriture pour créer le fichier s'il n'existe pas
        file = fopen(filename, "w");
        if (!file) {
            return;
        }
    }

    fprintf(file, "%s\n", data);

    fclose(file);
}

void sendCondensats(int client_sockid, const char *condensatFile) {
    FILE *file = fopen(condensatFile, "r");
    if (!file) {
        return;
    }

    char line[MAX_BUFFER_SIZE];
    char hash[MAX * 2 + 1];

    while (fgets(line, sizeof(line), file) != NULL) {
        size_t line_length = strlen(line);
        if (line_length > 0 && line[line_length - 1] == '\n') {
            line[line_length - 1] = '\0';
        }
        strcpy(hash, line);
	printf("\n");
	printf("Condensat send to client : %s \n", hash);
        sendData(hash, client_sockid);

        // Logiue: on est sûr d'envoyer le prochain hash que lorsque on a une reponse du client apr un délais else on envoie un prchn hash
        bool hashFound = false;
        while (!hashFound) {
            char tmp[MAX_BUFFER_SIZE];
            receiveData(client_sockid, tmp, sizeof(tmp));
            if (strlen(tmp) == 0) {
                sleep(30);
            } else {
		printf("\n");
                printf("\033[32m Hash Trouver %s\033[0m \n", tmp);
		hashbreakFile("hashFound.txt", tmp);
		sendData(hash, client_sockid);
                hashFound = true;
            }
        }

    }

    fclose(file);
}


int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Use : %s <server_ip> <server_port> <hash_list> \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    design_gilS();

    sockid = socket(AF_INET, SOCK_STREAM, 0);
    if (sockid == -1) {
        fprintf(stderr, "\033[1;31m[-] Init of Socket Failed\033[0m\n");
        signalErrors();
    }
    printf("\033[32m[+] Init of Socket Done\033[0m\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockid, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("\033[1;31m[-] Bind Failed\033[0m\n");
        signalErrors();
    }
    printf("\033[32m[+] Bind Done\033[0m\n");

    if (listen(sockid, 1) == -1) {
        perror("\033[1;31m[-] Listen Failed\033[0m\n");
        signalErrors();
    }
    printf("\033[32m[+] Serveur waiting to new Connexion Client loading.........\033[0m\n");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_sockid = accept(sockid, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client_sockid == -1) {
            perror("[-]\033[1;31mEchec de Connexion. File descriptor Client_sockid Failed.\033[0m\n");
            signalErrors();
        }

        printf("[+] Connexion accepted ip: %s port : %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        printf("\n");
        printf("Wecome to cmd. Entrez 'mode hashbreaker'  ou 'quit' to exit \n");

        printf("\n");
        char input[MAX * 2 + 1];
        while (1) {
            printf(" Server_GIL  > ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            if (strcmp(input, QUIT) == 0) {
                sendData(input, client_sockid);
                printf(" Server_ROOT > 'quit'. Fermeture...\n");
                close(client_sockid);
                close(sockid);
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(input, MODE_HASHBREAKER) == 0) {
                printf(" Server_HASH > Mode HashBreaker activé \n");
                printf(" Server_HASH > En attente d'une demande de condensat....... \n");

                while (!isCondensat) {
                    receiveData(client_sockid, input, sizeof(input));
                    if (strlen(input) == 0) {
                        sleep(30);
                    }
                    else {
                        isCondensat = 1;
                    }
                }
                printf("\n");
                printf("\033[32mDemande de Condensat reçue.\033[0m\n");
                printf("\n");
                printf(" Server_HASH > Demande de Condensat du Client confirmée \n");
                printf(" Server_HASH > Attack par ForceBrut via le Client......\n");
                sendCondensats(client_sockid, argv[3]);
            }
            else {
                printf("Entrée invalide. Veuillez saisir 'quit' ou 'mode hashbreaker'.\n");
            }
        }
    }
    close(sockid);

    return 0;
}

