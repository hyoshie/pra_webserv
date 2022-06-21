#include <exception>

#include "Selector.hpp"
#include "Server.hpp"
#include "color.hpp"

void eventLoop() {
  Server serv;
  Selector selector(serv.getAllSocketFd());

  for (;;) {
    selector.init(serv.getAllSocketFd());
    int event_cnt = selector.monitor();
    selector.showDebugInfo();

    // accept
    std::set<int> readablefds = selector.getReadyReadFds();
    if (readablefds.find(serv.getListenFd()) != readablefds.end()) {
      serv.accept();
    }

    // read
    std::set<int>::iterator it = readablefds.begin();
    std::set<int>::iterator ite = readablefds.end();
    for (; it != ite; it++) {
      if (*it != serv.getListenFd()) {
        int recvMsgSize = serv.recvClientMessage(*it);
        if (recvMsgSize > 0) {
          selector.addWriteFd(*it);
        } else {
          selector.removeWriteFd(*it);
          serv.close(*it);
        }
      }
    }

    // write
    std::set<int> writablefds = selector.getReadyWriteFds();
    it = writablefds.begin();
    ite = writablefds.end();
    for (; it != ite; it++) {
      int sendMsgSize = serv.sendMessage(*it);
      selector.removeWriteFd(*it);
    }
  }
}

int main() {
  std::cout << YELLOW << "Welcome to EchoServer!" << RESET << std::endl;

  try {
    // throw "hoge";
    eventLoop();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
