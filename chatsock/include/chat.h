#ifndef CHAT_H
#define CHAT_H

#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

typedef struct {
  int sockfd;
  struct sockaddr_in address;
  char username[32]; // Store the username of the client
} Client;

void *client_handler(void *arg); // Client request handler
void broadcast_message(const char *message,
                       int sender_sock); // Message broadcasting function
void add_client(Client *client);         // Add client to the list
void remove_client(int sockfd);          // Remove client from the list

#endif
