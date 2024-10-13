#include "http.h"
#include <stdio.h>
#include <string.h>

int server_init(Server *server, int port) {
  server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (server->sockfd < 0) {
    perror("failed create socket.");
    return -1;
  }

  server->address.sin_family = AF_INET;
  server->address.sin_addr.s_addr = INADDR_ANY;
  server->address.sin_port = htons(port);

  if (bind(server->sockfd, (struct sockaddr *)&server->address,
           sizeof(server->address)) < 0) {
    perror("failed binding");
    return -1;
  }

  if (listen(server->sockfd, 10) < 0) {
    perror("failed listen");
    return -1;
  }

  printf("Server Listen on %d port...\n", port);
  return 0;
}

void server_run(Server *server, int buffer_size, const char *doc_root) {
  while (1) {
    Client client;
    socklen_t client_len = sizeof(client.address);
    client.sockfd =
        accept(server->sockfd, (struct sockaddr *)&client.address, &client_len);
    if (client.sockfd < 0) {
      perror("failed connect client");
      continue;
    }
    handle_client_request(&client, buffer_size, doc_root);
  }
}

void handle_client_request(Client *client, int buffer_size,
                           const char *doc_root) {
  char buffer[buffer_size];
  read(client->sockfd, buffer, buffer_size - 1);
  printf("request: %s\n", buffer);

  char method[16], path[256];
  sscanf(buffer, "%s %s", method, path);
  if (strcmp(method, "GET") != 0) {
    send_response(client->sockfd, 405, "text/plain", METHOD_NOT_ALLOWED);
    return;
  }

  char full_path[512];
  snprintf(full_path, sizeof(full_path), "%s%s", doc_root, path);

  int file = open(full_path, O_RDONLY);
  if (file < 0) {
    send_response(client->sockfd, 404, "text/plain", NOT_FOUND);
    return;
  }

  const char *content_type = get_mime_type(full_path);
  char file_buffer[buffer_size];
  ssize_t bytes_read;

  dprintf(client->sockfd, "HTTP/1.1 200 OK\r\n");
  dprintf(client->sockfd, "Content-Type: %s\r\n\r\n", content_type);

  while ((bytes_read = read(file, file_buffer, buffer_size)) > 0) {
    write(client->sockfd, file_buffer, bytes_read);
  }
  close(file);
}

const char *get_mime_type(const char *path) {
  if (strstr(path, ".html"))
    return "text/html";
  if (strstr(path, ".css"))
    return "text/css";
  if (strstr(path, ".js"))
    return "application/javascript";
  if (strstr(path, ".png"))
    return "image/png";
  if (strstr(path, ".jpg") || strstr(path, ".jpeg"))
    return "image/jpeg";
  return "text/plain";
}

void send_response(int client_sock, int status_code, const char *content_type,
                   const char *body) {
  dprintf(client_sock, "HTTP/1.1 %d \r\n", status_code);
  dprintf(client_sock, "Content-Type: %s\r\n\r\n", content_type);
  dprintf(client_sock, "%s", body);
}
