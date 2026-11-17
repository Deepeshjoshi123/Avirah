#include <cassert>
#include <string_view>

#include "avirah/foundation/build_identity.hpp"

int main() {
  constexpr auto identity = avirah::foundation::build_identity("C++20", "test");
  assert(identity.product == std::string_view{"Avirah"});
  assert(identity.version_text == std::string_view{"0.1.0"});
  assert(identity.compiler == std::string_view{"C++20"});
  return 0;
}
