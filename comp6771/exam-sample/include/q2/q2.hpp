#ifndef Q1_HPP
#define Q1_HPP

namespace q2 {
    template <typename T>
    class smart_list {
        public:
        smart_list();
        ~smart_list();
        explicit smart_list(std::size_t count);
        smart_list(T const& one, T const& two, std::size_t count);
        smart_list(std::initializer_list<T> il);
        //Accessors
        std::size_t size();
        //Modifiers
        void push_back(const T& value);
        void pop_back();
        void emplace_back(Args... args);
        //Operator overloads
        operator[](std::size_t index);
        smart_list operator+(smart_list const& lhs, smart_list const& rhs);
        smart_list operator-(smart_list const& lhs, smart_list const& rhs);
        smart_list<smart_list<T>> operator*(smart_list const& lhs, smart_list const& rhs);
        smart_list<smart_list<T>> operator*(smart_list const& lhs, smart_list const& rhs);
        std::ostream& operator<<(std::ostream& os, smart_list const& sl);


        private:

    };

    template <typename T>
    class very_smart_list {};
}

#endif // Q2_HPP
