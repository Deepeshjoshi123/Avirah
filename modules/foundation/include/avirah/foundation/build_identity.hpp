#pragma once

#include <string_view>

namespace avirah::foundation {

inline constexpr std::string_view product_name = "Avirah";
inline constexpr std::string_view version = "0.1.0";

struct BuildIdentity {
  std::string_view product{product_name};
  std::string_view version_text{version};
  std::string_view compiler;
  std::string_view system;
};

constexpr BuildIdentity build_identity(std::string_view compiler_name,
                                       std::string_view system_name) {
  return {product_name, version, compiler_name, system_name};
}

}  // namespace avirah::foundation
