
// Purpose.  Visitor (double dispatch)
//
// Discussion.  On the left, the State derived classes must query the type of
// the Cmd objects they receive, in order to identify what the next course of
// action is.  "case" stmts are always a maintenance headache.  On the right,
// we have recognized that what we really want to do is "dispatch" based on
// the type of TWO objects, (a State object and a Cmd object).  The call to
// accept() discriminates the type of the State object that is being messaged,
// and then the call to visit() discriminates the type of the Cmd object
// (while passing the type of the State object).  If new Cmd classes are
// added, no change whatsoever is necessary in the code of the State classes.
// If new State classes are added, then every Cmd class must be changed, and
// Visitor is NOT the right approach to take.

#include <iostream>        
using std::cout;
using std::endl;
           
int  current = 0;                       
enum CmdTyp { OnT, OffT };              
class Cmd { public:                     
   virtual CmdTyp typ() = 0;            
};                                      
class On : public Cmd { public:         
   CmdTyp typ() { return OnT; }         
};                                      
class Off : public Cmd { public:        
   CmdTyp typ() { return OffT; }        
};                                      
                                        
class State { public:                   
   virtual void process( Cmd* c ) {     
      cout << "ERROR\n"; }              
};                                      
class One : public State { public:      
   void process( Cmd* c ) {             
      if (c->typ() == OnT) {            
         current = 1;                   
         cout << "One,On => Two\n"; }   
      else if (c->typ() == OffT)        
         State::process( c );
   }                                    
};                                      
class Two : public State { public:      
   void process( Cmd* c ) {             
      if (c->typ() == OnT)              
         State::process( c );           
      else if (c->typ() == OffT) {      
         current = 0;                   
         cout << "Two,Off => One\n"; }  
   }                                    
};                                      
State* states[] = { new One, new Two }; 
int main_visitor_3( void )                       
{                                       
   Cmd* c[] = { new Off,                
        new On, new Off, new Off, 0 };  
   for (int i=0; c[i]; i++)             
      states[current]->process( c[i] ); 
}                                       
// ERROR                                
// One,On => Two                        
// Two,Off => One                       
// ERROR                                