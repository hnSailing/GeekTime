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

size_t read_message(int fd, char *buffer, size_t length) {
	u_int32_t msg_length;
	u_int32_t msg_type;

	int rc;

	rc = readn(fd, (char *)&msg_length, sizeof(u_int32_t));
	if (rc != sizeof(u_int32_t)) 
		return rc< 0?-1:0;

	msg_length = ntohl(msg_length);

	rc = readn(fd, (char*)&msg_type, sizeof(msg_type));
	if (rc != sizeof(u_int32_t))
		return rc<0?-1:0;

	if (msg_length > length) {
		return -1;
	}

	rc = readn(fd, buffer, msg_length);
	if (rc != msg_length)
		return rc < 0?-1:0;

	return rc;
}

