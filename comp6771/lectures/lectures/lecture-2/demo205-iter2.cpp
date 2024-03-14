// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <vector>

int main() {
	std::vector<int> ages;
	ages.push_back(18);
	ages.push_back(19);
	ages.push_back(20);

	// type of iter would be std::vector<int>::iterator
	for (auto iter = ages.begin(); iter != ages.end(); ++iter) {
		//std::cout << *iter << "\n"; // prints 18,19,20
		(*iter)++; // OK
		//std::cout <<"(*iter)++:"<< *iter << "\n"; // prints 19,20,21

	}

	// type of iter would be std::vector<int>::const_iterator
	for (auto iter = ages.cbegin(); iter != ages.cend(); ++iter) {
		//std::cout  <<"*iter:"<< *iter << "\n"; // prints 19,20,21
		//(*iter)++; // NOT OK

	}

	// type of iter would be std::vector<int>::reverse_iterator
	for (auto iter = ages.rbegin(); iter != ages.rend(); ++iter) {
		std::cout << *iter << "\n"; // prints 21, 20, 19
	}

	// Can also use crbegin and crend
	for (auto iter = ages.crbegin(); iter != ages.crend(); ++iter) {
		std::cout <<"*iter ( in crbegin):"<< *iter << "\n"; // prints 21,20,19
	}
}