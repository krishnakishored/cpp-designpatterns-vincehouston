// Purpose.  Chain of Responsibility.  
//
// Discussion.  Instead of the client having to know about the number of  "handlers", and manually map requests to available handlers;
// design the handlers into an "intelligent" chain.  Clients "launch and leave" requests with the head of the chain.                       
                                       
#include <iostream> 

using std::cout;
using std::cin;
using std::endl;               
                                       
class H1 {                              
public:                                
   H1() {                               
      id_ = count_++;                  
      busy_ = 0;                       
   }                                   
   ~H1() {                              
      cout << id_ << " dtor" << endl;  
   }                                   
   int handle() {                      
      if (busy_ = !busy_) {   
         cout << id_ << " handles" << endl;                   
         return 1;                     
      } else {                         
         cout << id_ << " is busy" << endl;                   
         return 0;                     
   }  }                                
private:                               
   int        id_, busy_;              
   static int count_;                  
};
int H1::count_ = 1;                     

int main( void ) 
{                  
   const int TOTAL = 2;              
   H1* list[TOTAL] = { new H1, new H1};
                                     
   for (int i=0; i < 6; i++)
      for (int j=0; 1 ;              
               j = (j + 1) % TOTAL)  
         if (list[j]->handle())
            break;                   
                                     
   for (int k=0; k < TOTAL; k++)
      delete list[k]; 

   return 0;                
}                                    
// 1 handles                         
// 1 is busy                         
// 2 handles                         
// 1 handles                         
// 1 is busy                         
// 2 is busy                         
// 1 handles                         
// 1 is busy                         
// 2 handles                         
// 1 handles                         
// 1 dtor                            
// 2 dtor                            


 class H {
 public:
    H( H* next = 0 ) {
       id_   = count_++;
       busy_ = 0;
       next_ = next;
    }
    ~H() {
       cout << id_<<" dtor" << endl;
       // don't get into a loop
       if (next_->next_) {
          H* t = next_;
          next_ = 0;
          delete t;
    }  }
    void setNext( H* next ) {
       next_ = next;
    }
    void handle() {
       if (busy_ =  !busy_)
          cout << id_ << " handles" << endl;
       else {
          cout << id_ << " is busy" << endl;
          next_->handle();
    }  }
 private:
    int        id_, busy_;
    H*         next_;
    static int count_;
 };
 int H::count_ = 1;

 H* setUpList() {
                                           H* first = new H;
      H* last = new H(first);
      first->setNext( last );
      return first;
   }

int main_chainofresponsibility_2( void ) 
{
      H* head = setUpList();

      for (int i=0; i < 6; i++)
         head->handle();

      delete head;

      return 0;
}

   // 1 handles
   // 1 is busy
   // 2 handles
   // 1 handles
   // 1 is busy
   // 2 is busy
   // 1 handles
   // 1 is busy
   // 2 handles
   // 1 handles
   // 1 dtor
   // 2 dtor