#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include <sys/select.h>
#include <time.h>

#include <iostream>
#include <set>

void DieWithError(const char* errorMessage);

class Selector {
 public:
  Selector(std::set<int> readfds);
  ~Selector();

  void init(std::set<int> readfds);
  int monitor();
  void addReadFd(int fd);
  void addWriteFd(int fd);
  void removeReadFd(int fd);
  void removeWriteFd(int fd);
  fd_set toFdset(std::set<int> cont_fds);
  std::set<int> toSet(fd_set fds, std::set<int> cont_fds);

  //アクセッサー
  int getEventCount() const;
  std::set<int> getReadyReadFds() const;
  std::set<int> getReadyWriteFds() const;

  //デバッグ用
  void showDebugInfo() const;

 private:
  int max_fd_;
  int max_readfd_;
  int max_writefd_;

  struct timeval timeout_;
  std::set<int> target_readfds_;
  std::set<int> target_writefds_;

  int evnet_cnt_;
  std::set<int> ready_readfds_;
  std::set<int> ready_writefds_;

  static const int kTimeoutSec = 5;

 private:
  Selector();
  Selector(const Selector& other);
  Selector& operator=(const Selector& other);
};

#endif /* SELECTOR_HPP */
