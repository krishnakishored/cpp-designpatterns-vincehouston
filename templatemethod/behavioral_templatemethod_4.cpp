

// Purpose.  Template Method design pattern

// 1. Standardize the skeleton of an algorithm in a base class "template method"
// 2. Steps requiring peculiar implementations are "placeholders" in base class
// 3. Derived classes implement placeholder methods

#include"CommonHeader.h"
class Base {
   void a() { cout << "a  "; }
   void c() { cout << "c  "; }
   void e() { cout << "e  "; }
   // 2. Steps requiring peculiar implementations are "placeholders" in base class
   virtual void ph1() = 0;
   virtual void ph2() = 0;
public:
   // 1. Standardize the skeleton of an algorithm in a base class "template method"
   void execute() {  a();  ph1();  c();  ph2();  e(); }
};

class One : public Base {
   // 3. Derived classes implement placeholder methods
   /*virtual*/ void ph1() { cout << "b  "; }
   /*virtual*/ void ph2() { cout << "d  "; }
};

class Two : public Base {
   /*virtual*/ void ph1() { cout << "2  "; }
   /*virtual*/ void ph2() { cout << "4  "; }
};

int main_templatemethod_4( void ) 
{
  cout<<">>>>>>>> main_templatemethod_4 <<<<<<<<"<<endl;  
   Base* array[] = { &One(), &Two() }; //message: taking the address of a temporary object of type 'Two' [-Waddress-of-temporary]
   for (int i=0; i < 2; i++) {
      array[i]->execute();
      cout << '\n';
    }  
return 0;
}

// a  b  c  d  e
// a  2  c  4  e
