#include <cstdint>
#include <cxxopts.hpp>
#include <iostream>

#include "server.hpp"
#include "spdlog/spdlog.h"

int main(int argc, char* argv[]) {
  cxxopts::Options options("tcp_echo_server", "TCP echo server");
  auto option_adder = options.add_options()("h, help", "Print help")(
      "p, port", "Network port", cxxopts::value<std::uint16_t>())(
      "m, max_connections", "Maximum number of simultaneous connections",
      cxxopts::value<std::size_t>())("b, buffer_size",
                                     "Maximum buffer size (bytes)",
                                     cxxopts::value<std::size_t>())(
      "t, timeout", "Client response timeout", cxxopts::value<std::size_t>());

  try {
    auto parse_result = options.parse(argc, argv);
    if (parse_result.count("help")) {
      std::cout << options.help() << std::endl;
      return 0;
    }

    // if (parse_result.count()) {
    // }
    try {
      Server server(8814, 2, 1024, 5000);
      server.Start();
    } catch (std::exception& e) {
      spdlog::error("Server error: {}", e.what());
    }
  } catch (cxxopts::exceptions::exception& e) {
    spdlog::error(e.what());
    return 1;
  }

  return 0;
}