#include <iostream>
#include "is_a_pointer.h"
#include "is_real_number.h"

template <typename T>
auto printPointer(T t) {
  if constexpr (traits::is_a_pointer<T>::value) {
  	std::cout <<'*' << *t <<"\n";
  } else {
  	std::cout << t << "\n";
  }
}


template <typename T>
auto foo(T t){
	if (is_real_number<T>::value) {
  		std::cout << t << " Is real number" << "\n";
	}
	else{
		std::cout << t << " Is not real number" << "\n";
	}
}



auto main() -> int {
	int i = 5;
	int& k = i;


	decltype(i) x;
	//decltype(k) y; // not work
	decltype(k) y = i;
	decltype(std::move(i)) z;
	//decltype(4.2); // not work
	decltype(4.2) h;


	auto& ref = i;
	auto *pointer = &i;
	auto a = 'a';
	printPointer(ref);
	printPointer(pointer);

	foo(i);
	foo(ref);
	foo(pointer);
	foo(a);
}