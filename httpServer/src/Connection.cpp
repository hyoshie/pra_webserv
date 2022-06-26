#include "Connection.hpp"

Connection::Connection(int accepted_fd) : socket_fd_(accepted_fd) {}

Connection::~Connection() {}

int Connection::handleReadEvent() {
  ssize_t recv_size = recvFromClient();

  if (recv_size == 0) {
    return 0;
  }
  createResponse(recv_size);
  // else {
  //   createResponse(recv_size);
  // }
  std::cerr << "recv from fd(" << socket_fd_ << "): " << response_ << std::endl;
  return recv_size;
}

void Connection::handleWriteEvent() { sendResponse(); }

ssize_t Connection::recvFromClient() {
  ssize_t recv_size = recv(socket_fd_, recv_buffer_, kRecvBufferSize, 0);
  if (recv_size < 0) {
    throw std::runtime_error("recv() failed");
  }
  if (recv_size == 0) {
    std::cerr << "recv: EOF" << std::endl;
    return 0;
  }
  return recv_size;
}
void Connection::createResponse(ssize_t recv_size) {
  recv_buffer_[recv_size] = '\0';

  HttpResponse *current_response_ = new HttpResponse();
  current_response_->setBody("test body message\n");
  response_ = current_response_->toString();
}

void Connection::sendResponse() const {
  const char *response = response_.c_str();
  size_t response_len = response_.size();

  if (send(socket_fd_, response, response_len, 0) !=
      static_cast<ssize_t>(response_len)) {
    throw std::runtime_error("send() failed");
  }
}
