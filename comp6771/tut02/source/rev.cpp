#include <iostream>
#include <vector>

int main() {
	std::vector<int> temperatures{32, 34, 33, 28, 35, 28, 34};
	/**auto i = 0u; i < temperatures.size(); ++i
	-> int i = temperatures.size() - 1; i >= 0; --i
	**/
	for (auto i = temperatures.size() ; i > 0; --i) {
		std::cout << temperatures.at(i-1) << " ";
	}
	std::cout << "\n";
    // cant do it
	for (const auto& temp : temperatures) {
		std::cout << temp << " ";
	}
	std::cout << "\n";
    // cbegin() -> crbegin(), cend() -> crend()
	for (auto iter = temperatures.crbegin(); iter != temperatures.crend(); ++iter) {
		std::cout << *iter << " ";
	}
	std::cout << "\n";
}