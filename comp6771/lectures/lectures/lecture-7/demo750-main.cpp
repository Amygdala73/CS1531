#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>

#include "demo750-stack.hpp"

int main() {
    const int i = 0;
    int j = i;
    (void) j;

    const stack<int> istack;

    auto iter = istack.begin();
    (void) iter;
    // *iter = 5; won't compile

}