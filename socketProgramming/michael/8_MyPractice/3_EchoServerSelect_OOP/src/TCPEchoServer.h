#ifndef TCPECHOSERVER_H
#define TCPECHOSERVER_H

void DieWithError(const char *errormessage);
int RepeatClientMessage(int clntSock);
int CreateTCPServerSocket(unsigned short port);
int AcceptTCPConeection(int servSock);

#endif /* TCPECHOSERVER_H */
