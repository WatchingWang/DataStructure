#include <list>
#include <unordered_map>

template <typename KEY, typename VALUE>
class HashList {
 public:
  using iterator = typename std::list<VALUE>::iterator;

  bool Exist(const KEY& key) {
    auto it = hash_key_.find(key);
    return (it != hash_key_.end()) ? true : false;
  }

  bool Find(const KEY& key, VALUE& value) {
    auto it = hash_key_.find(key);
    if (it == hash_key_.end()) {
      return false;
    }

    value = *(it->second);
    return true;
  }

  bool PushBack(const std::pair<KEY, VALUE>& pair) {
    if (hash_key_.find(pair.first) != hash_key_.end()) {
      return false;
    }

    list_.push_back(pair.second);
    hash_key_[pair.first] = --list_.end();

    return true;
  }

 private:
  std::unordered_map<KEY, iterator> hash_key_;
  std::list<VALUE> list_;
};
