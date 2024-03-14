#include <vector>
//#include "sort_descending.hpp"
#include <algorithm>    // std::sort
//#include <bits/stdc++.h>
#include <iostream>
using namespace std;

auto sort_descending(std::vector<int>& numbers) -> void{
    std::sort(numbers, std::greater{});
}
