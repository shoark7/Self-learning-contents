#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9000
#define IPADDR "127.0.0.1"

int main()
{
	int c_socket;
	struct sockaddr_in c_addr;
	int len, n;

	char rcvBuffer[BUFSIZ];

	c_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);

	// 클라이언트가 서버에게 연결을 시도하도록 하는 함수!
	if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr)) == -1) {
		printf("Can not connect\n");
		close(c_socket);
		return -1;
	}

	// 리눅스 시스템 콜 read()가 맞다!
	if((n = read(c_socket, rcvBuffer, sizeof(rcvBuffer))) < 0) {
		return (-1);
	}

	rcvBuffer[n] = '\0';
	printf("received Data : %s\n", rcvBuffer);

	close(c_socket);
}
