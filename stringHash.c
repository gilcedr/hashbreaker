#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/evp.h>
#include "client.h"

#define MAX 32
#define MD5_DIGEST_LENGTH 16


void calculate_md5(const char *input, unsigned char *md5_result) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    OpenSSL_add_all_digests();
    md = EVP_get_digestbyname("md5");
    if (!md) {
        fprintf(stderr, "MD5 not supported!\n");
        exit(EXIT_FAILURE);
    }
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input, strlen(input));
    unsigned int md_len;
    EVP_DigestFinal_ex(mdctx, md5_result, &md_len);
    EVP_MD_CTX_free(mdctx);
}

void generate_combinations(char *prefix, int prefix_length, int remaining_characters, const char *hash, int sockfd) {
    if (remaining_characters == 0) {
        unsigned char md5_result[MD5_DIGEST_LENGTH];
        calculate_md5(prefix, md5_result);

        printf(" -[FORCE BRUTE] > string generate : %s - Hash : ", prefix);
        char str_hash[MD5_DIGEST_LENGTH*2 + 1];
       for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
            sprintf(&str_hash[i*2], "%02x", (unsigned int)md5_result[i]);
        }
        printf("%s\n", str_hash);

        if (strlen(hash) != strlen(str_hash)) {
            printf("Erreur : Les tailles de condensatLine et str_hash ne sont pas égales !\n");
            exit(EXIT_FAILURE);
        }

        if (strcmp(str_hash, hash) == 0) {
            printf("\033[32mMOt de passe trouvé : %s\033[0m\n", prefix);
            char plaintext_and_hash[MAX * 4 + 2];
            snprintf(plaintext_and_hash, sizeof(plaintext_and_hash), "%s: %s", prefix, hash);
            sendData(plaintext_and_hash, sockfd);
            memset(plaintext_and_hash, 0, sizeof(plaintext_and_hash));
            str_hash[0] = '\0';
            generate_combinations("", 0, 1, hash, sockfd);
            return;
        }
        return;
    }
    for (int i = 0; i < 10; i++) {
        char next_character = '0' + i;
        char *new_prefix = (char *)malloc((prefix_length + 2) * sizeof(char));
        strcpy(new_prefix, prefix);
        new_prefix[prefix_length] = next_character;
        new_prefix[prefix_length + 1] = '\0';
        generate_combinations(new_prefix, prefix_length + 1, remaining_characters - 1, hash, sockfd);
        free(new_prefix);
    }
    for (int i = 0; i < 26; i++) {
        char next_character = 'a' + i;
        char *new_prefix = (char *)malloc((prefix_length + 2) * sizeof(char));
        strcpy(new_prefix, prefix);
        new_prefix[prefix_length] = next_character;
        new_prefix[prefix_length + 1] = '\0';
        generate_combinations(new_prefix, prefix_length + 1, remaining_characters - 1, hash, sockfd);
        free(new_prefix);
    }
    for (int i = 0; i < 26; i++) {
        char next_character = 'A' + i;
        char *new_prefix = (char *)malloc((prefix_length + 2) * sizeof(char));
        strcpy(new_prefix, prefix);
        new_prefix[prefix_length] = next_character;
        new_prefix[prefix_length + 1] = '\0';
        generate_combinations(new_prefix, prefix_length + 1, remaining_characters - 1, hash, sockfd);
        free(new_prefix);
    }
}

void start_bruteforce(const char *hash, int sockfd) {
    char sequence_after_e[] = {'E', 'q', 'i',  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'p'};
    int sequence_length = sizeof(sequence_after_e) / sizeof(sequence_after_e[0]);
    for (int i = 0; i < sequence_length; i++) {
        char *prefix = (char *)malloc(2 * sizeof(char));
        prefix[0] = sequence_after_e[i];
        prefix[1] = '\0';
        generate_combinations(prefix, 1, 4, hash, sockfd);
        free(prefix);
    }

}

