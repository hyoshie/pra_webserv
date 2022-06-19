#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5

void	DieWithError(char *errorMessage);
void	HandleTCPClient(int clntSocket);
void	PrintSockBufSize(int socket, char *sockKind);

int	main(int argc, char *argv[])
{
	// 1.Set up application and analyze params
	int	servSock;
	int	clntSock;
	struct sockaddr_in	echoServAddr;
	struct sockaddr_in	echoClntAddr;
	unsigned short	echoServPort;
	unsigned int	clntLen;
	fd_set	set;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	echoServPort = atoi(argv[1]);

	// 2.Create and Set up socket
	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("socket() failed");

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	echoServAddr.sin_port = htons(echoServPort);

	if (bind(servSock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
		DieWithError("bind() failed");

	if(listen(servSock, MAXPENDING) < 0)
		DieWithError("listen() failed");

	//check socket bufsize
	PrintSockBufSize(servSock, "Listen");

	// 3.Handle request repeatedly
	for (;;)
	{
		clntLen = sizeof(echoClntAddr);

		if((clntSock = accept(servSock, (struct sockaddr *)&echoClntAddr, &clntLen)) < 0)
			DieWithError("accept() failed");

		printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

		PrintSockBufSize(servSock, "accept");
		HandleTCPClient(clntSock);
	}
	printf("from server\n");
	return (0);
}

void	PrintSockBufSize(int socket, char *sockKind)
{
	int	rcvBufferSize;
	int	sendBufferSize;
	int	sockOptSize;

	sockOptSize = sizeof(rcvBufferSize);
	if (getsockopt(socket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSize, &sockOptSize) < 0)
		DieWithError("getsockopt() failed");
	printf("[%s:rcvBufSize]%d\n", sockKind, rcvBufferSize);
	if (getsockopt(socket, SOL_SOCKET, SO_SNDBUF, &sendBufferSize, &sockOptSize) < 0)
		DieWithError("getsockopt() failed");
	printf("[%s:sendBufSize]%d\n", sockKind, sendBufferSize);
}