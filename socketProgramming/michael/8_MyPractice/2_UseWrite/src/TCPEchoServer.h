#ifndef TCPECHOSERVER_H
#define TCPECHOSERVER_H

void DieWithError(const char *errormessage);
int RepeatClientMessage(int clntSock);
int RecvMessage(int clntSock, char *echoBuffer);
int SendMessage(int clntSock, char *echoBuffer);
int CreateTCPServerSocket(unsigned short port);
int AcceptTCPConeection(int servSock);

#endif /* TCPECHOSERVER_H */
