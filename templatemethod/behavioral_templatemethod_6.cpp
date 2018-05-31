


// Purpose. Template Method design pattern

// 1. Standardize the skeleton of an algorithm in a base class "template" method
// 2. Common implementations of individual steps are defined in the base class
// 3. Steps requiring peculiar implementations are "placeholders" in base class
// 4. Derived classes can override placeholder methods
// 5. Derived classes can override implemented methods
// 6. Derived classes can override and "call back to" base class methods

#include <iostream>
using namespace std;

class A {
public:
   // 1. Standardize the skeleton of an algorithm in a "template" method
   void findSolution() {
      stepOne();
      stepTwo();
      stepThr();
      stepFor();
   }
protected:
   virtual void stepFor() { cout << "A.stepFor" << '\n'; }
private:
   // 2. Common implementations of individual steps are defined in base class
   void stepOne() { cout << "A.stepOne" << '\n'; }
   // 3. Steps requiring peculiar impls are "placeholders" in the base class
   virtual void stepTwo() = 0;
   virtual void stepThr() = 0;
};

class B : public A {
   // 4. Derived classes can override placeholder methods
   // 1. Standardize the skeleton of an algorithm in a "template" method
   /*virtual*/ void stepThr() {
      step3_1();
      step3_2();
      step3_3();
   }
   // 2. Common implementations of individual steps are defined in base class
   void step3_1() { cout << "B.step3_1" << '\n'; }
   // 3. Steps requiring peculiar impls are "placeholders" in the base class
   virtual void step3_2() = 0;
   void step3_3() { cout << "B.step3_3" << '\n'; }
};

class C : public B {
   // 4. Derived classes can override placeholder methods
   /*virtual*/ void stepTwo() { cout << "C.stepTwo" << '\n'; }
   void step3_2() { cout << "C.step3_2" << '\n'; }
   // 5. Derived classes can override implemented methods
   // 6. Derived classes can override and "call back to" base class methods
   /*virtual*/ void stepFor() {
      cout << "C.stepFor" << '\n';
      A::stepFor();
}  };

int main( void ) {
   C algorithm;
   algorithm.findSolution();
   return 0;
}

// A.stepOne
// C.stepTwo
// B.step3_1
// C.step3_2
// B.step3_3
// C.stepFor
// A.stepFor