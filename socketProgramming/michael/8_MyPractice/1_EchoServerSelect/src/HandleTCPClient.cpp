#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

using namespace std;

#define RCVBUFSIZE 32

void DieWithError(const char *errorMessage);

void HandleTCPClient(int clntSocket) {
  char echoBuffer[RCVBUFSIZE];
  int recvMsgSize;

  printf("START Handling client\n");
  if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
    DieWithError("recv() failed");

  while (recvMsgSize > 0) {
    if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
      DieWithError("send() failed");

    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
      DieWithError("recv() failed");
  }

  close(clntSocket);  // in TCPEchoServer is better?
  printf("END Handling client\n");
}

int RepeatClientMessage(int clntSock) {
  char echoBuffer[RCVBUFSIZE + 1];
  int recvMsgSize;

  if ((recvMsgSize = recv(clntSock, echoBuffer, RCVBUFSIZE, 0)) < 0) {
    DieWithError("recv() failed");
  }
  if (recvMsgSize == 0) {
    cerr << "recv: EOF" << endl;
    return 0;
  }
  echoBuffer[recvMsgSize] = '\0';
  //改行を削除
  char *nlptr;
  if ((nlptr = strstr(echoBuffer, "\r\n")) != NULL) {
    *nlptr = '\0';
  }
  cerr << "recv: " << echoBuffer << endl;
  if (send(clntSock, echoBuffer, recvMsgSize, 0) != recvMsgSize) {
    DieWithError("send() failed");
  }
  return 1;
}
