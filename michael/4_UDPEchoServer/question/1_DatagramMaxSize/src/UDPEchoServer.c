#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ECHOMAX 1 << 17 //131072

void	DieWithError(char *errorMessage);
void	HandleUDPClient(int clntSocket);

int	main(int argc, char *argv[])
{
	// 1.Set up application and analyze params
	// int	servSock;
	// int	clntSock;
	int	sock;
	struct sockaddr_in	echoServAddr;
	struct sockaddr_in	echoClntAddr;
	unsigned int	cliAddrLen;
	char	echoBuffer[ECHOMAX + 1];
	unsigned short	echoServPort;
	unsigned int	clntLen;
	int	recvMsgSize;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	echoServPort = atoi(argv[1]);

	// 2.Create and Set up socket
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		DieWithError("socket() failed");

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	echoServAddr.sin_port = htons(echoServPort);

	if (bind(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
		DieWithError("bind() failed");

	// 3.Handle request repeatedly
	for (;;)
	{
		cliAddrLen = sizeof(echoClntAddr);

		if((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0,
			(struct sockaddr *)&echoClntAddr, &cliAddrLen)) < 0)
			DieWithError("recvfrom()");
		printf("Handling client [IP]%s [Port]%u\n", inet_ntoa(echoClntAddr.sin_addr), ntohs(echoClntAddr.sin_port));

	if (sendto(sock, echoBuffer, recvMsgSize, 0,
		(struct sockaddr *)&echoClntAddr, sizeof(echoClntAddr)) != recvMsgSize)
		DieWithError("sendto() failed");
	}

	printf("[%dbytes]send!\n", recvMsgSize);
	printf("from server\n");
	return (0);
}

