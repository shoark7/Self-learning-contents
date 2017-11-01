#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

// 서버의 포트주소와 IP주소를 뜻한다. IP주소는 루프백 주소를 활용했다.
// 이 주소는 인터넷 연결이 되어있지 않아도 동작한다.
#define PORT 9000
#define IPADDR "127.0.0.1"

char buffer[BUFSIZ];

int main()
{
	int c_socket;
	struct sockaddr_in c_addr;
	// c_addr의 크기를 뜻한다. 즉, sizeof(c_addr)을 뜻한다.
	int len;

	char rcvBuffer[BUFSIZ];

	char *temp;
	int length = 0;

	int n;

	// 1. 소켓을 생성
	c_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2. 연결할 서버의 주소를 생성한다. 서버의 IP주소로 127.0.0.1을, 포트 번호로 9000번을 사용한다.
	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);

	// 3. 소켓을 주소에 연결한다. 연결 소켓인 c_socket으로 구조체 변수 c_addr에 설정된 주소(127.0.0.1와 9000)에 연결한다.
	if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr)) == -1) {
		printf("Can not connect\n");
		close(c_socket);
		return -1;
	}

	/* 4. 서비스 요청과 처리 

	   * 사용자로부터 ls를 입력받아 서버로 전송하고, 서버로부터 전송받은 파일 목록을 읽어 화면에 출력한다.
	   * 중간에 rcvbuffer어쩌고 하는 라인은 서버가 전송한 자료를 1바이트씩 읽어서 rcvBuffer에 저장한다.
	     read함수는 EOF를 읽으면 0을 반환한다. 그러므로 이 작업은 EOF를 수신할 때까지 계속된다. 
		 그런데 EOF는 서버가 close함수를 호출해서 연결을 종료하면 전송하게 된다.

	   * 예를 들어 서버가 문자열 'abc defg'의 8바이트를 보내고 close함수로 클라이언트와의 연결을 끊었다고 가정하면 
	     서버로부터 'a', 'b', 'c', ' ', 'd', 'e', 'f', 'g'의 8개의 문자와 EOF를 받게 된다. 
		 클라이언트는 read함수로 1바이트씩 읽어 rcvBuffer에 저장하다가 EOF를 만나면 read함수는 0을 반환하고 서버로부터 자료 읽기를 중단한다.
	 */

	scanf("%s", buffer);
	buffer[strlen(buffer)] = '\0';
	// write의 프로토타입은 다음과 같다. 필요한 헤더는 sys/types.h, sys/stat.h, unistd.h
	// ssize_t write(int fd, void *buf, size_t size);
	if((n = write(c_socket, buffer, strlen(buffer) + 1)) < 0) {
		printf("write error\n");
		exit(-1);
	}

	temp = rcvBuffer;
	while((n = read(c_socket, temp, 1)) > 0) {
		if(length == BUFSIZ) break;
		temp++; length++;
	}

	rcvBuffer[length] = '\0';

	printf("received Data : %s\n", rcvBuffer);
	// 5. 소켓 연결을 종료
	// 55번 줄에서는 서비스가 모두 끝나서 서버와 통신했던 연결 소켓(c_socket)을 닫는다. 전화를 끊는 과정이다.
	close(c_socket);
}
