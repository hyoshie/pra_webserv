#ifndef ECHOSERVER_SRC_SERVER_HPP_
#define ECHOSERVER_SRC_SERVER_HPP_

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <exception>
#include <iostream>
#include <set>

#include "color.hpp"

void DieWithError(const char* message);

class Server {
 public:
  Server();
  ~Server();

  int getListenFd() const;
  std::set<int> getConnectedFd() const;
  std::set<int> getAllSocketFd() const;
  int accept();
  int close(int fd);
  int recvClientMessage(int readable_fd);
  int sendMessage(int writable_fd);

 private:
  // not copy
  Server(const Server& other);
  Server& operator=(const Server& other);

 private:
  const int kServerPort = 5000;
  static const int kMaxPendig = 5;
  static const int kRecvBufferSize = 32;
  static const int kMaxConnection = 32;

  int listen_fd_;
  std::set<int> connected_fd_;
  char buffer_[kMaxConnection][kRecvBufferSize + 1];
};

#endif  // ECHOSERVER_SRC_SERVER_HPP_
