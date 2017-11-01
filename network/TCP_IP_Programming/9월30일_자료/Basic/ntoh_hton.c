// ntoh_hton.c
#include <stdio.h>
#include <arpa/inet.h>

int main()
{
	short h_data = 0x1234;
	short n_data;
	char *ch;

	printf("original data : 0x1234\n");

	// 이 캐스팅 기법과 배열 연산자를 쓰는 방법을 주의깊에 볼것
	ch = (char *) &h_data;

	if(ch[0] == 0x12 && ch[1] == 0x34)
		printf("host data(big-endian) : ");
	else if(ch[1] == 0x12 && ch[0] == 0x34)
		printf("host data(little-endian) : ");

	printf("0x%x%x\n", ch[0], ch[1]);

	n_data = htons(h_data);

	// 이 캐스팅 기법과 배열 연산자를 쓰는 방법을 주의깊게 볼것
	ch = (char *) &n_data;
	printf("network data(big-endian) : 0x%x%x\n", ch[0], ch[1]);
}
