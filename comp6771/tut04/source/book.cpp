#include "./book.h"
#include <algorithm>
#include <iostream>
#include <vector>


/**
 * @brief Write the function definition for a constructor
that takes values for name, author, isbn and price
and uses a member initializer list
to set the value of each data member.

Write the overloaded == operator to compare
if two book objects are identical

Write the overloaded != operator that calls
the already overloaded == operator to return true when two book objects
are not identical.

Write the overloaded << operator to print out
the name, author, isbn and price of a book using std::cout

Write the overloaded type conversion operator to enable the conversion
of the Book class to a std::string in the form of "author, name"

Create a main function that creates a std::vector,
add a few Book objects into the vector
with different isbn numbers and prices

Write the overloaded < operator to allow you to sort books
by their isbn number. Test this in your main method using std::sort
Call std::sort again with a lambda function as the predicate
that sorts the books by price.
 *
 */

 void print(const std::string& title, const std::vector<book>& books) {
  std::cout << title << '\n';
  for (const auto& b: books) {
    std::cout << "\t";
    std::cout << b << '\n';
  }
  std::cout << '\n';
}

int main() {
  std::vector<book> books1{
      book{"book1", "Author1", 2222, 12.2},
      book{"book2", "Author2", 1111, 11.50},
      book{"book3", "Author3", 3333, 10.50}};

  std::vector<book> books2{
      book{"book1", "Author1", 2222, 12.2},
      book{"book2", "Author2", 1111, 11.50},
      book{"book3", "Author3", 3333, 10.50}};

  print("books:", books1);

  // Call the std::vector<book> operator==() overload which in
  // turn calls book operator==() overload.
  std::cout << "Vector of books are equal: "
            << "books1 " << (books1 == books2 ? "==" : "!=")
            << " books2\n\n";

  std::sort(books1.begin(), books1.end());
  print("Default (ISBN) sorted books:", books1);

  std::cout << "Vector of books are no longer equal: "
            << "books1 " << (books1 == books2 ? "==" : "!=")
            << " books2\n\n";

  std::sort(books1.begin(), books1.end(),
            [](const book& a, const book& b) {
              return a.get_price() > b.get_price();
            }
  );

  print("Price sorted books:", books1);
}
