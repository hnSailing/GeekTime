#include "common.h"

#define MAXLINE 1024

int main(int argc, char **argv) {
	if (argc != 2) {
		error(1, 0, "usage: unixstreamclient <local_path>");
	}	

	int sockfd;
	struct sockaddr_un servaddr;

	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(sockfd < 0) {
		error(1, errno, "create socket failed");
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, argv[1]);

	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		error(1, errno, "connect failed");
	}

	char send_line[MAXLINE];
	bzero(send_line, MAXLINE);
	char recv_line[MAXLINE];

	while(fgets(send_line, MAXLINE, stdin) != NULL) {
		int nbytes = strlen(send_line);
		if(write(sockfd, send_line, nbytes) != nbytes)
			error(1, errno, "write error");

		bzero(&recv_line, MAXLINE);
		if(read(sockfd, recv_line, MAXLINE) == 0)
			error(1, errno, "server terminated prematurely");

		fputs(recv_line, stdout);
	}

	exit(0);
}
