#ifndef EVENTLOOP_HPP
#define EVENTLOOP_HPP

#include <map>

#include "ASocket.hpp"

class EventLoop {
 public:
  EventLoop();
  ~EventLoop();

  void loop();

 private:
  EventLoop(const EventLoop& other);
  EventLoop& operator=(const EventLoop& other);

  Observer* observer;
  std::map<int, ASocket*> fd2socket_;
  ;
};

#endif /* EVENTLOOP_HPP */
