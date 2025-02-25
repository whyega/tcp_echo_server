#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "util/socket.hpp"

class Server {
 private:
  static constexpr std::size_t kMTUSize = 1024;
  util::Socket server_socket_;
  std::size_t max_connections_;
  std::size_t connectioins_count_;
  std::size_t timeout_;
  std::size_t mtu_size_;

  void HandlePacket(std::vector<std::uint8_t> packet);

 public:
  Server() = delete;
  Server(std::uint16_t port, std::size_t max_connections, std::size_t mtu_size,
         std::size_t timeout);
  ~Server();

  void Start();
};