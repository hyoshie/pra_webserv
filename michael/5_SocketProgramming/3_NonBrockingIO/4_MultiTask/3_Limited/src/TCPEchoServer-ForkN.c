#include "TCPEchoServer.h"
#include <unistd.h>
#include <sys/wait.h>

void	ProcessMain(int servSock);

int	main(int argc, char *argv[])
{
	int	servSock;
	unsigned short	echoServPort;
	pid_t	processID;
	unsigned int	processLimit;
	unsigned int	processCt;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <Server Port>", argv[0]);
		exit(EXIT_FAILURE);
	}

	echoServPort = atoi(argv[1]);
	processLimit = atoi(argv[2]);

	servSock = CreateTCPServerSocket(echoServPort);

	for (int processCt = 0; processCt < processLimit; processCt++) {
		if ((processID = fork()) < 0)
			DieWithError("fork() failed");
		else if (processID == 0)
			ProcessMain(servSock);
	}
	exit(EXIT_SUCCESS);
}

void	ProcessMain(int servSock)
{
	int	clntSock;

	for (;;)
	{
		clntSock = AcceptTCPConeection(servSock);
		printf("with child process: %d\n", (unsigned int )getpid());
		HandleTCPClient(clntSock);
	}
}
