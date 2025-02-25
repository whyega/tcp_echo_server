#include "server.hpp"

#include <spdlog/spdlog.h>

#include <cstdint>
#include <vector>

#include "util/socket.hpp"

Server::Server(std::uint16_t port, std::size_t max_connections,
               std::size_t mtu_size, std::size_t timeout)
    : server_socket_(util::Socket::family_t::inet,
                     util::Socket::specification_t::stream,
                     util::Socket::protocol_t::tcp),
      mtu_size_(mtu_size) {
  server_socket_.Bind(util::Socket::family_t::inet, "127.0.0.1", port);
  // impl timeout
  server_socket_.SetTimeout(timeout);
  spdlog::info(
      "Server created (socket {}, port: {}, timeout: {}, max_connections {}, "
      "mtu_size {})",
      server_socket_.Get(), port, timeout, max_connections, mtu_size);
}

Server::~Server() {}

void Server::HandlePacket(std::vector<std::uint8_t>) {}

void Server::Start() {
  server_socket_.Listen();
  spdlog::info("Server starting");

  while (true) {
    auto client_socket = server_socket_.Accept();
    spdlog::info("New connection");

    auto packet = client_socket.Read(mtu_size_);
    spdlog::info("Receive buffer[{}]: {}", packet.size(),
                 std::string(packet.begin(), packet.end()).c_str());
    HandlePacket(packet);
  }
}