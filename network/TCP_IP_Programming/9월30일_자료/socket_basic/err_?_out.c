#include <stdio.h>

char str1[] = "this is test1";
char str2[] = "this is test2";

int main()
{
	// stdout은 줄 단위로 버퍼링되고, stderr은 버퍼링하지 않고 그냥 내보낸다.
	// 그리고 줄단위로 버퍼링이 이루어진다면 stdout은 stderr보다 빠르지만
	// 아니라면 stderr가 더 빠르다.

	// 다음은 stderr가 더 빠른 예다.
	fprintf(stdout, "%s", str1);
	fprintf(stderr, "%s", str2);

	// 다음은 stdout이 더 빠른 예다.
	fprintf(stdout, "%s\n", str1);
	fprintf(stderr, "%s", str2);
}
