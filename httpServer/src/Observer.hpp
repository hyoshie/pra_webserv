#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Observer {
 public:
  Observer();
  ~Observer();

  void addTargetReadFd(int fd);
  void addTargetWriteFd(int fd);
  void delTargetReadFd(int fd);
  void delTargetWriteFd(int fd);
  void notifyFdEvent();
  const std::set<int>& getReadyFds() const;
  void showInfo() const;

 private:
  static const int kTimeoutSec = 5;

  Observer(const Observer& other);
  Observer& operator=(const Observer& other);

  int max_fd_;
  fd_set readfds_;
  fd_set writefds_;

  std::set<int> ready_fds_;
  ;
};

#endif /* OBSERVER_HPP */
