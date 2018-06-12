// Purpose.  Adapter design pattern demo
// 
// Discussion.  LegacyRectangle's interface is not compatible with the system that would like to reuse it. 
// An abstract base class is created that specifies the desired interface.  
// An "adapter" class is defined that publicly inherits the interface of the abstract class, and privately inherits the implementation of the legacy component.  
// This adapter class "maps" or "impedance matches" the new interface to the old implementation.

#include "CommonInclude.h"
#include <time.h>

typedef int Coordinate;
typedef int Dimension;

/////////////////////////// Desired interface ///////////////////////////
class Rectangle {
public:
   virtual void draw() = 0;
};

/////////////////////////// Legacy component ///////////////////////////
class LegacyRectangle {
public:
   LegacyRectangle( Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2 ) 
   {
      x1_ = x1;  y1_ = y1;  x2_ = x2;  y2_ = y2;
      cout << "LegacyRectangle:  create.  (" << x1_ << "," << y1_ << ") => (" << x2_ << "," << y2_ << ")" << endl; 
   }
   void oldDraw() 
   {
      cout << "LegacyRectangle:  oldDraw.  (" << x1_ << "," << y1_ << ") => (" << x2_ << "," << y2_ << ")" << endl; 
   }
private:
   Coordinate x1_;
   Coordinate y1_;
   Coordinate x2_;
   Coordinate y2_;
};

/////////////////////////// Adapter wrapper ///////////////////////////
// An "adapter" class is defined that publicly inherits the interface of the abstract class, and privately inherits the implementation of the legacy component.  
class RectangleAdapter : public Rectangle, private LegacyRectangle {      
public:
   RectangleAdapter( Coordinate x, Coordinate y, Dimension w, Dimension h ) : LegacyRectangle( x, y, x+w, y+h ) 
   {
      cout << "RectangleAdapter: create.  (" << x << "," << y << "), width = " << w << ", height = " << h << endl; 
   }
   virtual void draw() {
      cout << "RectangleAdapter: draw." << endl;
      oldDraw(); 
      }
};

int main_legacy() 
{
  cout<<">>>>>>>> main_legacy <<<<<<<<"<<endl; 
   Rectangle*  r = new RectangleAdapter( 120, 200, 60, 40 );
   r->draw();
   return 0;
}
// output: 
// LegacyRectangle:  create.  (120,200) => (180,240)
// RectangleAdapter: create.  (120,200), width = 60, height = 40
// RectangleAdapter: draw.
// LegacyRectangle:  oldDraw.  (120,200) => (180,240)



// Purpose.  Adapter design pattern (External Polymorphism demo)
// 1. Specify the new desired interface
// 2. Design a "wrapper" class that can "impedance match" the old to the new
// 3. The client uses (is coupled to) the new interface
// 4. The adapter/wrapper "maps" to the legacy implementation

// 1. Specify the new i/f
class ExecuteInterface { public:                  
   virtual ~ExecuteInterface() { }
   virtual void execute() = 0;
};

// 2. Design a "wrapper" or "adapter" class
template <class TYPE>                             
class ExecuteAdapter : public ExecuteInterface {  
public:
   ExecuteAdapter( TYPE* o, void (TYPE::*m)() ) 
   { 
      object = o; 
      method = m; 
    }
   ~ExecuteAdapter() 
   { 
      delete object; 
   }
   // 4. The adapter/wrapper "maps" the new to the legacy implementation
   void execute()            
    /* the new */     
   {
      (object->*method)();
   }
private:                             
   TYPE* object; // ptr-to-object attribute
   void (TYPE::*method)();    /* the old */       // ptr-to-member-function attribute
};                                                

// The old: three totally incompatible classes // no common base class, // no hope of polymorphism
class Fea { public:                               
   ~Fea()        { cout << "Fea::dtor" << endl; }
   void doThis() { cout << "Fea::doThis()" << endl; }
};

class Feye { public:
   ~Feye()       { cout << "Feye::dtor" << endl; }
   void doThat() { cout << "Feye::doThat()" << endl; }
};

class Pheau { public:
   ~Pheau()          { cout << "Pheau::dtor" << endl; }
   void doTheOther() { cout << "Pheau::doTheOther()" << endl; }
};

/* the new is returned */ 
ExecuteInterface** initialize() 
{
   ExecuteInterface** array = new ExecuteInterface*[3]; /* the old is below */
   array[0] = new ExecuteAdapter<Fea>(   new Fea(),     &Fea::doThis       );
   array[1] = new ExecuteAdapter<Feye>(  new Feye(),    &Feye::doThat      );
   array[2] = new ExecuteAdapter<Pheau>( new Pheau(),   &Pheau::doTheOther );
   return array;
}

int main_external_polymorphism( void ) 
{

  
   main_legacy();
   cout<<">>>>>>>> main_external_polymorphism <<<<<<<<"<<endl; 
   
   //external_polymorphism   
   ExecuteInterface** objects = initialize();

   for (int i=0; i < 3; i++) objects[i]->execute();  // 3. Client uses the new
                                                     //    (polymporphism)
   for (int i=0; i < 3; i++) delete objects[i];
   delete objects;
   return 0;
}

//output: 
// Fea::doThis()
// Feye::doThat()
// Pheau::doTheOther()
// Fea::dtor
// Feye::dtor
// Pheau::dtor