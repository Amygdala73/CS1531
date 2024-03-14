#include <catch2/catch.hpp>
#include <string>
#include <iostream>
using namespace std;

auto is_permutation(std::string const& x, std::string const& y) -> bool;

TEST_CASE("is_permutation determines if x is a permutation of y") {

    std::cout <<is_permutation("12345","35412")<<"sfdsv"<<endl;
    std::cout <<is_permutation("12345","35411")<<"wwebv"<<endl;

    CHECK((is_permutation("12345","35fd11")) != 1);
    CHECK((is_permutation("12345","35fd11")) == 0);
    CHECK((is_permutation("12345","54321")) == 1);

}
