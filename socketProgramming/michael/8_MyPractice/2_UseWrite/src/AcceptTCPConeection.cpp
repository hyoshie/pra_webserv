#include <arpa/inet.h>
#include <sys/socket.h>

#include <iostream>

using namespace std;

void DieWithError(const char *errormessage);

int AcceptTCPConeection(int servSock) {
  int clntSock;
  struct sockaddr_in echoClntAddr;
  unsigned int clntLen;

  clntLen = sizeof(echoClntAddr);

  if ((clntSock =
           accept(servSock, (struct sockaddr *)&echoClntAddr, &clntLen)) < 0) {
    DieWithError("accept() failed");
  }
  cerr << "Accept: " << inet_ntoa(echoClntAddr.sin_addr) << endl;

  return clntSock;
}
