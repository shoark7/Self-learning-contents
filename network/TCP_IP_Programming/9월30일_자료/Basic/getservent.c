#include <stdio.h>
#include <netdb.h>

int main()
{
	struct servent *p;
	int n;

	for(;;) {
		if(!(p = getservent())) break;

		printf("%s\t %d/%s \t", p->s_name, ntohs(p->s_port), p->s_proto);
		for(n = 0; p->s_aliases[n] != NULL; n++)
			printf("%s ", p->s_aliases[n]);
		printf("\n");
	}
}
