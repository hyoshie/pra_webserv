#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> // for portability. read VM man.
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define ECHOMAX 1 << 17 //131072

void	DieWithError(char *errorMessage);

int	main(int argc, char *argv[])
{
	// 1.Set up application and analyze params
	int	sock;
	struct sockaddr_in	echoServAddr;
	struct sockaddr_in	fromAddr;
	unsigned short		echoServPort;
	unsigned int	fromSize;
	char	*servIP;
	char	*echoString;
	char	echoBuffer[ECHOMAX + 1];
	unsigned int	echoStringLen;
	unsigned int	respStringLen;

	if ((argc < 3) || (argc > 4))
	{
		fprintf(stderr, "Usage: %s <Server IP>  < Echo Word> [<Echo Port>]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	servIP = argv[1]; //IP of server
	echoString = argv[2]; //string to send

	if ((echoStringLen = strlen(echoString)) > ECHOMAX)
		DieWithError("Echo word too long");

	if (argc == 4)
		echoServPort = atoi(argv[3]);
	else
		echoServPort = 7; //7 is well-known port number

	// 2.Create UDP stream socket
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		DieWithError("socket() failed");

	// 3.Send string to server
	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(echoServPort);

	if (sendto(sock, echoString, echoStringLen, 0,
		(struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) != echoStringLen)
		DieWithError("sendto() sent a different number of bytes than expected");

	// 4.Recieve a response
	fromSize = sizeof(fromAddr);
	if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0,
		(struct sockaddr *)&fromAddr, &fromSize)) != echoStringLen)
			DieWithError("recvfrom() failed");

	if (echoServAddr.sin_addr.s_addr  == fromAddr.sin_addr.s_addr)
	{
		fprintf(stderr, "Error,: received a packet from unknown source.\n");
		exit(EXIT_FAILURE);
	}

	echoBuffer[respStringLen] = '\0';
	printf("Recieved: %s\n", echoBuffer);
	close(sock);
	exit(0);

	return (0);
}
