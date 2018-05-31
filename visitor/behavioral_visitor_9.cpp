



// Purpose.  Visitor - double dispatch - doing the right thing based on the
// type of two objects

#include <iostream>
#include <string>
using namespace std;

class Request { public:
   // second dispatch - the "visit()" method
   virtual void execute( class P1* ) = 0;
   virtual void execute( class P2* ) = 0;
};
class R1 : public Request { public:
   /*virtual*/ void execute( P1* );
   /*virtual*/ void execute( P2* );
};
class R2 : public Request { public:
   /*virtual*/ void execute( P1* );
   /*virtual*/ void execute( P2* );
};

class Processor { public:
   // first dispatch - the "accept()" method
   virtual void handle( class Request* ) = 0;
};
class P1 : public Processor { public:
   /*virtual*/ void handle( Request* req ) { req->execute( this ); }
   void procOneMethod() { cout << "processor one handling "; }
};
class P2 : public Processor { public:
   /*virtual*/ void handle( Request* req ) { req->execute( this ); }
   void procTwoMethod() { cout << "processor two handling "; }
};

/*virtual*/ void R1::execute( P1* p ) { p->procOneMethod(); cout << "request one\n"; }
/*virtual*/ void R1::execute( P2* p ) { p->procTwoMethod(); cout << "request one\n"; }
/*virtual*/ void R2::execute( P1* p ) { p->procOneMethod(); cout << "request two\n"; }
/*virtual*/ void R2::execute( P2* p ) { p->procTwoMethod(); cout << "request two\n"; }

int main( void ) {
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
