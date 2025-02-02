#define __TPOOL_H__

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "__define_types.h"


typedef int SOCKET_FAM, SOCKET_TYPE, SOCKET_PROTO;
typedef u_short NET_HOST;

bool IS_LOCAL_ADDR = false;

typedef struct {
  char* HTTP_ROUTES[50];
  char* SERVER_ADDR;
  NET_HOST SERVER_HOSTPORT;
  int BACKLOG_CLIENT;
} *__P_READY_SERVER;

__P_READY_SERVER READY_SERVER;

