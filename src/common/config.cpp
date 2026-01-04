#include "../../include/common/config.hpp"
#include <fstream>
#include <sstream>

Config::Config(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open())
    return;

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string key, value;
    if (std::getline(iss, key, '=') && std::getline(iss, value)) {
      data[key] = value;
    }
  }
}

std::string Config::getString(const std::string &key,
                              const std::string &defaultValue) const {
  auto it = data.find(key);
  return it != data.end() ? it->second : defaultValue;
}

int Config::getInt(const std::string &key, int defaultValue) const {
  auto it = data.find(key);
  if (it != data.end()) {
    try {
      return std::stoi(it->second);
    } catch (...) {
      return defaultValue;
    }
  }
  return defaultValue;
}
