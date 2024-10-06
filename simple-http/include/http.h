#ifndef HTTP_H
#define HTTP_H

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define DEFAULT_PORT 80 // HTTP 기본 포트
#define DEFAULT_BUFFER_SIZE 4096
#define DEFAULT_ROOT_DIR "./html"

#define NOT_FOUND "Not Found"
#define METHOD_NOT_ALLOWED "Method Not Allowed"

typedef struct {
  int sockfd;
  struct sockaddr_in address;
} Server;

typedef struct {
  int sockfd;
  struct sockaddr_in address;
} Client;

typedef struct {
  int port;
  char *doc_root;
  int client_buffer_size;
} HTTPConfig;

int server_init(Server *server, int port);

void server_run(Server *server, int buffer_size, const char *doc_root);

void handle_client_request(Client *client, int buffer_size,
                           const char *doct_root);

void send_response(int client_sock, int status_code, const char *content_type,
                   const char *body);

const char *get_mime_type(const char *path);

#endif
