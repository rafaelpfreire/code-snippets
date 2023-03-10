#include <iostream>

// The move constructor and move assignment are called when those functions have been defined,
// and the argument for construction or assignment is an r-value. Most typically,
// this r-value will be a literal or temporary value.

template<typename T>
class Auto_ptr
{
    T* m_ptr;
public:
    Auto_ptr(T* ptr = nullptr)
        :m_ptr(ptr)
    {
    }

    ~Auto_ptr()
    {
        delete m_ptr;
    }

    // Copy constructor
    // Do deep copy of a.m_ptr to m_ptr
    Auto_ptr(const Auto_ptr& a)
    {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }

    // Move constructor
    // Transfer ownership of a.m_ptr to m_ptr
    Auto_ptr(Auto_ptr&& a) noexcept
        : m_ptr(a.m_ptr)
    {
        a.m_ptr = nullptr;
    }

    // Copy assignment
    // Do deep copy of a.m_ptr to m_ptr
    Auto_ptr& operator=(const Auto_ptr& a)
    {
        // Self-assignment detection
        if (&a == this)
            return *this;

        // Release any resource the destination is holding
        delete m_ptr;

        // Copy the resource
        m_ptr = new T;
        *m_ptr = *a.m_ptr;

        return *this;
    }

    // Move assignment
    // Transfer ownership of a.m_ptr to m_ptr
    Auto_ptr& operator=(Auto_ptr&& a) noexcept
    {
        // Self-assignment detection
        if (&a == this)
            return *this;

        // Release any resource we're holding
        delete m_ptr;

        // Transfer ownership of a.m_ptr to m_ptr
        // Since ownership is being moved, assign old ptr to null
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;

        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_ptr<Resource> generateResource()
{
    Auto_ptr<Resource> res{new Resource};
    // this return value will invoke the move constructor
    // because it creates a temp value
    return res;
}

int main()
{
    Auto_ptr<Resource> mainres;
    mainres = generateResource(); // this assignment will invoke the move assignment

    return 0;
}
