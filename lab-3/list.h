#pragma once

template<typename T>
class List {
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& data, Node* prev, Node* next) : data(data), prev(prev), next(next) { }
    };

    Node _dummy;
    Node* _head;
    Node* _tail;
    size_t _size;

public:
    class ConstIterator {
        Node* node;

        ConstIterator(Node* node) : node(node) { }

    public:
        friend class List<T>;

        ConstIterator& operator++() {
            node = node->next;
            return *this;
        }

        ConstIterator operator++(int) {
            auto result(*this);
            node = node->next;
            return result;
        }

        // TODO List<T>::ConstIterator::operator--()

        // TODO List<T>::ConstIterator::operator--(int)

        const T& operator*() {
            return node->data;
        }

        // TODO List<T>::ConstIterator::operator->

        bool operator==(ConstIterator rhs) {
            return node == rhs.node;
        }

        bool operator!=(ConstIterator rhs) {
            return node != rhs.node;
        }
    };

    List() : _dummy(T(), nullptr, nullptr), _head(&_dummy), _tail(&_dummy), _size(0) {
        _dummy.prev = &_dummy;
        _dummy.next = &_dummy;
    }

    List(const List<T>& rhs) {
        // TODO List::List(const List<T>& rhs)
    }

    List(List<T>&& rhs) noexcept {
        // TODO List::List(List<T>&& rhs)
    }

    List<T>& operator=(const List<T>& rhs) {
        auto temp(rhs);
        swap(temp);
        return *this;
    }

    List<T>& operator=(List<T>&& rhs) noexcept {
        swap(rhs);
        return *this;
    }

    void swap(List<T>& rhs) noexcept {
        // TODO List::swap(List<T>& rhs)
    }

    size_t size() const noexcept {
        return _size;
    }

    ConstIterator begin() const {
        return ConstIterator(_head);
    }

    ConstIterator end() const {
        return ConstIterator(&_dummy);
    }

    ConstIterator insert(ConstIterator pos, const T& value) {
        // TODO List<T>::insert

        // Операция должна работать за O(1)!
        // Не забыть ++_size!
    }

    ConstIterator erase(ConstIterator pos) {
        // TODO List<T>::erase

        // Операция должна работать за O(1)!
        // Не забыть --_size!
    }

    void clear() noexcept {
        // TODO List<T>::clear

        // Не забыть _size = 0!
    }

    ~List() {
        clear();
    }
};
