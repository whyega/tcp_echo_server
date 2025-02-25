#pragma once

#include <cstdint>

#include "util/socket.hpp"

class Server {
 private:
  static constexpr std::size_t kMTUSize = 1024;
  util::Socket server_socket_;

 public:
  Server() = delete;
  Server(std::uint16_t port);
  ~Server();

  void Start();
};