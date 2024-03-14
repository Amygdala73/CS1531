#include <iostream>
#include <vector>
#include <sstream>
#include <string>


template<typename T>
auto min(T a, T b) -> T {
	return a < b ? a : b;
}

template <typename T>
void fun(T a) {
 std::cout << "The main template fun(): "
 << a << std::endl;
}
template<> // may be skipped, but prefer overloads
void fun(int a) {
 std::cout << "Explicit specialisation for int type: "
 << a << std::endl;
}

template<typename T1, typename T2>
void swap(T1 &a, T2 &b) {
 T2 temp = a;
 a = b;
 b = temp;
}

template<typename T>
T add_all(const std::vector<T> &list) {
	T accumulator = {};
	for (auto& elem:list){
 		accumulator += elem;
 	}

 	return accumulator;
}

template<>
T add_all(const std::vector<std::string> &list) {
	std::string accumulator = {};
	for (const std::string& elem : list){
 		for (const char& chr : elem)
 			accumulator += elem;
 		}

	return accumulator
}



auto main() -> int {
	std::cout << min(1, 2) << "\n"; // calls int min(int, int)
	std::cout << min(1.0, 2.0) << "\n"; // calls double min(double, double)
	fun<char>('a');
 	fun<int>(10);
 	//fun<float>(10.14); //implicit conversion loses floating-point precision: 'double' to 'float'
	fun<double>(10.14);

	int a = 10, b = 20;
 	double x = 20.3, y = 55.3;
 	std::cout << "Before Swap" << std::endl;
 	std::cout << "A=" << a << "\t" << "B=" << b << std::endl;
 	std::cout << "X=" << x << "\t" << "B=" << y << std::endl;
 	swap(a, b);
 	swap(x, y);
 	std::cout << "After Swap: "<< std::endl;
 	std::cout << "A=" << a << "\t" << "B=" << b << std::endl;
 	std::cout << "X=" << x << "\t" << "B=" << y << std::endl;

	std::vector<int> ivec = {4,3,2,4};
 	std::vector<double> dvec = {4.0,3.0,2.0,4.0};
 	std::vector<std::string> svec = {"abc", "bcd"};
 	std::cout << add_all(ivec) << std::endl;
 	std::cout << add_all(dvec) << std::endl;
 	std::cout << add_all(svec) << std::endl;

}
#include <iostream>
