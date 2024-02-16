#ifndef HASHBRUTEFORCE_H
#define HASHBRUTEFORCE_H
#include <string.h>


void calculate_md5(const char *input, unsigned char *md5_result);
void generate_combinations(char *prefix, int prefix_length, int remaining_characters, const char *hash, int sockfd);
void start_bruteforce(const char *hash, int sockfd);

#endif
