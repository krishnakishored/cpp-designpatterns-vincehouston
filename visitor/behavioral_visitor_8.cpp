

// Purpose.  Undesireable design - double dispatch - doing the right thing based
// on the type of two objects

#include <iostream>
#include <string>
using namespace std;

class Request { public: virtual string getType() = 0; };

class R1 : public Request { public:
   /*virtual*/ string getType() { return "One"; }
   void reqOneMethod( class P1* );
   void reqOneMethod( class P2* );
};
class R2 : public Request { public:
   /*virtual*/ string getType() { return "Two"; }
   void reqTwoMethod( P1* );
   void reqTwoMethod( P2* );
};

class Processor { public: virtual void handle( class Request* ) = 0; };

class P1 : public Processor { public:
   /*virtual*/ void handle( class Request* req ) {
      if (req->getType() == string("One"))      ((R1*)req)->reqOneMethod( this );
      else if (req->getType() == string("Two")) ((R2*)req)->reqTwoMethod( this );
   }
   void procOneMethod() { cout << "processor one handling "; }
};
class P2 : public Processor { public:
   /*virtual*/ void handle( class Request* req ) {
      if (req->getType() == string("One"))      ((R1*)req)->reqOneMethod( this );
      else if (req->getType() == string("Two")) ((R2*)req)->reqTwoMethod( this );
   }
   void procTwoMethod() { cout << "processor two handling "; }
};

void R1::reqOneMethod( P1* p ) { p->procOneMethod(); cout << "request one\n"; }
void R1::reqOneMethod( P2* p ) { p->procTwoMethod(); cout << "request one\n"; }
void R2::reqTwoMethod( P1* p ) { p->procOneMethod(); cout << "request two\n"; }
void R2::reqTwoMethod( P2* p ) { p->procTwoMethod(); cout << "request two\n"; }

int main_visitor_8( void ) {
   Processor* handlers[] = { new P1(), new P2() };
   Request*   commands[] = { new R1(), new R2() };
   for (int i=0; i < 2; i++)
      for (int j=0; j < 2; j++)
         handlers[i]->handle( commands[j] );
}

// processor one handling request one
// processor one handling request two
// processor two handling request one
// processor two handling request two
