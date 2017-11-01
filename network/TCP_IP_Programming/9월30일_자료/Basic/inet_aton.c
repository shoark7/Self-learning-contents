#include <stdio.h>
#include <arpa/inet.h>

int main()
{
	struct in_addr inp;
	const char *ip_addr = "203.249.39.3";
	char *addr;

	inet_aton(ip_addr, &inp);
	printf("ip(dotted decimal)[%s] -> ip(binary)[0x%x]\n", ip_addr, ntohl(inp.s_addr));

	addr = inet_ntoa(inp);
	printf("ip(binary[0x%x] -> ip(dotted decimal)[%s]\n", ntohl(inp.s_addr), addr);
}
