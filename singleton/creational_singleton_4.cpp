                                        
 #include <iostream>         
 using namespace std;  
 
class GlobalClass;
class SingDest {
public:
   SingDest( GlobalClass* s=0 ) {
      sing_ = s; }
   ~SingDest();
   void setSing( GlobalClass* s ) {
      sing_ = s; }
private:
   GlobalClass*  sing_;
};
class GlobalClass {
public:
   friend class SingDest;
   int  getValue() { return value_; }
   void setValue( int v ) {
      value_ = v; }
   static GlobalClass* inst() {
      if ( ! globalObj_ ) {
         globalObj_ = new GlobalClass;
         dest_.setSing( globalObj_ ); }
      return globalObj_; }
private:
   GlobalClass( int v=0 ) {
      cout << ":ctor: ";
      value_ = v; }
   ~GlobalClass() {
      cout << ":dtor:" << endl; }
   int    value_;
   static GlobalClass* globalObj_;
   static SingDest dest_;
};
GlobalClass*
   GlobalClass::globalObj_ = 0;
SingDest GlobalClass::dest_;
SingDest::~SingDest() { delete sing_; }
void foo( void ) {
   GlobalClass::inst()->setValue( 1 );
   cout << "foo: globalObj is " <<
      GlobalClass::inst()->getValue()
      << endl;
}
void bar( void ) {
   GlobalClass::inst()->setValue( 2 );
   cout << "bar: globalObj is " <<
      GlobalClass::inst()->getValue()
      << endl;
}
int main_singleton_4( void ) {
   cout << "main: globalObj is " <<
      GlobalClass::inst()->getValue()
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