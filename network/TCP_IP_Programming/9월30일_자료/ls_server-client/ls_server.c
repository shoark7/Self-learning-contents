#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>

#define PORT 9000

char err_1[] = "Directory Error";
char rBuffer[BUFSIZ];

int main()
{
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len, length;
	int n, i;
	char *temp;

	// DIR과 struct dirent의 차이점은?
	DIR *dp;
	struct dirent *dir;

	// 1. (서버)소켓을 생성
	s_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2. 연결 요청을 받을 주소와 포트를 결정 
	// 서버가 포트 번호 9000으로 들어노는 클라이언트의 연결 요청을 받아들일 수 있도록 구조체 변수 s_addr에 주소와 포트를 결정하고 있다.
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);

	// 3. 소켓을 주소와 포트에 연결(자신의 포트 주소와 IP주소를 명시하는 함수가 bind())
	if(bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
		printf("Can not Bind\n");
		return -1;
	}

	// 4. 커널에 개통을 요청(또는 랑데뷰 소켓을 명시하고, 연결 대기 큐의 최대한도를 설정한다.)
	if(listen(s_socket, 5) == -1) {
		printf("listen Fail()\n");
		return -1;
	}

	// 5. 무한 반복: 서버가 클라이언트의 요청을 받아 처리하는 작업을 반복적으로 할 수 있도록 무한 반복 구조로 되어 있다.
	for(;;) {
		// 6. 연결 요청을 수신한다: 다음 2줄은 클라이언트가 서버로 연결 요청을 해서 3방향 핸드셰이킹(3-Way Handshaking)을 거쳐
		// 성립된 ESTABLISHED 상태의 연결 소켓을 accept함수를 통해 가져온다.
		len = sizeof(c_addr);
		c_socket = accept(s_socket, (struct sockaddr *) &c_addr, *len);

		length = 0;
		temp = rBuffer;
		// 7. 이 부분은 상호작용하는 소켓 프로그램을 만들때도 사용했던 코드다. 그런데 여기서 while루프는 파일 목록을 출력하는 로직을 맡고 있다.
		// 7 - 1.if(!strcmp(...))전까지는 명령을 수신하는 기능을 한다. 클라이언트로부터의 서비스 요청을 한 줄이 완성될 때까지 1바이트씩 읽어들인다.
		while((n = read(c_socket, temp, 1)) > 0) {
			if(*temp == '\r') continue;
			if(*temp == '\n') break;
			if(*temp == '\0') break;

			if(length == BUFSIZ) break;
			temp++; length++;

			rBuffer[length] = '\0';

			// 7 - 2. 서비스 처리: 이 줄은 클라이언트로부터의 명령이 ls인 경우 파일 목록을 읽어 클라이언트로 전송하는 기능을 한다.
			// 이 코드 조각은 현재 디렉토리의 파일 목록을 출력하는 프로그램을 응용한 것으로 60, 65, 66번에서처럼 파일 이름을 printf()로 화면에 출력하지 않고,
			// write()로 소켓을 총해 클라이언트로 전송하도록 수정하였다. 
			// 마지막으로 출력 중에 파일 이름과 파일 이름 사이에 빈 공간이 있도록 파일 이름 뒤에 1바이트를 추가해서 클라이언트에 전송하고 있다.
			if(!strcmp(rBuffer, "ls")) {
				if((dp = opendir(".")) == NULL) {
					write(c_socket, err_1, strlen(err_1));
				} else {
					while((dir = readdir(dp)) != NULL) {
						if(dir->d_ino == 0) continue;

						write(c_socket, dir->d_name, strlen(dir->d_name));
						write(c_socket, " ", 1);
					}
					closedir(dp);
				}
			}
			// 클라이언트와의 연결을 종료한다.
			close(c_socket);
		}
	}
	// 서버와의 연결을 종료한다.
	close(s_socket);
}

/*
	문자열 hello, world을 출력하는 소켓 프로그램에서는 서버가 한 번에 전송한 약속한 크기(12바이트)의 문자열만을 클라이언트가 수신하면 된다.
	하지만 방금 구현한 서버 프로그램에서는 크기가 정해져 있지 않은 파일 목록을 여러 차례에 걸쳐서 전송하기 때문에 서버는 클라이언트에게 파일 목록의 끝을 알려주어야 한다. 
	다행히 서버가 close() 클라이언트와의 연결을 끊으면 끝을 의미하는 EOF를 자동으로 클라이언트에게 전송하기 때문에 클라이언트는 이것으로 수신하는 자료의 끝을 확인하면 된다.

	서버가 다음과 같이 write()를 세 번 호출해서 클라이언트로 자료를 전송하고 close()로 연결을 끊으면, 클라이언트로 어떻게 자료가 전송되는지를 살펴보자.

	write(c_socket, "abc", 3);
	write(c_socket, " ", 1);
	write(c_socket, "defg", 4);
	close(c_socket);

	세번의 write()호출로 각각 "abc", " ", "defg"를 클라이언트로 전송할 때 전체 크기는 8바이트다. 그런 다음 close함수를 호출해서 EOF를 클라이언트로 전송한다. 
	클라이언트에서 read함수로 서버가 전송한 자료를 읽어 들일 때 EOF를 만나면 0을 반환하기 때문에 이를 검사하면 자료의 끝을 알 수 있다.
 */








