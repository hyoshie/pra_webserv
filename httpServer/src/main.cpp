#include <exception>

#include "Selector.hpp"
#include "Server.hpp"
#include "color.hpp"

void eventLoop() {
  Server serv;
  Selector selector(serv.getAllSocketFd());

  for (;;) {
    selector.init(serv.getAllSocketFd());
    selector.monitor();
    // debug
    // selector.showDebugInfo();

    // accept
    std::set<int> readable_fds = selector.getReadyReadFds();
    if (readable_fds.find(serv.getListenFd()) != readable_fds.end()) {
      serv.createConnection();
      readable_fds.erase(serv.getListenFd());
    }

    // read
    std::set<int>::iterator it = readable_fds.begin();
    std::set<int>::iterator ite = readable_fds.end();
    for (; it != ite; it++) {
      int recvMsgSize = serv.handleReadEvent(*it);
      if (recvMsgSize > 0) {
        selector.addTargetWriteFd(*it);
      } else {
        selector.removeTargetWriteFd(*it);
        serv.destroyConnection(*it);
      }
    }

    // write
    std::set<int> writable_fds = selector.getReadyWriteFds();
    it = writable_fds.begin();
    ite = writable_fds.end();
    for (; it != ite; it++) {
      serv.handleWriteEvent(*it);
      selector.removeTargetWriteFd(*it);
    }
  }
}

int main() {
  std::cout << YELLOW << "Welcome to our http server!" << RESET << std::endl;

  try {
    eventLoop();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
