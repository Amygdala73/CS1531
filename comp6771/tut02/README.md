# Tutorial - Week 2

### Question 1

1. What is a `TEST_CASE`?

2. What is a `CHECK`? How is it different to an `assert`?

3. What is a `REQUIRE`? How is this different to an `assert`?

4. What are `SECTION` blocks in Catch2?

5. How do they make testing easier?

### Question 2

1. Why is this relationship between algorithms, iterators, containers so important, and how does it help us as programmers?

2. How does this relate to the DRY (don't repeat yourself) principle?

### Question 3

What is the difference between each kind of iterator?
<ul>
  <li>Input iterator</li>
  <li>Output iterator</li>
  <li>Forward iterator</li>
  <li>Bidirectional iterator</li>
  <li>Random-access iterator</li>
</ul>

### Question 4

What is different about a const iterator compared to a non-const iterator? Why would you want to do this?

### Question 5

Which algorithms can we replace these raw bits of code with?

```cpp
// And why doesn't this one work right away?
auto first(std::vector<int> const& v, int const needle) -> std::vector<int>::iterator {
  for (auto i = v.begin(); i != v.end(); ++i) {
    if (*i == needle) {
      return i;
    }
  }
  return v.end();
}

// Note: this one wasn't covered in the lectures. See C++ Reference to get an idea of what it might
// be: https://en.cppreference.com/w/cpp/algorithm.
auto second(std::vector<int>& v, std::vector<int>::iterator new_first) -> std::vector<int>::const_iterator {
  auto copy = std::vector<int>(v.begin(), new_first);
  v.erase(v.begin(), new_first);
  return v.insert(v.end(), copy.begin(), copy.end());
}
```

### Question 6

What kind of iterator is each of the following (and are the iterators const)?<
Which of these will compile, and which of these will not?

```cpp
const std::vector<int> vec;
std::list<int> li;
std::forward_list<double> forward_li;
std::string s;

vec.begin();
vec.cbegin();
(*vec.begin())++;
li.cbegin();
li.rbegin();
forward_li.cbegin();
(*forward_li.cbegin())++;
forward_li.crbegin();
s.begin();
std::back_inserter(vec);
std::back_inserter(li);
std::istream_iterator<int>(std::cin);
std::ostream_iterator<int>(std::cout, " ");
```

### Question 7

For the remainder of questions, you'll be asked to write a function or a program (i.e. also write a
`main` function). You should also write a test case for each of them in the corresponding files in
the `test` directory.

Write a function that sorts a vector of strings in _descending_ order.

You should write your algorithm in `source/sort_descending.cpp` and your test in
`test/sort_descending.cpp`.

### Question 8

We have written some code in `source/marks.cpp` to store information in a container and then access the middle element (to determine the median). What's wrong with this code? How could we modify this code to produce the intended result?

### Question 9

In `source/rev.cpp` you will see a C-style and C++-style method of forward iterating through an array. In each of these cases, how would we modify the code (rev.cpp) to iterate in the other direction? Why is the C++ way preferred?

### Question 10

In `source/overload.cpp` we have two functions - `minInt` and `minDouble`.Use function overloading to improve the style of this code.

### Question 11

> This question is from _Cracking the Coding Interview (6th Edition)_, by Gayle Laakmann McDowell.

Given two strings, write a function to determine if one string is a permutation of the other.

You should write your algorithm in `source/is_permutation.cpp` and your tests in
`test/is_permutation_test.cpp`.

### Question 12

Bonus question: Checkout `source/map.cpp` and ask your tutor to clarify any parts that you don't understand.