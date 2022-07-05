#include <chrono>
#include <iostream>
#include <string>

template <typename UNIT = std::chrono::microseconds>
class LifeTimer {
 public:
  explicit LifeTimer(const std::string& tag) : tag_(tag) {
    start_ = std::chrono::high_resolution_clock::now();
  }

  ~LifeTimer() {
    end_ = std::chrono::high_resolution_clock::now();
    std::cout << tag_ << "  spend: "
              << std::chrono::duration_cast<UNIT>(end_ - start_).count()
              << std::endl;
  }

 private:
  const std::string tag_;
  std::chrono::steady_clock::time_point start_;
  std::chrono::steady_clock::time_point end_;
};
