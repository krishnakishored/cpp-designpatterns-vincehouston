// Purpose.  Factory Method             
//           creation via inheritance   
//
// Discussion.  The architect has done an admirable job of decoupling the  client from Stooge concrete derived  
// classes, and, exercising polymorphism.  But there remains coupling where instances are actually created.   
// If we design an "extra level of indirection" (a "factory method") and have clients use it (instead of "new"), then the last    
// bit of coupling goes away.  The "factory method" (aka "virtual constructor") can be defined in the  
// Stooge base class, or, in a separate "factory" class.  Note that main() is no longer dependent on Stooge derived classes.           
                                        
#include "CommonInclude.h"                  
                                        
class Stooge { public:                  
   virtual void slapStick() = 0;        
};                                      
                                        
class Larry : public Stooge { public:   
   void slapStick() {
      cout << "Larry: poke eyes"        
         << endl; }                     
};                                      
class Moe : public Stooge { public:     
   void slapStick() {                   
      cout << "Moe: slap head"          
         << endl; }                     
};                                      
class Curly : public Stooge { public:   
   void slapStick() {                   
      cout << "Curly: suffer abuse"     
         << endl; }                     
};                                      
                                        
int main_factorymethod_1( void ) 
{
      cout<<">>>>>>>> main_factorymethod_1 <<<<<<<<"<<endl;                      
   Stooge*  roles[10];
   int      in, j, i = 0;               
                                        
   cout << "L(1) M(2) C(3) Go(0): ";    
   cin >> in;                           
   while (in) {                         
      if (in == 1)                      
         roles[i++] = new Larry;        
      else if (in == 2)                 
         roles[i++] = new Moe;
      else                              
         roles[i++] = new Curly;        
      cout << "L(1) M(2) C(3) Go(0): "; 
      cin >> in;                        
   }                                    
   for (j=0; j < i; j++)                
      roles[j]->slapStick();            
   for (j=0; j < i; j++)                
      delete roles[j];                  
}
