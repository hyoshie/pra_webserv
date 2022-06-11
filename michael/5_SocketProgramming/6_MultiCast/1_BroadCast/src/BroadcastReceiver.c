#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXRECVSTRING 255

void	DieWithError(char *errorMessage);

int	main(int argc, char *argv[])
{
	int	sock;
	struct sockaddr_in	broadcastAddr;
	unsigned int	boradcastPort;
	char	recvString[MAXRECVSTRING + 1];
	int	recvStringLen;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <BroadcastPort>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	boradcastPort = atoi(argv[1]);

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		DieWithError("socket() failed");

	memset(&broadcastAddr, 0, sizeof(broadcastAddr));
	broadcastAddr.sin_family = AF_INET;
	broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	broadcastAddr.sin_port = htons(boradcastPort);

	if (bind(sock, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) < 0)
		DieWithError("bind() failed");

	if((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0,
					NULL, 0)) < 0)
		DieWithError("recvfrom()");

	recvString[recvStringLen] = '\0';
	printf("Received:%s\n", recvString);

	close(sock);
	return (0);
}

