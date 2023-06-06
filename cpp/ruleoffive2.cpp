#include <iostream>

class ClassWithFive {
public:
    ClassWithFive() = default;
    ~ClassWithFive() = default;

    explicit ClassWithFive(int b): a(b) {
        std::cout << "Calling Class Constructor" << std::endl;
    }

    ClassWithFive(ClassWithFive &obj): a(obj.a) {
        std::cout << "Calling Copy Constructor" << std::endl;
        this->a = obj.a;
    }

    ClassWithFive(ClassWithFive &&obj): a(obj.a) {
        std::cout << "Calling Move Constructor" << std::endl;
        obj.a = 0;
    }

    ClassWithFive& operator=(const ClassWithFive& obj) {
        std::cout << "Calling Copy Assignment" << std::endl;
        if (&obj == this)
            return *this;

        this->a = obj.a;
        return *this;
    }

    ClassWithFive& operator=(ClassWithFive&& obj) {
        std::cout << "Calling Move Assignment" << std::endl;
        if (&obj == this)
            return *this;

        // It make more sense if you have pointer to data
        // allocated in the heap.
        this->a = obj.a;
        obj.a = 0;
        return *this;
    }

    int a;
};

ClassWithFive TestFunction1() {
    ClassWithFive local;
    local.a = 8;
    return std::move(local);
}

int main () {
    std::cout << "Line " << __LINE__ + 1 << " we're ";
    ClassWithFive var1(1);

    std::cout << "Line " << __LINE__ + 1 << " we're ";
    ClassWithFive var2(var1);

    std::cout << "Line " << __LINE__ + 1 << " we're ";
    var2 = var1;

    std::cout << "Line " << __LINE__ + 1 << " we're ";
    auto var3 = TestFunction1();

    std::cout << "Line " << __LINE__ + 1 << " we're ";
    var2 = std::move(var1);

    return 0;
}
