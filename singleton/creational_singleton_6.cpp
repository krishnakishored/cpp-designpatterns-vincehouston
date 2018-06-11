
                                        
 #include <iostream>         
 using namespace std;  

// New design.  "globalObj" is now a
// static variable in the inst() ac-
// cessor method.  The single inst-
// ance is enforced by declaring the
// ctor non-public.  [The dtor must
// be public because of the static
// variable instance.]  Global
// access is provided by the static
// inst() method.  The object is al-
// located on first demand by C++,
// and it is de-allocated automati-
// cally by C++.



class GlobalClass {
public:
   int  getValue() {
      return value_; }
   void setValue( int v ) {
      value_ = v; }
   static GlobalClass& inst() {
      static GlobalClass globalObj;
      return globalObj; }
   ~GlobalClass() {
      cout << ":dtor:" << endl; }
protected:
   GlobalClass( int v=0 ) {
      cout << ":ctor: ";
      value_ = v; }
private:
   int  value_;
};

void foo( void )
{
   GlobalClass::inst().setValue( 1 );
   cout << "foo: globalObj is " <<
      GlobalClass::inst().getValue()
      << endl;
}

void bar( void )
{
   GlobalClass::inst().setValue( 2 );
   cout << "bar: globalObj is " <<
      GlobalClass::inst().getValue()
      << endl;
}

int main_singleton_6( void )
{
   cout << "main: globalObj is " <<
      GlobalClass::inst().getValue()
      << endl;
   foo();
   bar();
   cout << "main: end" << endl;
}

// main: globalObj is :ctor: 0
// foo: globalObj is 1
// bar: globalObj is 2
// main: end
// :dtor:



// Purpose.  Singleton design pattern

// 1. Define a private static attribute in the "single instance" class
// 2. Define a public static accessor function in the class
// 3. Do "lazy initialization" (creation on demand) in the accessor function
// 4. Define all constructors to be protected or private
// 5. Clients may only use the accessor function to manipulate the Singleton
// 6. Inheritance can be supported, but static functions may not be overridden.
//    The base class must be declared a friend of the derived class (in order
//    to access the protected constructor).

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class Number {
public:
   static  Number* instance();      // 2. Define a public static accessor func
   static  void setType( string t ) { type = t;  delete inst;  inst = 0;}
   virtual void setValue( int in )  { value = in; }
   virtual int  getValue()          { return value; }
protected:
   int value;
   Number() { cout << ":ctor: "; }  // 4. Define all ctors to be protected
private:
   static string  type;
   static Number* inst;             // 1. Define a private static attribute
};

string  Number::type = "decimal";
Number* Number::inst = 0;

class Octal : public Number {       // 6. Inheritance can be supported
public:
   friend class Number;
   void setValue( int in ) {
      char buf[10];
      sprintf( buf, "%o", in );
      sscanf( buf, "%d", &value );
   }
protected:
   Octal() { }
};

Number* Number::instance() {
   if ( ! inst)
      // 3. Do "lazy initialization" in the accessor function
      if (type == "octal") inst = new Octal();
      else                 inst = new Number();
   return inst;
}

int main_singleton_6B( void ) {
   // Number  myInstance; --- error: cannot access protected constructor
   // 5. Clients may only use the accessor function to manipulate the Singleton
   Number::instance()->setValue( 42 );
   cout << "value is " << Number::instance()->getValue() << endl;
   Number::setType( "octal" );
   Number::instance()->setValue( 64 );
   cout << "value is " << Number::instance()->getValue() << endl;
}

// :ctor: value is 42
// :ctor: value is 100