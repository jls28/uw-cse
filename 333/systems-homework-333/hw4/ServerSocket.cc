/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project sequence
 *  (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>       // for snprintf()
#include <unistd.h>      // for close(), fcntl()
#include <sys/types.h>   // for socket(), getaddrinfo(), etc.
#include <sys/socket.h>  // for socket(), getaddrinfo(), etc.
#include <arpa/inet.h>   // for inet_ntop()
#include <netdb.h>       // for getaddrinfo()
#include <errno.h>       // for errno, used by strerror()
#include <string.h>      // for memset, strerror()
#include <iostream>      // for std::cerr, etc.

#include "./ServerSocket.h"

extern "C" {
#include "libhw1/CSE333.h"
}

namespace hw4 {

ServerSocket::ServerSocket(uint16_t port) {
  port_ = port;
  listen_sock_fd_ = -1;
}

ServerSocket::~ServerSocket() {
  // Close the listening socket if it's not zero.  The rest of this
  // class will make sure to zero out the socket if it is closed
  // elsewhere.
  if (listen_sock_fd_ != -1) close(listen_sock_fd_);
  listen_sock_fd_ = -1;
}

bool ServerSocket::BindAndListen(int ai_family, int *listen_fd) {
  // Use "getaddrinfo," "socket," "bind," and "listen" to
  // create a listening socket on port port_.  Return the
  // listening socket through the output parameter "listen_fd".

  // MISSING:

  // if AF_INET or AF_UNSPEC, ipv4
  // if AF_INET6, ipv6

  // Set the family
  sock_family_ = ai_family;

  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = ai_family;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  struct addrinfo *ai;

  char portString[6];
  sprintf(portString, "%u", port_);
  int res = getaddrinfo(nullptr, portString, &hints, &ai);
  if (res != 0) {
    return false;
  }
  int socketFD = -1;
  for (struct addrinfo *rp = ai; rp != nullptr; rp = rp->ai_next) {
    socketFD = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (socketFD == -1) {
      // failed to create socket, go to next
      std::cerr << "Failure to create socket" << std::endl;
      socketFD = 0;
      continue;
    }

    // Let the TCP stack reuse a socket
    int optval = 1;
    setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    // Try binding the socket to the address and port number returned
    if (bind(socketFD, rp->ai_addr, rp->ai_addrlen) == 0) {
      // Bind succeeeded!
      break;
    } else {
      close(socketFD);
      socketFD = -1;
    }
  }

  // All done with the addrinfo
  freeaddrinfo(ai);

  if (socketFD == -1) {
    // failed to make/bind socket
    std::cerr << "Failure on bind" << std::endl;
    return false;
  }

  if (listen(socketFD, 100) != 0) {
    // Failed to listen on socket
    std::cerr << "Failure on listen" << std::endl;
    close(socketFD);
    return false;
  }

  // make sure to set listen_sock_fd_ and *listen_fd!
  // Set the return param
  *listen_fd = socketFD;
  listen_sock_fd_ = socketFD;
  return true;
}

bool ServerSocket::Accept(int *accepted_fd, std::string *client_addr,
                          uint16_t *client_port, std::string *client_dnsname,
                          std::string *server_addr,
                          std::string *server_dnsname) {
  // Accept a new connection on the listening socket listen_sock_fd_.
  // (Block until a new connection arrives.)  Return the newly accepted
  // socket, as well as information about both ends of the new connection,
  // through the various output parameters.

  // MISSING:
  // gotta block!
  while (true) {
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    int client_fd = -1;
    client_fd = accept(listen_sock_fd_,
                       reinterpret_cast<struct sockaddr *>(&caddr), &caddr_len);
    if (client_fd < 0) {
      if ((errno == EAGAIN) || (errno == EINTR)) {
        continue;
      } else {
        std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
        return false;
      }
    }

    *accepted_fd = client_fd;

    char hostname[1024];
    struct sockaddr *client_info = reinterpret_cast<struct sockaddr *>(&caddr);
    if (getnameinfo(client_info, caddr_len, hostname, 1024, nullptr, 0, 0) !=
        0) {
      std::cerr << "Failure getting hostname: " << std::endl;
      return false;
    } else {
      *client_dnsname = hostname;
    }
    char client_ip[32];
    char client_portnum[6];
    if (getnameinfo(client_info, caddr_len, client_ip, 32, client_portnum, 6,
                    NI_NUMERICHOST | NI_NUMERICSERV) != 0) {
      std::cerr << "Failure getting ip and port: " << std::endl;
      return false;
    } else {
      *client_addr = client_ip;
      *client_port = std::stoi(client_portnum);
    }

    struct sockaddr_storage server_info_storage;
    socklen_t sistorage_len = sizeof(server_info_storage);
    if (getsockname(client_fd,
                    reinterpret_cast<struct sockaddr *>(&server_info_storage),
                    &sistorage_len) != 0) {
      std::cerr << "Failure getting sockname of server" << std::endl;
      return false;
    }

    struct sockaddr *srv_info =
        reinterpret_cast<struct sockaddr *>(&server_info_storage);
    char server_hostname[1024];
    if (getnameinfo(srv_info, sistorage_len, server_hostname, 1024, nullptr, 0,
                    0) != 0) {
      std::cerr << "Failure getting hostname of server" << std::endl;
      return false;
    }
    *server_dnsname = server_hostname;

    char server_ip[32];
    if (getnameinfo(srv_info, sistorage_len, server_ip, 32, nullptr, 0,
                    NI_NUMERICHOST) != 0) {
      std::cerr << "Failure getting ip of server" << std::endl;
      return false;
    }
    *server_addr = server_ip;

    // We've got all the fields!
    return true;
  }
}

}  // namespace hw4
