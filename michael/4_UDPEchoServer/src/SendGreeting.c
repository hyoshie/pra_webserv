#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define RCVBUFSIZE 32

void	DieWithError(char *errorMessage);

void	SendGreeting(int clntSocket)
{
	char	helloString[] = "hello, from server!\n";
	size_t	helloStringLen = strlen(helloString);

	if (send(clntSocket, helloString, helloStringLen, 0) != helloStringLen)
		DieWithError("send() failed");
	sleep(1);
}
