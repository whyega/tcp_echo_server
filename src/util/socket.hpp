#pragma once

#include <cstdint>
#include <string_view>

namespace util {
class Socket {
 public:
  using native_socket_handle_t = std::uintptr_t;
  enum class family_t { inet = 2 };
  enum class specification_t { stream = 1 };
  enum class protocol_t { tcp, udp };

 private:
  static constexpr native_socket_handle_t kSocketError = -1;

  native_socket_handle_t native_socket_handle_{};

 public:
  Socket() = delete;
  Socket(const Socket&) = delete;
  Socket& operator=(const Socket&) = delete;
  Socket(family_t family, specification_t specification, protocol_t protocol);
  ~Socket();
  Socket(const Socket&& other);
  Socket& operator=(const Socket&& other);

  void Bind(family_t family, std::string_view host, std::uint16_t port);
  void Listen(std::size_t);
  Socket Accept();
};
}  // namespace util