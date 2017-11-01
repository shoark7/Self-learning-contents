#include <stdio.h>
#include <sys/socket.h>

char str[128];

int main()
{
	int sd;

	sd = socket(AF_INET, SOCK_STREAM, 0);

	fscanf(stdin, "%s", str);
	fprintf(stdout, "%s \n", str);
	fprintf(stderr, "sd = [%d] \n", sd);
}


