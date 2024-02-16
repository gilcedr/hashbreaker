#ifndef CLIENT_H
#define CLIENT_H

void sendData(const char *msg, int sockfd);
ssize_t receiveData(int sockfd, char *buffer, size_t buffer_size);
void start_bruteforce(const char *hash, int sockfd);


#endif
