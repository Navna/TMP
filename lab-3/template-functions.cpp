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

int PersonAgeComparator(const Person& lhs, const Person& rhs) {
    return lhs.age - rhs.age;
}

struct PersonWeightComparator {
    int operator()(const Person& lhs, const Person& rhs) {
        return lhs.weight - rhs.weight;
    }
};

// Пример, что такое итератор
// Как в других языках
// bool MoveNext();
// Person GetValue();
class PersonListIterator {
    PersonNode* node;

public:
    PersonListIterator(PersonNode* node) : node(node) { }

    PersonListIterator& operator++() {
        node = node->next;
        return *this;
    }

    Person& operator*() {
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
        if (comparator(*begin, *min) < 0) {
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

    // Пример работы с указаталем на функцию
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
