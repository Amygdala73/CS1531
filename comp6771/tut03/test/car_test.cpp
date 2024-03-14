#include <string>
#include <vector>

#include "catch2/catch.hpp"

#include "../source/car.h"

TEST_CASE("car Checks") {
	car one;
	car two{"Toyota", 5};
	car three{two};
    CHECK(car::get_num_cars() == 3);
    car four{two};
    three.set_num_seats(6);
    CHECK(three.get_num_seats() == 6);
    CHECK(four.get_num_seats() == 5);
}
