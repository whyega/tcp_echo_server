#include "socket.hpp"

#include <winsock2.h>

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

#ifdef _WIN32
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

namespace util {
Socket::Socket(family_t family, specification_t specification,
               protocol_t protocol) {
#ifdef _WIN32
  WSAData wsa_data;
  if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
    throw std::runtime_error("Error WSAStartup");
  }
#endif

  native_socket_handle_ =
      socket(static_cast<int>(family), static_cast<int>(specification),
             static_cast<int>(protocol));
  family_ = family;
  specification_ = specification;
  protocol_ = protocol;
  if (native_socket_handle_ == kSocketError) {
    throw std::runtime_error("Error create socket");
  }
}

Socket::~Socket() {
#ifdef _WIN32
  closesocket(native_socket_handle_);
  WSACleanup();
#else
  close(native_socket_handle_);
#endif
}

Socket::Socket(Socket&& other)
    : native_socket_handle_(other.native_socket_handle_) {
  other.native_socket_handle_ = 0;
}

Socket& Socket::operator=(Socket&& other) {
  if (this != &other) {
    native_socket_handle_ = other.native_socket_handle_;
    other.native_socket_handle_ = 0;
  }
  return *this;
}

Socket::native_socket_handle_t& Socket::Get() { return native_socket_handle_; }

void Socket::Bind(family_t family, std::string host, std::uint16_t port) {
  sockaddr_in server_address;
  server_address.sin_family = static_cast<int>(family);
  server_address.sin_port = htons(port);
  if (inet_pton(static_cast<int>(family), host.c_str(),
                &server_address.sin_addr) == kSocketError) {
    throw std::runtime_error("Error inet_pton");
  }

  if (bind(native_socket_handle_, reinterpret_cast<sockaddr*>(&server_address),
           sizeof(server_address)) == kSocketError) {
    throw std::runtime_error("Error binding socket");
  }
}

void Socket::SetTimeout(std::size_t timeout) {}

void Socket::Listen(std::size_t backlog) {
  if (listen(native_socket_handle_, backlog) == kSocketError) {
    throw std::runtime_error("Error listing");
  }
}

Socket Socket::Accept() {
  sockaddr_in client_address;
  int client_address_size = sizeof(client_address);
  auto client_native_socket_handle = accept(
      native_socket_handle_, reinterpret_cast<sockaddr*>(&client_address),
      &client_address_size);
  if (client_native_socket_handle == kSocketError) {
    throw std::runtime_error("Error accept connection");
  }

  Socket client_socket(family_, specification_, protocol_);
  client_socket.native_socket_handle_ = client_native_socket_handle;

  return client_socket;
}

std::vector<std::uint8_t> Socket::Read(const std::size_t buffer_size) {
  std::vector<std::uint8_t> buffer(buffer_size);
  auto recv_size =
      recv(native_socket_handle_, reinterpret_cast<char*>(buffer.data()),
           buffer.size(), 0);
  if (recv_size == kSocketError) {
    throw std::runtime_error("Error read from socket");
  }

  buffer.resize(recv_size);
  return buffer;
}

void Socket::Write(const std::vector<std::uint8_t>& buffer) {
  auto send_size =
      send(native_socket_handle_, reinterpret_cast<const char*>(buffer.data()),
           buffer.size(), 0);
  if (send_size == kSocketError) {
    throw std::runtime_error("Error write to socket");
  }
}
}  // namespace util