#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <error.h>

int main()
{
	int tcp_sd1, tcp_sd2;
	int udp_sd1, udp_sd2;

	// IPv4 스트림 소켓 -> TCP(문제없음)
	if((tcp_sd1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket()-tcp_sd1");
	} else
		printf("TCP Socket open = %d\n", tcp_sd1);

	// IPv4 데이터그램 소켓 -> UDP(문제없음)
	if((udp_sd1 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("socket()-udp_sd1");
	} else
		printf("UDP Socket open = %d\n", udp_sd1);

	// IPv4 스트림 소켓 -> UDP(잘못된 조합 = 에러)
	if((tcp_sd2 = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP)) < 0) {
		perror("socket()-tcp_sd2");
	} else
		printf("TCP Socket open = %d\n", tcp_sd2);

	// IPv4 데이터그램 소켓 -> TCP(잘못된 조합 = 에러)
	if((udp_sd2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_TCP)) < 0) {
		perror("socket()-udp_sd2");
	} else
		printf("UDP Socket open = %d\n", udp_sd2);

	close(tcp_sd1);
	close(udp_sd1);
	close(tcp_sd2);
	close(udp_sd2);
}

