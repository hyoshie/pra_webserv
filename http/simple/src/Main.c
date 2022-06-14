#include "TCPEchoServer.h"
#include <unistd.h>
#include <sys/wait.h>

int	HttpServer(int sock);

int	main(int argc, char *argv[])
{
	int	servSock;
	int	clntSock;
	unsigned short	echoServPort;
	pid_t	processID;
	unsigned int	childProccount = 0;

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
		HttpServer(clntSock);
		close(clntSock);
	}
	// not reach
	close(servSock);
}
