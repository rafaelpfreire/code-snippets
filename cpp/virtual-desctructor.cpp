// A program with virtual destructor
#include <iostream>
 
using namespace std;
 
class base {
  public:
    base()    
    { cout << "Constructing base\n"; }
    virtual ~base()
    { cout << "Destructing base\n"; }    
};
 
class derived : public base {
  public:
    derived()    
    { cout << "Constructing derived\n"; }
    ~derived()
    { cout << "Destructing derived\n"; }
};
 
int main()
{
  derived *d = new derived(); 

  // Using polymorphism
  base *b = d;

  // Now b destructor is called. But since it is virutal
  // and we construct a derived class, d destructor will
  // also be called. If base destructor was not virtual
  // this line would have undefined behavior (probably
  // it will call only the base destructor.
  delete b;

  return 0;
}
