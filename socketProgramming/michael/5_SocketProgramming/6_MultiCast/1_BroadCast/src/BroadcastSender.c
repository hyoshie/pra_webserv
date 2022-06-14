#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> // for portability. read VM man.
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define ECHOMAX 255

void	DieWithError(char *errorMessage);

int	main(int argc, char *argv[])
{
	int	sock;
	struct sockaddr_in	broadcastAddr;
	unsigned short		broadcastPort;
	unsigned int	fromSize;
	char	*broadcastIP;
	char	*sendString;
	int	broadcastPermission;
	unsigned int	sendStringLen;

	if (argc < 4)
	{
		fprintf(stderr, "Usage: %s <IP address>  <Port> <Echo String>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	broadcastIP = argv[1];
	broadcastPort = atoi(argv[2]);
	sendString = argv[3];

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		DieWithError("socket() failed");

	//set socket broadcast
	broadcastPermission = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *)&broadcastPermission,
			sizeof(broadcastPermission)) < 0)
		DieWithError("setsockopt() failed");

	memset(&broadcastAddr, 0, sizeof(broadcastAddr));
	broadcastAddr.sin_family = AF_INET;
	broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);
	broadcastAddr.sin_port = htons(broadcastPort);

	sendStringLen = strlen(sendString);
	for (;;)
	{
		if (sendto(sock, sendString, sendStringLen, 0,
					(struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) != sendStringLen)
			DieWithError("sendto() sent a different number of bytes than expected");

		sleep(3);
	}
	//not reach
}
