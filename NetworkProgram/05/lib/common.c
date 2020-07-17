#include "common.h"

// 从socketfd描述符中读取size个字节
size_t readn(int fd, void *buffer, size_t size) {
	char *buffer_pointer = buffer;
	int length = size;

	while(length > 0) {
		int result = read(fd, buffer_pointer, length);

		if(result < 0) {
			if(errno == EINTR) 
				continue;		//考虑非阻塞的情况，这里需要再次调用read
			else
				return -1;
		} else if(result == 0) 
			break;				// EOF表示套接字关闭

		length -= result;
		buffer_pointer += result;
	}

	return (size - length);		// 返回的是实际读取的字节数
}
