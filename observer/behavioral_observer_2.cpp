#include<iostream>
#include<vector>
#include<string>

using std::cout;
using std::vector;
using std::string;
using std::cin;
using std::endl;



// Purpose.  Observer design pattern

// 1. Model the "independent" functionality with a "subject" abstraction
// 2. Model the "dependent" functionality with "observer" hierarchy
// 3. The Subject is coupled only to the Observer base class
// 4. Observers register themselves with the Subject
// 5. The Subject broadcasts events to all registered Observers
// 6. Observers "pull" the information they need from the Subject
// 7. Client configures the number and type of Observers

class Observer1;
class Subject {                      // 1. "independent" functionality
   vector<class Observer1*> views;    // 3. Coupled only to "interface"
   int value;
public:
   void attach( Observer1* obs ) { views.push_back( obs ); }
   void setVal( int val )       { value = val;  notify(); }
   int  getVal()                { return value; }
   void notify();
};

class Observer1 {                     // 2. "dependent" functionality
   Subject* model;
   int      denom;
public:
   Observer1( Subject* mod, int div ) {
      model = mod;  denom = div;
      // 4. Observers register themselves with the Subject
      model->attach( this );
   }
   virtual void update() = 0;
protected:
   Subject* getSubject() { return model; }
   int      getDivisor() { return denom; }
};

void Subject::notify() {             // 5. Publisher broadcasts
   for (int i=0; i < views.size(); i++) views[i]->update();
}

class DivObserver : public Observer1 { public:
   DivObserver( Subject* mod, int div ) : Observer1(mod,div) { }
   void update() {                   // 6. "Pull" information of interest
      int v = getSubject()->getVal(), d = getDivisor();
      cout << v << " div " << d << " is " << v / d << '\n';
}  };

class ModObserver : public Observer1 { public:
   ModObserver( Subject* mod, int div ) : Observer1(mod,div) { }
   void update() {
      int v = getSubject()->getVal(), d = getDivisor();
      cout << v << " mod " << d << " is " << v % d << '\n';
}  };

int main( void ) {
   Subject      subj;
   DivObserver  divObs1( &subj,4 );  // 7. Client configures the number and
   DivObserver  divObs2( &subj,3 );  //    type of Observers
   ModObserver  modObs3( &subj,3 );
   subj.setVal( 14 );
   return 0;
}

// 14 div 4 is 3
// 14 div 3 is 4
// 14 mod 3 is 2






// Purpose.  Observer design pattern, class inheritance vs type inheritance

// SensorSystem is the "subject".  Lighting, Gates, and Surveillance are the
// "views".  The subject is only coupled to the "abstraction" of AlarmListener.

// An object's class defines how the object is implemented.  In contrast, an
// object's type only refers to its interface.  Class inheritance defines an
// object's implementation in terms of another object's implementation.  Type
// inheritance describes when an object can be used in place of another.
// [GoF, pp13-17]



class AlarmListener { public: virtual void alarm() = 0; };

class SensorSystem {
   vector<AlarmListener*> listeners;
public:
   void attach( AlarmListener* al ) { listeners.push_back( al ); }
   void soundTheAlarm() {
      for (int i=0; i < listeners.size(); i++)
         listeners[i]->alarm();
}  };

class Lighting : public AlarmListener {
   public: /*virtual*/ void alarm() { cout << "lights up" << '\n'; }
};

class Gates : public AlarmListener {
   public: /*virtual*/ void alarm() { cout << "gates close" << '\n'; }
};

class CheckList {
   virtual void localize() { cout << "   establish a perimeter" << '\n'; }
   virtual void isolate()  { cout << "   isolate the grid"      << '\n'; }
   virtual void identify() { cout << "   identify the source"   << '\n'; }
public:
   void byTheNumbers() {  // Template Method design pattern
      localize();
      isolate();
      identify();
}  };
                     // class inheri.  // type inheritance
class Surveillance : public CheckList, public AlarmListener {
   /*virtual*/ void isolate() { cout << "   train the cameras" << '\n'; }
public:
   /*virtual*/ void alarm() {
      cout << "Surveillance - by the numbers:" << '\n';
      byTheNumbers();
}  };

int main_observer_2( void ) {
   SensorSystem ss;
   ss.attach( &Gates()        ); //message taking the address of a temporary object of type 'Lighting' [-Waddress-of-temporary]
   ss.attach( &Lighting()     );
   ss.attach( &Surveillance() );
   ss.soundTheAlarm();
}

// gates close
// lights up
// Surveillance - by the numbers:
//    establish a perimeter
//    train the cameras
//    identify the source




// Purpose.  Observer and Mediator demo
// 
// Observer - 1. Sender is coupled to a Receiver interface
//            2. Receivers register with Sender
//            3. Sender broadcasts (in the blind) to all Receivers
// 
// Mediator - 4. Sender(s) has handle to Mediator
//            5. Mediator has handle to Receiver(s)
//            6. Sender(s) sends to Mediator
//            7. Mediator sends to Receiver(s)


void gotoxy( int, int );

