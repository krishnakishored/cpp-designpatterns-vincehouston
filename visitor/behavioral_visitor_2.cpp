#include <iostream>
using std::cout;
using std::endl;

class Visitor;
class Color { public:
   virtual void accept( Visitor& ) = 0;
};
class Red : public Color { public:
   void accept( Visitor& );
   void eye() { cout << "Red::eye\n"; }
};
class Blu : public Color { public:
   void accept( Visitor& );
   void sky() { cout << "Blu::sky\n"; }
};
class Visitor { public:
   virtual void visit( Red& ) = 0;
   virtual void visit( Blu& ) = 0;
};
class CountV : public Visitor {
public:
   CountV() { numRed_ = numBlu_ = 0; }
   virtual void visit( Red& ) {
      numRed_++; }
   virtual void visit( Blu& ) {
      numBlu_++; }
   void reportNum() {
      cout << "Reds " << numRed_ <<
      ", Blus " << numBlu_ << endl; }
private:
   int  numRed_, numBlu_;
};
class CallV : public Visitor { public:
   virtual void visit( Red& r ) {
      r.eye(); }
   virtual void visit( Blu& b ) {
      b.sky(); }
};
void Red::accept( Visitor& v ) {
   v.visit( *this ); }
void Blu::accept( Visitor& v ) {
   v.visit( *this ); }
int main( void )
{
   Color* set[] = { new Red, new Blu,
      new Blu, new Red, new Red, 0 };
   CountV  countOp;
   CallV   callOp;
   for (int i=0; set[i]; i++) {
      set[i]->accept( countOp );
      set[i]->accept( callOp ); }
    countOp.reportNum();
}
// Red::eye
// Blu::sky
// Blu::sky
// Red::eye
// Red::eye
// Reds 3, Blus 2