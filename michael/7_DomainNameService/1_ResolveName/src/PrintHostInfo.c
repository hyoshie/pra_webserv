#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>

static void	PrintStringVector(char **vector);

void	PrintHostInfo(char name[])
{
	struct hostent	*host;

	if ((host = gethostbyname(name)) == NULL)
	{
		fprintf(stderr, "gethostbyname() failed");
		exit(EXIT_FAILURE);
	}

	printf("[host->h_name]%s\n", host->h_name);
	PrintStringVector(host->h_aliases);
	printf("[host->h_addrtype]%d\n", host->h_addrtype);
	printf("[host->h_length]%d\n", host->h_length);
	PrintStringVector(host->h_addr_list);
}

static void	PrintStringVector(char **vector)
{
	if (vector == NULL)
		exit(EXIT_FAILURE);
	while (*vector != NULL)
	{
		printf("[*vector]%s\n", *vector);
		vector++;
	}
}

