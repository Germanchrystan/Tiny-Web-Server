#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>

struct Server {
  int domain;
  int protocol;
  int service;
  u_long interface;
  int port;
  int backlog;

  struct sockaddr_in address;

  void (*launch)(struct Server* server);

  int socket;
};

struct Server server_constructor(
  int domain,
  int protocol,
  int service,
  u_long interface,
  int port,
  int backlog,
  void (*launch)(struct Server* server)
);


#endif /* Server_h */
