#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>  // for portability. read VM man.
#include <unistd.h>

#define RCVBUFSIZE 32

void DieWithError(const char *errorMessage);

int main(int argc, char *argv[]) {
  // 1.Set up application and analyze params
  struct sockaddr_in echoServAddr;
  uint16_t echoServPort = 7;
  char *servIP = argv[1];      // IP of server
  char *echoString = argv[2];  // string to send
  char echoBuffer[RCVBUFSIZE];

  if ((argc < 3) || (argc > 4)) {
    fprintf(stderr, "Usage: %s <Server IP>  < Echo Word> [<Echo Port>]\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  if (argc == 4) echoServPort = atoi(argv[3]);

  // 2.Create TCP stream socket
  int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock < 0) DieWithError("socket() failed");

  // 3.Connect to server
  memset(&echoServAddr, 0, sizeof(echoServAddr));
  echoServAddr.sin_family = AF_INET;
  echoServAddr.sin_addr.s_addr = inet_addr(servIP);
  echoServAddr.sin_port = htons(echoServPort);

  if (connect(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
    DieWithError("connect() failed");

  sleep(3);

  // 4.Send string to server
  unsigned int echoStringLen = strlen(echoString);

  if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
    DieWithError("send() sent a different number of bytes than expected");

  // 5.Recieve a response
  int totalBytesRcvd = 0;
  printf("Recieved: ");

  while (totalBytesRcvd < static_cast<int>(echoStringLen)) {
    int bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0);
    if (bytesRcvd <= 0)
      DieWithError("recv() failed or connection closed prematurely");
    totalBytesRcvd += bytesRcvd;
    echoBuffer[bytesRcvd] = '\0';
    printf("%s", echoBuffer);
  }

  printf("\n");

  // 6.Disconnect from server
  close(sock);
  exit(0);
  printf("from client\n");
  DieWithError("test");

  return (0);
}
