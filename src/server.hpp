#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "util/socket.hpp"

class Server {
 private:
  util::Socket server_socket_;
  std::size_t max_connections_{};
  std::size_t connectioins_count_{};
  std::size_t mtu_size_{};

  void HandlePacket(util::Socket& client_socket,
                    std::vector<std::uint8_t>& packet);

 public:
  Server() = delete;
  Server(std::uint16_t port, std::size_t max_connections, std::size_t mtu_size,
         std::size_t timeout);
  ~Server() = default;

  void Start();
};