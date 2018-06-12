                                    
#include "CommonHeader.h"
// Purpose.  Simple and "macro" commands
// 
// Discussion.  Encapsulate a request as an object.  
// SimpleCommand maintains a binding between a receiver object and an action stored as a pointer to a member function. 
// MacroCommand maintains a sequence of Commands.  
// No explicit receiver is required because the subcommands already define their receiver.  MacroCommand may contain MacroCommands.


class Number { 
 public:
   void dubble( int& value ) { value *= 2; }
};

class Command1 { 
public: virtual void execute( int& ) = 0; 
};

class SimpleCommand : public Command1 
{
   typedef void (Number::* Action)(int&);
   Number* receiver;
   Action  action;
public:
   SimpleCommand( Number* rec, Action act ) {
      receiver = rec;
      action = act;
   }
   /*virtual*/ void execute( int& num ) { (receiver->*action)( num ); }
};

class MacroCommand : public Command1 {
   vector<Command1*> list;
public:
   void add( Command1* cmd ) { list.push_back( cmd ); }
   /*virtual*/ void execute( int& num ) {
      for (int i=0; i < list.size(); i++)
         list[i]->execute( num );
}  };

int main_command_3A( void ) {
   cout<<">>>>>>>> main_command_3A <<<<<<<<"<<endl;  
   Number object;  //TODO:  "taking the address of a temporary object of type 'SimpleCommand' [-Waddress-of-temporary]",
   
   Command1* commands[3];
   
   commands[0] = &SimpleCommand( &object, &Number::dubble );

   MacroCommand two;
   two.add( commands[0] );   
   two.add( commands[0] );
   commands[1] = &two;

   MacroCommand four;
   four.add( &two );   
   four.add( &two );
   commands[2] = &four;

   int num, index;
   while (true) {
      cout << "Enter number selection (0=2x 1=4x 2=16x): ";
      cin >> num >> index;
      commands[index]->execute( num );
      cout << "   " << num << '\n';
}  }

// Enter number selection (0=2x 1=4x 2=16x): 3 0
//    6
// Enter number selection (0=2x 1=4x 2=16x): 3 1
//    12
// Enter number selection (0=2x 1=4x 2=16x): 3 2
//    48
// Enter number selection (0=2x 1=4x 2=16x): 4 0
//    8
// Enter number selection (0=2x 1=4x 2=16x): 4 1
//    16
// Enter number selection (0=2x 1=4x 2=16x): 4 2
//    64




// Purpose.  Command design pattern and inheritance
//
// Discussion.  The Command pattern promotes a deferred method invocation to
// full object status.  Each Command object is a "black box" - it is opaque to
// its holder/user.  Here, a portfolio's heterogeneous collection of financial
// instruments is being treated homogeneously, because, they all inherit from
// a common base class, and, they all have a "convert to currency" method with
// a common signature.

class Instrument { public: virtual ~Instrument() { } };

class IOU : public Instrument {
   int amount;
public:
   IOU( int in ) { amount = in; }
   int payUp() { return amount; }
};

class Check : public Instrument {
   int amount;
public:
   Check( int in ) { amount = in; }
   int cash() { return amount; }
};

class Stock : public Instrument {
   int amount;
public:
   Stock( int in ) { amount = in; }
   int redeem() { return amount; }
};

class Command3 {
public:
   typedef int (Instrument::*Action)();
   Command3( Instrument* o, Action m ) {
      object = o;
      method = m;
   }
   int execute() { return (object->*method)(); }
private:
   Instrument* object;
   Action      method;
};

int main_command_3B( void ) 
{
   cout<<">>>>>>>> main_command_3B <<<<<<<<"<<endl;  
      // error: taking the address of a temporary object of type  .. 
   Command3* portfolio[] = {  // old C cast, or new RTTI is required
      &Command3( &IOU(100),   (int(Instrument::*)())&IOU::payUp ),
      &Command3( &Check(200), static_cast<int(Instrument::*)()>(&Check::cash) ),
      &Command3( &Stock(300), static_cast<int(Instrument::*)()>(&Stock::redeem) ) };
   
   int netWorth,i;
   for (netWorth=0, i=0; i < 3; i++)
      netWorth += portfolio[i]->execute();
   cout << "net worth is now " << netWorth << '\n';
   return 0;
}

// net worth is now 600



