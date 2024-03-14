#define CATCH_CONFIG_MAIN

#include <vector>
#include <memory>

#include </tmp_amd/cage/export/cage/3/z5338676/comp6771/tut09/test/catch2/catch.hpp>
#include </tmp_amd/cage/export/cage/3/z5338676/comp6771/tut09/source/is_a_pointer.h>

TEST_CASE("our is_a_pointer type trait returns true for pointer types") {
    CHECK(traits::is_a_pointer<int*>::value);
    CHECK(traits::is_a_pointer<int**>::value);
    CHECK(traits::is_a_pointer<const int*>::value);
    CHECK(traits::is_a_pointer<std::vector<int>*>::value);
}

TEST_CASE("our is_a_pointer type trait returns false for non-pointer types") {
    CHECK(not traits::is_a_pointer<int>::value);
    CHECK(not traits::is_a_pointer<int&>::value);
    CHECK(not traits::is_a_pointer<int&&>::value);
    CHECK(not traits::is_a_pointer<int&&>::value);
    CHECK(not traits::is_a_pointer<const int>::value);
    CHECK(not traits::is_a_pointer<const int&>::value);
    CHECK(not traits::is_a_pointer<std::vector<int*>>::value);
    CHECK(not traits::is_a_pointer<std::unique_ptr<int>>::value);
}
