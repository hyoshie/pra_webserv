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

	if((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
		DieWithError("recv() failed:first");

	while (recvMsgSize > 0)
	{
		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
			DieWithError("send() failed");
		printf("[%dbytes]send!\n", recvMsgSize);

		if((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
			DieWithError("recv() failed:in loop");
	}

	close(clntSocket); //in TCPEchoServer is better?
}

// send evry byte
// #define RCVBUFSIZE 1

// void	DieWithError(char *errorMessage);

// void	HandleTCPClient(int clntSocket)
// {
// 	char	echoBuffer[RCVBUFSIZE];
// 	int	recvMsgSize;

// 	if((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
// 		DieWithError("recv() failed");

// 	while (recvMsgSize > 0)
// 	{
// 		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
// 			DieWithError("send() failed");
// 		printf("[%dbytes]send!\n", recvMsgSize);
// 		sleep(1);

// 		if((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
// 			DieWithError("recv() failed");
// 	}

// 	close(clntSocket); //in TCPEchoServer is better?
// }
