#include <algorithm>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

class Vector {
    float* data;
    size_t size;

public:
    Vector(size_t size) : data(new float[size]), size(size) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0;
        }
    }

    Vector(const Vector& rhs) : data(new float[rhs.size]), size(rhs.size) {
        puts("COPY-CTOR");
        for (size_t i = 0; i < size; ++i) {
            data[i] = rhs.data[i];
        }
    }

    Vector(Vector&& rhs) noexcept : data(rhs.data), size(rhs.size) {
        puts("MOVE-CTOR");
        rhs.data = nullptr;
        rhs.size = 0;
    }

    Vector& operator=(const Vector& rhs) {
        puts("COPY-ASSIGN");
        Vector tmp(rhs);
        Swap(tmp);
        return *this;
    }

    Vector& operator=(Vector&& rhs) noexcept {
        puts("MOVE-ASSIGN");
        Swap(rhs);
        return *this;
    }

    void Swap(Vector& rhs) noexcept {
        puts("CUSTOM SWAP");
        std::swap(data, rhs.data);
        std::swap(size, rhs.size);
    }

    size_t GetSize() const {
        return size;
    }

    float operator[](const size_t index) const {
        if (index >= size) {
            throw std::logic_error("Index out of range!");
        }
        return data[index];
    }

    float& operator[](size_t index) {
        if (index >= size) {
            throw std::logic_error("Index out of range!");
        }
        return data[index];
    }

    ~Vector() { // noexcept
        delete[] data;
    }
};

namespace std {
    // Специализация шаблона
    template<>
    void swap(Vector& lhs, Vector& rhs) noexcept {
        lhs.Swap(rhs);
    }
}

Vector& operator+=(Vector& lhs, const Vector& rhs) {
    if (lhs.GetSize() != rhs.GetSize()) {
        throw std::logic_error("Vectors must have the same size!");
    }
    const auto size = lhs.GetSize();
    for (size_t i = 0; i < size; ++i) {
        lhs[i] += rhs[i];
    }
}

Vector operator+(const Vector& lhs, const Vector& rhs) {
    Vector result(lhs);
    result += rhs;
    return result;
}

void Print(const Vector& v) {
    for (size_t i = 0; i < v.GetSize(); ++i) {
        printf("%f ", v[i]);
    }
    printf("\n");
}

int main() {
    Vector v1(3);
    v1[0] = 1;
    v1[1] = 2;
    v1[2] = 3;

    Vector v2(4);
    v2[0] = 4;
    v2[1] = 3;
    v2[2] = 2;
    v2[3] = 1;

    std::swap(v1, v2);
}
