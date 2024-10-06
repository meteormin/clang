#include "http.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

HTTPConfig parse_config(int argc, char *argv[]) {
  HTTPConfig config;
  config.port = DEFAULT_PORT;
  config.doc_root = DEFAULT_ROOT_DIR;
  config.client_buffer_size = DEFAULT_BUFFER_SIZE;

  int opt;
  while ((opt = getopt(argc, argv, "p:d:b:")) != -1) {
    switch (opt) {
    case 'p':
      config.port = atoi(optarg);
      break;
    case 'd':
      config.doc_root = optarg;
      break;
    case 'b':
      config.client_buffer_size = atoi(optarg);
      break;
    default:
      fprintf(stderr,
              "Usage: %s [-p port] [-d document_root] [-b buffer_size]\n",
              argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  printf("HTTP configuration:\n");
  printf("Port: %d\n", config.port);
  printf("Document Root: %s\n", config.doc_root);
  printf("Client Buffer Size: %d\n", config.client_buffer_size);

  return config;
}

int main(int argc, char *argv[]) {
  printf("Simple-HTTP.\n");

  HTTPConfig cfg = parse_config(argc, argv);

  Server server;
  if (server_init(&server, cfg.port) == 0) {
    server_run(&server, cfg.client_buffer_size, cfg.doc_root);
  }

  return 0;
}
