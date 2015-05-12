#include <Mystring.h>

void	test(void)
{
	t_string	test;
	char		*ptr;

	test = newString("Bonjour\n");
	putString(test);
	ptr = test.str;
	test.safe = 2;
	while (putString(test) >= 0)
		*ptr++ = '.';
	destroyString(&test);
	test.str = NULL;
}

int main(void)
{
	test();
	while (1);
}
