#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> // for portability. read VM man.
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define ECHOMAX 255
#define TIMEOUT_SECS 2
#define MAXTRIES 5

int	tries = 0; //use in signal handler

void	DieWithError(char *errorMessage);
void	CatchAlarm(int ignored);

int	main(int argc, char *argv[])
{
	// 1.Set up application and analyze params
	int	sock;
	struct sockaddr_in	echoServAddr;
	struct sockaddr_in	fromAddr;
	unsigned short		echoServPort;
	unsigned int	fromSize;
	struct sigaction	myAction;
	char	*servIP;
	char	*echoString;
	char	echoBuffer[ECHOMAX + 1];
	int	echoStringLen;
	int	respStringLen;

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

	// **Set SIGALRM handler
	myAction.sa_handler = CatchAlarm;
	if (sigfillset(&myAction.sa_mask) < 0)
		DieWithError("sigfillset() failed");
	myAction.sa_flags = 0;

	if (sigaction(SIGALRM, &myAction, 0) < 0)
		DieWithError("sigaction() failed for SIGALRM");

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
	alarm(TIMEOUT_SECS);

	while ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0,
			(struct sockaddr *)&fromAddr, &fromSize)) < 0)
	{
		if (errno == EINTR)
		{
			//catch sigalarm
			if (tries < MAXTRIES)
			{
				printf("timed out, %d more tries..\n", MAXTRIES - tries);
				if (sendto(sock, echoString, echoStringLen, 0,
					(struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) != echoStringLen)
					DieWithError("sendto() failed");
				alarm(TIMEOUT_SECS);
			}
			else
			{
				DieWithError("No Response");
			}
		}
		else
		{
			DieWithError("recvfrom failed()");
		}
	}
	printf("[respStringLen]%d\n", respStringLen);

	alarm(0);

	// if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
	// {
	// 	fprintf(stderr, "Error,: received a packet from unknown source.\n");
	// 	printf("recieve from [IP]%s [Port]%u\n", inet_ntoa(fromAddr.sin_addr), ntohs(fromAddr.sin_port));
	// 	exit(EXIT_FAILURE);
	// }

	echoBuffer[respStringLen] = '\0';
	printf("Recieved: %s, %d\n", echoBuffer, respStringLen);
	close(sock);
	exit(0);

	return (0);
}

void	CatchAlarm(int ignored)
{
	printf("from handler\n");
	tries += 1;
}
