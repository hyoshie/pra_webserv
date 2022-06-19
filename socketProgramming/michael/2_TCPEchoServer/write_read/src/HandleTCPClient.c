#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define RCVBUFSIZE 32

void	DieWithError(char *errorMessage);

void	HandleTCPClient(int clntSocket)
{
	char	echoBuffer[RCVBUFSIZE];
	int	recvMsgSize;

	// if((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
	if((recvMsgSize = read(clntSocket, echoBuffer, RCVBUFSIZE)) < 0)
		DieWithError("recv() failed");

	while (recvMsgSize > 0)
	{
		// if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
		if (write(clntSocket, echoBuffer, recvMsgSize) != recvMsgSize)
			DieWithError("send() failed");

		if((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
			DieWithError("recv() failed");
	}

	close(clntSocket); //in TCPEchoServer is better?
}