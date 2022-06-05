#include <stdio.h>
#include <limits.h> //CHAR_BIT

//in little endian
static void	print_in_little_endian(unsigned char c)
{
	for (int i = 0; i < CHAR_BIT; i++, c  >>= 1) {
		if (c & 1U)
			printf("1");
		else
			printf("0");
	}
	printf(":little\n");
}

//in big endian
static void	print_in_big_endian(unsigned char c)
{
	for (int i = 0; i < CHAR_BIT; i++, c <<= 1) {
		if (c & 128U)
			printf("1");
		else
			printf("0");
	}
	printf(":big\n");
}

void	print_bit_2way(unsigned char c)
{
	printf("%c[%d]:\n", c, c);
	print_in_big_endian(c);
	print_in_little_endian(c);
}


int	main(int argc, char *argv[])
{
	print_bit_2way('a');
	print_bit_2way('b');
	print_bit_2way('0');
	print_bit_2way('1');
	return (0);
}
