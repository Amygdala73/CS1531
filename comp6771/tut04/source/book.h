#include <string>
#include <ostream>

class book {
public:
	book(std::string const& name, std::string const& author,
		int isbn, double price):
      name_{name}, author_{author}, isbn_{isbn}, price_{price} {}

	auto get_isbn() const -> int {
		return isbn_;
	}
	auto get_price() const -> double {
		return price_;
	}
	// Type conversion operators
  	operator std::string() const;
	// Friend comparison operators. Note that we always declare these inline.
  	friend bool operator==(book const& a, book const& b) {
    	return (a.name_ == b.name_) && (a.author_ == b.author_) &&
        (a.isbn_ == b.isbn_) && (a.price_ == b.price_);
  	}

  	friend bool operator!=(book const& lhs, book const& rhs) {
    	return !(lhs == rhs);
  	}

  	friend bool operator<(book const& a, book const& b) {
    	return a.isbn_ < b.isbn_;
  	}

  	friend std::ostream& operator<<(std::ostream& out, book const& b) {
    	return out << "Name: \"" << b.name_ << "\", "
               		<< "(Author: \")" << b.author_ << "(\", )"
               		<< "ISBN: " << b.isbn_ << ", "
               		<< "Price: " << b.price_;
  	}



private:
	std::string name_;
	std::string author_;
	int isbn_;
	double price_;
};