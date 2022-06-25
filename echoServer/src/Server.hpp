#ifndef ECHOSERVER_SRC_SERVER_HPP_
#define ECHOSERVER_SRC_SERVER_HPP_

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <exception>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

#include "Connection.hpp"
#include "color.hpp"

void DieWithError(const char* message);

class Server {
 public:
  Server();
  ~Server();

  void createConnection();
  void destroyConnection(int fd);
  int handleReadEvent(int fd);
  void handleWriteEvent(int fd);

  // アクセッサー
  int getListenFd() const;
  const std::set<int>& getAllSocketFd() const;

 private:
  static const int kServerPortBase = 5000;
  static const int kMaxPendig = 5;
  static const int kMaxConnection = 32;

  // not copy
  Server(const Server& other);
  Server& operator=(const Server& other);

  int accept();
  int close(int fd);

  int listen_fd_;
  std::set<int> all_socket_fd_;
  std::map<int, Connection*> connections_;
};

#endif  // ECHOSERVER_SRC_SERVER_HPP_
