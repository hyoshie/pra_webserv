#include "Selector.hpp"

Selector::Selector(std::set<int> readfds) { init(readfds); }

Selector::~Selector() {}

void Selector::init(std::set<int> readfds) {
  target_readfds_ = readfds;

  std::set<int>::iterator ite = target_readfds_.end();
  ite--;
  max_fd_ = *ite;

  evnet_cnt_ = 0;
  timeout_.tv_sec = 10;
  timeout_.tv_usec = 0;
}

int Selector::monitor() {
  fd_set tmp_readfds = toFdset(target_readfds_);
  fd_set tmp_writefds = toFdset(target_writefds_);

  evnet_cnt_ =
      // select(max_fd_ + 1, &tmp_readfds, &tmp_writefds, NULL, &timeout_);
      select(max_fd_ + 1, &tmp_readfds, NULL, NULL, &timeout_);
  ready_readfds_ = toSet(tmp_readfds, target_readfds_);
  if (evnet_cnt_ < 0) {
    DieWithError("select failed()");
  }
  if (evnet_cnt_ == 0) {
    std::cerr << "Time out, you had tea break?" << std::endl;
  }

  // ready_writefds_ = toSet(tmp_writefds, target_writefds_);
  return evnet_cnt_;
}

int Selector::getEventCount() const { return evnet_cnt_; }

std::set<int> Selector::getReadyReadFds() const { return ready_readfds_; }

std::set<int> Selector::getReadyWriteFds() const { return ready_writefds_; }

void Selector::addReadFd(int fd) {
  target_readfds_.insert(fd);
  if (fd > max_fd_) {
    max_fd_ = fd;
  }
}

void Selector::addWriteFd(int fd) {
  target_writefds_.insert(fd);
  if (fd > max_fd_) {
    max_fd_ = fd;
  }
}

void Selector::removeReadFd(int fd) {
  target_readfds_.erase(fd);
  if (fd == max_fd_) {
    std::set<int>::iterator itr = target_readfds_.end();
    // std::set<int>::iterator itw = target_writefds_.end();
    itr--;
    // itw--;
    // max_fd_ = (*itr > *itw) ? *itr : *itw;
    max_fd_ = *itr;
  }
}

void Selector::removeWriteFd(int fd) {
  target_writefds_.erase(fd);
  // if (fd == max_fd_) {
  //   std::set<int>::iterator itr = target_readfds_.end();
  //   std::set<int>::iterator itw = target_writefds_.end();
  //   itr--;
  //   itw--;
  // }
}

fd_set Selector::toFdset(std::set<int> cont_fds) {
  fd_set fds;

  FD_ZERO(&fds);
  std::set<int>::iterator it = cont_fds.begin();
  std::set<int>::iterator ite = cont_fds.end();
  for (; it != ite; it++) {
    FD_SET(*it, &fds);
  }
  return fds;
}

std::set<int> Selector::toSet(fd_set fds, std::set<int> cont_fds) {
  std::set<int> new_cont_fds;

  std::set<int>::iterator it = cont_fds.begin();
  std::set<int>::iterator ite = cont_fds.end();
  for (; it != ite; it++) {
    if (FD_ISSET(*it, &fds)) {
      new_cont_fds.insert(*it);
    }
  }
  return new_cont_fds;
}

void printSetInfo(std::set<int> fds) {
  std::set<int>::iterator it = fds.begin();
  std::set<int>::iterator ite = fds.end();

  for (; it != ite; it++) {
    std::cerr << *it << ", ";
  }
  std::cerr << std::endl;
}

void Selector::showDebugInfo() const {
  std::cerr << std::endl;
  std::cerr << "###Selecter Info###" << std::endl
            << "max_fd: " << max_fd_ << std::endl
            << "evnet_cnt: " << evnet_cnt_ << std::endl;
  std::cerr << "ready_readfds: ";
  printSetInfo(ready_readfds_);
  std::cerr << "ready_writefds: ";
  printSetInfo(ready_writefds_);
  std::cerr << "###end###" << std::endl;
  std::cerr << std::endl;
}
