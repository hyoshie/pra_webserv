#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <sys/select.h>
#include <time.h>

#include <iostream>
#include <set>

class Observer {
 public:
  Observer();
  ~Observer();

  void notifyFdEvent();
  void init();
  void addTargetReadFd(int fd);
  void addTargetWriteFd(int fd);
  void delTargetReadFd(int fd);
  void delTargetWriteFd(int fd);
  const std::set<int>& getReadyFds() const;
  void showInfo() const;

 private:
  static const int kTimeoutSec = 5;

  Observer(const Observer& other);
  Observer& operator=(const Observer& other);

  void printfdset(fd_set fds) const;
  std::set<int> buildReadyFds() const;

  int maxfd_;
  int evnet_cnt_;
  fd_set readfds_;
  fd_set writefds_;
  struct timeval timeout_;

  std::set<int> readyfds_;
  std::set<int> targetfds_;
  ;
};

#endif /* OBSERVER_HPP */
