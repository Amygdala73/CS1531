#include "gdwg/graph.hpp"
#include <iostream>
#include <iterator>
#include <catch2/catch.hpp>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>

TEST_CASE("basic test") {
	// This will not compile straight away
	auto g = gdwg::graph<int, std::string>{};
	auto n = 5;
	g.insert_node(n);
	CHECK(g.is_node(n));
}

TEST_CASE("default constructor") {
	auto g = gdwg::graph<int, std::string>{};
	CHECK(g.empty());

	CHECK(g.insert_node(21));
	CHECK(g.insert_node(12));
	CHECK(g.insert_edge(21, 12, "test"));
	CHECK(g.empty() == false);
	CHECK(g.is_connected(21, 12));
}

TEST_CASE("graph(InputIt first, InputIt last);") {
	auto g = gdwg::graph<int, int>{1, 2, 3, 4};
	CHECK(g.is_node(2));
	CHECK(g.is_node(3));
	g.insert_edge(1, 2, 3);
	CHECK(g.is_connected(1, 2));

}

TEST_CASE("weight") {
 	using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2};
    CHECK(g.nodes() == std::vector<int>{1, 2});
    g.insert_edge(1, 2, 3);
    g.insert_edge(1, 2, 4);
 	CHECK(g.weights(1,2) == std::vector<int>{3,4});

    g = graph();
    CHECK(g.empty());
    CHECK_THROWS_WITH(g.weights(1,2), "Cannot call gdwg::graph<N, E>::weights if src or dst node don't exist in the graph");
}

TEST_CASE("empty graph") {
    using graph = gdwg::graph<int, int>;
    const auto g = graph();
    CHECK(g.begin() == g.end());

	const auto h = graph{1,2,3};
    CHECK(h.nodes() == std::vector<int>{1,2,3});
    CHECK(h.begin() == h.end());

}
