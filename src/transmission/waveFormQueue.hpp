#pragma once
#include <condition_variable>
#include <deque>
#include <mutex>
#include <vector>

class WaveFormQueue {
public:
  void push(std::vector<float> &&wf);
  std::vector<float> pop();
  bool empty() const;
  size_t size() const;

private:
  // lock
  mutable std::mutex m;
  std::condition_variable cv;

  // Double ended queue
  std::deque<std::vector<float>> q;
};
