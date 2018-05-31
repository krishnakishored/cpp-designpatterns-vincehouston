// Purpose.  Abstract Factory           
//
// Discussion.  Trying to maintain      
// portability across multiple "plat-   
// forms" routinely requires lots of    
// preprocessor "case" stmts.  The
// Factory pattern suggests defining    
// a creation services interface in a   
// Factory base class, and implement-   
// ing each "platform" in a separate    
// Factory derived class.               

#include <iostream>    
using std::cout;
using std::endl;
               
                                        
class Widget { public:                  
   virtual void draw() = 0;             
};                                      
class MotifBtn : public Widget {        
public:                                 
   void draw() { cout << "MotifBtn"     
      << endl; }
};                                      
                                        
class WindowsBtn : public Widget {      
public:                                 
   void draw() { cout << "WindowsBtn"   
      << endl; }
};                                      
                                        
void doThisWindow() {                   
   // create window, attach btn         
#ifdef MOTIF                            
   Widget* w = new MotifBtn;
#else // WINDOWS                        
   Widget* w = new WindowsBtn;
#endif                                  
   w->draw(); }                         
                                        
void doThatWindow() {                   
   // create window, attach btn
#ifdef MOTIF                            
   Widget* w = new MotifBtn;            
#else // WINDOWS                        
   Widget* w = new WindowsBtn;          
#endif
   w->draw(); }                         
                                        
int main( void )                       
{                                       
   // create window, attach btn         
#ifdef MOTIF                            
   Widget* w = new MotifBtn;            
#else // WINDOWS
   Widget* w = new WindowsBtn;          
#endif                                  
   w->draw();                           
   doThisWindow();                      
   doThatWindow();
   return 0;                      
}                                       
// WindowsBtn                           
// WindowsBtn                           
// WindowsBtn                           