//  Same example, single column 

#include "CommonInclude.h"

class Stooge {
public:
   virtual void slapStick() = 0;
   virtual ~Stooge(){}
};

class Larry : public Stooge {
public:
   void slapStick() {
      cout << "Larry: poke eyes" << endl; }
};
class Moe : public Stooge {
public:
   void slapStick() {
      cout << "Moe: slap head" << endl; }
};
class Curly : public Stooge {
public:
   void slapStick() {
      cout << "Curly: suffer abuse" << endl; }
};

int main_prototype_3( void ) 
{
   cout<<">>>>>>>> main_prototype_3 <<<<<<<<"<<endl;   
   Stooge*  roles[10];
   int      in, j, i = 0;

   cout << "L(1) M(2) C(3) Go(0): ";
   cin >> in;
   while (in) 
   {
      if (in == 1)
         roles[i++] = new Larry;
      else if (in == 2)
         roles[i++] = new Moe;
      else
         roles[i++] = new Curly;
      cout << "L(1) M(2) C(3) Go(0): ";
      cin >> in;
   }

   for (j=0; j < i; j++)
      roles[j]->slapStick();

   for (j=0; j < i; j++)
      delete roles[j];
      
   system( "pause" );
   return 0;
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

