#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <experimental/iterator>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// TODO
		// Constructors

		~euclidean_vector() = default;

		euclidean_vector() {
			this->dimension_ = 1;
			this->magnitude_ = std::make_unique<double[]>(1);
		};

		euclidean_vector(int dimensions) {
			this->dimension_ = dimensions;
			this->magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(dimensions));
		}

		euclidean_vector(int dimensions, double initialise_value) {
			this->dimension_ = dimensions;
			this->magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(dimensions));
			std::fill_n(this->magnitude_.get(), dimensions, initialise_value);
		}

		euclidean_vector(std::vector<double>::const_iterator begin,
	                                   std::vector<double>::const_iterator end) {
			this->dimension_ = static_cast<int>(end - begin);
			this->magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(this->dimension_));
			std::copy_n(begin, this->dimension_, this->magnitude_.get());
		}

		euclidean_vector(std::initializer_list<double> list) {
			this->dimension_ = static_cast<int>(list.size());
			this->magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(this->dimension_));
			std::copy_n(list.begin(), this->dimension_, this->magnitude_.get());
		}

		// Copy constructor
		euclidean_vector(euclidean_vector const& v) {
			this->dimension_ = v.dimension_;
			this->magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(v.dimension_));
			std::copy_n(v.magnitude_.get(), v.dimension_, this->magnitude_.get());
		}

		// Move constructor
		euclidean_vector(euclidean_vector&& v) {
			this->dimension_ = std::exchange(v.dimension_, 0);
			this->magnitude_ = std::exchange(v.magnitude_, nullptr);
		}
		// Operatations
		auto operator=(euclidean_vector const&) -> euclidean_vector&;
		auto operator=(euclidean_vector&&) noexcept -> euclidean_vector&;

		auto operator[](int i) const noexcept -> double;
		auto operator[](int i) noexcept -> double&;

		auto operator+() const noexcept -> euclidean_vector;
		auto operator-() const -> euclidean_vector;

		auto operator+=(euclidean_vector const&) -> euclidean_vector&;
		auto operator-=(euclidean_vector const&) -> euclidean_vector&;
		auto operator*=(double) -> euclidean_vector&;
		auto operator/=(double) -> euclidean_vector&;

		explicit operator std::vector<double>() const;
		explicit operator std::list<double>() const;

		// Member functions
		auto at(int) const -> double;
		auto at(int) -> double&;
		auto dimensions() const noexcept -> int;

		// Friends
		friend auto operator==(euclidean_vector const& a , euclidean_vector const& b) -> bool{
			return a.dimension_ == b.dimension_
			       && std::equal(a.magnitude_.get(),
			                     a.magnitude_.get() + b.dimension_,
			                     b.magnitude_.get());
		};
		friend auto operator!=(euclidean_vector const& a, euclidean_vector const& b) -> bool{
			return !(a == b);
		};
		friend auto operator+(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;
		friend auto operator-(euclidean_vector const& a, euclidean_vector const& b) -> euclidean_vector{
			auto c = a;
			return c -= b;
		};
		friend auto operator*(euclidean_vector const& v, double b) -> euclidean_vector{
			euclidean_vector scalar = v;
			scalar *= b;
			return scalar;
		};
		friend auto operator/(euclidean_vector const& v, double b) -> euclidean_vector{
			if (b == 0) {
				throw euclidean_vector_error("Invalid vector division by 0");
			}
			euclidean_vector scalar = v;
			scalar /= b;
			return scalar;
		};
		friend auto operator<<(std::ostream& o, euclidean_vector const& v) -> std::ostream&{
			o << '[';
			std::copy(v.magnitude_.get(),
			          v.magnitude_.get() + v.dimension_,
			          std::experimental::make_ostream_joiner(o, " "));
			o << ']';
			return o;
		};
		/*
		friend auto inner_dot(euclidean_vector const& x, euclidean_vector const& y) -> double {

		}*/

	private:
		// ass2 spec requires we use std::unique_ptr<double[]>
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
		// TODO more if needed
		int dimension_;
		//mutable double cached_norm_ = 0.0;
		std::unique_ptr<double> cached_norm_ = std::make_unique<double>(0);
		auto get_cached_norm() const noexcept -> double {
			return *this->cached_norm_;
		}

		friend auto euclidean_norm(euclidean_vector const& v) -> double;
	};
	// Utility Functions
	auto euclidean_norm(euclidean_vector const& v) -> double;
	auto unit(euclidean_vector const& v) -> euclidean_vector;
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
