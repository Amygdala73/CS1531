
#include <compare>
#include <iostream>

class point {
public:
point(int x, int y)
	: x_{x}
	, y_{y} {}

	// hidden friend - preferred
	// friend auto operator<=>(point p1, point p2) = default;
	// Partial ordering
	// ==, != excluded
	friend auto operator<=>(point const p1, point const p2) -> std::partial_ordering {
 		auto const x_result = p1.x_ <=> p2.x_;
 		auto const y_result = p1.y_ <=> p2.y_;
 		return x_result == y_result ? x_result
 		: std::partial_ordering::unordered;
	}

 private:
	int x_;
	int y_;
 };

 auto main() -> int {
 	auto const p2 = point{1, 2};
 	auto const p1 = point{1, 2};
 	//std::cout << "p1 == p2 " << (p1 == p2) << '\n';
 	//std::cout << "p1 != p2 " << (p1 != p2) << '\n';
 	std::cout << "p1 < p2 " << (p1 < p2) << '\n';
 	std::cout << "p1 > p2 " << (p1 > p2) << '\n';
 	std::cout << "p1 <= p2 " << (p1 <= p2) << '\n';
 	std::cout << "p1 >= p2 " << (p1 >= p2) << '\n';

 	auto const p3 = point{3, 5};

	//std::cout << "p1 == p3 " << (p1 == p3) << "\n";
	//std::cout << "p1 != p3 " << (p1 != p3) << "\n";
	std::cout << "p1 < p3 " << (p1 < p3) << "\n";
	std::cout << "p1 > p3 " << (p1 > p3) << "\n";
	std::cout << "p1 <= p3 " << (p1 <= p3) << "\n";
	std::cout << "p1 >= p3 " << (p1 >= p3) << "\n";
 }