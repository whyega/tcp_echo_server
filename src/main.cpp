#include <cxxopts.hpp>
#include <exception>
#include <iostream>

#include "server.hpp"
#include "spdlog/spdlog.h"

int main(int argc, char* argv[]) {
  cxxopts::Options options("tcp_echo_server", "TCP echo server");
  auto option_adder = options.add_options()("h, help", "Print help");

  try {
    auto parse_result = options.parse(argc, argv);
    if (parse_result.count("help")) {
      std::cout << options.help() << std::endl;
      return 0;
    }

    try {
      Server server(8814);
      server.Start();
    } catch (std::exception& e) {
      spdlog::error("Error intitialize server: {}", e.what());
    }
  } catch (cxxopts::exceptions::exception& e) {
    spdlog::error(e.what());
    return 1;
  }

  return 0;
}