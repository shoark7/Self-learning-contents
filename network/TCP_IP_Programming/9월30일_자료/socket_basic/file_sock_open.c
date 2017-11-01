#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

/*
	첨언: 소켓 기술자나 파일 기술자 모두 파일 디스크립터 테이블(Descripter table)의 색인(Index)이고, 
	이 기술자 테이블에는 소켓이나 파일에 대한 포인터가 저장되어 있다는 것을 기억하기 바란다. 
	참고로 리눅스에서는 기술자(Descripter)라는 용어를 사용하지만 윈도우에서는 핸들(Handle)이라는 용어를 사용한다.
 */

int main()
{
	int fd, sd;

	// 파일을 단순히 열어서 내용을 보고 싶다면 인자2개짜리 open()을 사용해도 좋다.
	// 하지만 파일을 만든다면, 최소한 mode_t mode에 적절한 인자를 줘야 할 것이다.
	fd = open("/etc/services", O_RDONLY);
	sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	printf("fd = [%d] \n", fd);
	printf("sd = [%d] \n", sd);
}

/*
	실제로 해당 프로그램을 실행해보면 새로운 파일과 소켓에 대한 기술자로 각각 3과 4가 할당된 것을 알 수 있다. 
	open()이나 socket()을 사용했을 때 할당된 기술자를 출력하면 보통 3부터 시작된다.  
	기술자 테이블의 색인 중 0, 1, 2는 다른 목적으로 이미 예약되어 있어서이다.
	0은 표준 입력, 1은 표준 출력, 2는 표준 오류에 사용된다.
	즉, 입출력 함수를 이용해서 기술자 0, 1, 2에 입출력을 하면 키보드나 모니터를 통해 이루어진다. 
 */
