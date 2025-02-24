#include "server.hpp"

#include <spdlog/spdlog.h>

#include <cstdint>

#include "util/socket.hpp"

Server::Server(std::uint16_t port)
    : server_socket_(util::Socket::family_t::inet,
                     util::Socket::specification_t::stream,
                     util::Socket::protocol_t::tcp) {
  server_socket_.Bind(util::Socket::family_t::inet, "127.0.0.1", port);
  spdlog::info("Server binding on {} port");
}

Server::~Server() {}

void Server::Start() {
  // todo
  server_socket_.Listen(1);
  auto client_socket = server_socket_.Accept();
}