#ifndef PYLIST_H
#define PYLIST_H

#include <iostream>
#include <memory>
#include <vector>

class pylist {
private:
    struct Node {
        enum Type { INT, LIST } type;
        int iv{};
        std::vector<pylist> lv;
        Node() : type(LIST), iv(0), lv() {}
        explicit Node(int v) : type(INT), iv(v), lv() {}
    };

    std::shared_ptr<Node> ptr;

    // Ensure this instance refers to a list node; if currently int, convert to empty list.
    void ensure_list() {
        if (!ptr) ptr = std::make_shared<Node>();
        if (ptr->type != Node::LIST) {
            ptr = std::make_shared<Node>();
        }
    }

public:
    // Default constructs an empty list
    pylist() : ptr(std::make_shared<Node>()) {}

    // Construct from int
    pylist(int v) : ptr(std::make_shared<Node>(v)) {}

    // Implicit conversion to int for arithmetic/printing contexts when this holds an int
    operator int() const {
        // Assumed valid by problem statement when used in arithmetic contexts
        return ptr->iv;
    }

    // Append an element (int or pylist convertible)
    void append(const pylist &x) {
        ensure_list();
        ptr->lv.push_back(x);
    }

    // Pop the last element and return it
    pylist pop() {
        ensure_list();
        pylist r = ptr->lv.back();
        ptr->lv.pop_back();
        return r;
    }

    // Indexing (as lvalue/rvalue)
    pylist &operator[](size_t i) {
        ensure_list();
        return ptr->lv[i];
    }

    // Const indexing if ever needed
    const pylist &operator[](size_t i) const {
        return ptr->lv[i];
    }

    friend std::ostream &operator<<(std::ostream &os, const pylist &ls) {
        if (ls.ptr->type == Node::INT) {
            os << ls.ptr->iv;
            return os;
        }
        os << '[';
        const auto &v = ls.ptr->lv;
        for (size_t i = 0; i < v.size(); ++i) {
            if (i) os << ", ";
            os << v[i];
        }
        os << ']';
        return os;
    }
};

#endif // PYLIST_H

