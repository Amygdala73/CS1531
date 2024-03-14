// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
//#include <ranges>

void add_n(std::vector<int>& v, int n) {
	std::for_each(v.begin(), v.end(), [n](int& val) { val = val + n; });
}

int main() {
	std::vector<int> v{1, 2, 3};
	// std::ranges::copy(v, std::ostream_iterator<char>(std::cout, " ")); //c++ 20
	std::ostream_iterator<int> out_it (std::cout,"\n");
  	//std::copy ( v.begin(), v.end(), out_it ); //1,2,3

	add_n(v, 10);
	std::copy ( v.begin(), v.end(), out_it );//11,12,13


}
