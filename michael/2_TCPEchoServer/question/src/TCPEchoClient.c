#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> // for portability. read VM man.
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define RCVBUFSIZE 32

void	DieWithError(char *errorMessage);

int	main(int argc, char *argv[])
{
	// 1.Set up application and analyze params
	int	sock;
	struct sockaddr_in	echoServAddr;
	unsigned short		echoServPort;
	char	*servIP;
	char	*echoString;
	char	echoBuffer[RCVBUFSIZE];
	unsigned int	echoStringLen;
	int	bytesRcvd, totalBytesRcvd;

	if ((argc < 3) || (argc > 4))
	{
		fprintf(stderr, "Usage: %s <Server IP>  < Echo Word> [<Echo Port>]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	servIP = argv[1]; //IP of server
	echoString = argv[2]; //string to send

	if (argc == 4)
		echoServPort = atoi(argv[3]);
	else
		echoServPort = 7; //7 is well-known port number

	// 2.Create TCP stream socket
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("socket() failed");

	// 3.Connect to server
	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(echoServPort);

	if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
		DieWithError("connect() failed");

	// 4.Send string to server
	echoStringLen = strlen(echoString);

	if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
		DieWithError("send() sent a different number of bytes than expected");

	// 5.Recieve a response

	printf("Greeting:\n");
	if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
		DieWithError("recv() failed or connection closed prematurely");
	echoBuffer[bytesRcvd] = '\0';
	printf("[%2dbytes]%s\n", bytesRcvd, echoBuffer);

	printf("Recieved:\n");
	totalBytesRcvd = 0;
	while (totalBytesRcvd < echoStringLen)
	{
		if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
			DieWithError("recv() failed or connection closed prematurely");
		totalBytesRcvd += bytesRcvd;
		echoBuffer[bytesRcvd] = '\0';
		printf("[%2dbytes]%s\n", bytesRcvd, echoBuffer);
		// fflush(stdout);
	}

	printf("\n");

	// 6.Disconnect from server
	close(sock);
	exit(0);
	printf("from client\n");
	DieWithError("test");

	return (0);
}