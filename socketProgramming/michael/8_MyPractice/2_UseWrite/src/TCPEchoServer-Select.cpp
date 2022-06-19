#include <sys/select.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "TCPEchoServer.h"

using namespace std;

// static const int MAX_CLIENTS = 10;
#define MAX_CLIENTS 2
#define RCVBUFSIZE 32

typedef struct {
  int maxfd;
  fd_set readfds;
  fd_set writefds;
  struct timeval timeout;
} selectInfo;

void InitSelectInfo(selectInfo *selInfo, int servSock, vector<int> &clntSocks) {
  FD_ZERO(&selInfo->readfds);
  // FD_ZERO(&selInfo->writefds);
  FD_SET(servSock, &selInfo->readfds);
  selInfo->maxfd = servSock;

  int clntCount = 0;
  for (vector<int>::iterator it = clntSocks.begin(); it < clntSocks.end();
       it++) {
    FD_SET(*it, &selInfo->readfds);
    // FD_SET(*it, &selInfo->writefds);
    if (*it > selInfo->maxfd) {
      selInfo->maxfd = *it;
      clntCount++;
    }
  }
  cerr << "connect with " << clntCount << " clients" << endl;

  selInfo->timeout.tv_sec = 10;
  selInfo->timeout.tv_usec = 0;
}

int main(int argc, char *argv[]) {
  int servSock;
  vector<int> clntSocks;
  unsigned short echoServPort;
  char echoBuffer[256][RCVBUFSIZE + 1];

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <Server Port>", argv[0]);
    exit(EXIT_FAILURE);
  }

  echoServPort = atoi(argv[1]);

  servSock = CreateTCPServerSocket(echoServPort);

  for (;;) {
    selectInfo selInfo;
    InitSelectInfo(&selInfo, servSock, clntSocks);
    switch (select(selInfo.maxfd + 1, &selInfo.readfds, NULL, NULL,
                   &selInfo.timeout)) {
      case -1:
        DieWithError("select() failed");
        break;

      case 0:
        cerr << "Time out!" << endl;
        break;

      default:
        cerr << "fire select" << endl;
        if (FD_ISSET(servSock, &selInfo.readfds)) {
          cerr << "New connection" << endl;
          int tmpSock;
          tmpSock = AcceptTCPConeection(servSock);
          if (clntSocks.size() >= MAX_CLIENTS) {
            cerr << "refuse connection, server is full" << endl;
            close(tmpSock);
          } else {
            clntSocks.push_back(tmpSock);
          }
        }
        //書き込み準備ができたソケットへバイト列を書き込む
        for (vector<int>::iterator it = clntSocks.begin(); it < clntSocks.end();
             it++) {
          if (FD_ISSET(*it, &selInfo.writefds)) {
            cerr << "Write Event" << endl;
            int ret;
            ret = SendMessage(*it, echoBuffer[*it]);
            echoBuffer[*it][0] = '\0';
            // close(*it);
            // clntSocks.erase(it);
          }
        }
        //読み込み準備ができたソケットからバイト列を読み取る
        FD_ZERO(&selInfo.writefds);
        for (vector<int>::iterator it = clntSocks.begin(); it < clntSocks.end();
             it++) {
          if (FD_ISSET(*it, &selInfo.readfds)) {
            cerr << "Read Event" << endl;
            int ret;
            ret = RecvMessage(*it, echoBuffer[*it]);
            if (ret == 0) {
              cerr << "EOF!!!" << endl;
              FD_SET(*it, &selInfo.writefds);
            }
          }
        }
    }
    // not reach
  }
}

// 0.無限ループ
// 1.selectの引数を用意する
//
// typedef struct {
// 	fd_set	readfds;
// 	struct timeval	timeout;
// 	int	maxfd;
// }	selectInfo;
// InitSelectInfo(selectInfo *selInfo);
// select用のfdの集合を作る
// 2.ファイルディスクリプタを監視する

// 3.新しい接続があればacceptして新しいfdを作る
// AddConnection(int clntSocks[], int servSock);
// 4.接続済みソケットと送受信する(recv, send一回ずつ)
// RepeatClientMessage(int clntSock);
// for (int i = 0; i < connection_count; i++)
// {
// 	if (FD_ISSET(clntSock[i], &readfds))
// 	{
// 		RepeatClientMessage(clntSock[i]);
// 	}
// }
