// Purpose.  State                      
//
// Discussion.  The boss's behavior is "morphing" radically as a function of his mood.  Operations have large "case" constructs that depend on     
// this "state" attribute.  Like large procedures, large conditional stmts are undesirable.  They're monolithic, and tend to make maintenance     
// very difficult.  The State pattern models individual states with derived classes of an inheritance hierarchy, and front-ends this       
// hierarchy with an "interface" object that knows its "current" state.  This partitions and localizes all state-specific responsibilities; allowing for a cleaner     
// implementation of dynamic behavior that must change as internal state changes.
#include "CommonHeader.h"

#include <ctime>

class Disposition;

class Boss1 {                            
public:                                 
   Boss1() {                             
      mood_ = DilbertZone;              
   }                                    
   void decide() {                      
      if (mood_ == DilbertZone) {       
         cout << "Eenie, meenie,";      
         cout << " mynie, moe.\n";      
      }                                 
      else if (mood_ == Sunny) {        
         cout << "You need it - you";   
         cout << " got it.\n";          
      }                                 
      toggle();                         
   }                                    
   void direct() {                      
      if (mood_ == DilbertZone) {       
         cout << "My whim - you're";
         cout << " nightmare.\n";       
      }                                 
      else if (mood_ == Sunny)          
         cout << "Follow me.\n";        
      toggle();                         
   }                                    
private:                                
   enum Disposition { Sunny, DilbertZone};
   Disposition  mood_;                  
   void toggle() 
   {
        //mood_ = !mood_;   //message : assigning to 'Boss1::Disposition' from incompatible type 'bool'
   }   
};                                      
                                        
int main_state_1A( void )                      
{   
  cout<<">>>>>>>> main_state_1A <<<<<<<<"<<endl;                                      
   Boss1 ph;                             
   for (int i=0; i < 2; i++)            
   {                                    
      ph.decide();                      
      ph.decide();                      
      ph.direct();                      
   }  
   return 0;                                  
}             


class Boss {
public:
   friend class Disposition;
   Boss();
   void decide();
   void direct();
private:
   Disposition*  moods_[2];
   int           current_;
};
class Disposition {
public:
   virtual void decide( Boss* ) = 0;
   virtual void direct( Boss* ) = 0;
protected:
   void toggle( Boss* b ) {
      b->current_ = ! b->current_; }
};
class DilbertZone :
      public Disposition { public:
   void decide( Boss* b ) {
      cout << "Eenie, meenie, mynie,";
      cout << " moe.\n";  toggle(b); }
   void direct( Boss* b ) {
      cout << "My whim - you're";
      cout << " nightmare.\n";
      toggle(b); }
};
class Sunny :
      public Disposition { public:
   void decide( Boss* b ) {
      cout << "You need it - you got";
      cout << " it.\n";  toggle(b); }
   void direct( Boss* b ) {
      cout << "Follow me.\n";
      toggle(b); }
};
Boss::Boss() {
   moods_[0] = new DilbertZone;
   moods_[1] = new Sunny;
   current_ = 0; }
void Boss::decide() {
   moods_[current_]->decide( this ); }
void Boss::direct() {
   moods_[current_]->direct( this ); }

int main_state_1B( void )
{
  cout<<">>>>>>>> main_state_1B <<<<<<<<"<<endl;  
   Boss ph;
   for (int i=0; i < 2; i++) 
   {
      ph.decide();
      ph.decide();
      ph.direct(); 
    }
    return 0;
}
// Eenie, meenie, mynie, moe.
// You need it - you got it.
// My whim - you're nightmare.
// You need it - you got it.
// Eenie, meenie, mynie, moe.
// Follow me.                          



// Purpose.  State design pattern - an FSM with two states and two events 
// (distributed transition logic - logic in the derived state classes)

           //Event    on      off State \      -------  -------
           // ON          nothing    OFF
           // OFF           ON     nothing
        
                                   
class Machine {                    
   class State* current;
public:
   Machine();
   void setCurrent( State* s ) { current = s; }
   void on();
   void off();
};

class State {
public:
   virtual void on( Machine* m )  { cout << "   already ON\n"; }
   virtual void off( Machine* m ) { cout << "   already OFF\n"; }
};

void Machine::on()  { current->on(  this ); }
void Machine::off() { current->off( this ); }

class ON : public State {
public:
   ON()  { cout << "   ON-ctor ";  };
   virtual ~ON() { cout << "   dtor-ON\n"; };
   void off( Machine* m );
};

class OFF : public State {
public:
   OFF()  { cout << "   OFF-ctor ";  };
   virtual ~OFF() { cout << "   dtor-OFF\n"; };//delete called on non-final 'OFF' that has virtual functions but non-virtual destructor [-Wdelete-non-virtual-dtor]
   void on( Machine* m ) {
      cout << "   going from OFF to ON";
      m->setCurrent( new ON() );
      delete this;
   }
};

void ON::off( Machine* m ) {
   cout << "   going from ON to OFF";
   m->setCurrent( new OFF() );
   delete this;
}

Machine::Machine() { current = new OFF();  cout << '\n'; }

int main_state_1C( void )  
{ 
 main_state_1A();
 main_state_1B();     
 cout<<">>>>>>>> main_state_1C <<<<<<<<"<<endl;  
  Machine fsm;
  int num;
  void (Machine::*ptrs[])() = { &Machine::off, &Machine::on }; 
  //void (Machine::*ptrs[])() = { Machine::off, Machine::on }; // message: call to non-static member function without an object argument
   
   while (1) 
   {
      cout << "Enter 0/1: ";
      cin >> num;
      (fsm.*ptrs[num])();
   }  
return 0;
}

//    OFF-ctor
// Enter 0/1: 0
//    already OFF
// Enter 0/1: 1
//    going from OFF to ON   ON-ctor    dtor-OFF
// Enter 0/1: 1
//    already ON
// Enter 0/1: 0
//    going from ON to OFF   OFF-ctor    dtor-ON
// Enter 0/1: 1
//    going from OFF to ON   ON-ctor    dtor-OFF
// Enter 0/1: 0
//    going from ON to OFF   OFF-ctor    dtor-ON
// Enter 0/1: 0
//    already OFF
// Enter 0/1:


