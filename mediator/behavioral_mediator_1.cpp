// Discussion.  On the left: Node objs interact directly with each other,recursion is required, removing a    
// Node is hard, and it is not possible to remove the first node. 

// On the right: a "mediating" List class focuses and simplifies all the administrative responsibilities,
// and the recursion (which does not scale up well) has been eliminated.
                                        
#include "CommonInclude.h"     
                                        
class Node {                            
public:                                 
   Node( int v, Node* n ) 
   {             
      val_ = v;                         
      next_ = n;                        
   }                                    
   void traverse() 
   {                    
      cout << val_ << "  ";             
      if (next_)                        
         next_->traverse();             
      else                              
         cout << endl;                  
   }                                    
   void removeNode( int v ) 
   {           
      Node*  ptr = (Node*) 1;           
      removeNode_( v, &ptr );           
   }                                    
private:                                
   int    val_;                         
   Node*  next_;                        
   void removeNode_(int v, Node** n) {  
      if (val_ == v)                    
         *n = next_;                    
      else                              
      {                                 
         next_->removeNode_( v, n );    
         if (*n != (Node*) 1)           
         {                              
            next_ = *n;
            *n = (Node*) 1;             
         }                              
      }                                 
   }                                    
};                                      
                                        
int main_mediator_1A( void )                       
{    
  cout<<">>>>>>>> main_mediator_1A <<<<<<<<"<<endl;                                       
   Node  fou( 44, 0 );                  
   Node  thr( 33, &fou );               
   Node  two( 22, &thr );               
   Node  one( 11, &two );               
   one.traverse();                      
   one.removeNode( 44 );                
   one.traverse();                      
   one.removeNode( 22 );
   one.traverse();
   return 0;                      
}                                       
                                        
// 11  22  33  44
// 11  22  33
// 11  33

/********************* ********************* ********************* ********************* *********************/

// Purpose.  Mediator

class Node2 
{
public:
   Node2( int v ) { val_ = v; }
   int getVal()  { return val_; }
private:
   int  val_;
};

class List 
{
public:
   List() 
   {
      for (int i=0; i < 10; i++)
         arr_[i] = 0;
         num_ = 0;
   }
   void addNode( Node2* n ) 
   {
      arr_[num_++] = n;
   }
   void traverse() 
   {
      for (int i=0; i < num_; i++)
         cout << arr_[i]->getVal()
            << "  ";
      cout << endl;
   }
   void removeNode( int v ) 
   {
      int  i, j;
      for (i=0; i < num_; i++)
         if (arr_[i]->getVal() == v)
         {
            for (j=i; j < num_; j++)
               arr_[j] = arr_[j+1];
            num_--;
            break;
         }
   }
private:
   Node2*  arr_[10];
   int    num_;
};

int main_mediator_1B( void )
{
   main_mediator_1A();
   cout<<">>>>>>>> main_mediator_1B <<<<<<<<"<<endl;                                       
   List  lst;
   Node2  one( 11 ),  two( 22 );
   Node2  thr( 33 ),  fou( 44 );
   lst.addNode( &one );
   lst.addNode( &two );
   lst.addNode( &thr );
   lst.addNode( &fou );
   lst.traverse();
   lst.removeNode( 44 );
   lst.traverse();
   lst.removeNode( 11 );
   lst.traverse();
   return 0;
}

// 11  22  33  44
// 11  22  33
// 22  33                                        