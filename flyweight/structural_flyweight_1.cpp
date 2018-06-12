// Purpose.  Flyweight                  
//
// Discussion.  Trying to use objects at very low levels of granularity is nice, but the overhead may be prohibitive.  
// Flyweight suggests removing the non-shareable state from the class, and having the client supply it when methods are called. 
// This places more responsibility on the client, but, considerably fewer instances of the Flyweight class are now created.     
// Sharing of these instances is facilitated by introducing a Factory class that maintains a "cache" of existing Flyweights.                 

// In this example, the "X" state is considered shareable (within each row anyways), and the "Y" state has been externalized 
// (it is supplied by the client when report() is called).                             
                                        
#include "CommonInclude.h"            
                                        
const int X = 6;                        
const int Y = 10;                       
                                        
class Gazillion1 {                       
public:                                 
   Gazillion1() {                        
      val1_ = num_ / Y;                 
      val2_ = num_ % Y;                 
      num_++;                           
   }
   void report() {                      
      cout << val1_ << val2_ << ' ';    
   }
private:                                
   int    val1_;                        
   int    val2_;                        
   static int num_;                     
};                                      
                                        
int Gazillion1::num_ = 0;                
                                        
// int main_flyweight_1( void )   
int main_without_flyweight()                       
{     
   cout<<">>>>>>>> main_without_flyweight <<<<<<<<"<<endl;                                      
   Gazillion1  matrix[X][Y];
   for (int i=0; i < X; i++)            
   {                                    
      for (int j=0; j < Y; j++)         
         matrix[i][j].report();         
      cout << endl;                     
   }    
   return 0;                                
}                                       
                                        
// 00 01 02 03 04 05 06 07 08 09        
// 10 11 12 13 14 15 16 17 18 19        
// 20 21 22 23 24 25 26 27 28 29        
// 30 31 32 33 34 35 36 37 38 39        
// 40 41 42 43 44 45 46 47 48 49        
// 50 51 52 53 54 55 56 57 58 59



class Gazillion {
public:
   Gazillion( int in ) {
      val1_ = in;
      cout << "ctor: "<< val1_<<endl; }
   ~Gazillion() {
      cout << val1_ << ' '; }
   void report( int in ) {
      cout << val1_ << in << ' '; }
private:
   int  val1_;
};

class Factory {
public:
   static Gazillion* getFly(int in) {
      if ( ! pool_[in])
         pool_[in] =
                 new Gazillion( in );
      return pool_[in];
   }
   static void cleanUp() {
      cout << "dtors: ";
      for (int i=0; i < X; i++)
         if (pool_[i])
            delete pool_[i];
      cout << endl;
   }
private:
   static Gazillion*  pool_[X];
};

Gazillion*  Factory::pool_[]  = {
                         0,0,0,0,0,0 };

int main_flyweight_vince_1( void )
{
   for (int i=0; i < X; i++)
   {
      for (int j=0; j < Y; j++)
         Factory::getFly(i)->report(j);
      cout << endl;
   }
   Factory::cleanUp();
   return 0;
}

// ctor: 0
// 00 01 02 03 04 05 06 07 08 09
// ctor: 1
// 10 11 12 13 14 15 16 17 18 19
// ctor: 2
// 20 21 22 23 24 25 26 27 28 29
// ctor: 3
// 30 31 32 33 34 35 36 37 38 39
// ctor: 4
// 40 41 42 43 44 45 46 47 48 49
// ctor: 5
// 50 51 52 53 54 55 56 57 58 59
// dtors: 0 1 2 3 4 5


