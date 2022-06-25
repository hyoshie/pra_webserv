#include "Server.hpp"

Server::Server() {
  // 接続待受用のソケットを作る, socketクラス作ったほうがよさげ
  struct sockaddr_in server_addr;

  listen_fd_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (listen_fd_ < 0) {
    throw std::runtime_error("socket() failed");
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(kServerPortBase);

  int opt = 1;
  if (setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR,
                 reinterpret_cast<char *>(&opt), sizeof(int)) < 0) {
    throw std::runtime_error("setsockopt() failed");
  }

  if (bind(listen_fd_, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    throw std::runtime_error("bind() failed");
  }

  if (listen(listen_fd_, kMaxPendig) < 0) {
    throw std::runtime_error("listen() failed");
  }
  all_socket_fd_.insert(listen_fd_);
}

// デストラクターと例外の関係調べる
Server::~Server() {
  if (::close(listen_fd_) < 0) {
    // throw std::runtime_error("close failed()");
  }
}

int Server::getListenFd() const { return listen_fd_; }

const std::set<int> &Server::getAllSocketFd() const { return all_socket_fd_; }

void Server::createConnection() {
  int socket = accept();
  Connection *new_Connection = new Connection(socket);
  connections_.insert(std::pair<int, Connection *>(socket, new_Connection));
}

void Server::destroyConnection(int fd) {
  close(fd);
  delete connections_[fd];
  connections_.erase(fd);
}

int Server::handleReadEvent(int fd) {
  return connections_[fd]->handleReadEvent();
}
void Server::handleWriteEvent(int fd) { connections_[fd]->handleWriteEvent(); }

int Server::accept() {
  int tmp_socket;

  tmp_socket = ::accept(listen_fd_, NULL, NULL);
  if (tmp_socket < 0) {
    throw std::runtime_error("accept failed()");
  }
  all_socket_fd_.insert(tmp_socket);
  // クライアントの数のバリデーション
  std::cout << "accept: fd(" << tmp_socket << "), "
            << "total connection:" << all_socket_fd_.size() - 1 << std::endl;
  return tmp_socket;
}

int Server::close(int fd) {
  int ret = ::close(fd);

  if (ret < 0) {
    throw std::runtime_error("close failed()");
  }
  all_socket_fd_.erase(fd);
  return ret;
}
