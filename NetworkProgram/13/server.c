#include "common.h"

int main(int argc, char **argv) {
	int socket_fd;
	int conn_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t cli_len;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		perror("create socket error!");
		return -1;
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERV_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))<0) {
		perror("bind error");
		return -1;
	}

	if(listen(socket_fd, LISTENQ)<0) {
		perror("listen error");
		return -1;
	}

	conn_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &cli_len);	
	if(conn_fd < 0) {
		perror("accept error");
		return -1;
	}
	while(1) {
		char buf[MAXLINE];
		bzero(buf, MAXLINE);
		int rn = read(conn_fd, buf, sizeof(buf));	
		if(rn < 0) {
			perror("read error");
		} else if (rn == 0) {
			printf("client closed\n");
			break;
		}
		printf("%s\n", buf);
	}
	return 0;
}
