#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int tcp_sd;
	struct sockaddr_in s_addr;

	if((tcp_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket()");
		exit(-1);
	}

	// bzero는 독특한 캐스팅을 해야한다. 
	// 내부적으로 시작주소부터 끝 주소까지 모든 메모리 정보를 0으로 채우는 루프가 있는 듯 하다.
	bzero((char *) &s_addr, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	inet_aton("203.249.39.3", &s_addr.sin_addr.s_addr);
	s_addr.sin_port = htons(7);

	// 다른 코드와는 달리 inet_ntoa의 인자는 struct in_addr을 인자로 받기 때문에
	// xxx.sin_addr.s_addr로 인자를 넘겨주는게 아니라 xxx.sin_addr에서 끝내야 한다.
	printf("ip(dotted decimal) = %s\n", inet_ntoa(s_addr.sin_addr));
	printf("ip(binary) = %x\n", ntohl(s_addr.sin_addr.s_addr));
	printf("port no = %d\n", ntohs(s_addr.sin_port));

	close(tcp_sd);
}
