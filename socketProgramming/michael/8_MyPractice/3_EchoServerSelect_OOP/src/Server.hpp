#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <exception>
#include <iostream>
#include <set>

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
  int repeatClientMessage(int readable_fd);  //接続を切るかは後で考える

 private:
  // not copy
  Server(const Server& other);
  Server& operator=(const Server& other);

 private:
  int listen_fd_;
  std::set<int> connected_fd_;

  const int kServerPort = 5000;
  const int kMaxPendig = 5;
  const int kRecvBufferSize = 32;
};

#endif /* SERVER_HPP */
