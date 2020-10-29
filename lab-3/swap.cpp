#include <algorithm>
#include <utility>

struct Int {
    int value;

    Int(int value) : value(value) { }

    bool operator<(const Int& rhs) const {
        return value < rhs.value;
    }
};

void swap(Int& lhs, Int& rhs) noexcept {
    puts("My plain swap");
    std::swap(lhs.value, rhs.value);
}

void Print(const Int* const data, const size_t n) {
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", data[i].value);
    }
    printf("\n");
}

int main() {
    Int data[] = { {4}, {3}, {2}, {1} };
    const size_t n = sizeof(data) / sizeof(*data);
    Print(data, n);
    std::swap_ranges(data, data + 2, data + 2);
    Print(data, n);
}
