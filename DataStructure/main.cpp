//
//  main.cpp
//  DataStructure
//
//  Created by Watching Wang on 2022/7/5.
//

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

#include "HashList.h"
#include "Timer.h"

template <typename T>
class PrintFunc {
 public:
  void operator()(T data) { std::cout << data << " "; }
};

// 采样字符集
static constexpr char CCH[] =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

// sz: 字符串的长度
// printable：是否可打印。如果用作key，可以使用不可打印的字符哟
std::string makeRandStr(int sz, bool printable) {
  std::string ret;
  ret.resize(sz);
  std::mt19937 rng(std::random_device{}());
  for (int i = 0; i < sz; ++i) {
    if (printable) {
      uint32_t x = rng() % (sizeof(CCH) - 1);
      ret[i] = CCH[x];
    } else {
      ret[i] = rng() % 0xFF;
    }
  }

  return ret;
}

void GenerateRandomVecStr(std::vector<std::string>& vec, size_t size) {
  while (--size) {
    vec.emplace_back(makeRandStr(100, true));
  }
}

int main(int argc, const char* argv[]) {
  std::vector<std::string> random_key;

  HashList<std::string, std::string> list;
  std::vector<std::string> vec;
  GenerateRandomVecStr(random_key, 100);
  {
    LifeTimer timer("PUSH_BACK");
    for (const auto& str : random_key) {
      list.PushBack(std::make_pair(str, str));
      vec.push_back(str);
    }
  }

  // std::for_each(vec.begin(),vec.end(), PrintFunc<std::string>());

  std::default_random_engine generator{std::random_device{}()};

  std::shuffle(vec.begin(), vec.end(), generator);

    std::string value;
  {
    LifeTimer timer("Hash find");
    for (const auto& str : random_key) {
      if (list.Find(str,value) == false) {
        std::cout << "wrong";
      };
    }
  }

  {
    LifeTimer timer("Vec find");
    for (const auto& str : random_key) {
      for (const auto& ve : vec) {
        if (ve.compare(str) == 0) {
          break;
        }
      }
    }
  }
  std::cout << "Hello, World!\n";
  return 0;
}
