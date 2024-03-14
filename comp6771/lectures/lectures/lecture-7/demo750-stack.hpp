#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>
#include <type_traits>

template <typename T>
class stack {
	template <typename ValueType = T>
	class iter {
		using vec_iter = std::conditional_t<std::is_const_v<ValueType>,
			typename std::vector<ValueType>::const_iterator,
			typename std::vector<ValueType>::iterator>;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = ValueType;
		using reference = ValueType&;
		using pointer = ValueType*;
		using difference_type = std::ptrdiff_t;

		iter(vec_iter v_iter = {}) : internal_iter_{v_iter} {}

		auto operator*() const -> reference {
			return *internal_iter_;
		}

		auto operator->() const -> pointer {
			return &(this->operator*());
		}

		auto operator==(const iter &) const -> bool = default;

		auto operator++() -> iter& {
			++internal_iter_;
			return *this;
		}

		auto operator++(int) -> iter {
			auto ret = *this;
			++*this;
			return ret;
		}

		auto operator--() -> iter& {
			--internal_iter_;
			return *this;
		}

		auto operator--(int) -> iter {
			auto ret = *this;
			--*this;
			return ret;
		}

	private:
		vec_iter internal_iter_;
	};

public:
	using iterator = iter<T>;
	using const_iterator = iter<const T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	stack() noexcept = default;

	auto push(T elem) -> void {
		stack_.push_back(elem);
	}

	auto pop() -> T {
		auto ret = stack_.back();
		stack_.pop_back();
		return ret;
	}

	auto begin() noexcept -> iterator {
		return iterator{stack_.begin()};
	}
	auto begin() const noexcept -> const_iterator {
		return const_iterator{stack_.begin()};
	}
	auto end() noexcept -> iterator;
	auto end() const noexcept -> const_iterator;
	auto cbegin() const noexcept -> const_iterator;
	auto cend() const noexcept -> const_iterator;

	auto rbegin() noexcept -> reverse_iterator;
	auto rbegin() const noexcept -> const_reverse_iterator;
	auto rend() noexcept -> reverse_iterator;
	auto rend() const noexcept -> const_reverse_iterator;
	auto crbegin() const noexcept -> const_reverse_iterator;
	auto crend() const noexcept -> const_reverse_iterator;

private:
	std::vector<T> stack_;
};