#include <WinSock2.h>
#include <Windows.h>
#include <minwindef.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main() {
  WSAData wsa_data;
  if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
    std::cout << "Error WSAStartup" << std::endl;
    return 1;
  }
  auto socket_handle = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_handle == SOCKET_ERROR) {
    std::cout << "Error socket create" << std::endl;
    return 1;
  }

  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8814);
  inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
  if (connect(socket_handle, reinterpret_cast<sockaddr*>(&server_address),
              sizeof(server_address)) == SOCKET_ERROR) {
    std::cout << "Connection error" << std::endl;
    return 1;
  }

  const char* message = "Hello, TCP Server!";
  send(socket_handle, message, strlen(message), 0);

  closesocket(socket_handle);
  WSACleanup();
}