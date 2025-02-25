#include <cstdint>
#include <cxxopts.hpp>
#include <iostream>

#include "server.hpp"
#include "spdlog/spdlog.h"

int main(int argc, char* argv[]) {
  cxxopts::Options options("tcp_echo_server", "TCP echo server");
  options.add_options()("h, help", "Print help");
  options.add_options()("p, port", "Network port",
                        cxxopts::value<std::uint16_t>());
  options.add_options()("m, max_connections",
                        "Maximum number of simultaneous connections",
                        cxxopts::value<std::size_t>());
  options.add_options()("b, buffer_size", "Maximum buffer size (bytes)",
                        cxxopts::value<std::size_t>());
  options.add_options()("t, timeout", "Client response timeout",
                        cxxopts::value<std::size_t>());

  try {
    auto parse_result = options.parse(argc, argv);
    if (parse_result.count("help")) {
      std::cout << options.help() << std::endl;
      return 0;
    }

    if (!parse_result.count("port")) {
      throw cxxopts::exceptions::missing_argument("port");
    } else if ((!parse_result.count("max_connections"))) {
      throw cxxopts::exceptions::missing_argument("max_connections");
    } else if ((!parse_result.count("buffer_size"))) {
      throw cxxopts::exceptions::missing_argument("buffer_size");
    } else if ((!parse_result.count("timeout"))) {
      throw cxxopts::exceptions::missing_argument("timeout");
    }

    try {
      Server server(parse_result["port"].as<std::uint16_t>(),
                    parse_result["max_connections"].as<std::size_t>(),
                    parse_result["buffer_size"].as<std::size_t>(),
                    parse_result["timeout"].as<std::size_t>());
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