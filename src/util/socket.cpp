#include "socket.hpp"

#include <stdexcept>

#ifdef _WIN32
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
  // todo: add static wsa initialize
  native_socket_handle_ =
      socket(static_cast<int>(family), static_cast<int>(specification),
             static_cast<int>(protocol));
  if (native_socket_handle_ == kSocketError) {
    throw std::runtime_error("Error create socket");
  }
}

Socket::~Socket() {
#ifdef _WIN32
  closesocket(native_socket_handle_);
#else
  close(native_socket_handle_);
#endif
}

Socket::Socket(const Socket&& other) {}

Socket& Socket::operator=(const Socket&& other) {
  ;
  return *this;
}

void Socket::Bind(family_t family, std::string_view host, std::uint16_t port) {}

void Socket::Listen(std::size_t) {}

// Socket Socket::Accept() {  }
}  // namespace util