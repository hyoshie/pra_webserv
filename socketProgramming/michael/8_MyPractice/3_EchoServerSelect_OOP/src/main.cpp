#include <iostream>

#include "Selector.hpp"
#include "Server.hpp"
#include "color.hpp"

int main() {
  std::cout << YELLOW << "Welcome to EchoServer!" << RESET << std::endl;

  Server serv;
  Selector sel(serv.getAllSocketFd());

  for (;;) {
    sel.init(serv.getAllSocketFd());
    int event_cnt = sel.monitor();
    sel.showDebugInfo();

    std::set<int> readablefds = sel.getReadyReadFds();
    if (readablefds.find(serv.getListenFd()) != readablefds.end()) {
      serv.accept();
    }

    std::set<int>::iterator it = readablefds.begin();
    std::set<int>::iterator ite = readablefds.end();
    for (; it != ite; it++) {
      if (*it != serv.getListenFd()) {
        int recvMsgSize = serv.repeatClientMessage(*it);
        if (recvMsgSize <= 0) {
          serv.close(*it);
        }
      }
    }
  }
}
