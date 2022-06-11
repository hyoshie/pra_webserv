#include "TCPEchoServer.h"
#include <unistd.h>
#include <sys/wait.h>

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
		// multi proc
		if ((processID = fork()) < 0)
		{
			DieWithError("fork() failed");
		}
		else if (processID == 0) //child proc
		{
			close(servSock);
			sleep(5);
			HandleTCPClient(clntSock);

			exit(EXIT_SUCCESS);
		}
		//parent proc
		printf("with child process: %d\n", (int)processID);
		close(clntSock);
		childProccount++;

		//clean zombie proc
		while (childProccount)
		{
			printf("Wait Start:[childProccount]%d\n", childProccount);
			processID = waitpid((pid_t)-1, NULL, WNOHANG);
			if (processID < 0)
				DieWithError("waitpid() failed");
			else if (processID == 0)
			{
				printf("[\x1b[32mBreak\x1b[39m]\n");
				break;
			}
			else
				childProccount--;
			printf("with child process: %d\n", (int)processID);
			printf("##Wait End:[childProccount]%d\n", childProccount);
		}
	}
	// not reach
}
