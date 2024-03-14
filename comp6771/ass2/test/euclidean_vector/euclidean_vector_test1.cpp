#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <sstream>
#include <vector>



TEST_CASE("Euclidean vector is trivially default constructible") {
	auto const a = comp6771::euclidean_vector{};

	CHECK(true);
	CHECK(a.dimensions() == 1);
	CHECK(a.at(0) == 0);
}

TEST_CASE("Constructor (int , double)") {
	auto const a = comp6771::euclidean_vector(1, 1.0);
	auto const b = comp6771::euclidean_vector(3, 1.0);

	CHECK(a.at(0) == 1.0);
	CHECK(a.dimensions() == 1);
	CHECK(b.at(0) == 1.0);
	CHECK(b.at(2) == 1.0);
	CHECK(b.dimensions() == 3);

	CHECK_THROWS_WITH(a.at(1), "Index 1 is not valid for this euclidean_vector object");
	CHECK_THROWS_WITH(b.at(4), "Index 4 is not valid for this euclidean_vector object");
}

TEST_CASE("Initializer_List list constructor") {
	SECTION("regular case") {
		auto const a = comp6771::euclidean_vector{1.1, 2.22, 3.334};
		REQUIRE(a.dimensions() == 3);
		CHECK(a.at(0) == 1.1);
		CHECK(a.at(1) == 2.22);
		CHECK(a.at(2) == 3.334);
	}
}

TEST_CASE("Unary operators") {
	SECTION("+") {
		auto a = comp6771::euclidean_vector{1.1, 2.22, 3.334};
		auto b = +a;
		REQUIRE(a.dimensions() == b.dimensions());
		for (auto i = 0; i < b.dimensions(); i++) {
			CHECK(a.at(i) == b.at(i));
		}
	}

	SECTION("-") {
		auto a = comp6771::euclidean_vector{1, 2, 3.5};
		auto b = comp6771::euclidean_vector{2, 1, 1};
		auto c = a - b;
		REQUIRE(c.dimensions() == b.dimensions());
		CHECK(c == comp6771::euclidean_vector{-1, 1, 2.5});
		c = -b;
		REQUIRE((-b).dimensions() == c.dimensions() );
		CHECK(c == comp6771::euclidean_vector{-2, -1, -1});

		for (auto i = 0; i < b.dimensions(); i++) {
			CHECK(b.at(i) == -c.at(i));
		}

	}

	SECTION("Dimension mismatch") {
		auto a = comp6771::euclidean_vector{0, 0, 0};
		auto b = comp6771::euclidean_vector{0, 0};
		auto const message = "Dimensions of LHS(" + std::to_string(a.dimensions()) + ") and RHS("
			                    + std::to_string(b.dimensions()) + ") do not match";
		REQUIRE_THROWS(a - b);
		CHECK_THROWS_MATCHES(a - b,
		                     comp6771::euclidean_vector_error,
		                     Catch::Matchers::Message(message));
	}
	SECTION("*=") {
		auto a = comp6771::euclidean_vector{1.4, 1, -1};
		a *= 2.0;
		CHECK(a == comp6771::euclidean_vector{2.8,2,-2});
	}
	SECTION("*/=") {
		auto a = comp6771::euclidean_vector{1.4, 1, -1};
		a /= 2.0;
		CHECK(a == comp6771::euclidean_vector{0.7,0.5,-0.5});
	}
}

TEST_CASE("Copy and move") {
	SECTION("copy") {
		auto a = comp6771::euclidean_vector(6);
		auto b = a;
		CHECK(b.dimensions() == 6);
		CHECK(b.at(0) == 0);
		CHECK(b.at(1) == 0);

		auto c = comp6771::euclidean_vector{1.1, 2.22, 3.334};
		b = c;
		CHECK(b.dimensions() == 3);
		CHECK(b.at(0) == 1.1);
		CHECK(b.at(1) == 2.22);
	}

	SECTION("move") {
		auto a = comp6771::euclidean_vector(3, 3);
		auto b = std::move(a);
		CHECK(b.dimensions() == 3);
		CHECK(b.at(0) == 3);
		CHECK(b.at(1) == 3);
	}
}

TEST_CASE("operator!= and ==") {
		auto a = comp6771::euclidean_vector{0,0,0};
		CHECK(a == a);
		CHECK(not(a != a));

		auto b = comp6771::euclidean_vector{1.1, 2.22, 3.334};
		auto c= comp6771::euclidean_vector{2, 1, 1};

		CHECK(not(b == c));
		CHECK((b != c));
}

TEST_CASE("Utility functions"){
	SECTION("unit") {
		CHECK_THROWS_MATCHES(comp6771::unit(comp6771::euclidean_vector(0)),
		                     comp6771::euclidean_vector_error,
		                     Catch::Matchers::Message("euclidean_vector with no dimensions does not have a unit vector"));
		CHECK_THROWS_MATCHES(comp6771::unit(comp6771::euclidean_vector()),
		                     comp6771::euclidean_vector_error,
		                     Catch::Matchers::Message("euclidean_vector with zero euclidean normal does not have a unit vector"));

		auto a = comp6771::euclidean_vector{3, 4};
		auto b = comp6771::unit(a);

		CHECK(b.at(0) == double(0.6));
		CHECK(b.at(1) == double(0.8));
	}


}