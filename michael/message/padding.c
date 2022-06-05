#include <stdio.h>
#include <stddef.h>

struct s_bank {
	int	centsDeposited;
	int	centsWithdrawn;
	unsigned short	numDeps;
	unsigned short	numWds;
}	msgBuf;

int	main(void)
{
	printf("[sizeof(msgBuf)]%zu\n", sizeof(msgBuf));
	printf("centsDeposited:%zu\n", offsetof(struct s_bank, centsDeposited));
	printf("centsDeposited:%zu\n", offsetof(struct s_bank, numDeps));
	printf("centsDeposited:%zu\n", offsetof(struct s_bank, centsWithdrawn));
	printf("centsDeposited:%zu\n", offsetof(struct s_bank, numWds));
	return (0);
}
