#include "CommonInclude.h"
// Purpose.  TypedMessage - embellished Observer, decoupled messaging
//
// Messages inherit from TypedMessage<self>
// Message listeners inherit from many Message::Handlers
// Application tells message to publish/broadcast/notify
// Messages are the subject (receive registrations from subscribers)
// Subsystems are the observers (receive broadcast messages)
// TypedMessage accomodates everything: registration, containment, and notification of observers

template <class T>

class TypedMessage {
   static vector<Handler*> registry;
public:
   class Handler
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

class On : public TypedMessage<On>  
{
   string comment;
public:
   On( string str )   { comment = str; }
   void start() const { cout << "OnEvent.start - " << comment << '\n'; }
};
vector<TypedMessage<On>::Handler*> TypedMessage<On>::registry; //TODO:
//declaration is incompatible with "std::__1::vector<<error-type> *, std::__1::allocator<<error-type> *>> TypedMessage<T>::registry [with T=On]" (declared at line 14)

class Off : public TypedMessage<Off>  {
   string comment;
public:
   Off( string str ) { comment = str; }
   void stop() const { cout << "OffEvent.stop - " << comment << '\n'; }
};
vector<TypedMessage<Off>::Handler*> TypedMessage<Off>::registry; //TODO:

class MasterConsole : public On::Handler, public Off::Handler 
{ 
public:
   void handleEvent( const On* msg ) {
      cout << "MasterConsole - ";  msg->start(); }
   void handleEvent( const Off* msg ) {
      cout << "MasterConsole - ";  msg->stop(); }
};

class PowerMonitor : public On::Handler
{ 
    public:
   void handleEvent( const On* msg ) {
      cout << "PowerMonitor - ";  msg->start(); }
};

int main_observer_4( void ) 
{
   cout<<">>>>>>>> main_observer_4 <<<<<<<<"<<endl;
   MasterConsole  mc;
   PowerMonitor   pm;
   On oneEvent( "lights" ); 
   Off thrEvent( "elevators" );
   On twoEvent( "hvac" );    
   Off fouEvent( "frontDoor" ); 
   oneEvent.notify();  
   twoEvent.notify();
   thrEvent.notify(); 
   fouEvent.notify();
   return 0;
}

// MasterConsole - OnEvent.start - lights
// PowerMonitor - OnEvent.start - lights
// MasterConsole - OnEvent.start - hvac
// PowerMonitor - OnEvent.start - hvac
// MasterConsole - OffEvent.stop - elevators
// MasterConsole - OffEvent.stop - frontDoor



