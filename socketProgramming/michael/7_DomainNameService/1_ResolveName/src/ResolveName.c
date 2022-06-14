#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>

unsigned long	ResolveName(char name[])
{
	struct hostent	*host;

	if ((host = gethostbyname(name)) == NULL)
	{
		fprintf(stderr, "gethostbyname() failed");
		exit(EXIT_FAILURE);
	}

	return *((unsigned long*)host->h_addr_list[0]);
}
