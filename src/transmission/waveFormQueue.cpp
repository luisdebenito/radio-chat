#include "waveFormQueue.hpp"

void WaveFormQueue::push(std::vector<float> &&wf) {
  {
    std::lock_guard<std::mutex> lock(m);
    q.emplace_back(std::move(wf));
  }
  cv.notify_one();
}

std::vector<float> WaveFormQueue::pop() {
  std::unique_lock<std::mutex> lock(m);
  cv.wait(lock, [&] { return !q.empty(); });

  std::vector<float> wf = std::move(q.front());
  q.pop_front();
  return wf;
}

bool WaveFormQueue::empty() const {
  std::lock_guard<std::mutex> lock(m);
  return q.empty();
}

size_t WaveFormQueue::size() const {
  std::lock_guard<std::mutex> lock(m);
  return q.size();
}
