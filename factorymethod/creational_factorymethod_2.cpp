#include <iostream>
using namespace std;
class Stooge {
public:
   virtual void slapStick() = 0;
};
class Factory {
public:
   // Factory Method (virtual ctor)
   static Stooge* create( int );
};

int main_factorymethod_2( void ) {
   Stooge*  roles[10];
   int      in, j, i = 0;
   while (1) {
      cout << "L(1) M(2) C(3) Go(0): ";
      cin >> in;
      if ( ! in ) break;
      roles[i++] = Factory::create(in);
   }
   for (j=0; j < i; j++)
      roles[j]->slapStick();
   for (j=0; j < i; j++)
      delete roles[j];
}
class Larry : public Stooge { public:
   void slapStick() {
      cout << "Larry: poke eyes"
         << endl; }
};
class Moe : public Stooge { public:
   void slapStick() {
      cout << "Moe: slap head"
         << endl; }
};
class Curly : public Stooge { public:
   void slapStick() {
      cout << "Curly: suffer abuse"
         << endl; }
};
Stooge* Factory::create( int in ) {
   if (in == 1)
      return new Larry;
   else if (in == 2)
      return new Moe;
   else
      return new Curly;
}
// L(1) M(2) C(3) Go(0): 1
// L(1) M(2) C(3) Go(0): 2
// L(1) M(2) C(3) Go(0): 3
// L(1) M(2) C(3) Go(0): 1
// L(1) M(2) C(3) Go(0): 0
// Larry: poke eyes
// Moe: slap head
// Curly: suffer abuse
// Larry: poke eyes