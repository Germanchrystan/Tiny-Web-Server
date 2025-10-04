#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h" 
#include <string.h>

void launch(struct Server* server)
{
  char *response = get_response(server);
  char buffer[server->buffer_len];

  printf("======= Server launched! =======\n");
  while(1) {

    int addrlen = sizeof(server->address);
    int new_socket = accept(
      server->socket,
      (struct sockaddr*)&server->address,
      (socklen_t*)&addrlen
    );

    if (new_socket < 0) {
      perror("Server accept failed\n");
      exit(1);
    }

    read(new_socket, buffer, server->buffer_len);
    printf("%s\n", buffer);
    
    write(new_socket, response, strlen(response));
    close(new_socket);
  }
}

int main() {
  struct Server server = server_constructor(
    AF_INET,
    IPPROTO_TCP,
    SOCK_STREAM,
    INADDR_ANY,
    8080,
    10,
    launch,
    "index.html"
  );

  server.launch(&server);
}