#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../include/Practical.h"

#define BUFSIZE 512

int main(int argc, char *argv[])
{
	if(argc < 3 || argc > 4) // 명령어 인자의 정확한 개수를 확인한다.
		DieWithUserMessage("Parameter(s)",
				"<Server Address> <Echo Word> [<Server Port>]");

	char *servIP = argv[1];     // 첫 번째 인자: 서버 IP 주소(dotted형식)
	char *echoString = argv[2]; // 두 번째 인자: 보내려는 에코 문자열

	// 세 번째 인자(선택): 서버 포트(숫자형식). 7이 잘 알려진 포트(에코 서버 사용시 Well-known port임)로 생략 시 7을 사용한다.
	in_port_t servPort = (argc == 4) ? atoi(argv[3]) : 7;

	// TCP를 사용하여 안정된 스트림 소켓을 생성한다. 인자는 차례대로 int domain, int type, int protocol)이다.
	// 반환 값으로는 소켓 식별자(int)를 반환하는데, 파일 디스크립터를 생각하면 쉽게 이해할 수 있다.
	// 맨 앞은 네트워크 계층으로 어떤 프로토콜을 선택할 것인지 고른다. 주로  AF_INET, PF_INET을 많이 고르는데, 둘은 같은 것을 가리킨다.
	// 둘째는 어떤 타입의 소켓을 만들것인지 고른다. SOCK_STREAM, SOCK_DGRAM이 준비되어 있는데, 앞은 TCP소켓이고, 뒤는 UDP소켓이다.
	// 셋째는 protocol이다. 전송계층의 프로토콜로 어떤것을 고를지 선택하면 된다. 주로 IPPOTO_TCP와 IPPROTO_UDP가 있다.
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0)
		DieWithSystemMessage("socket() failed");

	// 서버 구조체 생성 -> 버클리 소켓 API에서 제공하는 자료구조는 어느정도 익힐 필요가 있다. 이것도 표로 제공하자.
	struct sockaddr_in servAddr;            // 서버주소
	memset(&servAddr, 0, sizeof(servAddr)); // 0으로 구조체 초기화 -> 관련 구조체들은 항상 memset()으로 초기화를 해야 한다는 점을 잊지 말자!
	servAddr.sin_family = AF_INET;          // IPv4 주소 패밀리

	// 주소 변환
	int rtnVal= inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
	if(rtnVal == 0)
		DieWithUserMessage("inet_pton() failed", "invalid address string");
	else if(rtnVal < 0)
		DieWithSystemMessage("inet_pton() failed");
	servAddr.sin_port = htons(servPort); // 서버 포트

	// 에코 서버(즉 서버에 연결을 설정한다.)에 연결 설정, connect()의 프로토타입은 다음과 같다.
	// int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) connect가 성공하면 양수를 반환하고, 실패하면 음수를 반환한다.
	// 첫번째 인자는 연결할 소켓 식별자를 받는다. 물론 소켓이 만들어져 있어야 할 것이다.
	// 두번째 인자는 struct sockaddr타입의 변수나 또는 형변환이 허용되는 타입의 변수여야 한다. 소켓의 주소를 담고 있다.
	// 세번째 인자는 소켓 주소의 길이를 뜻한다. 문제는 따로 typedef가 되어 있다는 점을 주의해야 한다.
	if(connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		DieWithSystemMessage("connect() failed");

	size_t echoStringLen = strlen(echoString); // 입력받은 문자열의 길이를 확인

	// 서버에 에코 문자열을 전송한다. send()의 프로토타입은 다음과 같다.
	// ssize_t send(int sockfd, void *buf, size_t len, int flags) 반환값으로 메시지의 길이(즉, 메시지 문자열의 길이)를 반환한다. send()가 실패하면 음수를 반환한다.
	// 첫번째 인자는 int sockfd다. TCP연결의 경우, 미리 connect() 되어 있는 socket만 recv()의 인자가 될 수 있다.
	// 두번째 인자는 void *buf다. 이는 서버로 보낼 데이터의 주소를 가리키도록 한다.
	// 세번째 인자는 size_t len이다. 이는 서버로 보낼 데이터의 길이를 나타내도록 한다.
	// 네번째 인자는 int flags다. 매크로로 정의된 몇가지 flag가 존재하지만 여기서는 그냥 0(default)으로 인자를 주기로 한다.

	ssize_t numBytes = send(sock, echoString, echoStringLen, 0);
	if(numBytes < 0)
		DieWithSystemMessage("send() failed");
	else if(numBytes != echoStringLen)
		DieWithUserMessage("send()", "sent unexpected number of bytes");

	// 서버로부터 동일한 문자열을 수신한다.

	unsigned int totalBytesRcvd = 0; // 수신한 문자 개수
	fputs("Received: ", stdout);     // 돌려받은 에코 문자열 출력을 위한 설정
	while(totalBytesRcvd < echoStringLen) {
		char buffer[BUFSIZE]; // 입/출력 버퍼
		/* 버퍼 크기(byte) 만큼 서버로 부터 수신
		   (널 문자를 위해 1바이트 남겨놓음) */
		// recv()는 송신대신 수신한다는 것만 제외한다면 인자나 기타 다른 것이 완전히 같다. 
		numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
		if(numBytes < 0)
			DieWithSystemMessage("recv() failed");
		else if(numBytes == 0)
			DieWithUserMessage("recv()", "connection closed prematurely");
		totalBytesRcvd += numBytes; // 총 받은 크기를 기록
		buffer[numBytes] = '\0';    // 널 문자를 추가하여 문자열 완성!
		fputs(buffer, stdout);      // 에코 버퍼를 출력한다.
	}

	fputc('\n', stdout); // 마지막으로 개행문자 출력

	close(sock);
	exit(0);
}

