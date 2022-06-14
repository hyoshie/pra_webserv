#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void	DieWithError(char *errormessage);

int		AcceptTCPConeection(int servSock)
{
	int	clntSock;
	struct sockaddr_in	echoClntAddr;
	unsigned int	clntLen;

	clntLen = sizeof(echoClntAddr);

	printf("Before Accept..\n", inet_ntoa(echoClntAddr.sin_addr));

	if ((clntSock = accept(servSock, (struct sockaddr *)&echoClntAddr, &clntLen)) < 0)
		DieWithError("accept() failed");

	printf("Accept!: Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

	return clntSock;
}
