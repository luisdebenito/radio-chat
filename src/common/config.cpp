#include "config.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

// Define the hidden implementation
class Config::Impl {
public:
  std::unordered_map<std::string, std::string> config_;

  void load(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
      std::cerr << "Cannot open config file: " << filename << "\n";
      return;
    }

    std::string line;
    while (std::getline(file, line)) {
      if (line.empty() || line[0] == '#')
        continue;

      std::istringstream iss(line);
      std::string key, value;
      if (std::getline(iss, key, '=') && std::getline(iss, value)) {
        config_[key] = value;
      }
    }
  }

  std::string getString(const std::string &key,
                        const std::string &defaultValue) const {
    auto it = config_.find(key);
    return it != config_.end() ? it->second : defaultValue;
  }

  int getInt(const std::string &key, int defaultValue) const {
    auto it = config_.find(key);
    if (it != config_.end()) {
      try {
        return std::stoi(it->second);
      } catch (...) {
        std::cerr << "Invalid integer for key: " << key << "\n";
      }
    }
    return defaultValue;
  }
};

// Config constructor/destructor
Config::Config(const std::string &filename) : pImpl(new Impl()) {
  pImpl->load(filename);
}

std::string Config::getString(const std::string &key,
                              const std::string &defaultValue) const {
  return pImpl->getString(key, defaultValue);
}

int Config::getInt(const std::string &key, int defaultValue) const {
  return pImpl->getInt(key, defaultValue);
}
