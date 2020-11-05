template<typename T>
class Vector {
    T* data;
    size_t size;

public:
    using iterator = T*;
    using const_iterator = const T*;

    Vector(size_t size) : data(new T[size]), size(size) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0;
        }
    }

    Vector(const Vector<T>& rhs) : data(new T[rhs.size]), size(rhs.size) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = rhs.data[i];
        }
    }

    Vector(Vector<T>&& rhs) noexcept : data(rhs.data), size(rhs.size) {
        rhs.data = nullptr;
        rhs.size = 0;
    }

    Vector<T>& operator=(const Vector<T>& rhs) {
        Vector<T> tmp(rhs);
        swap(tmp);
        return *this;
    }

    Vector<T>& operator=(Vector<T>&& rhs) noexcept {
        swap(rhs);
        return *this;
    }

    void swap(Vector<T>& rhs) noexcept {
        std::swap(data, rhs.data);
        std::swap(size, rhs.size);
    }

    size_t size() const noexcept {
        return size;
    }

    const T& operator[](const size_t index) const {
        return data[index];
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const_iterator begin() const {
        return data;
    }

    const_iterator end() const {
        return data + size;
    }

    iterator insert(const_iterator pos, const T& value) {
        // TODO
    }

    iterator erase(const_iterator pos) {
        // TODO
    }

    void clear() noexcept {
        // TODO
    }

    ~Vector() { // noexcept
        delete[] data;
    }
};
