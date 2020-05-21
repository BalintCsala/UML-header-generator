#ifndef UML_GENERATOR_TESTCLASSES_H
#define UML_GENERATOR_TESTCLASSES_H

class C {

};

class B : public C {
    int a;
    int b;

    void hello(int e, int f) {

    }
};

template<typename T, class U, int size>
class MultipleTemplateClassTest {
    int a;
    int b;
public:
    int c;
    int d;
    T t;
    U u;
    int *arr;

    MultipleTemplateClassTest() : arr(new int[size]) {};

    int hello(int e, int f) {

    }

    int helloDefault(int e, int f = 10) {
        return a + b + c + d + e + f;
    }

    T helloTemplateParam(int e, int f, T t) {
        return t;
    }

    template<typename K>
    K helloTemplated(T e, K h) {

    }

    ~MultipleTemplateClassTest() {
        delete[] arr;
    }
};

namespace testNameSpace {

    class NameSpaceTestBase {

    };

    class NameSpaceTest : public NameSpaceTestBase {

    };

}

#endif //UML_GENERATOR_TESTCLASSES_H