class Observer { public: virtual void update( int ) = 0; };

class Mediator {
   vector<Observer*> groups[3];         // 1. Sender is coupled to an interface
public:
   enum Message { ODD, EVEN, THREE };   // 1. Sender is coupled to an interface
   void attach( Observer* o, Message type ) { groups[type].push_back( o ); }
   void disseminate( int num ) {
         if (num % 2 == 1)  // odd      // 3,7. Sender/Mediator broadcasts
            for (int i=0; i < groups[0].size(); i++) groups[0][i]->update(num);
         else               // even
            for (int i=0; i < groups[1].size(); i++) groups[1][i]->update(num);
         if (num % 3 == 0)  // /3
            for (int i=0; i < groups[2].size(); i++) groups[2][i]->update(num);
}  };

class OddObserver : public Observer {
   int col, row;
public:
   OddObserver( Mediator& med, int c ) {
      col = c;           row = 3;
      gotoxy( col, 1 );  cout << "Odd";
      gotoxy( col, 2 );  cout << "---";
      med.attach( this, Mediator::ODD );  // 2,5. Receivers register with Sender
   }
   void update( int num ) { gotoxy( col, row++ );  cout << num; }
};

class EvenObserver : public Observer {
   int col, row;
public:
   EvenObserver( Mediator& med, int c ) {
      col = c;           row = 3;
      gotoxy( col, 1 );  cout << "/2";
      gotoxy( col, 2 );  cout << "--";
      med.attach( this, Mediator::EVEN );
   }
   void update( int num ) { gotoxy( col, row++ );  cout << num; }
};

class ThreeObserver : public Observer {
   int col, row;
public:
   ThreeObserver( Mediator& med, int c ) {
      col = c;           row = 3;
      gotoxy( col, 1 );  cout << "/3";
      gotoxy( col, 2 );  cout << "--";
      med.attach( this, Mediator::THREE );
   }
   void update( int num ) { gotoxy( col, row++ );  cout << num; }
};

class Publisher { public:            // 6. Sender sends to Mediator
   Publisher( Mediator& med ) { for (int i=1; i < 10; i++) med.disseminate(i); }
};

int main_observer_3( void ) {
   Mediator   mediator;
   OddObserver(   mediator,  1 );
   EvenObserver(  mediator, 11 );
   ThreeObserver( mediator, 21 );
   Publisher  producer( mediator );  // 4. Sender has handle to Mediator
   return 0;
}

// Odd       /2        /3
// ---       --        --
// 1         2         3
// 3         4         6
// 5         6         9
// 7         8
// 9




// Purpose.  TypedMessage - embellished Observer, decoupled messaging
//
// Messages inherit from TypedMessage<self>
// Message listeners inherit from many Message::Handlers
// Application tells message to publish/broadcast/notify
// Messages are the subject (receive registrations from subscribers)
// Subsystems are the observers (receive broadcast messages)
// TypedMessage accomodates everything: registration, containment, and
//   notification of observers



template <class T>
class TypedMessage {
   static vector<Handler*> registry;
public:
   class 
    {
   public:
      Handler() { TypedMessage<T>::registerHandler( this ); }
      virtual void handleEvent( const T* t ) = 0;
   };
   void notify() {
      for (int i=0; i < registry.size(); i++)
         registry.at(i)->handleEvent( (T*)this );
   }
   static void registerHandler( Handler* h ) { registry.push_back( h ); }
};

class On : public TypedMessage<On>  {
   string comment;
public:
   On( string str )   { comment = str; }
   void start() const { cout << "OnEvent.start - " << comment << '\n'; }
};
vector<TypedMessage<On>::Handler*> TypedMessage<On>::registry;

class Off : public TypedMessage<Off>  {
   string comment;
public:
   Off( string str ) { comment = str; }
   void stop() const { cout << "OffEvent.stop - " << comment << '\n'; }
};
vector<TypedMessage<Off>::Handler*> TypedMessage<Off>::registry;

class MasterConsole : public On::Handler, public Off::Handler { 
    public:
   void handleEvent( const On* msg ) {
      cout << "MasterConsole - ";  msg->start(); }
   void handleEvent( const Off* msg ) {
      cout << "MasterConsole - ";  msg->stop(); }
};

class PowerMonitor : public On::Handler{ 
    public:
   void handleEvent( const On* msg ) {
      cout << "PowerMonitor - ";  msg->start(); }
};

int main( void ) {
   MasterConsole  mc;
   PowerMonitor   pm;
   On oneEvent( "lights" );  Off thrEvent( "elevators" );
   On twoEvent( "hvac" );    Off fouEvent( "frontDoor" ); 
   oneEvent.notify();  twoEvent.notify();
   thrEvent.notify();  fouEvent.notify();
   return 0;
}

// MasterConsole - OnEvent.start - lights
// PowerMonitor - OnEvent.start - lights
// MasterConsole - OnEvent.start - hvac
// PowerMonitor - OnEvent.start - hvac
// MasterConsole - OffEvent.stop - elevators
// MasterConsole - OffEvent.stop - frontDoor



