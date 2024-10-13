#include "chat.h"

// 수신 메시지를 처리하는 스레드
void *receive_messages(void *arg) {
  int sock = *(int *)arg;
  char buffer[BUFFER_SIZE];
  while (1) {
    int bytes = recv(sock, buffer, sizeof(buffer), 0);
    if (bytes <= 0) {
      printf("Disconnected from server.\n");
      break;
    }
    buffer[bytes] = '\0';

    // 수신한 메시지를 출력하고, 입력 프롬프트를 새 줄에서 표시
    printf("\r%s\n> ", buffer); // 수신한 메시지 출력
    fflush(stdout);             // 출력 버퍼 플러시
  }
  return NULL;
}

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Socket creation failed");
    return 1;
  }

  struct sockaddr_in server_addr;
  char ip[16];
  int port;

  // IP와 포트 입력 받기
  printf("Enter server IP: ");
  scanf("%15s", ip);
  printf("Enter server port: ");
  scanf("%d", &port);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip, &server_addr.sin_addr);

  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed");
    return 1;
  }

  char username[32];
  printf("Enter your username: ");
  scanf("%31s", username);

  // 서버에 사용자 이름 전송
  send(sock, username, sizeof(username), 0);

  pthread_t tid;
  pthread_create(&tid, NULL, receive_messages, (void *)&sock);

  char message[BUFFER_SIZE];
  while (1) {
    printf("> "); // 프롬프트 출력
    fgets(message, BUFFER_SIZE, stdin);

    // 메시지에 사용자 이름 추가
    char full_message[BUFFER_SIZE];
    snprintf(full_message, sizeof(full_message), "%s: %s", username, message);
    // 메시지를 보내기 전에 줄바꿈 제거
    full_message[strcspn(full_message, "\n")] =
        0; // Remove newline from message
    send(sock, full_message, strlen(full_message), 0);
  }

  close(sock);
  return 0;
}
