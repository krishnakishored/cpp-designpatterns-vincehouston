// Purpose.  Strategy                   
//                                      
// Discussion.  The class Stat has a Bubble sort algorithm hard-wired in it.  It would be nice if the choice of algorithm were configurable.
// The Strategy pattern suggests "define a family of algo's, encapsulate each one, and make them interchangeable" via an abstract base class.  
#include"CommonHeader.h"
       
                                        
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
                                        
// int main_strategy_1( void )                       
int main()
{                                     
  cout<<">>>>>>>> main_strategy_1 <<<<<<<<"<<endl;   
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

  return 0;                         
}                                       
                                        
/***** current implementation *****/
// Vector: 6 9 9 8 6 5 7 9 2            
// Bubble: 2 5 6 6 7 8 9 9 9            
// min is 2, max is 9, median is 7      
/*** an upgraded implementation ***/    
// Vector: 4 8 6 4 6 7 4 7 2            
// Shell:  2 4 4 4 6 6 7 7 8            
// min is 2, max is 8, median is 6      
                                        