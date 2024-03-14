#include <iterator>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <iostream>
#include <algorithm>
#include <deque>

template <typename T>
class streaming_median {
 public:
  auto add(T value) -> void { data_.insert(std::move(value)); }

  auto median() const -> T {
    if (data_.empty()) {
      throw std::runtime_error{"Cannot get median of empty stream."};
    }

    auto middle = std::next(data_.begin(), data_.size() / 2);

    if (data_.size() % 2 == 0) {
      if constexpr(std::is_arithmetic_v<T>){
        auto low = *std::prev(middle);
        return (*middle+low)/2;
      }
      else{
        throw std::runtime_error{"Cannot get median of an evenly sized stream."};
      }
    }

    return *middle;
  }

 private:
  std::multiset<T> data_;
};