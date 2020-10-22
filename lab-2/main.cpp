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

    Vector(Vector&& rhs) : data(rhs.data), size(rhs.size) {
        puts("MOVE-CTOR");
        rhs.data = nullptr;
        rhs.size = 0;
    }

    Vector& operator=(const Vector& rhs) {
        puts("COPY-ASSIGN");
        // Сделать через swap.
        // См. главу 56 в Саттере & Александреску
        if (this == &rhs) {
            return *this;
        }
        if (size != rhs.size) {
            delete[] data;
            data = new float[rhs.size];
            size = rhs.size;
        }
        for (size_t i = 0; i < size; ++i) {
            data[i] = rhs.data[i];
        }
    }

    Vector& operator=(Vector&& rhs) noexcept {
        puts("MOVE-ASSIGN");
        // TODO
        return *this;
    }

    void Swap(Vector& rhs) {
        std::swap(data, rhs.data);
        std::swap(size, rhs.size);
    }

    size_t GetSize() const {
        return size;
    }

    float GetValue(size_t index) const {
        return data[index];
    }

    void SetValue(size_t index, float value) {
        data[index] = value;
    }

    ~Vector() { // noexcept
        delete[] data;
    }
};

Vector& operator+=(Vector& lhs, const Vector& rhs) {
    if (lhs.GetSize() != rhs.GetSize()) {
        throw std::logic_error("Vectors must have the same size!");
    }
    const auto size = lhs.GetSize();
    for (size_t i = 0; i < size; ++i) {
        lhs.SetValue(i, lhs.GetValue(i) + rhs.GetValue(i));
    }
}

Vector operator+(const Vector& lhs, const Vector& rhs) {
    Vector result(lhs);
    result += rhs;
    return result;
}

void Print(const Vector& v) {
    for (size_t i = 0; i < v.GetSize(); ++i) {
        printf("%f ", v.GetValue(i));
    }
    printf("\n");
}

int main() {
    Vector v1(3);
    v1.SetValue(0, 1);
    v1.SetValue(1, 2);
    v1.SetValue(2, 3);

    Vector v2(3);
    v2.SetValue(0, 0);
    v2.SetValue(1, -1);
    v2.SetValue(2, 2);

    auto v = std::move(v2);
}
