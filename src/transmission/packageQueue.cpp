#include "../../include/transmission/packageQueue.hpp"

void PackageQueue::push(Package &&pkg) {
  {
    std::lock_guard<std::mutex> lock(m);
    q.push_back(std::move(pkg));
  }
  cv.notify_one();
}

Package PackageQueue::pop() {
  std::unique_lock<std::mutex> lock(m);
  cv.wait(lock, [this] { return !q.empty(); });
  Package pkg = std::move(q.front());
  q.pop_front();
  return pkg;
}

bool PackageQueue::empty() const {
  std::lock_guard<std::mutex> lock(m);
  return q.empty();
}

size_t PackageQueue::size() const {
  std::lock_guard<std::mutex> lock(m);
  return q.size();
}
