#include <iostream>

#include "Connection.hpp"
#include "Server.hpp"
#include "ServerSocket.hpp"

void print(ASocket *socket) { socket->notifyFdEvent(); }

int main() {
  // ServerSocket sock;
  // Connection connection(5);

  // print(&sock);
  // print(&connection);
  Server server;
  server.run();
}
