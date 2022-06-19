#include <arpa/inet.h>
#include <sys/socket.h>

#include <cstring>

#define MAXPENDING 5

void DieWithError(const char *errormessage);

int CreateTCPServerSocket(unsigned short port) {
  int sock;
  struct sockaddr_in echoServAddr;

  // Create socket for incoming connection request
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    DieWithError("socket() failed");
  }

  // Set struct sockaddr_in in local
  memset(&echoServAddr, 0, sizeof(echoServAddr));
  echoServAddr.sin_family = AF_INET;
  echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  echoServAddr.sin_port = htons(port);

  //ソケットオプション（再利用フラグ）を設定
  int opt = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(int)) <
      0) {
    DieWithError("setsockopt failed()");
  }

  // Bind local address
  if (bind(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0) {
    DieWithError("bind() failed");
  }

  // Mark listning on socket
  if (listen(sock, MAXPENDING) < 0) {
    DieWithError("listen() failed");
  }

  return sock;
}
