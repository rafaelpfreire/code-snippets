#include <iostream>

class Test {
    public:
        explicit Test(int resource = 0): m_res(resource) {}
        ~Test() = default;

        void print() {
            std::cout << "Resource = " << m_res << std::endl;
        }

        void printConst() const {
            std::cout << "Resource = " << m_res << std::endl;
        }

        void update(int &res) {
            m_res = res;
        }

        void updateConst(const int &res) {
            m_res = res;
        }

    private:
        int m_res;
};

int main() {
    const int num1 = 0;
    int num2 = 2;
    Test t{ 5 };
    const Test tconst{ 10 };

    t.print();
    //t.update(num1); // This is prohibited as function is defined as receiving a const ref
    t.updateConst(num2);
    t.printConst();

    //tconst.print(); // This is prohibited as obj is const and function dont
    //tconst.update(num); // This is prohibited as obj is const and function dont
    //tconst.print(); // This is prohibited as obj is const and function dont
    //tconst.updateConst(num); // This is prohibited as obj is const and function dont
    tconst.printConst();
}
09
