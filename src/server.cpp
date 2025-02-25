#include "server.hpp"

#include <spdlog/spdlog.h>

#include <cstdint>
#include <vector>

#include "util/socket.hpp"
#include "util/string.hpp"

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

void Server::HandlePacket(util::Socket& client_socket,
                          std::vector<std::uint8_t> packet) {
  auto data = std::string(packet.begin(), packet.end());
  spdlog::info("Receive buffer[{}]:\n{}", packet.size(), data.c_str());

  auto formated = util::replace_all(data, "<", "&lt;");
  formated = util::replace_all(formated, ">", "&gt;");
  formated = util::replace_all(formated, "&", "&amp;");
  formated = util::replace_all(formated, "'", "&apos;");
  formated = util::replace_all(formated, "\"", "&lt;");

  spdlog::info("Formated: {}", formated);

  client_socket.Write({data.begin(), data.end()});
}

void Server::Start() {
  server_socket_.Listen();
  spdlog::info("Server starting");

  while (true) {
    auto client_socket = server_socket_.Accept();
    spdlog::info("New connection");

    auto packet = client_socket.Read(mtu_size_);
    HandlePacket(client_socket, packet);
  }
}