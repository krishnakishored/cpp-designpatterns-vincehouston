



// Purpose.  Acyclic Visitor design pattern [PLOPD vol 3, p93]
//
// Problem.  In GOF Visitor, Element depends on Visitor, Visitor depends on
// all Element derivatives, and Element derivatives depend on Element; this is
// cyclic dependency.  Additionally, adding an Element derivative requires the
// entire Visitor hierarchy to change.  "These problems can be solved by using
// multiple inheritance and dynamic_cast()."
//
// Solution.  Element derived classes are only coupled to Visitor base class.
// Visitor derived classes are only coupled to the Element derived classes that
// they choose to be coupled to.  If a new Element derived class is added,
// Visitor derived classes can update themselves if, and when, they choose.

#include <iostream>
#include <string>
using namespace std;

class Element { public:
   virtual void accept( class Visitor& v ) = 0;
};

class This : public Element { public:
   /*virtual*/ void accept( Visitor& v );
   string thiss() { return "This"; }
};

class That : public Element { public:
   /*virtual*/ void accept( Visitor& v );
   string that() { return "That"; }
};

class TheOther : public Element { public:
   /*virtual*/ void accept( Visitor& v );
   string theOther() { return "TheOther"; }
};

class Visitor { public:
   virtual ~Visitor() { };
};
class ThisVisitor { public:
   virtual void visit( This* e ) = 0;
};
class ThatVisitor { public:
   virtual void visit( That* e ) = 0;
};
class TheOtherVisitor { public:
   virtual void visit( TheOther* e ) = 0;
};

/*virtual*/ void This::accept( Visitor& v ) {
   ThisVisitor* tv = dynamic_cast<ThisVisitor*>( &v );
   if (tv) tv->visit( this );
   else cout << "the visitor was not accepted\n";
}
/*virtual*/ void That::accept( Visitor& v ) {
   ThatVisitor* tv = dynamic_cast<ThatVisitor*>( &v );
   if (tv) tv->visit( this );
   else cout << "the visitor was not accepted\n";
}
/*virtual*/ void TheOther::accept( Visitor& v ) {
   TheOtherVisitor* tv = dynamic_cast<TheOtherVisitor*>( &v );
   if (tv) tv->visit( this );
   else cout << "the visitor was not accepted\n";
}

class UpVisitor : public Visitor, public ThisVisitor, public ThatVisitor,
      public TheOtherVisitor {
   /*virtual*/ void visit( This* e ) {
      cout << "do Up on " + e->thiss() << '\n'; }
   /*virtual*/ void visit( That* e ) {
      cout << "do Up on " + e->that() << '\n'; }
   /*virtual*/ void visit( TheOther* e ) {
      cout << "do Up on " + e->theOther() << '\n'; }
};

class DownVisitor : public Visitor, public ThisVisitor, public ThatVisitor,
      public TheOtherVisitor {
   /*virtual*/ void visit( This* e ) {
      cout << "do Down on " + e->thiss() << '\n'; }
   /*virtual*/ void visit( That* e ) {
      cout << "do Down on " + e->that() << '\n'; }
   /*virtual*/ void visit( TheOther* e ) {
      cout << "do Down on " + e->theOther() << '\n'; }
};

int main( void ) {
   Element* list[] = { new This(), new That(), new TheOther() };
   UpVisitor    up;             // 4. Client creates
   DownVisitor  down;           //    "visitor" objects
   for (int i=0; i < 3; i++)    //    and passes each
      list[i]->accept( up );    //    to accept() calls
   for (int i=0; i < 3; i++)
      list[i]->accept( down );
}

// do Up on This                // do Down on This
// do Up on That                // do Down on That
// do Up on TheOther            // do Down on TheOther