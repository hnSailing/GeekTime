#ifndef __COMMON_H_
#define __COMMON_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <error.h>
#include <errno.h>
#include <signal.h>

#define MAXLINE	4096
#define SERV_PORT 6633
#define LISTENQ	128

size_t readn(int fd, void *buffer, size_t size);
size_t read_message(int fd, char *buffer, size_t length);

int tcp_server(int port);
int tcp_client(char *address, int port);

#endif
