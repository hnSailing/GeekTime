#ifndef __COMMON_H_
#define __COMMON_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <error.h>
#include <errno.h>

size_t readn(int fd, void *buffer, size_t size);

#endif
