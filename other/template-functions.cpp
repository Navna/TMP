#include <algorithm>
#include <cstdio>

struct Person {
    int age;
    float weight;
    Person(int age, float weight) : age(age), weight(weight) {    }
};

void Print(const Person& p) {
    printf("%d %f\n", p.age, p.weight);
}

struct PersonNode {
    Person person;
    PersonNode* next;

    PersonNode(const Person& person, PersonNode* next) : person(person), next(next) { }
};

bool PersonAgeComparator(const Person& lhs, const Person& rhs) {
    return lhs.age < rhs.age;
}

struct PersonWeightComparator {
    bool operator()(const Person& lhs, const Person& rhs) {
        return lhs.weight < rhs.weight;
    }
};

// Пример итератора по связному списку
// Как в других языках:
//     bool MoveNext();
//     Person GetValue();
class PersonListIterator {
    PersonNode* node;

public:
    // См. https://en.cppreference.com/w/cpp/iterator/iterator_traits
    using difference_type = ptrdiff_t;                   // A signed integer type that can be used to identify distance between iterators.
    using value_type = Person;                           // The type of the values that can be obtained by dereferencing the iterator. This type is void for output iterators.
    using pointer = Person*;                             // Defines a pointer to the type iterated over (value_type).
    using reference = const Person&;                     // Defines a reference to the type iterated over (value_type).
    using iterator_category = std::forward_iterator_tag; // The category of the iterator. Must be one of iterator category tags: https://en.cppreference.com/w/cpp/iterator/iterator_tags.

    PersonListIterator(PersonNode* node) : node(node) { }

    PersonListIterator& operator++() {
        node = node->next;
        return *this;
    }

    const Person& operator*() {
        return node->person;
    }

    bool operator==(PersonListIterator rhs) {
        return node == rhs.node;
    }

    bool operator!=(PersonListIterator rhs) {
        return node != rhs.node;
    }
};

template<typename Iterator, typename Comparator>
Iterator FindMin(Iterator begin, Iterator end, Comparator comparator) {
    Iterator min = begin;
    ++begin;
    while (begin != end) {
        if (comparator(*begin, *min)) {
            min = begin;
        }
        ++begin;
    }
    return min;
}

int main() {
    Person persons[] = { {20, 60}, {25, 35}, { 18, 40 } };

    auto n3 = new PersonNode(Person(18, 40), nullptr);
    auto n2 = new PersonNode(Person(25, 35), n3);
    auto head = new PersonNode(Person(20, 60), n2);

    PersonWeightComparator weightComparator;

    // МаПример работы с указаталем на функцию
    const auto ageIterator1 = FindMin(persons, persons + sizeof(persons) / sizeof(*persons), PersonAgeComparator);
    auto listIterator = FindMin(PersonListIterator(head), PersonListIterator(nullptr), PersonAgeComparator);

    // Пример с лямбда-выражением (анонимной функцией)
    const auto ageIterator2 = FindMin(persons, persons + sizeof(persons) / sizeof(*persons),
        [](const Person& lhs, const Person& rhs) {
            return lhs.age - rhs.age;
        });

    // Пример работы с объектом компаратора
    const auto weightIterator = FindMin(persons, persons + sizeof(persons) / sizeof(*persons), weightComparator);
    printf("MIN: Age=%d Weight=%f\n", (*listIterator).age, (*listIterator).weight);
    printf("MIN: Index=%td Age=%d Weight=%f\n", ageIterator1 - persons, ageIterator1->age, ageIterator1->weight);
    printf("MIN: Index=%td Age=%d Weight=%f\n", ageIterator2 - persons, ageIterator2->age, ageIterator2->weight);
    printf("MIN: Index=%td Age=%d Weight=%f\n", weightIterator - persons, weightIterator->age, weightIterator->weight);

    // Пример работы с std::algorithm
    // У всех ли людей в списке возраст превышает указанное значение?
    printf("all_of: %d\n", std::all_of(PersonListIterator(head), PersonListIterator(nullptr),
        [](const Person& p) {
            return p.age >= 19;
        })
    );

    std::for_each(PersonListIterator(head), PersonListIterator(nullptr), Print);

    delete head;
    delete n2;
    delete n3;
}
