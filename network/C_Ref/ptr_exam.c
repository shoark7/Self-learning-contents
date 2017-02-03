#include <stdio.h>

int main(void)
{
	int a = 0;
	int *a_ptr = &a;

	printf("%x is a and type is int\n", a);
	printf("%x is a's adressand type is (int *)\n", &a);
	printf("%x is a_ptr's dereference and type is int\n", *a_ptr);
	printf("%x is a_ptr and type is (int *)\n", a_ptr);
	printf("%x is a_ptr's adress and type is(int **)\n", &a_ptr);
}
