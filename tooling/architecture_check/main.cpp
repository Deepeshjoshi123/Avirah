#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "usage: architecture-check <source-root>\n";
    return 2;
  }
  const std::filesystem::path root{argv[1]};
  const std::filesystem::path modules = root / "modules";
  bool valid = true;
  if (!std::filesystem::exists(modules)) {
    std::cerr << "missing modules directory\n";
    return 1;
  }
  for (const auto& entry : std::filesystem::recursive_directory_iterator(modules)) {
    if (!entry.is_regular_file() || entry.path().extension() != ".hpp") continue;
    std::ifstream input(entry.path());
    std::string line;
    while (std::getline(input, line)) {
      if (line.find("Wt/") != std::string::npos || line.find("sqlite3.h") != std::string::npos ||
          line.find("docker") != std::string::npos) {
        std::cerr << "forbidden infrastructure dependency in public module header: "
                  << entry.path().string() << "\n";
        valid = false;
      }
    }
  }
  return valid ? 0 : 1;
}
