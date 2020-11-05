#include <iostream>
#include <vector>

using namespace std;

struct SomeType {
    SomeType() {
        puts("default");
    }
    SomeType(const SomeType&) {
        puts("copy ctor");
    }
    SomeType(SomeType&& rhs) noexcept {
        puts("move ctor");
    }
    SomeType& operator=(const SomeType&) {
        puts("copy assign");
        return *this;
    }
    SomeType& operator=(SomeType&&) noexcept {
        puts("move assign");
        return *this;
    }
};

int main() {
    std::vector<SomeType> vector;
    for (size_t i = 0; i < 16; ++i) {
        cout << "size=" << vector.size() << " capacity=" << vector.capacity() << endl;
        vector.insert(vector.end(), SomeType());
        cout << "size=" << vector.size() << " capacity=" << vector.capacity() << endl;
        cout << endl;
    }
}
