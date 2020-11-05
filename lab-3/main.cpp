#include <iostream>
#include <list>
#include <vector>

#include "list.h"
#include "vector.h"

using namespace std;

template<typename T>
using CollectionType = std::list<T>;

int main() {
    CollectionType<int> collection;
    collection.insert(collection.begin(), 1);
    collection.insert(collection.end(), 2);
    collection.insert(collection.begin(), 0);

    for (auto value : collection) {
        cout << value << endl;
    }
}
