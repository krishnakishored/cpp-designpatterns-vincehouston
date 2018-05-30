// Purpose.  Bridge                     
//
// Discussion.  Even though Date has a clean interface and a well encapsulated implementation, the client still has to recompile if the class architect changes his/her mind.      
// Instead, create a wrapper (or interface) class that contains and delegates to a body (or implementation) class. 
// Client can now specify at run-time exactly what s/he wants.    
                                        
#include <iostream>                   
#include <iomanip>
#include <stdio.h>
#include <string>

using std::endl;
using std::cout;
                                        
class Date {                                                                    
    public:
        Date( int y, int m, int d ):year_(y),month_(m),day_(d){}
        void output();                      
                                        
    private:                                                                                                 
        int  year_, month_, day_;                   
                                                             
};   

//  class DateOk : public DateImp {
//  public:
//     DateOk( int y, int m, int d );
//     void output();
//  private:
//     int  year_, month_, day_;
//  };

void Date::output() {                   
   char buf[20];                        
   int year = year_ - (year_/100*100);  
   sprintf( buf, "%02d%02d%02d",year, month_, day_ );             
   cout << buf << "  "; 
}                                         
                                        
int main_2( void )                       
{                                       
   Date  d1( 1996, 2, 29 );             
   Date  d2( 1996, 2, 30 );             
   d1.output();                         
   d2.output();                         
   cout << endl;    
   return 0;                    
}                                       

// 960229  960230                             



