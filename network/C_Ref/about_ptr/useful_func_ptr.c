#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int WhoIsFirst(int age1, int age2, int (*cmp)(int, int))
{
	return cmp(age1, age2);
}

int OlderFirst(int age1, int age2)
{
	return (age1 > age2) ? age1 :
	       (age1 < age2) ? age2 : 0;
}

int YoungerFirst(int age1, int age2)
{
	return (age1 < age2) ? age1 :
	       (age1 > age2) ? age2 : 0;
}

int (*WhoIsFirst_func(const char initial))(int, int)
{
	switch(initial)
	{
		case 'O':
		case 'o':
			return OlderFirst;
			break;
		case 'Y':
		case 'y':
			return YoungerFirst;
		default:
			printf("Error\n");
			exit(1);
	}
}
int main(void)
{
	int age1 = 20;
	int age2 = 30;
	int first;
	int (*first_func)(int, int);

	// 함수 포인터를 인자로 받아 내부적으로 호출하는 방법
	printf("장유유서 \n");
	first = WhoIsFirst(age1, age2, OlderFirst);
	printf("%d세와 %d세 중 %d세가 먼저 입장! \n\n", age1, age2, first);

	printf("왜 애를 기를 죽이고 그래요?\n");
	first = WhoIsFirst(age1, age2, YoungerFirst);
	printf("%d세와 %d세 중 %d세가 먼저 입장! \n\n", age1, age2, first);

	// 함수 포인터를 반환하는 함수로 인자를 직접 넘겨서 바로 호출하는 방법
	printf("장유유서 \n");
	printf("%d세와 %d세 중 %d세가 먼저 입장! \n\n", age1, age2, WhoIsFirst_func('O')(age1, age2));

	printf("왜 애를 기를 죽이고 그래요?\n");
	printf("%d세와 %d세 중 %d세가 먼저 입장! \n\n", age1, age2, WhoIsFirst_func('Y')(age1, age2));

	// 함수 포인터 변수를 선언하여 담고, 그 함수 포인터 변수로 호출하는 방법
	printf("장유유서 \n");
	first_func = WhoIsFirst_func('O');
	printf("%d세와 %d세 중 %d세가 먼저 입장! \n\n", age1, age2, first_func(age1, age2));

	printf("왜 애를 기를 죽이고 그래요?\n");
	first_func = WhoIsFirst_func('Y');
	printf("%d세와 %d세 중 %d세가 먼저 입장! \n\n", age1, age2, first_func(age1, age2));

	return 0;
}
