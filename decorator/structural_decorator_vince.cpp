// Purpose.  Decorator design patterns
// 1. Create a "lowest common denominator" that makes classes interchangeable
// 2. Create a second level base class for optional functionality
// 3. "Core" class and "Decorator" class declare an "isa" relationship
// 4. Decorator class "hasa" instance of the "lowest common denominator"
// 5. Decorator class delegates to the "hasa" object
// 6. Create a Decorator derived class for each optional embellishment
// 7. Decorator derived classes delegate to base class AND add extra stuf
// 8. Client has the responsibility to compose desired configurations

#include <iostream>
using namespace std;


// 1. "lowest common denominator"
class Widget { public: virtual void draw() = 0; };  

// 3. "Core" class & "isa"
class TextField : public Widget {                   
   int width, height;
 public:
   TextField( int w, int h ) { width  = w;  height = h; }
   /*virtual*/ void draw() { cout << "TextField: " << width << ", " << height << '\n'; }
};

// 2. 2nd level base class                                                   
class Decorator1 : public Widget {// 3. "isa" relationship
   Widget* wid;// 4. "hasa" relationship
 public:
   Decorator1( Widget* w )  { wid = w; }
   /*virtual*/ void draw() { wid->draw(); }// 5. Delegation
};

// 6. Optional embellishment
class BorderDecorator : public Decorator1 {
 public:  
   BorderDecorator( Widget* w ) : Decorator1( w ) { }
   /*virtual*/ void draw() {
      Decorator1::draw();  // 7. Delegate to base class
      cout << "   BorderDecorator" << '\n'; //    and add extra stuff
      }  
};

// 6. Optional embellishment
class ScrollDecorator : public Decorator1 { 
 public:  
   ScrollDecorator( Widget* w ) : Decorator1( w ) { }
   /*virtual*/ void draw() {
      Decorator1::draw(); // 7. Delegate to base class
      cout << "   ScrollDecorator" << '\n'; //and add extra stuff
      }
};

int main_decorator_Vince_1() {
   // 8. Client has the responsibility to compose desired configurations
   Widget* aWidget = new BorderDecorator(
                        new BorderDecorator(
                           new ScrollDecorator(
                              new TextField( 80, 24 ))));
   aWidget->draw();
   return 0;
}

// TextField: 80, 24
//    ScrollDecorator
//    BorderDecorator
//    BorderDecorator

// Purpose.  Inheritance run amok
class A1 { 
    public:
        virtual void doIt() { cout << "A1"; }
};

class AwithX : public A1 {
   void doX() { cout << 'X'; }
public:
   /*virtual*/ void doIt() {
      A1::doIt();
      doX();
}  };

class AwithY : public A1 {
protected:
   void doY() { cout << 'Y'; }
public:
   /*virtual*/ void doIt() {
      A1::doIt();
      doY();
}  };

class AwithZ : public A1 {
protected:
   void doZ() { cout << 'Z'; }
public:
   /*virtual*/ void doIt() {
      A1::doIt();
      doZ();
}  };

class AwithXY : public AwithX, public AwithY { public:
   /*virtual*/ void doIt() {
      AwithX::doIt();
      AwithY::doY();
}  };

class AwithXYZ : public AwithX, public AwithY, public AwithZ { public:
   /*virtual*/ void doIt() {
      AwithX::doIt();
      AwithY::doY();
      AwithZ::doZ();
}  };

int main_inheritance_amok() {
   AwithX    anX;
   AwithXY   anXY;
   AwithXYZ  anXYZ;
   anX.doIt();    cout << '\n';
   anXY.doIt();   cout << '\n';
   anXYZ.doIt();  cout << '\n';
   return 0;
}

// AX
// AXY
// AXYZ

// Purpose.  Replacing inheritance with wrapping-delegation
//
// Discussion.  Use aggregation instead of inheritance to implement embellishments to a "core" object.  
// Client can dynamically compose permutations, instead of the architect statically wielding multiple inheritance.

class I { public:
   virtual ~I() { }
   virtual void doIt() = 0;
};

