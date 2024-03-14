#include <exception>
#include <string>
#include <iostream>

class Logger {
public:
    auto log(std::string const& msg) -> void{
        std::cerr<<msg<<'\n';
    }
};

class DBConn {
public:
    auto try_connect(std::string const& uname, std::string const& pword) -> void{
        (void) uname;
        (void) pword;
        (void) active_;
        throw std::string("hi");

    };

private:
    bool active_ = false;
};

auto make_connection(std::string const& uname, std::string const& pword) -> DBConn {
    auto db = DBConn{};
    try {
        db.try_connect(uname, pword);
        return db;
    } catch (std::string const& e) {
        std::cout << e << std::endl;
        throw e;
    }
    return db;
}

int main() {
    auto l = Logger{};
    (void) l;
    try {
        make_connection("hsmith", "swagger/10");
    } catch (std::string const& e) {
        std::cout << e << std::endl;
        l.log(std::string{"Could not establish connection"});
    }
}
