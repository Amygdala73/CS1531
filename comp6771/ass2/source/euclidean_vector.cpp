// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <comp6771/euclidean_vector.hpp>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <string>
#include <array>
#include <sstream>
#include <cassert>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <functional>


#include <limits>
#include <memory>
#include <numeric>

#include <stdexcept>
#include <system_error>
#include <utility>
#include <sys/types.h>
namespace comp6771 {
	// Implement solution here

	auto euclidean_vector::operator=(euclidean_vector const& v) -> euclidean_vector& {
		auto copy = euclidean_vector(v);
		std::swap(this->dimension_, copy.dimension_);
		std::swap(this->magnitude_, copy.magnitude_);
		return *this;
	}

	auto euclidean_vector::operator=(euclidean_vector&& v) noexcept -> euclidean_vector& {
		std::swap(this->dimension_, v.dimension_);
		std::swap(this->magnitude_, v.magnitude_);
		return *this;
	}

	auto euclidean_vector::operator[](int pos) const noexcept -> double {
		assert(pos >= 0 && pos < this->dimension_);
		return this->magnitude_[static_cast<std::size_t>(pos)];
	}

	auto euclidean_vector::operator[](int pos) noexcept -> double& {
		assert(pos >= 0 && pos < this->dimension_);
		return this->magnitude_[static_cast<std::size_t>(pos)];
	}

	auto euclidean_vector::operator+() const noexcept -> euclidean_vector {
		return *this;
	}

	auto euclidean_vector::operator-() const -> euclidean_vector {
		auto copy = this;
		std::transform(copy->magnitude_.get(),
		               copy->magnitude_.get()+ this->dimension_,
		               copy->magnitude_.get(),
		               std::negate<double>());
		return *this;
	}

	auto euclidean_vector::operator+=(euclidean_vector const& v) -> euclidean_vector& {
		if (this->dimension_ != v.dimension_) {
			auto throw_string = "Dimensions of LHS(" + std::to_string(this->dimension_) + ") and RHS("
			                    + std::to_string(v.dimension_) + ") do not match";
			throw euclidean_vector_error(throw_string);
		}

		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               v.magnitude_.get(),
		               this->magnitude_.get(),
		               std::plus<double>());
		return *this;
	}

	auto euclidean_vector::operator-=(euclidean_vector const& v) -> euclidean_vector& {
		if (this->dimension_ != v.dimension_) {
			auto throw_string = "Dimensions of LHS(" + std::to_string(this->dimension_) + ") and RHS("
			                    + std::to_string(v.dimension_) + ") do not match";
			throw euclidean_vector_error(throw_string);
		}

		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               v.magnitude_.get(),
		               this->magnitude_.get(),
		               std::minus<double>());
		return *this;
	}

	auto euclidean_vector::operator*=(double scalar) -> euclidean_vector& {
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               this->magnitude_.get(),
		               std::bind(std::multiplies<double>(), std::placeholders::_1, scalar));
		return *this;
	}

	auto euclidean_vector::operator/=(double scalar) -> euclidean_vector& {
		if (scalar == 0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               this->magnitude_.get(),
		               std::bind(std::divides<double>(), std::placeholders::_1, scalar));
		return *this;
	}
	euclidean_vector::operator std::vector<double>() const {
		return std::vector<double>{this->magnitude_.get(), this->magnitude_.get() + this->dimension_};
	}

	euclidean_vector::operator std::list<double>() const {
		return std::list<double>{this->magnitude_.get(), this->magnitude_.get() + this->dimension_};
	}

	auto euclidean_vector::at(int pos) const -> double {
		if (pos < 0 || pos >= this->dimension_) {
			auto throw_string =
			   "Index " + std::to_string(pos) + " is not valid for this euclidean_vector object";
			throw euclidean_vector_error(throw_string);
		}

		return this->magnitude_[static_cast<std::size_t>(pos)];
	}

	auto euclidean_vector::at(int pos) -> double& {
		if (pos < 0 || pos >= this->dimension_) {
			auto throw_string =
			   "Index " + std::to_string(pos) + " is not valid for this euclidean_vector object";
			throw euclidean_vector_error(throw_string);
		}

		return this->magnitude_[static_cast<std::size_t>(pos)];
	}

	auto euclidean_vector::dimensions() const noexcept -> int {
		return dimension_;
	}

	auto euclidean_norm(euclidean_vector const& v) -> double {
		if (v.dimensions() == 0) {
			return 0.0;
		}
		if (v.get_cached_norm() != -1) {
			return v.get_cached_norm();
		}


		return get_norm(v);
	}

	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit vector");
		}
		auto norm = euclidean_norm(v);
		if (norm == 0.0) {
			throw euclidean_vector_error("euclidean_vector with zero euclidean normal does not have a unit vector");
		}

		return v/norm;
	}

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimensions() != y.dimensions()) {
			auto throw_string = "Dimensions of LHS(" + std::to_string(x.dimensions()) +
			") and RHS(" + std::to_string(y.dimensions()) + ") do not match";
			throw euclidean_vector_error(throw_string);
		}

		auto product = 0.0;

		for (auto i = 0; i < x.dimensions(); i++) {
			product += x.at(i) * y.at(i);
		}
		return product;
	}

} // namespace comp6771
