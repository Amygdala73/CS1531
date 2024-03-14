// Copyright (c) Hayden Smith
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <iostream>
#include <vector>

char to_upper(char value) {
	return static_cast<char>(std::toupper(static_cast<unsigned char>(value)));
}

char to_lower(char value) {
	return static_cast<char>(std::tolower(static_cast<unsigned char>(value)));
}

int main() {
	std::string s = "hello world";
	// std::for_each modifies each element
	std::for_each(s.begin(), s.end(), toupper);
	std::cout << s << "\n";

	std::string upper;
	// std::transform adds to third iterator.
	std::transform(s.begin(), s.end(), std::back_inserter(upper), to_upper);
	std::cout << upper << "\n";

	std::transform(s.begin(), s.end(), upper.begin(), to_lower);
	std::cout << s << "\n";

	std::for_each(upper.begin(), upper.end(), toupper);
	std::cout << s << "\n";
}
