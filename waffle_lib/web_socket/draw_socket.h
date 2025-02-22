/**
 * 
 *  AN ENTITRE CUSTOMIZABLE NET-SOCKET MODULE
 *  
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <vector>
#include <assert.h>
#include "__utils.h"
#include "__define_macros.h"
#include "__define_types.h"

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>

#elif defined(__linux__) || defined(__UNIX__)
#include <sys/socket.h>
#include <arpa/inet>

typedef unsigned int* SOCKET;
typedef int socklen_t;

#define SOCKET_ERROR -1
#define INVALID_SOCKET (SOCKET)(~0)
#endif

#define __USES_HTTP "HTTP/1.1"
#define BUFFER_SIZE 1024

typedef int SOCKET_FAM, SOCKET_TYPE, SOCKET_PROTO;
typedef u_short NET_HOST;

bool IS_LOCAL_ADDR = false;

int server_fd, client_fd;
int recv_bytes;
struct sockaddr_in* server_struct, client_struct;
socklen_t addrlen = sizeof(server_struct);

const char* HTTP_CODES[] = {
  "200 OK", "400 Bad Request", 
  "404 Not Found", "403 Method Not Allowed", 
  "410 Gone"
};

class sys_socket {
private:
  SOCKET_PROTO server_protocol;
  NET_HOST server_hostport;
  const char* server_addr;

protected:
  SOCKET_FAM server_family;
  SOCKET_TYPE server_type;
  int backlog;

public:
  sys_socket(SOCKET_FAM family = -1, SOCKET_TYPE type = -1,  SOCKET_PROTO protocol = -1):
  server_family(family), server_type(type), server_protocol(protocol) {}

  ~sys_socket() {}

  void init_data() {
    
    server_struct->sin_addr.s_addr = IS_LOCAL_ADDR? inet_addr(server_addr): INADDR_ANY;
    server_struct->sin_family = server_family;
    server_struct->sin_port = server_hostport;
    
  }

  bool IS_ERROR_SOCKET(SOCKET net_server, SOCKET net_client) {
    bool IS_ERROR_BIND_OR_LISTEN = false;

    bool IS_ERROR_BINDING = (bind(net_server, (struct sockaddr*)&server_struct, addrlen) == SOCKET_ERROR);
    bool IS_ERROR_LISTEN = (listen(net_server, READY_SERVER->BACKLOG_CLIENT) == SOCKET_ERROR);
    bool IS_INVALID_SOCKET = ((net_server == INVALID_SOCKET) || (net_client == INVALID_SOCKET));

    IS_ERROR_BIND_OR_LISTEN = (IS_ERROR_BINDING || IS_ERROR_LISTEN);

    return (IS_INVALID_SOCKET || IS_ERROR_BIND_OR_LISTEN);

  }

  /**
   *  Return a status code if `path` exists in given `routes`
   * 
   * Syntax: `HTTP_VERSION + STATUS_CODE`
   * 
   * 
  */
  char* __STATUS_ROUTE(const char* routes[], char* path){
    int index;
    char* response;
    int num_routes = sizeof(routes) / sizeof(routes[0]);

    for (index = 0; index < num_routes; index ++) {
      bool IS_EXISTENT_ROUTE = strcmp(path, routes[index]) == 0;
      response = IS_EXISTENT_ROUTE? strcat(__USES_HTTP, HTTP_CODES[0])
                                  : strcat(__USES_HTTP, HTTP_CODES[2]);
    }
    return response;
  }

  void handle_client(SOCKET client_fd, int recv_client_bytes, char* response) {
    int flag = 0;
    char method[10], *path, protocol[10];
    char* line = strtok(response, "\r\n");
    size_t count = ((_countof(method) * 2) + _countof(protocol));
    int matched = sscanf_s(line, "%9s %s %9s", method, path, protocol, (unsigned)count);

    char* http_message = __STATUS_ROUTE(READY_SERVER->HTTP_ROUTES, path);

    snprintf(response, sizeof(response), http_message, path);
    send(client_fd, response, strlen(response), flag);

  }

  void create_server() {
    this->init_data();
    server_fd = socket(server_struct->sin_family, this->server_type, this->server_protocol);
    client_fd = accept(server_fd, (struct sockaddr*)&server_addr, &addrlen);

    if (this->IS_ERROR_SOCKET(server_fd, client_fd)) perror("Cannot handle server connection due to an error: ");

    char buffer[BUFFER_SIZE];
    recv_bytes = recv(client_fd, buffer, BUFFER_SIZE, 0);
    this->handle_client(client_fd, recv_bytes, buffer);

  }





};

