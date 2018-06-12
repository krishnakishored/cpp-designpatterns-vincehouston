// Purpose.  Builder                    
//                                      
// The monolithic design supports a     
// single representation.  The Builder  
// design allows a different rep per    
// Builder derived class, and the com-
// mon input and parsing have been de-  
// fined in the Director class.  The D  
// constructs, the B returns result.    
#include"CommonInclude.h"     
#include<deque>
using std::deque;

class Array {                           
public:                                 
   void addFront( char ch ) {           
      lst.push_front( ch ); }           
   void addBack( char ch ) {            
      lst.push_back( ch ); }            
   void traverse() {                    
      for (i=0; i < lst.size(); i++)
         cout << lst[i] << ' ';         
      cout << endl; }                   
private:                                
   deque<char> lst;   int i;            
};                                      
                                        
string in[] = { "fa", "bb", "fc",       
   "bd", "fe", "bf", "fg", "bh" };      
                                        
int main_builder_1( void ) 
{
   cout<<">>>>>>>> main_builder_1 <<<<<<<<"<<endl;                     
   Array  list;                         
   for (int i=0; i < 8; i++)
      if (in[i][0] == 'f')              
         list.addFront( in[i][1] );     
      else if (in[i][0] == 'b')
         list.addBack( in[i][1] );      
   list.traverse(); 
   
   return 0;
   }                   
                                        
// g e c a b d f h                      
                                        

       