#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace util {
class Socket {
 public:
  using native_socket_handle_t = std::uintptr_t;
  enum class family_t { inet = 2 };
  enum class specification_t { stream = 1 };
  enum class protocol_t { tcp, udp };

  static constexpr std::size_t kMaxBacklog = 0x7FFFFFFF;

 private:
  enum class option { timeout };
  static constexpr native_socket_handle_t kSocketError = -1;

  native_socket_handle_t native_socket_handle_{};
  family_t family_;
  specification_t specification_;
  protocol_t protocol_;

 public:
  Socket() = delete;
  Socket(const Socket&) = delete;
  Socket& operator=(const Socket&) = delete;
  Socket(family_t family, specification_t specification, protocol_t protocol);
  ~Socket();
  Socket(Socket&& other);
  Socket& operator=(Socket&& other);

  native_socket_handle_t& Get();

  void Bind(family_t family, std::string host, std::uint16_t port);
  void SetTimeout(std::size_t timeout);
  void Listen(std::size_t backlog = util::Socket::kMaxBacklog);
  Socket Accept();

  std::vector<std::uint8_t> Read(const std::size_t buffer_size);
  void Write(const std::vector<std::uint8_t>& buffer);
};
}  // namespace util