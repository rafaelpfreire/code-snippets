#include <iostream>
#include <memory> // for std::unique_ptr
#include <utility> // for std::move

// std::unique_ptr has only one owner so it doesn't implements a copy constructor
// or a copy assignment. It only implements the move constructor and move assignment
//
// std::shared_ptr can be used when you need multiple smart pointers that can co-own a resource.
// The resource will be deallocated when the last std::shared_ptr goes out of scope.
//
// std::weak_ptr can be used when you want a smart pointer that can see and use a shared resource,
// but does not participate in the ownership of that resource. Use the member function expired()
// to check if the resource is still available or not

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }

    friend std::ostream& operator<<(std::ostream& out, const Resource &res)
    {
        out << "I am a resource";
        return out;
    }
};

void takeOwnership(std::unique_ptr<Resource> res)
{
     if (res) // use implicit cast to bool to ensure res contains a Resource
          std::cout << *res << '\n';
} // the Resource is destroyed here

// Returns a std::weak_ptr to an invalid object
std::weak_ptr<Resource> getWeakPtr()
{
	auto ptr{ std::make_shared<Resource>() };
	return std::weak_ptr<Resource>{ ptr };
} // ptr goes out of scope, Resource destroyed

// Returns a dumb pointer to an invalid object
Resource* getDumbPtr()
{
	auto ptr{ std::make_unique<Resource>() };
	return ptr.get();
} // ptr goes out of scope, Resource destroyed

int main()
{
    std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
    std::unique_ptr<Resource> res2{}; // Start as nullptr
    auto res3{ std::make_unique<Resource>() };

    std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
    std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

    // res2 = res1; // Won't compile: copy assignment is disabled
    res2 = std::move(res1); // res2 assumes ownership, res1 is set to null

    std::cout << "Ownership transferred\n";

    std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
    std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

    // takeOwnership(ptr); // This doesn't work, need to use move semantics
    takeOwnership(std::move(res3)); // ok: use move semantics

    auto ptr1 { std::make_shared<Resource>() };
    {
        // create ptr2 using copy of ptr1
        // This is better because the shared_ptr's
        // control block is not allocated again
        auto ptr2 { ptr1 };

        std::cout << "Killing one shared pointer\n";
    } // ptr2 goes out of scope here, and the allocated Resource is destroyed

    auto dumb{ getDumbPtr() };
	std::cout << "Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");

	auto weak{ getWeakPtr() };
	std::cout << "Our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");

    std::cout << "Ending program\n";

    return 0;
} // Resource destroyed here when res2 goes out of scope
