#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_BUFFER_LEN 30000

struct Server server_constructor(
    int domain,
    int protocol,
    int service,
    u_long interface,
    int port,
    int backlog,
    void (*launch)(struct Server *server),
    char *path
  )
{
  struct Server server;

  server.domain = domain;
  server.protocol = protocol;
  server.service = service;
  server.interface = interface;
  server.port = port;
  server.backlog = backlog;

  server.address.sin_family = domain;
  server.address.sin_port = htons(port);
  server.address.sin_addr.s_addr = htonl(interface);

  server.launch = launch;

  if (path != NULL) {
    server.file_path = path;
  } else {
    server.file_path = "index.html";
  }
  server.buffer_len = DEFAULT_BUFFER_LEN;

  server.socket = socket(domain, service, protocol);
  if (server.socket < 0)
  {
    perror("Socket creation failed\n");
    exit(1);
  }

  if (bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
  {
    perror("Socket binding failed\n");
    exit(1);
  };

  if (listen(server.socket, server.backlog) < 0)
  {
    perror("Socket listening failed\n");
    exit(1);
  };

  server.launch = launch;

  return server;
}

const char *HTML_HEADER = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Content-Length: %zu\r\n"
                          "\r\n";

char *get_response(struct Server *server)
{
  char buffer[30000];
  FILE *fp = fopen(server->file_path, "r");

  if (!fp)
  {
    perror("File not found\n");
    exit(1);
  }

  char html[30000];
  size_t html_len = fread(html, 1, DEFAULT_BUFFER_LEN, fp);
  fclose(fp);

  int header_len = snprintf(NULL, 0, HTML_HEADER, html_len);
  char *response = malloc(header_len + html_len + 1);
  if (!response)
  {
    perror("Failed to allocate response buffer\n");
    exit(1);
  }

   int response_len = snprintf(response, header_len + html_len + 1,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %zu\r\n"
        "\r\n"
        "%.*s",
        html_len, (int)html_len, html);
  
  return response;
}