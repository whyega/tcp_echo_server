#pragma once

#include <string>

namespace util::string {
std::string replace_all(std::string str, const std::string& from,
                        const std::string& to);
}  // namespace util::string