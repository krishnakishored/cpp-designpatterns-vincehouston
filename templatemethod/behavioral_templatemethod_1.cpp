// Purpose.  Template Method            
                                        
            
#include"CommonHeader.h"                    
#include <time.h>     


                         
                                        
class SortUp {  ///// Shell sort /////  
public:                                 
   void doIt( int v[], int n ) {        
      for (int g = n/2; g > 0; g /= 2)  
         for (int i = g; i < n; i++)    
            for (int j = i-g; j >= 0;
                              j -= g)   
               if (v[j] > v[j+g])       
                  doSwap(v[j],v[j+g]);  
   }                                    
private:                                
   void doSwap(int& a,int& b) {         
      int t = a; a = b; b = t; }        
};                                      
                                        
class SortDown {                        
public:                                 
   void doIt( int v[], int n ) {        
      for (int g = n/2; g > 0; g /= 2)  
         for (int i = g; i < n; i++)    
            for (int j = i-g; j >= 0;   
                              j -= g)   
               if (v[j] < v[j+g])       
                  doSwap(v[j],v[j+g]);
   }                                    
private:                                
   void doSwap(int& a,int& b) {         
      int t = a; a = b; b = t; }        
};                                      
                                        
int main_templatemethod_1( void )                       
{                                  
   cout<<">>>>>>>> main_templatemethod_1 <<<<<<<<"<<endl;      
   const int NUM = 10;
   int       array[NUM];                
   time_t    t;                         
   srand((unsigned) time(&t));          
   for (int i=0; i < NUM; i++) {        
      array[i] = rand() % 10 + 1;       
      cout << array[i] << ' '; }        
   cout << endl;                        
                                        
   SortUp  upObj;                       
   upObj.doIt( array, NUM );            
   for (int u=0; u < NUM; u++)
      cout << array[u] << ' ';          
   cout << endl;                        
                                        
   SortDown  downObj;                   
   downObj.doIt( array, NUM );          
   for (int d=0; d < NUM; d++)
      cout << array[d] << ' ';          
   cout << endl;   
   return 0;                     
}                                       
                                        
// 3 10 5 5 5 4 2 1 5 9                 
// 1 2 3 4 5 5 5 5 9 10                 
// 10 9 5 5 5 5 4 3 2 1
                                        
                                        
                                        