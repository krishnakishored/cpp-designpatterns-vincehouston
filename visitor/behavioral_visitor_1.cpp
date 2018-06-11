// Purpose.  Visitor (adding ops)       
//                                      
// Discussion.  On the left, adding
// new operations requires modifying    
// all the current Color classes.  If   
// we introduce an extra level of in-   
// direction (a Visitor hierarchy),
// then operations capable of opera-    
// ting on Color classes can be added   
// without modifying any existing       
// code.  On the right, an entry point  
// for all future operations has been   
// added in the form of the accept()    
// method.  Each of the previous op-    
// erations has been encapsulated in    
// its own derived Visitor class.  Any
// new operations simply require the    
// addition of a new Visitor class.     
//                                      
// When we call accept() on a Color     
// object, dynamic binding gets us to
// the correct derived class of Color.  
// Then when we call visit() on the     
// Visitor object, dynamic binding      
// gets us to the correct derived       
// class of Visitor.  [Visitors and     
// Colors can be passed by address or   
// passed by reference.]                
                                        
#include <iostream>                   

using std::cout;
using std::endl;

class Color {                           
public:                                 
   virtual void count() = 0;            
   virtual void call()  = 0;
   static void reportNum() {            
      cout << "Reds " << numRed_ <<     
      ", Blus " << numBlu_ <<endl; }    
protected:                              
   static int numRed_, numBlu_;         
};                                      
int Color::numRed_ = 0;
int Color::numBlu_ = 0;                 
                                        
class Red : public Color { public:      
   void count() { numRed_++; }          
   void call() { eye(); }
   void eye() { cout << "Red::eye\n";}  
};                                      
                                        
class Blu : public Color { public:      
   void count() { numBlu_++; }          
   void call() { sky(); }               
   void sky() { cout << "Blu::sky\n";}  
};                                      
                                        
int main_visitor_1( void )                       
{                                       
   Color* set[] = { new Red, new Blu,
      new Blu, new Red, new Red, 0 };   
   for (int i=0; set[i]; i++) {         
      set[i]->count();                  
      set[i]->call(); }                 
    Color::reportNum();                 
}                                       