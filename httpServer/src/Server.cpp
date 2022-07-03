#include "Server.hpp"

Server::Server() {}

Server::~Server() {}

void Server::run() {
  ServerSocket serv_sock;
  std::map<int, ASocket *> fd2set;
  fd2set[serv_sock.getFd()] = &serv_sock;

  Observer *observer = new Observer;
  observer->addTargetReadFd(serv_sock.getFd());
  EventLoop eventloop(observer, fd2set);
  eventloop.loop();
}
