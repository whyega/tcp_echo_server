#include <WinSock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

#include <fstream>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Enter server address and port" << std::endl;
    return 1;
  }

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

  auto port = std::stoi(argv[1]);
  auto host = argv[2];

  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  inet_pton(AF_INET, host, &server_address.sin_addr);
  if (connect(socket_handle, reinterpret_cast<sockaddr*>(&server_address),
              sizeof(server_address)) == SOCKET_ERROR) {
    std::cout << "Connection error" << std::endl;
    return 1;
  }

  std::string text = "<<Hello>> & 'World' \"Yeee\"";

  send(socket_handle, text.c_str(), text.size(), 0);

  std::string response(1024, '\0');
  auto bytes_received =
      recv(socket_handle, response.data(), response.size(), 0);
  response.resize(bytes_received);

  std::cout << "Response" << response << std::endl;

  {
    std::ofstream file("index.html");
    file << response;
  }

  closesocket(socket_handle);
  WSACleanup();
}