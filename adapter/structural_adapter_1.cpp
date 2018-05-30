#include <iostream>
#include <stdio.h>
#include <time.h>
using std::cout;
using std::endl;

// Purpose.  Adapter
//
// Discussion.  The Adapter pattern discusses how to "wrap" the old interface of a legacy component, so that it can continue to contribute in a new system.  
// It is about "impedance matching" an old dog with new tricks (to mix metaphors).  

class ManlyTime {
  public:
        char* getTime() {
            static char buf[30];
            time_t  lt;
            tm*     ltStruct;
            time( &lt );
            ltStruct = localtime(&lt);
            strftime( buf, 30, "%H%M", ltStruct );
            return buf;
        }
    };

// On the right, private derivation is used to accomplish the same result.                                
class WimpyTime : private ManlyTime 
{   
    public:      
        char* getTime() 
        {         
            static char buf[30];
            char *ptr, mi[3], am[3];
            int  hr;
            ptr = ManlyTime::getTime();
            cout << "old interface time is " << ptr << endl;
            strcpy( mi, &(ptr[2]) );
            ptr[2] = '\0';
            sscanf( ptr, "%d", &hr );
            strcpy( am, "AM" );
            if (hr > 12) 
            {
                hr -= 12;
                strcpy( am, "PM" ); 
            }
            sprintf( buf, "%d:%s %s",hr, mi, am );
            return buf;
        }
    };

// On the left, WimpyTime "has_a" instance of the legacy component, and delegates the "heavy lifting" to it. 

class WimpyTime_2 {                             
    public:                                       
        char* getTime() 
        {                          
            static char buf[30];                      
            char *ptr, mi[3], am[3];                
            int  hr;                                
            ptr = imp_.getTime();                   
            cout << "old interface time is "        
                << ptr << endl;                      
            strcpy( mi, &(ptr[2]) );                   
            ptr[2] = '\0';                             
            sscanf( ptr, "%d", &hr );               
            strcpy( am, "AM" );                        
            if (hr > 12) {                          
                hr -= 12;                        
                strcpy( am, "PM" ); }          
            sprintf( buf, "%d:%s %s",
                hr, mi, am );                 
            return buf;                       
        }                                       
    private:                                   
        ManlyTime  imp_;                       
};          


// int main_adapter( void )     
int main_adapter_basic()
{
   WimpyTime  newT;                     
   char*      ptr;                      
   ptr = newT.getTime();
   cout << "new interface(private derivation) time is "<< ptr << endl;

   WimpyTime_2 newT2;
   char*      ptr2;                      
   ptr2= newT2.getTime();
   cout << "new interface('has_a' instance) time is "<< ptr << endl;


   return 0;
}

