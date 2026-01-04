#pragma once
#include "../common/package.hpp"
#include <condition_variable>
#include <deque>
#include <mutex>

class PackageQueue {
public:
  void push(Package &&pkg);
  Package pop();
  bool empty() const;
  size_t size() const;

private:
  mutable std::mutex m;
  std::condition_variable cv;
  std::deque<Package> q;
};
