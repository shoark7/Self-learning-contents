#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>

char buf[BUFSIZ];
char data[] = "This is from sd[0]";

// 같은 프로세스 안에서 유닉스 소켓으로 통신하는 예제,
// 유닉스 소켓은 하나의 컴퓨터에서만 생성되고 실행되고 때문에,
// 실제 통신망에 연결된 두 컴퓨터 간에 자료를 송수신할 때 사용하기에는 한계가 있다.
// 즉 sd[0]과 sd[1]소켓은 모두 한 컴퓨터 상에 있기 때문에 구내 전화망에 비유되는 통신만을 할 수 있다.

// 참고로 프로세스는 파일/소켓 디스크립터 테이블과 그 인덱스만을 가진다.
// 실제로 명령을 수행하는 객체(파일)은 커널 안에 있다.
int main()
{
	int sd[2], result;
	int n1, n2;

	// 이 부분에서 주의해야 할 점이 있는데, AF_INET이나 AF_INET6로 사용하면 안된다.
	// 꼭 AF_UNIX나 AF_LOCAL로 인자를 넘겨야 하는데, 요즘엔 AF_LOCAL을 잘 쓰지 않는다.
	if((result = socketpair(AF_UNIX, SOCK_STREAM, 0, sd)) < 0) {
		printf("socketpair Fail()\n");
		return -1;
	}


	n1 = write(sd[0], data, strlen(data));
	printf("[send] %s\n", data);

	n2 = read(sd[1], buf, BUFSIZ);
	// 소켓으로 문자열을 주고받을 때는 반드시 필요한 절차다.
	buf[n2] = '\0';
	printf("[received] %s\n", buf);

	close(sd[0]);
	close(sd[1]);
}
