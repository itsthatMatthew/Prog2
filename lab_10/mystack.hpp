/**
 * \file: mystack.hpp
 *
 */
#include <vector>
#include <stdexcept>

template <class T, class Container = std::vector<T> > class MyStack {
private:
    Container con;
    size_t siz;
public:
    MyStack() : con(), siz(0) {}
    ~MyStack() {}
    T& top() {
        if (empty()) throw std::out_of_range("MyStack.top(): ures");
        return con.at(siz-1);
    }
    void push(const T& t) { con.at(siz++) = t; }
    void pop() {
        if (empty()) throw std::out_of_range("MyStack.pop(): ures");
        siz--;
    }
    bool empty() { return siz == 0; }

}; // class MyStack
