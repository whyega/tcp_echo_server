#include "server.hpp"

#include <spdlog/spdlog.h>

#include <cstdint>
#include <vector>

#include "util/socket.hpp"
#include "util/string.hpp"

auto kBeginHtmlData = R"(<!DOCTYPE html>
<html>
<head>
    <title>Echo Server</title>
</head>
<body>
    <h1>You said:</h1>
    <p>)";

auto kAfterHtmlData = R"(</p>
</body>
</html>)";

Server::Server(std::uint16_t port, std::size_t max_connections,
               std::size_t mtu_size, std::size_t timeout)
    : server_socket_(util::Socket::family_t::inet,
                     util::Socket::specification_t::stream,
                     util::Socket::protocol_t::tcp),
      max_connections_(max_connections),
      mtu_size_(mtu_size) {
  server_socket_.Bind(util::Socket::family_t::inet, "127.0.0.1", port);
  server_socket_.SetTimeout(timeout);
  spdlog::info(
      "Server created (socket {}, port: {}, timeout: {}, max_connections {}, "
      "mtu_size {})",
      server_socket_.Get(), port, timeout, max_connections, mtu_size);
}

void Server::HandlePacket(util::Socket& client_socket,
                          std::vector<std::uint8_t> packet) {
  auto data = std::string(packet.begin(), packet.end());
  spdlog::info("Receive buffer[{}]:\n{}", packet.size(), data.c_str());

  auto formated = util::string::replace_all(data, "&", "&amp;");
  formated = util::string::replace_all(formated, ">", "&gt;");
  formated = util::string::replace_all(formated, "<", "&lt;");
  formated = util::string::replace_all(formated, "'", "&apos;");
  formated = util::string::replace_all(formated, "\"", "&quot;");

  auto result_response = kBeginHtmlData + formated + kAfterHtmlData;

  spdlog::info("Response:\n{}", result_response);

  client_socket.Write({result_response.begin(), result_response.end()});
}

void Server::Start() {
  server_socket_.Listen();
  spdlog::info("Server starting");

  while (true) {
    auto client_socket = server_socket_.Accept();
    // Single thread
    // if (connectioins_count_ > max_connections_) {
    //   continue;
    // }
    // connectioins_count_++;

    spdlog::info("New connection");

    auto packet = client_socket.Read(mtu_size_);
    HandlePacket(client_socket, packet);
    // connectioins_count_--;
  }
}