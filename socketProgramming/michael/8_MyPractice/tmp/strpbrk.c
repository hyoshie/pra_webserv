#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*p = strpbrk("hello c world!", "wo");
	printf("[p]%s\n", p);
	return (0);
}
