#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9000

char buffer[BUFSIZ] = "hello, world";
char rBuffer[BUFSIZ];

int main()
{
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int n, i;

	char *temp;
	int length;

	s_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&s_addr, 0, sizeof(s_addr));
	// 어떤 IP라도 받아들이기 위해서 INADDR_ANY를 사용하는 것이다!
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_familiy = AF_INET;
	s_addr.sin_port = htons(PORT);

	// bind와 listen은 서버의 주소, 서버의 소켓을 넘기면 된다.
	if(bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
		printf("Can not Bind\n");
		return -1;
	}

	if(listen(s_socket, 5) == -1) {
		printf("listen Fail\n");
		return -1;
	}

	// 사실상 무한루프 안쪽은 c_socket의 영역이다.
	for(;;) {
		len = sizeof(c_addr);
		// 그리고 accept()의 반환형은 소켓 식별자가 되는데 이는 c_socket으로 받아주고 활용해야 한다.
		// accept()의 프로토타입은 int accept(int socket, struct sockaddr *clientAddress, socklen_t *addressLength)
		// 주의 할 점은 3가지! 1. 클라이언트의 소켓을 넘겨야 한다 2. 클라이언트의 주소를 넘겨야 한다 3. 소켓 길이를 넘기되, 그 주소를 넘겨야 한다.
		c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);

		length = 0;
		temp = rBuffer;
		while((n = read(c_socket, temp, 1)) > 0) {
			if(*temp == '\r') continue;
			if(*temp == '\n') break;
			if(*temp == '\0') break;

			if(length == BUFSIZ) break;
			temp++; length++;
		}

		// 문자열을 완성시키기 위해서 맨 마지막에는 널 문자를 넣는다.
		rBuffer[length] = '\0';

		// 만약 "print" 문자열이 rBuffer에 있다면, 문자열을 클라이언트로 보내는 코드가 실행된다.
		if(!strcmp(rBuffer, "print")) {
			n = strlen(buffer);
			write(c_socket, buffer, n);
		}
		close(c_socket);
	}
	close(s_socket);
}
