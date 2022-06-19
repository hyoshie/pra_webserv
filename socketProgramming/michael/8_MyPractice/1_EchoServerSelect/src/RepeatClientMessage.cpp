#include <sys/socket.h>
#include <sys/types.h>

#include <cstring>
#include <iostream>

using namespace std;

#define RCVBUFSIZE 32

void DieWithError(const char *errorMessage);

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
