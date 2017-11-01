/*
	지금까지는 하나의 프로세스에서 socketpair()로 한 쌍의 소켓을 생성하고, 
	한쪽 소켓에서 자료를 전송하고 다른 쪽 자료를 전송받는 간단한 구조의 프로그램을 살펴보았다.
	이제부터는 프로세스 간의 통신 개념을 보다 명확하게 하기 위해서 fork()로 프로세스를 하나 더 만들겠다.
	이렇게 해서 두 프로세스 간에 소켓을 이용해서 자료를 송수신하는 프로그램을 다루어 보자.

	프로세스란 실행중인 프로그램을 말한다. 
	그리고 fork()는 호출하면 자신과 동일한 프로세스가 하나 더 생성된다.
	이 때 원래의 프로세스를 부모 프로세스라 하고, 새로 생성된 프로세스를 자식 프로세스라 한다.

	첨언: 보통 우리가 생각하는 일반적인 부모-자식 관계나 객체 지향 프로그래밍에서 상속을 떠올릴수도 있는데,
	내 생각에는 영화 아일랜드에서 나오는 복제인간이나 서유기에 나오는 손오공이 분신술을 사용하는 것을 생각하면 좀 더 이해가 빠를 것 같다.

 */
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>

const char data_parent[] = "From Parent";
const char data_child[] = "From Child";

char buf[BUFSIZ];

int main()
{
	int pid;
	int sd[2], result;

	result = socketpair(AF_UNIX, SOCK_STREAM, IPPROTO_TCP, sd);

	pid = fork();
	if(pid > 0) {           // 부모 프로세스
		close(sd[1]);

		read(sd[0], buf, BUFSIZ);
		printf("[parent:%d] %s\n", getpid(), buf);

		write(sd[0], data_parent, sizeof(data_parent));

		close(sd[0]);
	} else if(pid == 0) {   // 자식 프로세스
		close(sd[0]);

		write(sd[1], data_child, sizeof(data_child));
		read(sd[1], buf, BUFSIZ);
		printf("[child:%d] %s\n", getpid(), buf);

		close(sd[1]);
	} else if(pid == -1) {  // fork() 오류 발생에 대비하는 코드
		perror("fork()");
	}
}

// 일련의 과정이 모두 끝나면 부모/자식 프로세스 모두 필요한 출력을 하고 종료된다.
// 그리고 이제 프로세스 하나의 내부에서 서로 통신하는게 아니라 두개의 프로세스가 커널을 통해서 통신을 하고 있지만,
// 두 소켓은 하나의 호스트(컴퓨터)에서만 생성되고 실행되기 때문에 실제 통신망에 연결된 두 컴퓨터 간에 자료를 송수신할 때 사용하기에는 한계가 있다.

