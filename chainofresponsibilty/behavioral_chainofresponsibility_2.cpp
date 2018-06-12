
// Purpose.  Chain of Responsibility design pattern

// 1. Put a "next" pointer in the base class
// 2. The "chain" method in the base class always delegates to the next object
// 3. If the derived classes cannot handle, they delegate to the base class

#include <iostream>
#include <vector>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

class Base {
   Base* next;                // 1. "next" pointer in the base class
public:
   Base() { next = 0; }
   void setNext( Base* n ) { next = n; }
   void add( Base* n ) { if (next) next->add( n ); else next = n; }
   // 2. The "chain" method in the base class always delegates to the next obj
   virtual void handle( int i ) { next->handle( i ); }
};

class Handler1 : public Base { public:
   /*virtual*/ void handle( int i ) {
      if (rand() % 3) {       // 3. Don't handle requests 3 times out of 4
         cout << "H1 passsed " << i << "  ";
         Base::handle( i );   // 3. Delegate to the base class
      } else
         cout << "H1 handled " << i << "  ";
}  };

class Handler2 : public Base { public:
   /*virtual*/ void handle( int i ) {
      if (rand() % 3) { cout << "H2 passsed " << i << "  "; Base::handle( i ); }
      else cout << "H2 handled " << i << "  ";
}  };

class Handler3 : public Base { public:
   /*virtual*/ void handle( int i ) {
      if (rand() % 3) { cout << "H3 passsed " << i << "  "; Base::handle( i ); }
      else cout << "H3 handled " << i << "  ";
}  };

int main_chainofresponsibilty_2( void )
 {
cout<<">>>>>>>> main_chainofresponsibility_2 <<<<<<<<"<<endl;     
   srand( time( 0 ) );
   Handler1 root;   Handler2 two;   Handler3 thr;
   root.add( &two );   root.add( &thr );
   thr.setNext( &root );
   for (int i=1; i < 10; i++) {
      root.handle( i );   cout << '\n';
   }  
return 0;
}

// H1 passsed 1  H2 passsed 1  H3 passsed 1  H1 passsed 1  H2 handled 1
// H1 handled 2
// H1 handled 3
// H1 passsed 4  H2 passsed 4  H3 handled 4
// H1 passsed 5  H2 handled 5
// H1 passsed 6  H2 passsed 6  H3 passsed 6  H1 handled 6
// H1 passsed 7  H2 passsed 7  H3 passsed 7  H1 passsed 7  H2 handled 7
// H1 handled 8
// H1 passsed 9  H2 passsed 9  H3 handled 9




// Purpose.  Chain of Responsibility and Composite

// 1. Put a "next" pointer in the base class
// 2. The "chain" method in the base class always delegates to the next object
// 3. If the derived classes cannot handle, they delegate to the base class

class Component {
   int        value;
   Component* next;             // 1. "next" pointer in the base class
public:
   Component( int v, Component* n ) { value = v;  next = n; }
   void setNext( Component* n )     { next = n; }
   virtual void traverse()          { cout << value << ' '; }
   // 2. The "chain" method in the base class always delegates to the next obj
   virtual void volunteer()         { next->volunteer(); }
};

class Primitive : public Component { public:
   Primitive( int val, Component* n = 0 ) : Component( val, n ) { }
   /*virtual*/ void volunteer() {
      Component::traverse();
      // 3. Primitive objects don't handle volunteer requests 5 times out of 6
      if (rand() * 100 % 6 != 0)
         // 3. Delegate to the base class
         Component::volunteer();
}  };

class Composite : public Component {
   vector<Component*> children;
public:
   Composite( int val, Component* n = 0 ) : Component( val, n ) { }
   void add( Component* c ) { children.push_back( c ); }
   /*virtual*/ void traverse() {
      Component::traverse();
      for (int i=0; i < children.size(); i++)
         children[i]->traverse();
   }
   // 3. Composite objects never handle volunteer requests
   /*virtual*/ void volunteer() { Component::volunteer(); }
};

