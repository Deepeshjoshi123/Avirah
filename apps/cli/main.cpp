#include <iostream>

#include "avirah/foundation/build_identity.hpp"

int main() {
  constexpr auto identity = avirah::foundation::build_identity("C++20", "portable");
  std::cout << identity.product << " cli " << identity.version_text
            << " (" << identity.compiler << ", " << identity.system << ")\n";
  return 0;
}
