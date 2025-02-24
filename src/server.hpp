#pragma once

#include <cstdint>

#include "util/socket.hpp"

class Server {
 private:
  util::Socket server_socket_;

 public:
  Server() = delete;
  Server(std::uint16_t port);
  ~Server();

  void Start();
};