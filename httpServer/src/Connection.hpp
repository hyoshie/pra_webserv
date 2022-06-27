#ifndef HTTPSERVER_SRC_CONNECTION_HPP_
#define HTTPSERVER_SRC_CONNECTION_HPP_

#include <sys/socket.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include <string>

// #include "Request.hpp"
#include "HttpResponse.hpp"

class Connection {
 public:
  explicit Connection(int accepted_fd);
  ~Connection();

  int handleReadEvent();
  void handleWriteEvent();

 private:
  static const int kRecvBufferSize = (1 << 16);
  // 65536, httpServerだとリクエストの文字数の上限かな

  Connection();
  Connection(const Connection& other);
  Connection& operator=(const Connection& other);

  ssize_t recvFromClient();
  void createResponse(ssize_t recv_size);
  void sendResponse() const;

  int socket_fd_;
  char recv_buffer_[kRecvBufferSize + 1];
  std::string response_;
  // Request* current_request_;
  HttpResponse* current_response_;
};

#endif  // HTTPSERVER_SRC_CONNECTION_HPP_
