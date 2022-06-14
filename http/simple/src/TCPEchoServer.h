#ifndef TCPECHOSERVER_H
#define TCPECHOSERVER_H

#include <stdio.h>
#include <stdlib.h>

void	DieWithError(char *errormessage);
int		CreateTCPServerSocket(unsigned short port);
int		AcceptTCPConeection(int servSock);

#endif /* TCPECHOSERVER_H */
