#include "Server.hpp"

Server::Server() {
  //接続待受用のソケットを作る, socketクラス作ったほうがよさげ
  struct sockaddr_in server_addr;

  listen_fd_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (listen_fd_ < 0) {
    throw std::runtime_error("socket() failed");
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(kServerPort);

  int opt = 1;
  if (setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                 sizeof(int)) < 0) {
    throw std::runtime_error("setsockopt() failed");
  }

  if (bind(listen_fd_, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    throw std::runtime_error("bind() failed");
  }

  if (listen(listen_fd_, kMaxPendig) < 0) {
    throw std::runtime_error("listen() failed");
  }
}

//デストラクターと例外の関係調べる
Server::~Server() {
  if (::close(listen_fd_) < 0) {
    // throw std::runtime_error("close failed()");
  }
}

int Server::getListenFd() const { return listen_fd_; }

std::set<int> Server::getConnectedFd() const { return connected_fd_; }

std::set<int> Server::getAllSocketFd() const {
  std::set<int> all_socket_fds(connected_fd_);

  all_socket_fds.insert(listen_fd_);
  return all_socket_fds;
}

int Server::accept() {
  int tmp_socket;

  tmp_socket = ::accept(listen_fd_, NULL, NULL);
  if (tmp_socket < 0) {
    throw std::runtime_error("accept failed()");
  }
  connected_fd_.insert(tmp_socket);
  //クライアントの数のバリデーション
  std::cout << "accept: fd(" << tmp_socket << "), "
            << "total connection:" << connected_fd_.size() << std::endl;
  return tmp_socket;
}

int Server::close(int fd) {
  int ret = ::close(fd);

  if (ret < 0) {
    throw std::runtime_error("close failed()");
  }
  connected_fd_.erase(fd);
  return ret;
}

int Server::recvClientMessage(int readable_fd) {
  int recvMsgSize;

  recvMsgSize = recv(readable_fd, buffer_[readable_fd], kRecvBufferSize, 0);
  if (recvMsgSize < 0) {
    throw std::runtime_error("recv() failed");
  }
  if (recvMsgSize == 0) {
    std::cerr << "recv: EOF" << std::endl;
    return 0;
  }
  buffer_[readable_fd][recvMsgSize] = '\0';
  std::cerr << "recv from fd(" << readable_fd << "): " << buffer_[readable_fd]
            << std::endl;

  return recvMsgSize;
}

int Server::sendMessage(int writable_fd) {
  // char message[] = "42tokyo\n";
  if (send(writable_fd, buffer_[writable_fd], strlen(buffer_[writable_fd]),
           0) != strlen(buffer_[writable_fd])) {
    throw std::runtime_error("send() failed");
  }
  return 0;
}
