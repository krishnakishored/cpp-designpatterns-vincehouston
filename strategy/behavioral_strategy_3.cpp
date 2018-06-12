// Purpose.  Strategy (template         
//                     approach)        
// A template can be used to configure a client with a Strategy.  
// This technique is appropriate if: 1) the Strategy can be selected at compile-time, and 
// 2) it does not have to be changed at run-time.  
// With a  template, there is no need to specify the interface in a SortImp base class.  
// The Stat class now has an instance of the sort object, instead of a ptr to the base class.    
// The inheritance approach offers more options and expressiveness.     
// The template approach offers mildly better efficiency.             


#include "CommonHeader.h"
                                        
class Stat {     /* Bubble sort */      
public:
   void readVector( int v[], int n ) {  
      sort_( v, n );                    
      min_ = v[0];   max_ = v[n-1];     
      med_ = v[n/2]; }                  
   int getMin() { return min_; }
   int getMax() { return max_; }        
   int getMed() { return med_; }        
private:                                
   int min_, max_, med_;                
   void sort_( int v[], int n ) {
      for (int i=n-1; i > 0; i--)       
         for (int j=0; j < i; j++)
            if (v[j] > v[j+1]) {        
               int t = v[j];            
               v[j] = v[j+1];           
               v[j+1] = t; }            
      cout << "Bubble: ";               
      for (int k=0; k < n; k++)         
         cout << v[k] << ' ';           
      cout << endl;                     
   }                                    
};                                      
int main_strategy_3( void ) 
{ 
  cout<<">>>>>>>> main_strategy_3 <<<<<<<<"<<endl;                     
   const int NUM = 9;                   
   int       array[NUM];                
   time_t    t;                         
   srand((unsigned) time(&t));          
   cout << "Vector: ";                  
   for (int i=0; i < NUM; i++) {
      array[i] = rand() % 9 + 1;        
      cout << array[i] << ' '; }        
   cout << endl;                        
                                        
   Stat  obj;                           
   obj.readVector( array, NUM );        
   cout << "min is " << obj.getMin()    
      << ", max is " << obj.getMax()
      << ", median is " << obj.getMed() 
      << endl;                          
}                                       
                                        
// Vector: 6 9 9 8 6 5 7 9 2            
// Bubble: 2 5 6 6 7 8 9 9 9
// min is 2, max is 9, median is 7