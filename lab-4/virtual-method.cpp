#include <iostream>

using namespace std;

struct A {
    void f() const {
        cout << "A::f()" << endl;
    }

    virtual void vf() const {
        cout << "A::vf()" << endl;
    }

    virtual ~A() {
        cout << "A::~A()" << endl;
    }
};

struct B : public A {
    void f() const {
        cout << "B::f()" << endl;
    }

    virtual void vf() const override {
        cout << "B::vf()" << endl;
    }

    ~B() {
        cout << "B::~B()" << endl;
    }
};

int main() {
    // Приведение типов для указателей
    {
        A* p = new B();
        cout << dynamic_cast<B*>(p) << endl;
        delete p;
    }
    {
        A* p = new A();
        cout << dynamic_cast<B*>(p) << endl;
        delete p;
    }

    // Приведение типов для ссылок
    {
        A* p = new B();
        dynamic_cast<B&>(*p).vf();
        delete p;
    }
    {
        A* p = new A();
        //dynamic_cast<B&>(*p).vf();
        delete p;
    }

    A* paa = new A();   //   Формальный тип: A   Фактический тип: A
    A* pab = new B();   //   Формальный тип: A   Фактический тип: B
    B* pbb = new B();   //   Формальный тип: B   Фактический тип: B

    paa->f();
    pab->f();
    pbb->f();

    cout << endl;

    paa->vf();
    pab->vf();
    pbb->vf();

    cout << endl;

    delete paa;
    cout << endl;

    delete pab;
    cout << endl;

    delete pbb;
}
