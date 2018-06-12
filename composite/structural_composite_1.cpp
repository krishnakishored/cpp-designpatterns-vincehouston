// Purpose.  Composite design pattern
//
// 1. Identify the scalar/primitive classes and vector/container classes
// 2. Create an "interface" (lowest common denominator) that can make all concrete classes "interchangeable"
// 3. All concrete classes declare an "is a" relationship to the interface
// 4. All "container" classes couple themselves to the interface (recursive composition, Composite "has a" set of children up the "is a" hierarchy)
// 5. "Container" classes use polymorphism as they delegate to their children

#include"CommonInclude.h"     

// 2. Create an "interface" (lowest common denominator)
class Component { public: virtual void traverse() = 0; };

class Leaf : public Component {        // 1. Scalar class   3. "is_a" relationship
   int value;
public:
   Leaf( int val ) { value = val; }
   void traverse() { cout << value << ' '; }
};

class Composite1 : public Component {   // 1. Vector class   3. "is_a" relationship
   vector<Component*> children;        // 4. "container" coupled to the interface
public:
   // 4. "container" class coupled to the interface
   void add( Component* ele ) { children.push_back( ele ); }
   void traverse() {
      for (int i=0; i < children.size(); i++)
         // 5. Use polymorphism to delegate to children
         children[i]->traverse();
      }  
};

int main_composite_1A( void ) 
{
   cout<<">>>>>>>> main_composite_1A <<<<<<<<"<<endl;  
   Composite1 containers[4];

   for (int i=0; i < 4; i++)
      for (int j=0; j < 3; j++)
         containers[i].add( new Leaf( i * 3 + j ) );

   for (int i=1; i < 4; i++)
      containers[0].add( &(containers[i]) );

   for (int i=0; i < 4; i++) {
      containers[i].traverse();
      cout << endl;
      }  

   return 0;
}

// 0 1 2 3 4 5 6 7 8 9 10 11
// 3 4 5
// 6 7 8
// 9 10 11

// Purpose.  Composite design pattern - multiple container classes
// class Component { public: virtual void traverse() = 0; };

class Primitive : public Component {
   int value;
public:
   Primitive( int val ) { value = val; }
   void traverse()      { cout << value << "  "; }
};

class Composite : public Component {
   vector<Component*> children;
   int                value;
public:
   Composite( int val )     { value = val; }
   void add( Component* c ) { children.push_back( c ); }
   void traverse() {
      cout << value << "  ";
      for (int i=0; i < children.size(); i++)
          children[i]->traverse();
}  };

class Row : public Composite { public:     // Two different kinds of "container" classes.  Most of the "meat" is in the Composite base class.
   Row( int val ) : Composite( val ) { }   
   void traverse() {                        
      cout << "Row";                       
      Composite::traverse();
}  };

class Column : public Composite { public:
   Column( int val ) : Composite( val ) { }
   void traverse() {
      cout << "Col";
      Composite::traverse();
}  };

int main_composite_1B( void ) 
{
      main_composite_1A() ;
      cout<<">>>>>>>> main_composite_1B <<<<<<<<"<<endl;
      Row    first( 1 );                     
      Column second( 2 );                  
      Column third( 3 );                   
      Row    fourth( 4 );                  
      Row    fifth( 5 );                   
      first.add( &second );                
      first.add( &third  );                
      third.add( &fourth );                
      third.add( &fifth  );  
      Primitive P1(6);
      Primitive P2(7);  
      Primitive P3(8);
      Primitive P4(9);
      Primitive P5(10);            
      first.add(&P1);     
      second.add(&P2);      
      third.add(&P3);          
      fourth.add(&P4);
      fifth.add( &P5 );       
      // fifth.add(  &Primitive(10 ) );       // error: taking the address of a temporary object of type 'Primitive' [-Waddress-of-temporary]
      first.traverse();  cout << '\n';     
      return 0;
}
// Row1
  //   |
  //   +-- Col2
  //   |     |
  //   |     +-- 7
  //   +-- Col3
  //   |     |
  //   |     +-- Row4
  //   |     |     |
  //   |     |     +-- 9
  //   |     +-- Row5
  //   |     |     |
  //   |     |     +-- 10
  //   |     +-- 8
  //   +-- 6


// Row1  Col2  7  Col3  Row4  9  Row5  10  8  6



