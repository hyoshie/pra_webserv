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
	struct sockaddr_in	multicastAddr;
	unsigned short		multicastPort;
	unsigned int	fromSize;
	char	*multicastIP;
	char	*sendString;
	unsigned char	multicastTTL;
	unsigned int	sendStringLen;

	if ((argc < 4) || (argc > 5))
	{
		fprintf(stderr, "Usage: %s <Multicast address> <Port> <Send String> [<TTL>]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	multicastIP = argv[1];
	multicastPort = atoi(argv[2]);
	sendString = argv[3];

	if (argc == 5)
		multicastTTL = atoi(argv[4]);
	else
		multicastTTL = 1;

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		DieWithError("socket() failed");

	//set multicast TTL
	if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&multicastTTL,
			sizeof(multicastTTL)) < 0)
		DieWithError("setsockopt() failed");

	memset(&multicastAddr, 0, sizeof(multicastAddr));
	multicastAddr.sin_family = AF_INET;
	multicastAddr.sin_addr.s_addr = inet_addr(multicastIP);
	multicastAddr.sin_port = htons(multicastPort);

	sendStringLen = strlen(sendString);
	for (;;)
	{
		if (sendto(sock, sendString, sendStringLen, 0,
					(struct sockaddr *)&multicastAddr, sizeof(multicastAddr)) != sendStringLen)
			DieWithError("sendto() sent a different number of bytes than expected");

		sleep(3);
	}
	//not reach
}
