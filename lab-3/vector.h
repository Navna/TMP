#pragma once

template<typename T>
class Vector {
    T* _data;
    size_t _size;
    size_t _capacity;

public:
    using iterator = T*;
    using const_iterator = const T*;

    Vector() : _data(nullptr), _size(0), _capacity(0) { }

    Vector(const Vector<T>& rhs) : _data(new T[rhs._size]), _size(rhs._size), _capacity(rhs._capacity) {
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = rhs._data[i];
        }
    }

    Vector(Vector<T>&& rhs) noexcept : _data(rhs.data), _size(rhs._size) {
        rhs._data = nullptr;
        rhs._size = 0;
    }

    Vector<T>& operator=(const Vector<T>& rhs) {
        auto temp(rhs);
        swap(temp);
        return *this;
    }

    Vector<T>& operator=(Vector<T>&& rhs) noexcept {
        swap(rhs);
        return *this;
    }

    void swap(Vector<T>& rhs) noexcept {
        std::swap(_data, rhs._data);
        std::swap(_size, rhs._size);
        std::swap(_capacity, rhs._capacity);
    }

    size_t size() const noexcept {
        return _size;
    }

    size_t capacity() const noexcept {
        return _capacity;
    }

    const T& operator[](const size_t index) const {
        return _data[index];
    }

    T& operator[](size_t index) {
        return _data[index];
    }

    const_iterator begin() const {
        return _data;
    }

    const_iterator end() const {
        return _data + _size;
    }

    iterator insert(const_iterator pos, const T& value) {
        // TODO Vector<T>::insert

        // Не забыть ++_size!
        // На какую величину изменяется _capacity в случае перераспределения памяти - решить самостоятельно!

        // Если move не осилили - сдвигайте массив по-обычному, как на первом курсе, через оператор присваивания копированием.

        // Если move осилили - в идеале в случае перераспределения памяти вы должны:
        // 1) перемещать объекты, если move-операция у типа T является noexcept;
        // 2) в противном случае копировать объекты, если у типа T доступна операция копирования;
        // 3) только в случае безысходности использовать move-операцию, если он не является noexcept.
        // Для покрытия всех трёх ветвей одним кодом - см. https://en.cppreference.com/w/cpp/utility/move_if_noexcept.
    }

    iterator erase(const_iterator pos) {
        // TODO Vector<T>::erase

        // Не забыть --_size!
        // _capacity не изменяется!

        // Аналогично insert: хотя бы сделать через оператор присваивания копированием; в идеале - через перемещение с гарантией транзакционности (по возможности).
    }

    void clear() noexcept {
        delete[] _data;
        _data = nullptr;
        _size = 0;
        _capacity = 0;
    }

    ~Vector() {
        clear();
    }
};
