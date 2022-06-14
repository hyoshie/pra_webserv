#include "TCPEchoServer.h"
#include <unistd.h>
#include <pthread.h>

void	*ThreadMain(void *arg);

struct	ThreadArgs
{
	int	clntSock;
};

int	main(int argc, char *argv[])
{
	int	servSock;
	int	clntSock;
	unsigned short	echoServPort;
	pthread_t	threadID;
	struct ThreadArgs	*threadArgs;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <Server Port>", argv[0]);
		exit(EXIT_FAILURE);
	}

	echoServPort = atoi(argv[1]);

	servSock = CreateTCPServerSocket(echoServPort);

	for(;;)
	{
		clntSock = AcceptTCPConeection(servSock);
		// multi thread
		if ((threadArgs = (struct ThreadArgs *)malloc(sizeof(struct ThreadArgs))) < 0)
		{
			DieWithError("malloc() failed");
		}
		threadArgs->clntSock = clntSock;

		if (pthread_create(&threadID, NULL, ThreadMain, (void *)threadArgs) != 0)
		{
			DieWithError("pthread_create() failed");
		}
		printf("with thread: %ld\n", (long int)threadID);
	}
	// not reach
}

void	*ThreadMain(void *threadArgs)
{
	int	clntSock;

	pthread_detach(pthread_self());
	clntSock = ((struct ThreadArgs *)threadArgs)->clntSock;
	free(threadArgs);

	HandleTCPClient(clntSock);
	return NULL;
}
