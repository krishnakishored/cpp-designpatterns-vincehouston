#include "CommonHeader.h"


// Purpose.  Observer design pattern, class inheritance vs type inheritance

// SensorSystem is the "subject".  Lighting, Gates, and Surveillance are the "views".  
// The subject is only coupled to the "abstraction" of AlarmListener.

// An object's class defines how the object is implemented.  In contrast, an object's type only refers to its interface.  
// Class inheritance defines an object's implementation in terms of another object's implementation.  
// Type inheritance describes when an object can be used in place of another.
// [GoF, pp13-17]



class AlarmListener { public: virtual void alarm() = 0; };

class SensorSystem 
{
   vector<AlarmListener*> listeners;
public:
   void attach( AlarmListener* al ) { listeners.push_back( al ); }

   void soundTheAlarm() 
   {
      for (int i=0; i < listeners.size(); i++)
         listeners[i]->alarm();
   }  
};

class Lighting : public AlarmListener {
   public: /*virtual*/ void alarm() { cout << "lights up" << '\n'; }
};

class Gates : public AlarmListener {
   public: /*virtual*/ void alarm() { cout << "gates close" << '\n'; }
};

class CheckList 
{
   virtual void localize() { cout << "   establish a perimeter" << '\n'; }
   virtual void isolate()  { cout << "   isolate the grid"      << '\n'; }
   virtual void identify() { cout << "   identify the source"   << '\n'; }
public:
   void byTheNumbers() 
   {  // Template Method design pattern
      localize();
      isolate();
      identify();
   }  
};
                     // class inheri.  // type inheritance
class Surveillance : public CheckList, public AlarmListener {
   /*virtual*/ void isolate() { cout << "   train the cameras" << '\n'; }
public:
   /*virtual*/ void alarm() {
      cout << "Surveillance - by the numbers:" << '\n';
      byTheNumbers();
}  };

int main_observer_2( void ) 
{
   cout<<">>>>>>>> main_observer_2A <<<<<<<<"<<endl;
   SensorSystem ss;
   Gates myGates;
   Lighting myLighting;
   Surveillance mySurveillance;

   ss.attach( &myGates        ); 
   ss.attach( &myLighting     );
  // ss.attach( &Surveillance() );//message taking the address of a temporary object of type 'Lighting' [-Waddress-of-temporary]
   ss.attach( &mySurveillance     );
   ss.soundTheAlarm();
   return 0;
}

// gates close
// lights up
// Surveillance - by the numbers:
//    establish a perimeter
//    train the cameras
//    identify the source