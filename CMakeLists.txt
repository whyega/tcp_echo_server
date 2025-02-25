cmake_minimum_required(VERSION 3.15)
project(tcp_echo_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TCP_ECHO_SERVER_BUILD_TEST ON)

add_subdirectory(vendor)

list(APPEND TCP_ECHO_SERVER_SRC
  src/main.cpp
  src/server.cpp
  src/util/socket.cpp
  src/util/string.cpp
)
add_executable(tcp_echo_server ${TCP_ECHO_SERVER_SRC})
target_link_libraries(tcp_echo_server PRIVATE
  spdlog::spdlog
  cxxopts::cxxopts
)

if (TCP_ECHO_SERVER_BUILD_TEST)
  add_subdirectory(tests)
endif()