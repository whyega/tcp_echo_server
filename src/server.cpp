#include "server.hpp"

#include <spdlog/spdlog.h>

#include <cstdint>

#include "util/socket.hpp"

Server::Server(std::uint16_t port)
    : server_socket_(util::Socket::family_t::inet,
                     util::Socket::specification_t::stream,
                     util::Socket::protocol_t::tcp) {
  server_socket_.Bind(util::Socket::family_t::inet, "127.0.0.1", port);
  spdlog::info("Server binding on {} port", port);
}

Server::~Server() {}

void Server::Start() {
  server_socket_.Listen();
  spdlog::info("Server starting");

  while (true) {
    auto client_socket = server_socket_.Accept();
    spdlog::info("New connection");

    auto receive_buffer = client_socket.Read(kMTUSize);
    spdlog::debug("Receive buffer {}", receive_buffer.data()[0]);
  }
}