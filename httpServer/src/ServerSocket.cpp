#include "ServerSocket.hpp"

ServerSocket::ServerSocket()
    : ASocket(socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) {
  struct sockaddr_in server_addr;

  if (fd_ < 0) {
    throw std::runtime_error("socket() failed");
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(kServerPort);

  int opt = 1;
  if (setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&opt),
                 sizeof(int)) < 0) {
    throw std::runtime_error("setsockopt() failed");
  }

  if (bind(fd_, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    throw std::runtime_error("bind() failed");
  }

  if (listen(fd_, kMaxPendig) < 0) {
    throw std::runtime_error("listen() failed");
  }
}

ServerSocket::~ServerSocket() {}

void ServerSocket::notifyFdEvent() {
  std::cout << "From notify" << std::endl;
  std::cout << "fd:" << fd_ << std::endl;
  std::cout << createConnection() << std::endl;
}

int ServerSocket::createConnection() {
  std::cout << "From CreateCon" << std::endl;
  return 2;
}
