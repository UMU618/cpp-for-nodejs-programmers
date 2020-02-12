// UMU: 这是不好的实现！
#include <chrono>
#include <future>
#include <iostream>
#include <vector>

class Timer {
 public:
  template <typename T>
  void setTimeout(T function, int delay);
  void stop();
  void wait();

 private:
  bool clear = false;
  std::vector<std::thread> pool;
};

template <typename T>
void Timer::setTimeout(T function, int delay) {
  this->clear = false;
  pool.emplace_back(std::thread([=]() {
    if (this->clear) {
      return;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    if (this->clear) {
      return;
    }
    function();
  }));
}

void Timer::stop() {
  this->clear = true;
}

void Timer::wait() {
  for (std::thread& thread : pool) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

int main() {
  Timer timer;
  //timer.setTimeout([&]() { std::cout << "step1\n"; timer.stop(); }, 1000);
  timer.setTimeout([]() { std::cout << "step1\n"; }, 1000);
  timer.setTimeout([]() { std::cout << "step2\n"; }, 2000);
  timer.setTimeout([]() { std::cout << "step3\n"; }, 3000);
  timer.wait();
  return 0;
}
