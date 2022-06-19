#ifndef TCPECHOSERVER_H
#define TCPECHOSERVER_H

#include <stdio.h>
#include <stdlib.h>

void DieWithError(const char *errormessage);
void HandleTCPClient(int clntSocket);
int RepeatClientMessage(int clntSock);
int CreateTCPServerSocket(unsigned short port);
int AcceptTCPConeection(int servSock);

#endif /* TCPECHOSERVER_H */
