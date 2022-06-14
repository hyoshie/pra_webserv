#ifndef TCPECHOSERVER_H
#define TCPECHOSERVER_H

#include <stdio.h>
#include <stdlib.h>

void	DieWithError(char *errormessage);
void	HandleTCPClient(int clntSocket);
int		CreateTCPServerSocket(unsigned short port);
int		AcceptTCPConeection(int servSock);

#endif /* TCPECHOSERVER_H */
