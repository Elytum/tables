#include <Mystring.h>
#include <Myfloats.h>

void	test1(void)
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

void test2(void)
{
	t_floats floats;

    floats = newFloats(2, 3.3f, 4.4f);
    putFloats(floats);
    destroyFloats(&floats);
}

int main(void)
{
	test2();
	while (1);
}