int main_chainofresponsibilty_3( void ) 
{
   cout<<">>>>>>>> main_chainofresponsibility_3 <<<<<<<<"<<endl;     
   srand( time( 0 ) );                             // 1
   Primitive seven( 7 );                           // |
   Primitive six( 6, &seven );                     // +-- 2
   Composite three( 3, &six );                     // |   |
   three.add( &six );  three.add( &seven );        // |   +-- 4 5
   Primitive five( 5, &three );                    // |
   Primitive four( 4, &five );                     // +-- 3
   Composite two( 2, &four );                      // |   |
   two.add( &four );   two.add( &five );           // |   +-- 6 7
   Composite one( 1, &two );                       // |
   Primitive nine( 9, &one );                      // +-- 8 9
   Primitive eight( 8, &nine );
   one.add( &two );  one.add( &three );  one.add( &eight );  one.add( &nine );
   seven.setNext( &eight );
   cout << "traverse: ";   one.traverse();   cout << '\n';
   for (int i=0; i < 8; i++) {
      one.volunteer();  cout << '\n';
   }  
   return 0;
}

// traverse: 1 2 4 5 3 6 7 8 9
// 4
// 4 5 6 7
// 4 5 6 7 8 9 4 5 6 7 8 9 4
// 4
// 4 5 6
// 4 5
// 4 5
// 4 5 6 7 8 9 4 5 6 7 8 9 4 5 6




// Purpose.  Chain of Responsibility - links bid on job, chain assigns job
//
// 1. Base class maintains a "next" pointer
// 2. Each "link" does its part to handle (and/or pass on) the request
// 3. Client "launches and leaves" each request with the chain
// 4. The current bid and bidder are maintained in chain static members
// 5. The last link in the chain assigns the job to the low bidder



class Link {
   int   id;
   Link* next;                       // 1. "next" pointer
   static int   theBid;              // 4. Current bid and bidder
   static Link* bidder;
public:
   Link( int num ) { id = num;  next = 0; }
   void addLast( Link* l ) {
      if (next) next->addLast( l );  // 2. Handle and/or pass on
      else      next = l; 
   }
   void bid() {
      int num = rand() % 9;
      cout << id << '-' << num << "  ";
      if (num < theBid) {
         theBid = num;               // 4. Current bid and bidder
         bidder = this;
      }
      if (next) next->bid();         // 2. Handle and/or pass on
      else      bidder->execute();   // 5. The last 1 assigns the job
   }
   void execute() {
      cout << id << " is executing\n";
      theBid = 999;
}  };
int   Link::theBid = 999;            // 4. Current bid and bidder
Link* Link::bidder = 0;

int main_chainofresponsibilty_4( void ) 
{
      main_chainofresponsibilty_2();
      main_chainofresponsibilty_3();
      cout<<">>>>>>>> main_chainofresponsibility_4 <<<<<<<<"<<endl;     
   Link chain( 1 );
   for (int i=2; i < 7; i++)
      chain.addLast( new Link( i ) );
   srand( time( 0 ) );
   for (int i=0; i < 10; i++)
      chain.bid();                   // 3. Client "launches & leaves"
return 0;
}

// 1-1  2-6  3-0  4-3  5-1  6-0  3 is executing
// 1-1  2-1  3-1  4-0  5-7  6-1  4 is executing
// 1-0  2-1  3-0  4-6  5-1  6-2  1 is executing
// 1-6  2-3  3-8  4-0  5-1  6-4  4 is executing
// 1-8  2-0  3-5  4-8  5-4  6-2  2 is executing
// 1-1  2-0  3-8  4-8  5-7  6-0  2 is executing
// 1-1  2-1  3-3  4-1  5-6  6-2  1 is executing
// 1-2  2-1  3-0  4-3  5-6  6-8  3 is executing
// 1-7  2-5  3-4  4-2  5-1  6-2  5 is executing
// 1-3  2-6  3-7  4-7  5-6  6-0  6 is executing