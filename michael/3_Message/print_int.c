#include <stdio.h>
#include <limits.h>

static void	print_int_inside(int nbr)
{
	printf("[nbr]%d\n", nbr);

	int	*iptr = &nbr;
	unsigned char	*cptr = (char *)iptr;

	for (int i = 0; i < sizeof(int); i++, cptr++) {
		printf("%d", *cptr);
		if (i != sizeof(int) - 1)
			printf(", ");
		else
			printf("\n");
	}
}

int	main(void)
{
	print_int_inside(0);
	print_int_inside(1);
	print_int_inside(16);
	print_int_inside(256);
	print_int_inside(INT_MAX);
	print_int_inside(INT_MIN);
	print_int_inside(42);
	print_int_inside(17998720);
	print_int_inside(47034615);
	return (0);
}
