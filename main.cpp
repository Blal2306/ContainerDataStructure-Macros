#include <iostream>
#include "Deque.hpp"

using namespace std;

struct MyClass {
    int id;
    char name[10];
};

bool MyClass_less_by_id(const MyClass &o1, const MyClass &o2) {
    return o1.id < o2.id;
}
bool int_less(const int &o1, const int &o2)
{
    return o1 < o2;
}
Deque_DEFINE(MyClass)
Deque_DEFINE(int)
int main()
{
    //++++++ TEST FOR MY CLASS ++++++//
    Deque_MyClass deq3;
    Deque_MyClass_ctor(&deq3, MyClass_less_by_id);

    assert(deq3.size(&deq3) == 0);
    assert(deq3.empty(&deq3));

    // Should print "---- Deque_MyClass, 14".
    printf("---- %s, %d\n", deq3.type_name, (int) sizeof(deq3.type_name));
    // std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
    assert(sizeof deq3.type_name == 14);

    deq3.push_back(&deq3, MyClass{1, "Joe"});
    deq3.push_back(&deq3, MyClass{2, "Mary"});
    deq3.push_back(&deq3, MyClass{3, "Tom"});
    deq3.push_front(&deq3, MyClass{0, "Mike"});
    deq3.push_front(&deq3, MyClass{-1, "Mary"});


    assert(deq3.front(&deq3).id == -1);
    assert(deq3.back(&deq3).id == 3);

    deq3.pop_front(&deq3);
    deq3.pop_back(&deq3);
    assert(deq3.front(&deq3).id == 0);
    assert(deq3.back(&deq3).id == 2);

    assert(deq3.size(&deq3) == 3);





    //++++++++++++++++++++++++++++++//
    Deque_int deq;
    Deque_int_ctor(&deq, int_less);

    assert(deq.size(&deq) == 0);
    assert(deq.empty(&deq));

    printf("--- %s, %d\n", deq.type_name, int(sizeof(deq.type_name)));
    assert(sizeof deq.type_name == 10);

    deq.push_back(&deq, 1);
    deq.push_back(&deq, 2);
    deq.push_back(&deq, 3);
    deq.push_front(&deq, 0);
    deq.push_front(&deq, -1);

    printf("%d\n", deq.front(&deq));
    printf("%d\n", deq.back(&deq));

    assert(deq.front(&deq) == -1);
    assert(deq.back(&deq) == 3);

    deq.pop_front(&deq);
    deq.pop_back(&deq);
    assert(deq.front(&deq) == 0);
    assert(deq.back(&deq) == 2);

    assert(deq.size(&deq) == 3);

    for (Deque_int_Iterator it = deq.begin(&deq);
         !Deque_int_Iterator_equal(it, deq.end(&deq)); it.inc(&it))
    {
        printf("%d\n", it.deref(&it));
    }

    // Test decrement.
    {
        auto it = deq.end(&deq);
        it.dec(&it);
        assert(it.deref(&it) == 2);
    }

    printf("Using at.\n");

    for (size_t i = 0; i < 3; i++)
    {
        printf("%d: %d\n", int(i), deq.at(&deq, i));
    }

    deq.clear(&deq);
    deq.dtor(&deq);


    Deque_int deq1, deq2;
    Deque_int_ctor(&deq1, int_less);
    Deque_int_ctor(&deq2, int_less);

    deq1.push_back(&deq1, 1);
    deq1.push_back(&deq1, 2);
    deq1.push_back(&deq1, 3);
    deq2.push_back(&deq2, 1);
    deq2.push_back(&deq2, 2);
    deq2.push_back(&deq2, 3);

    assert(Deque_int_equal(deq1, deq2));

    deq1.pop_back(&deq1);
    assert(!Deque_int_equal(deq1, deq2));
    deq1.push_back(&deq1, 4);
    assert(!Deque_int_equal(deq1, deq2));

    deq1.dtor(&deq1);
    deq2.dtor(&deq2);
    //+++++++++++++++++++++++++++++++++++++++++//
    cout << " *** NEW TESTS ******" << endl;
    Deque_int temp;
    Deque_int_ctor(&temp, int_less);
    long int count = 0;
    for(int i = 0; i < 98; i++)
    {
        temp.push_back(&temp, i+1);
    }
    for(int i = 0; i < 98; i++)
    {
        cout << temp.at(&temp, i) << endl;
    }
}