class A : public I { 
 public:
   ~A() { cout << "A dtor" << '\n'; }
   /*virtual*/ void doIt() { cout << 'A'; }
};

class D : public I {
   I* wrappee;
public:
   D( I* inner )           { wrappee = inner; }
   ~D()                    { delete wrappee; }
   /*virtual*/ void doIt() { wrappee->doIt(); }
};

class X : public D { public:
   X( I* core ) : D(core) { }
   ~X() { cout << "X dtor" << "   "; }
   /*virtual*/ void doIt() { D::doIt();  cout << 'X'; }
};

class Y : public D { public:
   Y( I* core ) : D(core) { }
   ~Y() { cout << "Y dtor" << "   "; }
   /*virtual*/ void doIt() { D::doIt();  cout << 'Y'; }
};

class Z : public D { public:
   Z( I* core ) : D(core) { }
   ~Z() { cout << "Z dtor" << "   "; }
   /*virtual*/ void doIt() { D::doIt();  cout << 'Z'; }
};

int main_decorator_vince( void ) {
   I* anX = new X( new A );
   I* anXY = new Y( new X( new A ) );
   I* anXYZ = new Z( new Y( new X( new A ) ) );
   anX->doIt();    cout << '\n';
   anXY->doIt();   cout << '\n';
   anXYZ->doIt();  cout << '\n';
   delete anX;   delete anXY;   delete anXYZ;
   return 0;
}

// AX
// AXY
// AXYZ
// X dtor   A dtor
// Y dtor   X dtor   A dtor
// Z dtor   Y dtor   X dtor   A dtor




// // Purpose.  Decorator - encoding and decoding layers of header/packet/trailer
class Interface { public:
   virtual ~Interface() { }
   virtual void write( string& ) = 0;
   virtual void read(  string& ) = 0;
};

class Core : public Interface { public:
   ~Core() { cout << "dtor-Core\n"; }
   /*virtual*/ void write( string& b ) { b += "MESSAGE|"; }
   /*virtual*/ void read( string& );
};

class Decorator : public Interface {
   Interface* inner;
public:
   Decorator( Interface* c ) { inner = c; }
   ~Decorator()              { delete inner; }
   /*virtual*/ void write( string& b ) { inner->write( b ); }
   /*virtual*/ void read(  string& b ) { inner->read( b ); }
};

class Wrapper : public Decorator {
   string forward, backward;
public:
   Wrapper( Interface* c, string str ) : Decorator(c) {
      forward = str;
      string::reverse_iterator it;
      it = str.rbegin();
      for ( ; it != str.rend(); ++it)
         backward += *it;
   }
   ~Wrapper() { cout << "dtor-" << forward << "  "; }
   void write( string& );
   void read(  string& );
};

int main_decorator_vince_2( void ) {
   Interface* object = new Wrapper( new Wrapper( new Wrapper(
                          new Core(), "123" ), "abc" ), "987" );
   string buf;
   object->write( buf );
   cout << "main: " << buf << endl;
   object->read( buf );
   delete object;
   return 0;
}

// main: 987]abc]123]MESSAGE|321]cba]789]
// Wrapper: 987
// Wrapper: abc
// Wrapper: 123
// Core: MESSAGE
// Wrapper: 321
// Wrapper: cba
// Wrapper: 789
// dtor-987  dtor-abc  dtor-123  dtor-Core

void Core::read(string& b) {
   int num = b.find_first_of( '|' );
   cout << "Core: " << b.substr(0,num) << '\n';
   b = b.substr(num+1);
}

void Wrapper::write( string& b ) {
   b += forward + "]";
   Decorator::write( b );
   b += backward + "]";
}

void Wrapper::read( string& b ) {
   int num = b.find_first_of( ']' );
   cout << "Wrapper: " << b.substr(0,num) << '\n';
   b = b.substr(num+1);
   Decorator::read( b );
   num = b.find_first_of( ']' );
   cout << "Wrapper: " << b.substr(0,num) << '\n';
   b = b.substr(num+1);
}