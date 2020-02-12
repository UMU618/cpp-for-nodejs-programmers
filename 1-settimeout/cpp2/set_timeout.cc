#include <chrono>
#include <iostream>
#include <vector>

#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>

class Timer {
 public:
  template <typename T>
  void setTimeout(T function, int delay);
  void stop();
  void wait();

 private:
  boost::asio::io_context io;
  std::vector<boost::asio::steady_timer> timers;
  size_t count;
};

template <typename T>
void Timer::setTimeout(T function, int delay) {
  auto& timer = timers.emplace_back(boost::asio::steady_timer(io));
  ++count;
  timer.expires_from_now(std::chrono::milliseconds(delay));
  timer.async_wait([=](const boost::system::error_code& error) {
    // boost::system::error::operation_canceled
    // boost::asio::error::operation_aborted
    if (!error) {
      function();
    }
  });
}

void Timer::stop() {
  for (auto& timer : timers) {
    timer.cancel();
  }
}

void Timer::wait() {
  io.run();
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
