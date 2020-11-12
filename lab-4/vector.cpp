#include <iostream>
#include <vector>

struct Vector {
    virtual size_t GetSize() const = 0;

    virtual float GetValue(size_t index) const = 0;

    virtual void SetValue(size_t index, float value) = 0;

    bool Equals(const Vector& rhs) const {
        const auto size = GetSize();
        if (size != rhs.GetSize()) {
            return false;
        }
        // WARNING: Float equality comparison!
        for (size_t i = 0; i < size; ++i) {
            if (GetValue(i) != rhs.GetValue(size)) {
                return false;
            }
        }
        return true;
    }

    void Print(std::ostream& stream) const {
        stream << "[";
        PrintRealType(stream);
        stream << "]";

        const auto n = GetSize();
        for (size_t i = 0; i < n; ++i) {
            stream << " " << GetValue(i);
        }
        stream << std::endl;
    }

    virtual ~Vector() = default;

protected:
    Vector() = default;
    Vector(const Vector&) = default;
    Vector& operator=(const Vector& rhs) = default;

    virtual void PrintRealType(std::ostream& stream) const = 0;
};

void Sum(const Vector& lhs, const Vector& rhs, Vector& dst) {
    const auto n = dst.GetSize();

    for (size_t i = 0; i < n; ++i) {
        const auto a = lhs.GetValue(i);
        const auto b = rhs.GetValue(i);
        dst.SetValue(i, a + b);
    }
}

class BufferedVector final : public Vector {
    std::vector<float> data;

public:
    BufferedVector(size_t size) {
        data.resize(size);
    }

    virtual size_t GetSize() const override {
        return data.size();
    }

    virtual float GetValue(size_t index) const override {
        return data[index];
    }

    virtual void SetValue(size_t index, float value) override {
        data[index] = value;
    }

protected:
    virtual void PrintRealType(std::ostream& stream) const override {
        stream << "BufferedVector";
    }
};

class SubVector final : public Vector {
    Vector& v;
    size_t start;
    size_t size;

public:
    SubVector(Vector& v, size_t start, size_t size) : v(v), start(start), size(size) { }

    virtual size_t GetSize() const override {
        return size;
    }

    virtual float GetValue(size_t index) const override {
        return v.GetValue(start + index);
    }

    virtual void SetValue(size_t index, float value) override {
        v.SetValue(start + index, value);
    }
    
protected:
    virtual void PrintRealType(std::ostream& stream) const override {
        stream << "SubVector";
    }
};

int main() {
    BufferedVector v1(5);
    v1.SetValue(0, 1);
    v1.SetValue(1, 2);
    v1.SetValue(2, 3);
    v1.SetValue(3, 4);
    v1.SetValue(4, 5);

    BufferedVector v2(2);
    v2.SetValue(0, 6);
    v2.SetValue(1, 7);

    SubVector v3(v1, 0, 2);

    v1.Print(std::cout);
    v2.Print(std::cout);
    v3.Print(std::cout);
    
    std::cout << std::endl;

    v3.SetValue(0, -3);
    v1.Print(std::cout);
    v2.Print(std::cout);
    v3.Print(std::cout);
    std::cout << std::endl;

    SubVector v4(v1, 3, 2);
    Sum(v2, v3, v4);
    v1.Print(std::cout);
    v2.Print(std::cout);
    v3.Print(std::cout);
}
