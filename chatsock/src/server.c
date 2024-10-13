#include "chat.h"

Client *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void add_client(Client *client) {
  pthread_mutex_lock(&clients_mutex);
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (!clients[i]) {
      clients[i] = client;
      break;
    }
  }
  pthread_mutex_unlock(&clients_mutex);
}

void remove_client(int sockfd) {
  pthread_mutex_lock(&clients_mutex);
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (clients[i] && clients[i]->sockfd == sockfd) {
      clients[i] = NULL;
      break;
    }
  }
  pthread_mutex_unlock(&clients_mutex);
}

void *client_handler(void *arg) {
  Client *cli = (Client *)arg;
  char buffer[BUFFER_SIZE];

  while (1) {
    int bytes = recv(cli->sockfd, buffer, sizeof(buffer), 0);
    if (bytes <= 0) {
      remove_client(cli->sockfd);
      close(cli->sockfd);
      free(cli);
      pthread_exit(NULL);
    } else {
      buffer[bytes] = '\0';
      printf("Received message: %s\n", buffer); // 수신한 메시지 출력
      broadcast_message(buffer, cli->sockfd);
    }
  }
}

void broadcast_message(const char *message, int sender_sock) {
  pthread_mutex_lock(&clients_mutex);
  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (clients[i] && clients[i]->sockfd != sender_sock) {
      send(clients[i]->sockfd, message, strlen(message), 0);
    }
  }
  pthread_mutex_unlock(&clients_mutex);
}

int main() {
  int server_sock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_addr;

  // 포트 입력 받기
  int port;
  printf("Enter server port: ");
  scanf("%d", &port);

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(server_sock, MAX_CLIENTS);

  printf("Chat server started on port %d\n", port);

  while (1) {
    Client *client = (Client *)malloc(sizeof(Client));
    socklen_t client_len = sizeof(client->address);
    client->sockfd =
        accept(server_sock, (struct sockaddr *)&client->address, &client_len);
    // 클라이언트 사용자 이름 수신
    recv(client->sockfd, client->username, sizeof(client->username), 0);
    add_client(client);
    printf("New client connected: %s\n", client->username);
    pthread_t tid;
    pthread_create(&tid, NULL, client_handler, client);
  }

  return 0;
}
