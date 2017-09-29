#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9000
#define IPADDR "127.0.0.1"

char buffer[BUFSIZ];

int main()
{
	int c_socket;
	struct sockaddr_in c_addr;
	int len;

	char revBuffer[BUFSIZ];

	int n;

	c_socket = socket(PF_INET, SOCK_STREAM, IPPORTO_TCP);

	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);

	// connect의 경우 클라이언트 사이드에서만 사용하는 경우가 많고, 클라 소켓, 클라 주소 구조체를 인자로 넘긴다.
	if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr)) == -1) {
		printf("Can not connect\n");
		close(c_socket);
		return -1;
	}

	scanf("%s", buffer);
	buffer[strlen(buffer)] = '\0';
	write(c_socket, buffer, strlen(buffer)+1);

	// 연산자 우선순위를 조심하자!
	if((n = read(c_socket, rcvBuffer, sizeof(rcvBuffer))) < 0) {
		return (-1);
	}

	rcvBuffer[n] = '\0';
	printf("received Data : %s\n", rcvBuffer);

	close(c_socket);
}
