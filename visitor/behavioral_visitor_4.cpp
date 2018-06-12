#include <iostream>
using std::cout;
using std::endl;

int  current = 0;
class One;  class Two;
class Cmd { public:
   virtual void visit( One* ) {
      cout << "ERROR\n"; }
   virtual void visit( Two* ) {
      cout << "ERROR\n"; }
};
class On : public Cmd { public:
   void visit( One* ) {
      current = 1;
      cout << "One,On => Two\n"; }
   void visit( Two* t ) {
      Cmd::visit( t ); }
};
class Off : public Cmd { public:
   void visit( One* o ) {
      Cmd::visit( o ); }
   void visit( Two* ) {
      current = 0;
      cout << "Two,Off => One\n"; }
};
class State { public:
   virtual void accept( Cmd* c ) = 0;
};
class One : public State { public:
   void accept( Cmd* c ) {
      c->visit( this ); }
};
class Two : public State { public:
   void accept( Cmd* c ) {
      c->visit( this ); }
};
State* states[] = { new One, new Two };
int main_visitor_4( void )
{
   Cmd* c[] = { new Off,
        new On, new Off, new Off, 0 };
   for (int i=0; c[i]; i++)
      states[current]->accept( c[i] );
 return 0;
}
// ERROR
// One,On => Two
// Two,Off => One
// ERROR