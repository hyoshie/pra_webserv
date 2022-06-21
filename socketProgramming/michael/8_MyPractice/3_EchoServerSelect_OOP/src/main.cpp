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

    // accept
    std::set<int> readablefds = sel.getReadyReadFds();
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
          sel.addWriteFd(*it);
        } else {
          sel.removeWriteFd(*it);
          serv.close(*it);
        }
      }
    }

    // write
    std::set<int> writablefds = sel.getReadyWriteFds();
    it = writablefds.begin();
    ite = writablefds.end();
    for (; it != ite; it++) {
      int sendMsgSize = serv.sendMessage(*it);
      sel.removeWriteFd(*it);
    }
  }
}
