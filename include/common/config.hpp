#pragma once
#include <map>
#include <string>

class Config {
public:
  explicit Config(const std::string &filename);

  std::string getString(const std::string &key,
                        const std::string &defaultValue = "") const;
  int getInt(const std::string &key, int defaultValue = 0) const;

private:
  std::map<std::string, std::string> data;
};