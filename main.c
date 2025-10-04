#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h" 
#include <string.h>
#define BUFFER_LEN 30000

void launch(struct Server* server)
{
  char buffer[BUFFER_LEN];
char *hello = "HTTP/1.1 200 OK\r\n"
              "Content-Type: text/html\r\n"
              "Content-Length: 70\r\n"
              "\r\n"
              "<!DOCTYPE html><html><body><h1>Hello, world!</h1></body></html>";  
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

    read(new_socket, buffer, BUFFER_LEN);
    printf("%s\n", buffer);
    
    write(new_socket, hello, strlen(hello));
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
    launch
  );

  server.launch(&server);
}