#include "EventLoop.hpp"

// EventLoop::EventLoop() : observer(new Observer) {}
EventLoop::EventLoop(Observer *observer,
                     const std::map<int, ASocket *> &fd2socket)
    : observer_(observer), fd2socket_(fd2socket) {}

EventLoop::~EventLoop() {}

void EventLoop::loop() {
  while (true) {
    observer_->notifyFdEvent();
    printf("[\x1b[32mpass observ\x1b[39m]\n");
    std::set<int> readyfds = observer_->getReadyFds();
    std::set<int>::iterator it = readyfds.begin();
    std::set<int>::iterator ite = readyfds.end();
    for (; it != ite; it++) {
      fd2socket_[*it]->notifyFdEvent();
    }
  }
}

// EventLoop::EventLoop(const EventLoop& other) {
//   *this = other;
// }

// EventLoop& EventLoop::operator=(const EventLoop& other) {
//   if (this != &other) {
//   }
//   return *this;
// }
