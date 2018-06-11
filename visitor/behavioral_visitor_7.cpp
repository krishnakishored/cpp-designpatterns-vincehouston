




// Purpose.  Combining Visitor with Composite's recursive traversal

#include <iostream>
#include <vector>
using namespace std;

class Visitor { public:
   virtual void visit( class Leaf* e )      = 0;
   virtual void visit( class Composite* e ) = 0;
};

class Component { public:
   virtual void traverse() = 0;
   virtual void accept( class Visitor& v ) = 0;
};

class Leaf : public Component {
   int value;
public:
   Leaf( int val ) { value = val; }
   /*virtual*/ void traverse() { cout << value << ' '; }
   /*virtual*/ void accept( class Visitor& v ) { v.visit( this ); }
   int getValue() { return value; }
};

class Composite : public Component {
   char value;
   vector<Component*> children;
   static char next;
public:
   Composite() { value = next++; }
   void add( Component* ele ) { children.push_back( ele ); }
   /*virtual*/ void traverse() {
      cout << value << ' ';
      for (int i=0; i < children.size(); i++)
         children[i]->traverse();
   }
   /*virtual*/ void accept( class Visitor& v ) {
      v.visit( this );
      // accept() has been embellished to include the logic in traverse()
      for (int i=0; i < children.size(); i++)
         children[i]->accept( v );
   }
   char getValue() { return value; }
};
char Composite::next = 'a';

class TransformVisitor : public Visitor { public:
   /*virtual*/ void visit( Leaf* e ) { cout << e->getValue() + 100 << ' '; }
   /*virtual*/ void visit( Composite* e ) { cout << (char)(e->getValue()-32) <<' ';}
};

int main_visitor_7( void ) {
   Composite containers[4];
   for (int i=0; i < 4; i++)
      for (int j=0; j < 3; j++)
         containers[i].add( new Leaf( i * 3 + j ) );
   for (int i=1; i < 4; i++) containers[0].add( &(containers[i]) );

   containers[0].traverse();   cout << endl;

   TransformVisitor tv;
   // don't need an "iteration" capability with this design
   containers[0].accept( tv );   cout << endl;
}

// a 0 1 2 b 3 4 5 c 6 7 8 d 9 10 11
// A 100 101 102 B 103 104 105 C 106 107 108 D 109 110 111